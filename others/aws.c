#include<stdio.h>
int main(){
for(int i=1;i<10;i++){
for(int j=1;j<10;j++){
if(i!=j){
int num1=10*i+j;
for(int k=1;k<10;k++){
for(int l=1;l<10;l++){
if(k!=l){
int num2=10*k+l;
if(num1>num2){
if(num1*num2==(10*j+i)*(10*l+k)){
printf("%d * %d = %d * %d\n",num1,num2,10*j+i,10*l+k);}
}}}}}}};



return 0;
}