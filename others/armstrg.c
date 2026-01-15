#include<stdio.h>
int main(){
int n;
printf("enter the number");
scanf("%d",&n);
int p;
p=n;
int sum=0;
while(p){
int temp;
temp=p%10;
p/=10;
sum+=(temp*temp*temp);
}
if(sum==n){
printf("the given %d number is armstrong number",n);
}
else{ printf("the given %d number is not armstrong number",n);
};
for(int i=100;i<1000;i++)
{int o;
o=i;
int sum1=0;
while(o){
int temp;
temp=o%10;
o/=10;
sum1+=(temp*temp*temp);
}
if(sum1==i){printf("\n %d ",i);
};};

return 0;}