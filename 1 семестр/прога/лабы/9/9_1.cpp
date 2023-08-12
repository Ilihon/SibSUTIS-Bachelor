#include <stdio.h>
#include <stdlib.h>
int random (int i) {return rand()%i; }
int main()
{ int t,i, num[10][10],a=-100,b=100,x=0,k=0;
/* загрузка чисел */
for(t=0; t<10; ++t)
for (i=0; i<10; ++i)
num[t][i] = random(b-a+1) + a;
/* вывод чисел */
printf("Matrica do \n");
printf("\n");
for (t=0; t<10; ++t)
{
printf("\n");
for (i=0; i<10; ++i)
printf("%4d  ",num[t][i]);
printf ("\n");
}
//новая матрица из первой//
printf ("\n");
printf("Matrica posle \n");
printf ("\n");
for (t=0; t<10; ++t){
for (i=0; i<10; ++i){
 x = num[0][i];
  num[0][i] = num[1][i];
  num[1][i] = x;
  x = num[2][i];
  num[2][i] = num[3][i];
  num[3][i] = x;
  x = num[4][i];
  num[4][i] = num[5][i];
  num[5][i] = x;
  x = num[6][i];
  num[6][i] = num[7][i];
  num[7][i] = x;
  x = num[8][i];
  num[8][i] = num[9][i];
  num[9][i] = x;
}
printf("\n");
for (t=0; t<10; ++t)
{
printf("\n");
for (i=0; i<10; ++i)
printf("%4d  ",num[t][i]);
printf ("\n");
}
}
system("PAUSE");
return 0;
}
