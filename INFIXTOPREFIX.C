#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>

int icp(char c){
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case ')':
            return 3;
        default:
            return 0;
    }
}
int isp(char c){
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case ')':
            return 0;
        default:
            return -1;
    }
}
bool isempty(int top){return top==-1?true:false;}
void push(char *arr,int *top,char c){
    arr[++(*top)]=c;
}
char pop(char *arr,int *top){
if(!isempty(*top)){
    return arr[(*top)--];
}
}

int main(){
    int top1=-1;
    int top2=-1;
    char opstk[50];
    char prestk[50];
    push(opstk,&top1,'#');
    int n=0;
    printf("enter the size of expression");
    scanf("%d",&n);
    getchar();
    char inp[n+1];
    printf("enter the expression");
    fgets(inp,sizeof(inp),stdin);
    for(int i=n-1;i>=0;i--){
        char c=inp[i];
        if(c>='a'&& c<='z'){push(prestk,&top2,c);}
         else if(c=='('){
         while(opstk[top1]!=')'){
            push(prestk,&top2,pop(opstk,&top1));
         }
         pop(opstk,&top1);
        }
        else if(c==')'||icp(c)>=isp(opstk[top1])){
            push(opstk,&top1,c);
        }
       
        else if(icp(c)<isp(opstk[top1])){
            while(icp(c)<isp(opstk[top1])){
                push(prestk,&top2,pop(opstk,&top1));

            }
             push(opstk,&top1,c);
        }

        }
        while (opstk[top1] != '#') {
        prestk[++top2] = opstk[top1--];
    }
    for(int i=top2;i>=0;i--){
        printf("%c ",prestk[i]);
    }
    




    
}