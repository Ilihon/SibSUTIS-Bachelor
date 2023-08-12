#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
setlocale(LC_ALL, "Rus");
float x1,x2,x3,x4;
float min, max;
printf("input: x1,x2,x3,x4 ");
scanf("\n %f%f%f%f", &x1,&x2,&x3,&x4);
min = x1;
max = 0;
if(x2<min)
min = x2;
if(x3<min)
min = x3;
if(x4<min)
min = x4;
if(x1>max)
max = x1;
if(x2>max)
max = x2;
if(x3>max)
max = x3;
if(x4>max)
max = x4;
printf("–азность между наибольшим и наименьшим числами = %f", max-min);
system("PAUSE");
return 0;
}
