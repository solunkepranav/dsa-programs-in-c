#include<stdio.h>
int main(){ int n1,n2,cp1,cp2;
printf("enter the two numbers: ");
scanf("%d%d",&n1,&n2);
cp1=n1;
cp2=n2;
while(cp1){
int temp=cp1;
cp1=cp2%cp1;
cp2=temp;}
printf("\n the gcd of the given two numbers is  %d",cp2);
printf("\n the lcm of the given two numbers is  %d",(n1*n2)/cp2);
return 0;
}