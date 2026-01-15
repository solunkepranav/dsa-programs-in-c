#include <stdio.h>
int main() { double feet, meters;
 printf("Enter length in feet: ");
 scanf("%lf", &feet); 
meters = feet * 0.3048;
 printf("Length in meters: %.3lf\n", meters); return 0;
}
