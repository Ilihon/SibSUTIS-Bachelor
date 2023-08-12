#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
setlocale(LC_ALL, "Rus");
float x1,x2,x3,x4,x5,x6,x7,x8;
int y, y1;
printf("input: x1,x2,x3,x4,x5,x6,x7,x8 ");
scanf("\n %f%f%f%f%f%f%f%f", &x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8);
y=0;
y1=0;
if(x1>0)
{
y++;
} else {
if(x1!=0)
y1++;
}
if(x2>0)
{
y++;
} else {
if(x2!=0)
y1++;
}
if(x3>0)
{
y++;
} else {
if(x3!=0)
y1++;
}
if(x4>0)
{
y++;
} else {
if(x4!=0)
y1++;
}
if(x5>0)
{
y++;
} else {
if(x5!=0)
y1++;
}
if(x6>0)
{
y++;
} else {
if(x6!=0)
y1++;
}
if(x7>0)
{
y++;
} else {
if(x7!=0)
y1++;
}
if(x8>0)
{
y++;
} else {
if(x8!=0)
y1++;
}
printf("%d отрицательных чисел, %d положительных чисел", y1, y);
system("PAUSE");
return 0;
}
