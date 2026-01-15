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
#include<stdlib.h>
#include<stdio.h>
 typedef struct node{
 int d;
 char c;
 struct node* l,*r;
 }node;
 
 
 node* createnode(char ch){ int data;
 node* new= malloc(sizeof(node));
 new->c=ch;
 new->l=NULL;
 new->r=NULL;
 
 if(ch<='z'&&ch>='a'){
 
 printf("enter the value for the node %c : ",new->c);
 scanf("%d",&data);
 new->d=data;
 }
 return new;
 }
 
 
 
 
 node* create(char* postfix){
 node* stack[11];
 int top=-1;
 int i=0;
 while(postfix[i]){
 char ch=postfix[i];
 node* new=createnode(ch);
 if(ch<='z'&&ch>='a'){stack[++top]=new;
 
}
else{
new->r=stack[top--];
new->l=stack[top--];
stack[++top]=new;}

i++;}
return stack[0];
}


void infix(node *root){
if(root==NULL){
printf("the tree is empty ");
return;}


node* cur=root;
if(cur->l){
    printf("(");
infix(cur->l);}
char ch=cur->c;
if(ch>='a'&&ch<='z'){
    printf(" %d ",cur->d);
}
else{
printf(" %c ",cur->c);}
if(cur->r){
   
    infix(cur->r);
       printf(")"); //for clarity

}}

int eval(node* root){
node *cur=root;
if((cur->l==NULL)&&(cur->r==NULL)){
return cur->d;}

int left=eval(cur->l);
int right=eval(cur->r);
switch(cur->c){
case '+': return left+right;
case '-':return left-right;
case '*':return left*right;
case '/':return left/right;
}

}
 
 
 
 
 int main(){
 
 printf("enter  the postfix exp : ");
 char postfix[11];scanf("%s",postfix);
 
node* root=create(postfix);
printf("the tree is : ");
infix(root);
int ans=eval(root);
printf("\nthe ans is the : %d",eval(root));
}

 