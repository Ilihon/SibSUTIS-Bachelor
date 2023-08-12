
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
float x1,x2,x3;
float y;
printf("input: x1,x2,x3 ");
scanf("\n %f%f%f", &x1,&x2,&x3);

if(x1>x2){
if(x1>x3){
if(x2>x3) {
y = x1;
x1 = x3;
x3 = y;
} else {
y = x1;
x1 = x2;
x2 = y;
}
} else {
y = x3;
x3 = x2;
x2 = y;
}
} else {
if(x1>x3){
y = x3;
x3 = x2;
x2 = y;
} else {
if(x2>x3){
y = x1;
x1 = x2;
x2 = y;
} else {
y = x1;
x1 = x3;
x3 = y;
}
}
}

printf("x1 =%f, x2 = %f, x3 = %f", x1, x2, x3);
system("PAUSE");
return 0;
}
