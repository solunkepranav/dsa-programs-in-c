#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100   // upper bound on cars

int TRACKS;       // number of side tracks (user input)
int n;            // number of cars (user input)

int track[20][MAX];   // support up to 20 tracks
int top[20];          // top index for each track
int output[MAX], outPos = 0;

// initialize tracks as empty
void initTracks() {
    for (int i = 0; i < TRACKS; i++) {
        top[i] = -1;
    }
}

// push car onto a track
void pushToTrack(int t, int car) {
    track[t][++top[t]] = car;
}

// pop car from a track
void popFromTrack(int t) {
    if (top[t] >= 0) {
        top[t]--;
    }
}

// check if required car is available on any track top
int moveIfAvailable(int need) {
    for (int i = 0; i < TRACKS; i++) {
        if (top[i] >= 0 && track[i][top[i]] == need) {
            output[outPos++] = need;
            printf("\nCar %d moved from track %d to output", need, i + 1);
            popFromTrack(i);
            return 1;
        }
    }
    return 0;
}

// put car into a suitable track
int putInTrack(int num) {
    int chosen = -1;
    int minTop = INT_MAX;

    // choose track where top > num, but as small as possible
    for (int i = 0; i < TRACKS; i++) {
        if (top[i] >= 0 && track[i][top[i]] > num && track[i][top[i]] < minTop) {
            minTop = track[i][top[i]];
            chosen = i;
        }
    }

    // if no such track, use empty one
    if (chosen == -1) {
        for (int i = 0; i < TRACKS; i++) {
            if (top[i] == -1) {
                chosen = i;
                break;
            }
        }
    }

    if (chosen != -1) {
        pushToTrack(chosen, num);
        printf("\nCar %d kept in track %d", num, chosen + 1);
        return 1;
    } else {
        printf("\nNo track available for Car %d!", num);
        return 0;
    }
}

int main() {
    int input[MAX];

    // take inputs
    printf("Enter number of side tracks: ");
    scanf("%d", &TRACKS);

    printf("Enter number of cars: ");
    scanf("%d", &n);

    printf("Enter the sequence of cars: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &input[i]);
    }

    int need = 1;
    outPos = 0;
    initTracks();

    // process each car
    for (int i = 0; i < n; i++) {
        if (input[i] == need) {  // goes directly to output
            output[outPos++] = need;
            printf("\nCar %d goes directly to output", need);
            need++;
            while (moveIfAvailable(need)) need++;
        } else {
            if (!putInTrack(input[i])) {
                printf("\nArrangement failed!\n");
                return 0;
            }
            while (moveIfAvailable(need)) need++;
        }
    }

    // flush remaining
    while (moveIfAvailable(need)) need++;

    // print result
    printf("\n\nFinal Output: ");
    for (int i = 0; i < outPos; i++) printf("%d ", output[i]);
    printf("\n");

    if (outPos == n)
        printf("All cars arranged successfully!\n");
    else
        printf("Not possible, %d cars stuck in tracks.\n", n - outPos);

    return 0;
}
