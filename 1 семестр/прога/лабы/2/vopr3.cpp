#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
setlocale(LC_ALL, "Rus");
float x1,x2,x3,x4;
printf("input: x1, x2, x3, x4 ");
scanf("\n %f%f%f%f", &x1,&x2,&x3,&x4);
if(x1<0)
x1=0;
if(x2<0)
x2=0;
if(x3<0)
x3=0;
if(x4<0)
x4=0;
printf("x1=%.2f, x2=%.2f, x3=%.2f, x4=%.2f", x1,x2,x3,x4);
system("PAUSE");
   return 0;
}
