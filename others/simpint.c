#include<stdio.h>
int main(){ int p,t;
float r;
printf("enter the principle , duration in years and rate in percentage:\n");
scanf("%d %d %f" ,&p,&t,&r);
printf("\n the simple intrest after %d years is %5.3f:",t,p*t*r/100);
return 0;
}