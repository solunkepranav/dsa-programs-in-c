#include<stdio.h>
#include<stdlib.h>

typedef struct mtrx{
 int data;
 struct mtrx *d,*r;

}mtrx;
  mtrx *createnode(int n){ 
 mtrx*  new= malloc(sizeof(mtrx));
 new->data=n;
 new->r=NULL;
 new->d=NULL;
return new;}




mtrx* construct(int m, int n,int matrix[m][n]){
    mtrx* mat[m][n];
    for(int i=m-1;i>=0;i--){
       for(int j=n-1;j>=0;j--){
        mtrx* new=createnode(matrix[i][j]);
        new->r=j!=n-1?mat[i][j+1]:NULL;
        new->d=i!=m-1?mat[i+1][j]:NULL;
        mat[i][j]=new;
       }
    }
return mat[0][0];

  }


void display(mtrx* mat ){
    mtrx* rowh=mat;
  while(rowh!=NULL){
    mtrx* cur=rowh;
while(cur!=NULL){
    printf(" %d ",cur->data);
    cur=cur->r;
}
printf("\n");
 rowh=rowh->d;
  }
}

void freematrix(mtrx* mat){
mtrx* rowh=mat;
  while(rowh!=NULL){
    mtrx* cur=rowh;
    mtrx* nextr=rowh->d;
    while(cur!=NULL){
   mtrx* temp=cur;
    cur=cur->r;
    free(temp);
    }
 rowh=nextr;
  }
}

int main(){

int arr[3][3]={0,1,2,3,4,5,6,7,8};
mtrx* head=construct(3,3,arr);
display(head);
freematrix(head);
}
