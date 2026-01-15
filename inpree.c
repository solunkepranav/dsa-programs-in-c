/*
evaluation of expression- by stack
by tree 
2.by tree - bottom up- post order
eval(left)->eval(right) then eval(right)(node)eval(right) 
recursive
if left(node)=right(node)==null , then eval return node;
1)blding an exp tree
2)eval only in post fix
3)full  bin tree - whatever max h , all nodes (2^lvl) nodes are present on all lvl , triangular shape , every parent has 2 child
4)complete bin tree- full tree upto k-1 lvl , 
5)induction 
all full are complete

*/
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
 typedef struct node{
 char c;
 struct node* l,*r;
 }node;
 
 
 node* createnode(){ int data;
 node* new= malloc(sizeof(node));
 
 new->l=NULL;
 new->r=NULL;
 
 return new;
 }


int search(char ch, char* infix, int start, int end){
    int i;
    for(i = start; i <= end; i++){
        if(infix[i] == ch){
            return i; 
        }
    }
    return -1; 
}

node* figureout(char* infix,char* prefix,int start,int end,int *top){

if(start>end)return NULL;

    node* new=createnode();
   new->c= prefix[(*top)++];
    if(start==end){ return new;}
    int pos=search(new->c,infix,start,end);    
    new->l=figureout(infix,prefix,start,pos-1,top);
     new->r=figureout(infix,prefix,pos+1,end,top);
     return new;
     
}
 
 
 
 
 
 node* create(char* prefix,char* infix,int *top){
node* root=figureout(infix,prefix,0,strlen(infix)-1,top);
return root;

}


void infix1(node *root){
if(root==NULL){
    return;
}



node* cur=root;
if(cur->l){
infix1(cur->l);}
char ch=cur->c;
printf(" %c ",cur->c);
if(cur->r){infix1(cur->r);}
}

void prefix1(node *root){
    if(root == NULL) return;

    printf(" %c ", root->c);
    prefix1(root->l);
    prefix1(root->r);
}

 
 
 
 int main(){
 
 printf("enter  the prefix exp : ");
 char prefix[11];scanf("%s",prefix);

  printf("enter  the infix exp : ");
 char infix[11];scanf("%s",infix);
int top = 0;


 
node* root=create(prefix,infix,&top);
printf("Infix traversal: ");
infix1(root);
printf("\nPrefix traversal: ");
prefix1(root);
printf("\n");

}


 