#include<stdio.h>

int main(){

int days, yr, month, rdays;

printf("enter the number of days");

scanf("%d",&days);

yr=days/366;
rdays=days-(yr*366);

month=rdays/30;

rdays=rdays- (month*30);

printf(" the remaining days =%d\n months=%d \n years = %d",rdays, month,yr);


return 0;}

