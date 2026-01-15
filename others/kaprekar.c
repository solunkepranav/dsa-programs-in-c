#include<stdio.h>
int main(){ int n,p;

printf("enter the num  ");
scanf("%d",&n);
p=n;
int pow=1;
while(p){ pow*=10;
p/=10;}
p=((n*n)%pow)+((n*n)/pow);
if(n==p){
printf("\nenterd %d number is a kaprekar number",n);
}
else{ printf("\nenterd %d number is not a kaprekar number",n);};

return 0;}