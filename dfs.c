#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int time;
#define wht 0
#define gr 1
#define blk 2

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct vertex {
    int clr;
    int stime;
    int ftime;
    struct vertex *par;
    node *head;
    int key;
} vertex;


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
    new->stime = new->ftime=0;
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
void dfs(vertex** ver,int n,vertex* u){
    time=time+1;
    u->stime=time;
    u->clr=gr;
    
    
    node* temp=u->head;
    while(temp){
        vertex* v=search(ver,n,temp->data);
        if(v->clr==wht){
            v->par=u;
           dfs(ver,n,v);
           
        }
        
        temp=temp->next;


    }
    u->clr=blk;
    time=time+1;
    u->ftime=time;


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

printf("\n enter the source for dfs : ");
scanf("%d",&a);
vertex* s=search(ver,n,a);

// s->clr=gr;
// s->stime=s->ftime=0;
// s->par=NULL;
time=0;
// vertex *u;

printf("\n enter the target for bfs: ");
int t;
scanf("%d",&t);
vertex *tar=search(ver,n,t);
printf("\n  dfs traversal : ");
if (s->clr == wht) {
    dfs(ver, n, s);
}

for(int i=0;i<n;i++){
if(ver[i]->clr==wht){
    dfs(ver,n,ver[i]);

}}

if(tar!=NULL&&tar->clr!=wht){
    printf("the key is found \n path :  ");
    vertex* path=tar;
    while(path){
        printf("%d (d/f - %d/%d)->",path->key,path->stime,path->ftime);
path=path->par;


    }
    printf("NULL");
}
else{ printf("the path is not found");}
//freeeeeeeeeee

    for(int i = 0; i < n; i++) {
        node* temp = ver[i]->head;
        while(temp != NULL) {
            node* to_free = temp;
            temp = temp->next;
            free(to_free); // Free each node in the adjacency list
        }
        free(ver[i]); // Free the vertex itself
    }


 
  


}










