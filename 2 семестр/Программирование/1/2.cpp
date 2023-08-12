#include <iostream>
#include <math.h>
using namespace std;

float fact(int n){
if (n<=0) return 1;
return (fact(n-1)*n);
}

float summa(float x, int n)
{
float f;
f=(pow((-1),n)*pow(x,(2*n)))/(fact(2*n));
if((f*pow(-1,n))<=0.0001)
{
return f;
} 
return summa(x,n+1)+f; 
}

main() {
float x,s,c;
cin>> x ;
s=1+summa(x,1);
c=cos(x);
printf("%.3f \n",s);
printf("%.3f \n",c);
return 0;
}
