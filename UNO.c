#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constants ---
#define RED     0
#define YELLOW  1
#define GREEN   2
#define BLUE    3

#define ZERO    0
#define ONE     1
#define TWO     2
#define THREE   3
#define FOUR    4
#define FIVE    5
#define SIX     6
#define SEVEN   7
#define EIGHT   8
#define NINE    9
#define SKIP    10
#define REVERSE 11

// --- Structures ---

// Card
struct Card {
    int color;     // 0–3
    int type;      // 0–11
    struct Card *next;
    struct Card *prev;
};

// Player
struct Player {
    int id;
    int cardCount;
    struct Card *hand; // Head of DLL
    struct Player *next;
    struct Player *prev;
};

// Stack for discard pile
struct StackNode {
    struct Card card;
    struct StackNode *next;
};

// --- Global Variables ---
struct StackNode *discardPile = NULL;
int turnDirection = 1;

// --- Utility Functions ---

const char* getColorName(int c) {
    switch (c) {
        case RED: return "Red";
        case YELLOW: return "Yellow";
        case GREEN: return "Green";
        case BLUE: return "Blue";
    }
    return "";
}

const char* getTypeName(int t) {
    static char buffer[10];
    if (t >= ZERO && t <= NINE) {
        sprintf(buffer, "%d", t);
        return buffer;
    }
    switch (t) {
        case SKIP: return "Skip";
        case REVERSE: return "Reverse";
    }
    return "";
}

void printCard(struct Card c) {
    printf("%s %s", getColorName(c.color), getTypeName(c.type));
}

// --- Card Management ---

struct Card* createRandomCard() {
    struct Card* newCard = (struct Card*)malloc(sizeof(struct Card));
    newCard->color = rand() % 4;
    newCard->type = rand() % 12;
    newCard->next = NULL;
    newCard->prev = NULL;
    return newCard;
}

void addCardToHand(struct Player* player, struct Card* newCard) {
    if (player->hand == NULL) {
        player->hand = newCard;
    } else {
        struct Card* temp = player->hand;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newCard;
        newCard->prev = temp;
    }
    player->cardCount++;
}

void removeCardFromHand(struct Player* player, struct Card* cardToRemove) {
    if (player->hand == NULL || cardToRemove == NULL) return;
    if (player->hand == cardToRemove) player->hand = cardToRemove->next;
    if (cardToRemove->next != NULL) cardToRemove->next->prev = cardToRemove->prev;
    if (cardToRemove->prev != NULL) cardToRemove->prev->next = cardToRemove->next;
    player->cardCount--;
    free(cardToRemove);
}

void printHand(struct Player* player) {
    printf("Player %d's Hand (%d cards):\n", player->id, player->cardCount);
    struct Card* temp = player->hand;
    int i = 1;
    while (temp != NULL) {
        printf("  %d: ", i++);
        printCard(*temp);
        printf("\n");
        temp = temp->next;
    }
}

struct Card* getCardFromHand(struct Player* player, int n) {
    struct Card* temp = player->hand;
    int count = 1;
    while (temp != NULL) {
        if (count == n) return temp;
        temp = temp->next;
        count++;
    }
    return NULL;
}

// --- Discard Pile ---

void pushToDiscard(struct Card card) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->card = card;
    newNode->next = discardPile;
    discardPile = newNode;
}

struct Card* peekDiscard() {
    if (discardPile == NULL) return NULL;
    return &(discardPile->card);
}

// --- Player Management ---

struct Player* createPlayers(int numPlayers) {
    if (numPlayers <= 0) return NULL;
    struct Player* head = (struct Player*)malloc(sizeof(struct Player));
    head->id = 1; head->cardCount = 0; head->hand = NULL;
    struct Player* prevPlayer = head;
    for (int i = 2; i <= numPlayers; i++) {
        struct Player* newPlayer = (struct Player*)malloc(sizeof(struct Player));
        newPlayer->id = i; newPlayer->cardCount = 0; newPlayer->hand = NULL;
        prevPlayer->next = newPlayer; newPlayer->prev = prevPlayer;
        prevPlayer = newPlayer;
    }
    prevPlayer->next = head; head->prev = prevPlayer;
    return head;
}

// --- Game Logic ---

int canPlayCard(struct Card* cardToPlay, struct Card* topOfDiscard) {
    return (cardToPlay->color == topOfDiscard->color || cardToPlay->type == topOfDiscard->type);
}

int canPlayerMakeMove(struct Player* player, struct Card* topOfDiscard) {
    struct Card* temp = player->hand;
    while (temp != NULL) {
        if (canPlayCard(temp, topOfDiscard)) return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    // ❌ no time.h, no srand(time(NULL))
    srand(1);   // fixed seed (same sequence every run)

    int numPlayers;
    printf("--- Welcome to Simplified UNO! ---\n");
    printf("Enter number of players: ");
    scanf("%d", &numPlayers);

    if (numPlayers < 2) {
        printf("You need at least 2 players.\n");
        return 1;
    }

    struct Player* currentPlayer = createPlayers(numPlayers);
    struct Player* tempPlayer = currentPlayer;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < 3; j++) {
            addCardToHand(tempPlayer, createRandomCard());
        }
        tempPlayer = tempPlayer->next;
    }

    struct Card* firstCard;
    do {
        firstCard = createRandomCard();
    } while (firstCard->type > NINE);

    printf("\nInitial card on discard pile: ");
    printCard(*firstCard);
    printf("\n---------------------------------\n");
    pushToDiscard(*firstCard);
    free(firstCard);

    struct Player* winner = NULL;
    int isDraw = 0;
    int consecutiveStuckTurns = 0;

    while (winner == NULL && !isDraw) {
        printf("\nPlayer %d's turn.\n", currentPlayer->id);
        struct Card* topCard = peekDiscard();
        printf("Top of discard pile: ");
        printCard(*topCard);
        printf("\n");

        if (!canPlayerMakeMove(currentPlayer, topCard)) {
            printf("Player %d has no valid cards to play. Turn skipped.\n", currentPlayer->id);
            consecutiveStuckTurns++;
            if (consecutiveStuckTurns >= numPlayers) {
                isDraw = 1;
                continue;
            }
        } else {
            consecutiveStuckTurns = 0;
            printHand(currentPlayer);

            int choice = 0;
            struct Card* chosenCard = NULL;
            int isValidMove = 0;

            while (!isValidMove) {
                printf("Choose a card to play (enter number): ");
                scanf("%d", &choice);

                if (choice < 1 || choice > currentPlayer->cardCount) {
                    printf("Invalid choice. Try again.\n");
                    continue;
                }

                chosenCard = getCardFromHand(currentPlayer, choice);
                if (canPlayCard(chosenCard, topCard)) {
                    isValidMove = 1;
                } else {
                    printf("Invalid move. Must match color or type.\n");
                }
            }

            struct Card cardPlayed = *chosenCard;
            printf("Player %d played: ", currentPlayer->id);
            printCard(cardPlayed);
            printf("\n");

            removeCardFromHand(currentPlayer, chosenCard);
            pushToDiscard(cardPlayed);

            if (currentPlayer->cardCount == 0) {
                winner = currentPlayer;
                continue;
            }

            if (cardPlayed.type == SKIP) {
                printf("Player %d's turn is skipped!\n",
                    (turnDirection == 1) ? currentPlayer->next->id : currentPlayer->prev->id);
                currentPlayer = (turnDirection == 1) ? currentPlayer->next : currentPlayer->prev;
            } else if (cardPlayed.type == REVERSE) {
                printf("Turn direction has been reversed!\n");
                turnDirection *= -1;
            }
        }
        currentPlayer = (turnDirection == 1) ? currentPlayer->next : currentPlayer->prev;
        printf("---------------------------------\n");
    }

    printf("\n=================================\n");
    if (winner != NULL) {
        printf("Player %d has won the game!\n", winner->id);
    } else if (isDraw) {
        printf("All players are stuck! The game is a DRAW.\n");
    }
    printf("=================================\n");
    return 0;
}
