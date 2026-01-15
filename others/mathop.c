#include <stdio.h>
 int main()
{
int a,b; printf("Enter 2 numbers\n"); 
scanf("%d %d", &a,&b);
 printf("\nThe sum is %d",(a+b));
 printf("\nThe subtraction is %d",(a-b));
 printf("\nThe multiplication is %d",(a*b)); 
printf("\nThe remainder on dividing %d by %d is %d",b,a,(a%b));
 printf("\nThe value of %d/%d is %d",a,b,(a/b)); 
return 0;
}
