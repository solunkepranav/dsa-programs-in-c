#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
struct Node {
    int data;
    struct Node *next;
};

// Global head and tail pointers for efficient appends
struct Node *head = NULL;
struct Node *tail = NULL;

// --- Function Prototypes ---

// Iterative functions
void create();
void append();
void display();
void insert();
void del();
void search();
void reverse();
void sort();

// Recursive functions
struct Node* rcreate();
void rappend(struct Node* curr, struct Node* nn);
void rdisplay(struct Node *p);
struct Node* rinsert(struct Node *curr, int val, int pos);
struct Node* rdel(struct Node *curr, int pos);
int rsearch(struct Node *curr, int key, int pos);
struct Node* rrev(struct Node *curr);
void rsort(int n);
int count_nodes();

// Cycle detection function
void detectCycle();
void createTestCycleList();


int main() {
    int ch, val, pos, key, n, res;
    struct Node *nn = NULL;

    while (1) {
        printf("\n\n--- EFFICIENT SINGLY LINKED LIST MENU ---\n");
        printf(" 1. Create (Iterative)      2. Create (Recursive)\n");
        printf(" 3. Append (Iterative)      4. Append (Recursive)\n");
        printf(" 5. Display (Iterative)     6. Display (Recursive)\n");
        printf(" 7. Insert (Iterative)      8. Insert (Recursive)\n");
        printf(" 9. Delete (Iterative)     10. Delete (Recursive)\n");
        printf("11. Search (Iterative)     12. Search (Recursive)\n");
        printf("13. Reverse (Iterative)    14. Reverse (Recursive)\n");
        printf("15. Sort (Iterative)       16. Sort (Recursive)\n");
        printf("17. Detect Cycle in List\n");
        printf(" 0. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: create(); break;
            case 2:
                head = tail = NULL;
                head = rcreate();
                printf("List creation complete.\n");
                break;
            case 3: append(); break;
            case 4:
                nn = (struct Node*)malloc(sizeof(struct Node));
                printf("Enter data: ");
                scanf("%d", &nn->data);
                nn->next = NULL;
                if(!head) { head = tail = nn; }
                else { rappend(head, nn); }
                printf("Node appended.\n");
                break;
            case 5: display(); break;
            case 6:
                if (!head) { printf("Empty list.\n"); }
                else { printf("HEAD -> "); rdisplay(head); }
                break;
            case 7: insert(); break;
            case 8:
                printf("Enter pos & val: ");
                scanf("%d %d", &pos, &val);
                if (pos < 1) { printf("Invalid pos.\n"); }
                else { head = rinsert(head, val, pos); }
                break;
            case 9: del(); break;
            case 10:
                if (!head) { printf("Empty list.\n"); break; }
                printf("Enter pos to delete: ");
                scanf("%d", &pos);
                if (pos < 1) { printf("Invalid pos.\n"); }
                else { head = rdel(head, pos); }
                break;
            case 11: search(); break;
            case 12:
                if (!head) { printf("Empty list.\n"); break; }
                printf("Enter key to search: ");
                scanf("%d", &key);
                res = rsearch(head, key, 1);
                if (res != -1) printf("Key %d found at pos %d.\n", key, res);
                else printf("Key %d not found.\n", key);
                break;
            case 13: reverse(); break;
            case 14:
                if (!head) { printf("Empty list.\n"); break; }
                tail = head;
                head = rrev(head);
                printf("List reversed.\n");
                break;
            case 15: sort(); break;
            case 16:
                if (!head) { printf("Empty list.\n"); break; }
                n = count_nodes();
                rsort(n);
                printf("List sorted.\n");
                break;
            case 17:
                createTestCycleList(); // Create the predefined list with a cycle
                detectCycle();
                head = tail = NULL; // Clear list after test
                break;
            case 0: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}

// Iteratively creates a list by repeatedly calling append
void create() {
    head = tail = NULL;
    int ch = 1;
    do {
        append();
        printf("Add another node? (1=Yes/0=No): ");
        scanf("%d", &ch);
    } while (ch == 1);
    printf("List creation complete.\n");
}

// Appends a new node to the end of the list
void append() {
    struct Node *nn;
    nn = (struct Node *)malloc(sizeof(struct Node));
    printf("Enter data: ");
    scanf("%d", &nn->data);
    nn->next = NULL;
    if (head == NULL) { // If list is empty
        head = tail = nn;
    } else { // Append to the end and update tail
        tail->next = nn;
        tail = nn;
    }
}

// Displays the list from head to tail
void display() {
    if (!head) { printf("Empty list.\n"); return; }
    struct Node *tmp = head;
    printf("HEAD -> ");
    while (tmp) {
        printf("%d -> ", tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

// Inserts a node at a specified position
void insert() {
    int pos, val, i;
    struct Node *nn, *tmp = head;
    printf("Enter pos & val: "); scanf("%d %d", &pos, &val);
    if (pos < 1) { printf("Invalid pos.\n"); return; }
    nn = (struct Node *)malloc(sizeof(struct Node));
    nn->data = val;
    if (pos == 1) {
        nn->next = head;
        head = nn;
        if (tail == NULL) { tail = head; } // if list was empty
    } else {
        for (i = 1; i < pos - 1 && tmp; i++) tmp = tmp->next;
        if (!tmp) { printf("Pos out of bounds.\n"); free(nn); return; }
        nn->next = tmp->next;
        tmp->next = nn;
        if (nn->next == NULL) { tail = nn; } // update tail if inserted at end
    }
    printf("Node inserted.\n");
}

// Deletes a node from a specified position
void del() {
    if (!head) { printf("Empty list.\n"); return; }
    int pos, i;
    struct Node *tmp = head, *prev = NULL;
    printf("Enter pos to delete: "); scanf("%d", &pos);
    if (pos < 1) { printf("Invalid pos.\n"); return; }
    if (pos == 1) {
        head = tmp->next;
        if (head == NULL) { tail = NULL; } // if list becomes empty
        free(tmp);
        printf("Node deleted.\n");
        return;
    }
    for (i = 1; i < pos && tmp; i++) { prev = tmp; tmp = tmp->next; }
    if (!tmp) { printf("Pos out of bounds.\n"); return; }
    prev->next = tmp->next;
    if (prev->next == NULL) { tail = prev; } // update tail if last node deleted
    free(tmp);
    printf("Node deleted.\n");
}

// Iteratively searches for a key in the list
void search() {
    if (!head) { printf("Empty list.\n"); return; }
    int key, pos = 1;
    struct Node *tmp = head;
    printf("Enter key to search: "); scanf("%d", &key);
    while (tmp) {
        if (tmp->data == key) {
            printf("Key %d found at pos %d.\n", key, pos);
            return;
        }
        tmp = tmp->next;
        pos++;
    }
    printf("Key %d not found.\n", key);
}

// Iteratively reverses the list by changing links
void reverse() {
    if (!head) { printf("Empty list.\n"); return; }
    struct Node *prev = NULL, *curr = head, *nxt = NULL;
    tail = head; // Old head becomes the new tail
    while (curr) {
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    head = prev; // Old last node becomes the new head
    printf("List reversed.\n");
}

// Sorts the list using bubble sort (by swapping data)
void sort() {
    if (!head) { printf("Empty list.\n"); return; }
    struct Node *curr, *idx;
    int tmp_d;
    for (curr = head; curr->next; curr = curr->next) {
        for (idx = curr->next; idx; idx = idx->next) {
            if (curr->data > idx->data) {
                tmp_d = curr->data;
                curr->data = idx->data;
                idx->data = tmp_d;
            }
        }
    }
    printf("List sorted.\n");
}

// Recursively creates a linked list
struct Node* rcreate() {
    struct Node* nn;
    int choice;
    printf("Add a node? (1=Yes/0=No): ");
    scanf("%d", &choice);

    if (choice == 0) return NULL;

    nn = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter data: ");
    scanf("%d", &nn->data);
    nn->next = rcreate();

    if (nn->next == NULL) { // Last node created becomes the tail
        tail = nn;
    }
    return nn;
}

// Recursively appends a node
void rappend(struct Node* curr, struct Node* nn) {
    if(curr->next == NULL) {
        curr->next = nn;
        tail = nn; // Update tail
        return;
    }
    rappend(curr->next, nn);
}

// Recursively displays the list
void rdisplay(struct Node *p) {
    if (!p) { printf("NULL\n"); return; }
    printf("%d -> ", p->data);
    rdisplay(p->next);
}

// Recursively inserts a node
struct Node* rinsert(struct Node *curr, int val, int pos) {
    if (pos == 1) {
        struct Node *nn = (struct Node*)malloc(sizeof(struct Node));
        nn->data = val;
        nn->next = curr;
        if (head == tail) { tail = curr; } // update tail if list had 1 node
        printf("Node inserted.\n");
        return nn;
    }
    if (!curr) { printf("Pos out of bounds.\n"); return NULL; }
    curr->next = rinsert(curr->next, val, pos - 1);
    // update tail if inserted at the end
    if(curr->next != NULL && curr->next->next == NULL) {
        tail = curr->next;
    }
    return curr;
}

// Recursively deletes a node
struct Node* rdel(struct Node *curr, int pos) {
    if (!curr) { printf("Pos out of bounds.\n"); return NULL; }
    if (pos == 1) {
        struct Node *tmp = curr->next;
        if(head == tail) { head = tail = NULL; }
        free(curr);
        printf("Node deleted.\n");
        return tmp;
    }
    curr->next = rdel(curr->next, pos - 1);
    if (curr->next == NULL) { tail = curr; } // update tail if last node deleted
    return curr;
}

// Recursively searches for a key
int rsearch(struct Node *curr, int key, int pos) {
    if (!curr) return -1;
    if (curr->data == key) return pos;
    return rsearch(curr->next, key, pos + 1);
}

// Recursively reverses the list
struct Node* rrev(struct Node *curr) {
    if (!curr || !curr->next) return curr;
    struct Node *rest = rrev(curr->next);
    curr->next->next = curr;
    curr->next = NULL;
    return rest;
}

// Helper function for recursive sort
void rsort(int n) {
    if (n <= 1) return;
    struct Node *curr = head;
    struct Node *nxt = head->next;
    int i, tmp_d;
    // One pass of bubble sort
    for(i=0; i < n - 1; i++) {
        if (curr->data > nxt->data) {
            tmp_d = curr->data;
            curr->data = nxt->data;
            nxt->data = tmp_d;
        }
        curr = curr->next;
        nxt = nxt->next;
    }
    // Recur for remaining n-1 elements
    rsort(n - 1);
}

// Counts the number of nodes in the list
int count_nodes() {
    int count = 0;
    struct Node *tmp = head;
    while(tmp) {
        count++;
        tmp = tmp->next;
    }
    return count;
}


// Creates a hardcoded list: 1->2->3->4->5->3
void createTestCycleList() {
    head = tail = NULL;
    // Create nodes
    struct Node *n1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n3 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n4 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n5 = (struct Node*)malloc(sizeof(struct Node));

    // Assign data
    n1->data = 1; n2->data = 2; n3->data = 3; n4->data = 4; n5->data = 5;

    // Link nodes
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n3; // This creates the cycle

    head = n1; // Set the head of the list
    printf("Created a test list: 1->2->3->4->5->3 (cycles back to 3).\n");
}

// Detects cycle using Floyd's Tortoise and Hare algorithm
void detectCycle() {
    struct Node *slow_p = head, *fast_p = head;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        // If pointers meet, there is a cycle
        if (slow_p == fast_p) {
            printf("Result: Cycle detected in the linked list.\n");
            return;
        }
    }
    // If loop finishes, no cycle was found
    printf("Result: No cycle detected in the linked list.\n");
}