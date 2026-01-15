#include<stdio.h>
int main(){int n;
int count=1;
printf("enter a number\n");
scanf("%d",&n);
for(int i=1;i<=n;i++){ 
for(int j=1;j<=i;j++){
printf("%d \t",count);
++count;
}printf("\n");
}
return 0;
}