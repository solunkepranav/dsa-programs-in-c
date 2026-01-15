#include<stdio.h>
int main(){int n,p;
printf("eneter nums");
scanf("%d%d",&n,&p);
n=p%n;
printf(" by variable: %d\n ",n);
printf(" direct : %d",p%n);

return 0;
}