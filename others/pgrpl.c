#include <stdio.h>
#include <stdbool.h>
#define MAX 50

// Function to check if a page is already present in frames [cite: 56]
int isPresent(int frames[], int n, int page) {
    for (int i=0; i<n; i++)
        if(frames[i]==page)
            return 1;
    return 0;
}

// Function to find index of least recently used page [cite: 69]
int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i)
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    return pos;
}

// FIFO Page Replacement [cite: 78]
void FIFO(int pages[], int n, int framesCount) {
    int frames[MAX], front = 0, pageFaults = 0, hits = 0;
    for (int i=0; i < framesCount; i++)
        frames[i] = -1;
    for (int i=0; i < n; i++) {
        if (!isPresent(frames, framesCount, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % framesCount;
            pageFaults++;
        } else {
            hits++;
        }
    }
    printf("\nFIFO Algorithm:\n");
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Hits: %d\n", hits);
    printf("Hit Ratio: %.2f%%\n", (hits * 100.0) / n);
}

// LRU Page Replacement [cite: 101]
void LRU(int pages[], int n, int framesCount) {
    int frames[MAX], time[MAX], counter = 0, pageFaults = 0, hits = 0;
    for (int i=0; i < framesCount; ++i)
        frames[i] = -1;
    
    // Remove consecutive duplicates handling logic included in source [cite: 107-112]
    int uniquePages[MAX], uniqueCount = 0;
    for (int i=0; i<n; i++) {
        if (i==0 || pages[i] != pages[i - 1]) {
            uniquePages[uniqueCount++] = pages[i];
        }
    }

    for (int i=0; i < uniqueCount; ++i) {
        if (isPresent(frames, framesCount, uniquePages[i])) {
             hits++;
             for (int j=0; j < framesCount; ++j)
                if (frames[j] == uniquePages[i])
                    time[j] = ++counter;
        } else {
            pageFaults++;
            int empty = -1;
            for (int j=0; j < framesCount; ++j)
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            if (empty != -1) {
                frames[empty] = uniquePages[i];
                time[empty] = ++counter;
            } else {
                int pos = findLRU(time, framesCount);
                frames[pos] = uniquePages[i];
                time[pos] = ++counter;
            }
        }
    }
    printf("\nLRU Algorithm (with repetitive handling):\n");
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Hits: %d\n", hits);
    printf("Hit Ratio: %.2f%%\n", (hits * 100.0) / uniqueCount);
}

// Optimal Page Replacement [cite: 150]
void Optimal(int pages[], int n, int framesCount) {
    int frames[MAX], pageFaults = 0, hits = 0;
    for (int i=0; i < framesCount; i++)
        frames[i] = -1;
    for (int i=0; i < n; i++) {
        if (isPresent(frames, framesCount, pages[i])) {
            hits++;
            continue;
        }
        int pos = -1, farthest = i;
        for (int j=0; j < framesCount; j++) {
            if (frames[j] == -1) {
                pos = j;
                break;
            }
            int k;
            for (k = i + 1; k < n; k++) {
                if (frames[j] == pages[k])
                    break;
            }
            if (k == n) {
                pos = j;
                break; 
            }
            if (k > farthest) {
                farthest = k;
                pos = j;
            }
        }
        frames[pos] = pages[i];
        pageFaults++;
    }
    printf("\nOptimal Algorithm:\n");
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Hits: %d\n", hits);
    printf("Hit Ratio: %.2f%%\n", (hits * 100.0) / n);
}

int main() {
    int n, framesCount, pages[MAX];
    printf("Enter the number of pages in reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i=0; i<n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &framesCount);
    FIFO(pages, n, framesCount);
    LRU(pages, n, framesCount);
    Optimal(pages, n, framesCount);
    return 0;
}