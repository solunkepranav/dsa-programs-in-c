#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node* r;
    struct node* l;
    struct node* p;
} node;

void insert(node**); 

node* create() {
    node* n = malloc(sizeof(node));
    int d;
    printf("enter the root element");
    scanf("%d", &d);
    n->data = d;
    n->p = NULL;
    n->l = NULL;
    n->r = NULL;
    printf("the root is created \n do you want to input 1(yes) 0(no))");
    scanf("%d", &d);

    while (d) {
        insert(&n);
        printf("\n do you want to input more (1 yes 0 no))");
        scanf("%d", &d);
    }
    return n;
}

void insert(node** n) {
    int d;
    if (*n == NULL) {
        printf("Tree is not created yet \n ");
        *n = create();
        return;
    }
    node* temp = malloc(sizeof(node));

    printf("enter the element");
    scanf("%d", &d);
    temp->data = d;
    temp->p = NULL;
    temp->l = NULL;
    temp->r = NULL;
    node* cur = *n;
    while (1) {
        if ((temp->data < cur->data)) {
            if (cur->l) {
                cur = cur->l;
            } else {
                cur->l = temp;
                temp->p = cur;
                printf("%d is inserted ", temp->data);
                break;
            }
        } else if ((temp->data > cur->data)) {
            if (cur->r) {
                cur = cur->r;
            } else {
                cur->r = temp;
                temp->p = cur;
                printf("%d is inserted ", temp->data);
                break;
            }
        } else {
            printf("Duplicate values are not allowed");
            free(temp);
            break;
        }
    }
}

void display(node* R) {
    if (R == NULL) {
        printf("the tree is empty");
        return;
    }
    if (R->l) {
        display(R->l);
    }
    printf("%d \t", R->data);
    if (R->r) {
        display(R->r);
    }
}

node* search(node* root, int data) {
    node* current = root;
    while (current != NULL) {
        if (data == current->data) {
            printf("%d is found.\n", data);
            return current; 
        } 
        else if (data < current->data) {
            current = current->l;
        } 
        else {
            current = current->r;
        }
    }
    printf("%d was not found in the tree.\n", data);
    return NULL; 
}

node* findSuccessor(node *n) {
    if (n == NULL) return NULL;

    if (n->r != NULL) {
        node* current = n->r;
        while (current->l != NULL) {
            current = current->l;
        }
        return current;
    }

    node* p = n->p;
    while (p != NULL && n != p->l) {
        n = p;
        p = p->p;
    }
    return p;
}

void deleteNode(node* d, node** r) {
    if (d == NULL) {
        return;
    }

    if (d->l != NULL && d->r != NULL) {
        node* s = findSuccessor(d);
        int successor_data = s->data;
        deleteNode(s, r);
        d->data = successor_data;
        return;
    }

    node* parent = d->p;
    node* child = (d->l != NULL) ? d->l : d->r;

    if (parent == NULL) {
        *r = child;
    }
    else if (d == parent->l) {
        parent->l = child;
    } 
    else {
        parent->r = child;
    }

    if (child != NULL) {
        child->p = parent;
    }

    free(d);
}

int main() {
    int d;
    int data;
    node *r = NULL;
    node *s; 

    while (1) {
        printf("\n\n1.Create 2.Insert 3.Display 4.Search 5.delete  0.Exit\nEnter choice: ");
        scanf("%d", &d);

        switch (d) {
            case 1:
                r = create();
                break;
            case 2:
                insert(&r);
                break;
            case 3:
                display(r);
                break;
            
            case 4:
                if (r == NULL) {
                    printf("Tree is empty. Cannot search.\n");
                    break;
                }
                printf("Enter value to search for: ");
                scanf("%d", &data);
                search(r, data);
                break;

            case 0:
                return 0;
            
            case 5:
                if (r == NULL) {
                    printf("Tree is empty. Cannot delete.\n");
                    break;
                }
                printf("Enter the number to delete: ");
                scanf("%d", &data);

                s = search(r, data);

                if (s != NULL) {
                    deleteNode(s, &r);
                    printf("Node with value %d has been deleted.\n", data);
                }
                break;
            
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}