#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define wht 0
#define gr 1
#define blk 2

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct vertex {
    int clr;
    int dist;
    struct vertex *par;
    node *head;
    int key;
} vertex;

// ---------------- Queue ----------------
bool isFull(int f, int r, int n) {
    return (r + 1) % n == f;
}

bool isEmpty(int f, int r) {
    return f == r;
}

void enq(int arr[], int *f, int *r, int n, int ele) {
    if (!isFull(*f, *r, n)) {
        *r = (*r + 1) % n;
        arr[*r] = ele;
        // printf("\nEnqueued: %d", ele);
    } else {
        // printf("\nQueue is FULL\n");
    }
}

int deq(int arr[], int *f, int *r, int n) {
    if (!isEmpty(*f, *r)) {
        *f = (*f + 1) % n;
        return arr[*f];
    } else {
        // printf("\nQueue is EMPTY\n");
        return -1;
    }
}

// ---------------- Graph ----------------
node *createnode() {
    int a;
    scanf("%d", &a);
    if (a == 0)
        return NULL;
    node *new = malloc(sizeof(node));
    new->data = a;
    new->next = NULL;
    return new;
}

vertex *createvertex(int v) {
    vertex *new = malloc(sizeof(vertex));
    new->clr = wht;
    new->dist = -1;
    new->par = NULL;
    new->head = NULL;
    new->key = v;
    return new;
}

vertex *search(vertex **ver, int n, int data) {
    for (int i = 0; i < n; i++) {
        if (ver[i]->key == data)
            return ver[i];
    }
    return NULL;
}


int main(){
    //creation adj list
    int a;
printf("enter the number of nodes : ");
int n;
scanf("%d",&n);
vertex* ver[n];
int c=n;
while(c){

printf("enter the node and its adj list(0 for NULL) : ");

scanf("%d",&a);
ver[n-c]=createvertex(a);
a=1;
node *head=NULL;
node *last=NULL;
while(a){
node *new=createnode();
if(new==NULL)break;
if(head==NULL)head=new;
else{
last->next=new;
}

last=new;
}
ver[n-c]->head=head;
c--;
}//printing adj list
c=n;
printf("the adj list (vertex,list)");
while(c){

printf("\n | %d |",ver[n-c]->key);
node* temp=ver[n-c]->head;
while(temp){
printf("->");
printf("%d",temp->data);
temp=temp->next;}
printf("->NULL");
c--;

}

    int arr[n];
    int f = 0, r = 0;

    int  ele;
printf("\n enter the source for bfs : ");
scanf("%d",&a);
vertex* s=search(ver,n,a);
s->clr=gr;
s->dist=0;
s->par=NULL;
vertex *u;
enq(arr,&f,&r,n,a);
printf("\n enter the target for bfs: ");
int t;
scanf("%d",&t);

 vertex *tar=search(ver,n,t);
 if(tar==NULL){printf("the target is not present in the graph");}
 else{
printf("\n  bfs traversal : ");
while(!isEmpty(f,r)){
  int a=deq(arr, &f, &r, n);
    printf(" %d ",a);
  if(a==t)break;

  u=search(ver,n,a);
  node* temp=u->head;
  while(temp){
   vertex *v=search(ver,n,temp->data);
   if(v->clr==wht){
    v->clr=gr;
    v->dist=u->dist+1;
    v->par=u;
    enq(arr,&f,&r,n,temp->data);
      
   }
     temp=temp->next;}
   u->clr=blk;
  }
   
   if (tar->dist == -1) {
    printf("\nTarget %d is not reachable from source.\n", t);
} else {
    printf("\nThe distance is: %d", tar->dist);
    printf("\nThe path for shortest distance is: ");
    while (tar) {
        printf(" %d ->", tar->key);
        tar = tar->par;
    }
    printf(" NULL\n");
}

 
  


}}










