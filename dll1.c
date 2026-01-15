/*P1. Create a Menu driven program for Doubly linked List

1. Create - creates Linked list

2. Display ( take choice from user to print in left to right direction or reverse )

3. insert an lement in doubly linked list at first position

4. insert at Last position

5. insert at N th position

6. delete specified element

7. lenth of the list. */
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* next;
    struct node* prev;
};
struct node* head=NULL;
struct node* tail=NULL;
void create();
void display();
void append();
void insert();/*
delete(int val);
int length();
struct node* search(int val);*/
int main() {
    int choice;

    printf("### Doubly Linked List Operations ###\n");

    while (1) {
        printf("\n----------- MENU -----------\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Insert at First\n");
        printf("4. Insert at Last\n");
        printf("5. Insert at N-th Position\n");
        printf("6. Delete a specific element\n");
        printf("7. Get Length of the List\n");
        printf("8. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
                
            case 3:
                insert(5);
                break;
                
            case 4:
                append();
                break;
                
            case 5:
                insert();
                break;/*
            case 6:
                deleteElement();
                break;
            case 7:
                getLength();
                break;
            case 8:
                printf("Exiting the program. Goodbye!\n");
                exit(0);*/
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

