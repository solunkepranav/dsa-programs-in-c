#include<stdio.h>
int main(){ int x,y;
printf("enter two numbers which are to be swapped:\n");
scanf("%d %d",&x,&y);
printf("\n numbers before swapping: %d %d\n",x,y);
x=x+y;
y=x-y;
x=x-y;
printf("\n numbers after swapping: %d %d\n",x,y);
return 0;
}