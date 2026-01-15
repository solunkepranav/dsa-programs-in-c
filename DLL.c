#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

// Function Prototypes
void createList();
void displayList();
void insertAtFirst();
void insertAtLast();
void insertAtNth();
void deleteElement();
int  getLength();


// Main function with menu
int main() {
    int choice;

    while (1) {
        printf("\n\n========== MENU ==========\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Insert at First\n");
        printf("4. Insert at Last\n");
        printf("5. Insert at Nth Position\n");
        printf("6. Delete Specified Element\n");
        printf("7. Get Length of List\n");
        printf("8. Exit\n");
        printf("========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createList(); break;
            case 2: displayList(); break;
            case 3: insertAtFirst(); break;
            case 4: insertAtLast(); break;
            case 5: insertAtNth(); break;
            case 6: deleteElement(); break;
            case 7: printf("\nLength of the list is: %d\n", getLength()); break;
            case 8: printf("Exiting program.\n"); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// 1. Creates the linked list
void createList() {
    int n, data, i;
    struct Node *newNode, *temp;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of nodes must be positive.\n");
        return;
    }

    head = NULL; // Overwrite existing list

    printf("Enter data for node 1: ");
    scanf("%d", &data);
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    head = newNode;
    temp = head;

    for (i = 2; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);
        newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->prev = temp;
        newNode->next = NULL;
        temp->next = newNode;
        temp = newNode;
    }
    printf("List created successfully.\n");
}

// 2. Displays the list
void displayList() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    int choice;
    struct Node *temp;
    printf("Display Direction:\n  1. Left to Right\n  2. Right to Left\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nList (L->R): NULL <-> ");
        temp = head;
        while (temp != NULL) {
            printf("%d <-> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    } else if (choice == 2) {
        printf("\nList (R->L): NULL <-> ");
        temp = head;
        while (temp->next != NULL) { // Go to the last node
            temp = temp->next;
        }
        while (temp != NULL) { // Traverse backwards
            printf("%d <-> ", temp->data);
            temp = temp->prev;
        }
        printf("NULL\n");
    } else {
        printf("Invalid choice.\n");
    }
}

// 3. Inserts at the first position
void insertAtFirst() {
    int data;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    
    printf("Enter data for the new node: ");
    scanf("%d", &data);
    
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
    printf("Node inserted at the beginning.\n");
}

// 4. Inserts at the last position
void insertAtLast() {
    int data;
    struct Node *newNode, *temp;
    
    printf("Enter data for the new node: ");
    scanf("%d", &data);

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("Node inserted at the end.\n");
}

// 5. Inserts at the Nth position
void insertAtNth() {
    int data, pos, i, len;
    struct Node *newNode, *temp;

    printf("Enter position to insert at: ");
    scanf("%d", &pos);

    len = getLength();
    if (pos < 1 || pos > len + 1) {
        printf("Invalid position. Please enter a position between 1 and %d.\n", len + 1);
        return;
    }
    
    if (pos == 1) {
        insertAtFirst();
        return;
    }

    printf("Enter data for the new node: ");
    scanf("%d", &data);

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;

    temp = head;
    for (i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    
    newNode->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    newNode->prev = temp;
    temp->next = newNode;
    
    printf("Node inserted at position %d.\n", pos);
}


// 6. Deletes a specified element
void deleteElement() {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    int val;
    struct Node *temp = head;
    printf("Enter data of the node to delete: ");
    scanf("%d", &val);

    // Find the node
    while (temp != NULL && temp->data != val) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element %d not found in the list.\n", val);
        return;
    }

    if (temp->prev != NULL) { // If it's not the head node
        temp->prev->next = temp->next;
    } else { // It is the head node
        head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Node with data %d deleted.\n", val);
}

// 7. Gets the length of the list
int getLength() {
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}