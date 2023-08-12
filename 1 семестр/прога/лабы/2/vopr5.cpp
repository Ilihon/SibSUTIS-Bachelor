#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{

float x1,x2,x3,x4;
float min;
int num;
printf("input: x1,x2,x3,x4 ");
scanf("\n %f%f%f%f", &x1,&x2,&x3,&x4);
min = x1;
num = 1;
if(x2<min){
min = x2;
num = 2;
}
if(x3<min){
min = x3;
num = 3;
}
if(x4<min){
min = x4;
num = 4;
}

printf("%d poziciya minimalna", num);
system("PAUSE");
return 0;
}
