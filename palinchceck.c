#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct node{
    int d;
    struct node *next;
}node;

node *createnode(int key){
    node* new=malloc(sizeof(node));
    new->d=key;
    new->next=NULL;
    return new;
}
node *createlist(){
    
    printf("enter the head node");
    int n;
    scanf("%d",&n);
    node *head=createnode(n);
    node *temp=head;
     printf("enter the data of further node (0  for stopping)");
     while(n){
       
        scanf("%d",&n);
         if(n==0)break;
    temp->next=createnode(n);
    temp=temp->next;
     }
     return head;
}

int  display(node *new){
    int d=0;
         printf("\n");
    while(new){
        printf("%d ->",new->d);
        new=new->next;
         d++;
    }
     printf("NULL");
     return d;
}
void usingstack(node *head,int count){
    int stack[count];
    int top=-1;
   node * temp=head;
    while(temp){
      stack[++top]=temp->d;
      temp=temp->next;
    }
    for(int i=top;i>=count/2;i--){
        if(stack[i]!=head->d){
            printf("\nit is not a palindrome");
            return;
        }
        head=head->next;
    }
    printf("\nits a palindrome");
    
}
node *rev(node *head){
    if((!head)||!(head->next)){
        return head;
    }
    node *rest=rev(head->next);
    head->next->next=head;
    head->next=NULL;
   return rest;

}
node* deldupl(node* head) {
    if (head == NULL) return NULL; // Handle empty list

    node* start = head;
    node* unq = head->next;

    while (unq != NULL) {
        // Fix: Check if unq exists AND is a duplicate
        if (start->d== unq->d) {
            unq = unq->next; // Just skip it
        } else {
            // Found a unique node, link it
            start->next = unq;
            start = unq;
            unq = unq->next;
        }
    }
    // Final Step: Ensure the list is terminated correctly
    // If the list ended with duplicates (e.g., 1->2->2), start still points to the first 2.
    // We need to make sure start->next becomes NULL to cut off the extra 2.
    start->next = NULL; 
    
    return head;
}

void usingptr(node * head){
    node *slow=head;
    node *fast=head;
    
     while(fast->next && fast->next->next){
        slow=slow->next;
        fast=fast->next->next;
    }
        
    node* shalfcpy=rev(slow->next);

    node* shalf=shalfcpy;
    node *fhalf=head;
    int flg=1;
        while(shalfcpy){
            if(shalfcpy->d!=fhalf->d){
                flg=0;
            }
            shalfcpy=shalfcpy->next;
            fhalf=fhalf->next;
        }
      if (flg){
        printf("\nIt is a palindrome");}
    else{
        printf("\nIt is not a palindrome");}

    // Optional Step 4: Restore the list (Reverse the second half again)
    slow->next = rev(shalf);
}
    


int main(){
    node *head=createlist();
    int d=display(head);
    deldupl(head);
    display(head);
    // display(rev(head));
    // usingstack(head,d);
   
}