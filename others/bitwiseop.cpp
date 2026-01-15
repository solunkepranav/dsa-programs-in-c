#include<iostream>
using namespace std;
int main(){ //2's complement - negative numbers are stored by taking 2's complement of their positive version, out of 32 bits , 1st bit is for sign,if 0 means it is positive and if 1 it is negative
//bitwise op- &,|nd ^(xor),left shift op(<<)[multiplies by 2^shiftnum]{num<<shiftnum},right shift op(>>)[divides by 2^shiftnum]{num>>shift num}
//op precedance A-->A++, scope [fun is in  call stack,then is gets erased,global scope and local scope, after return statement no code of that block excutes further,data type modifiers- long(8b),longlong(8b),short(2b),signed(default),unsigned(1 extra bit for int,1st bit)
//homework problem;
int p;
cout<<"enter a num";
cin>>p;
if((p%2)==0){
cout<<"it is a power of 2\n";
}
else{cout<<"it is not a power of 2";
}
return 0;}
