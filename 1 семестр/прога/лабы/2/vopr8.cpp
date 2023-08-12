#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
float x1,x2,x3,x4;
float max1, max2;
printf("input: x1,x2,x3,x4 ");
scanf("\n %f%f%f%f", &x1,&x2,&x3,&x4);
max1 = -100000;
max2 = -100000;
if(x1>max1)
max1 = x1;
if(x2>max1)
max1 = x2;
if(x3>max1)
max1 = x3;
if(x4>max1)
max1 = x4;

if(x1<max1){
if(max2<x1)
max2 = x1;
}
if(x2<max1){
if(max2<x2)
max2 = x2;
}
if(x3<max1){
if(max2<x3)
max2 = x3;
}
if(x4<max1){
if(max2<x4)
max2 = x4;
}
printf("nibolshee chislo:%f %f", max1, max2);
system("PAUSE");
return 0;
}
