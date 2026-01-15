#include<iostream>
using namespace std;
int main(){ int num1,num2,base1,base2,dec,pow;
cout<<"enter the number and its system(expect hex)\n";
cin>>num1>>base1;
cout<<"enter the system(expect hex) in which u want to convert \n";
cin>>base2;
int p=num1;
pow=1;
dec=0;
while(num1){
dec+=((num1%10)*pow);
num1/=10;
pow*=base1;
}
pow=1;
num2=0;
cout<<"\nthe "<<p<<" of "<<base1<<" system in decimal system is :"<<dec;
while(dec){
num2+=(dec%base2)*pow;
dec/=base2;
pow*=10;
}
cout<<"\nthe "<<p<<" of "<<base1<<" system is equal to :"<<num2<<"of "<<base2<<" system";
return 0;}
