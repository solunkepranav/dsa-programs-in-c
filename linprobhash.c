#include <stdio.h>
#include <stdlib.h>

int m;
#define del -1
#define occ 1
#define emp 0

// Hash function
int hash(int key) {
if(key>0){
    return key % m;
   
}
else{
return (key % m)+m;
}}

int find(int key, int arr[][2]) {
    int indx = hash(key);
    int start = indx;
    do {
        if (arr[indx][0] == emp) {
            return -1; // Empty position
        }
        if (arr[indx][0] == occ && arr[indx][1] == key) {
            return indx;
        }
        indx = (indx + 1) % m;
    } while (indx != start);
    return -1;
}

void insert(int key, int arr[][2]) {
    int indx = hash(key);
    int start = indx;
   
    do {
        if (arr[indx][0] != occ) {
            if (arr[indx][0] == del && arr[indx][1] == key) {
                arr[indx][0] = occ; // Reuse
                return;
            }
            arr[indx][1] = key;
            arr[indx][0] = occ;
            printf("The key %d is inserted at index %d successfully.\n", key, indx);
            return;
        }
        indx = (indx + 1) % m;
    } while (indx != start);
    printf("Hash table is full! Cannot insert.\n");
}

// Delete
void delete(int key, int arr[][2]) {
    int indx = find(key, arr);
    if (indx == -1) {
        printf("Key not found, cannot delete.\n");
        return;
    }
    arr[indx][0] = del;
    printf("The element %d at index %d is deleted.\n", arr[indx][1], indx);
}


void display(int arr[][2]) {
    printf("\nIndex\tStatus\tElement\n");
    for (int i = 0; i < m; i++) {
    char c;
   
  if(arr[i][0]==-1)c='D';
  if(arr[i][0]==0)c='E';
  if(arr[i][0]==1)c='O';
 
   
        printf("%d\t%c\t%d\n", i, c, arr[i][1]);
    }
}

int main() {
    printf("Enter the size of the hash table (prime number): ");
    scanf("%d", &m);

   
    int arr[m][2];
    for (int i = 0; i < m; i++) {

        arr[i][0] = emp;
        arr[i][1] = 0;  
    }

    int opt;
    while (1) {
        printf("\nEnter the option for operations:\n");
        printf("1. Insert\n2. Find\n3. Delete\n4. Display\n0. Exit\n");
        scanf("%d", &opt);

        switch (opt) {
            case 1: {
                int inp;
                printf("Enter the number to insert: ");
                scanf("%d", &inp);
                insert(inp, arr);
                break;
            }
            case 2: {
                int inp;
                printf("Enter the number to find: ");
                scanf("%d", &inp);
                int idx = find(inp, arr);
                if (idx == -1) {
                    printf("The number is not found.\n");
                } else {
                    printf("The number %d is found at index %d.\n", inp, idx);
                }
                break;
            }
            case 3: {
                int inp;
                printf("Enter the number to delete: ");
                scanf("%d", &inp);
                delete(inp, arr);
                break;
            }
            case 4:
                display(arr);
                break;

             case 0:
                printf("Exiting the program.\n");
                return 0; // Just exit. 
          
        }
    }

    return 0;
}
