	#include <stdio.h>
#include <stdlib.h>
int random (int i) {return rand()%i; }
int main()
{ int t,i, num[5][5],a=-10,b=10,x=0,k=0;
/* загрузка чисел */
for(t=0; t<5; ++t)
for (i=0; i<5; ++i)
num[t][i] = random(b-a+1) + a;
/* вывод чисел */
printf("Matrica do \n");
printf("\n");
for (t=0; t<5; ++t)
{
printf("\n");
for (i=0; i<5; ++i)
printf("%4d  ",num[t][i]);
printf ("\n");
}
//новая матрица из первой//
printf ("\n");
printf("Matrica posle \n");
printf ("\n");
for (t=0; t<5; ++t)
{for (i=0; i<5; ++i)
{ x = num[0][0];
  num[0][0] = num[1][1];
  num[1][1] = x;
  x = num[2][2];
  num[2][2] = num[3][3];
  num[3][3] = x;
  x = num[4][4];
  num[4][4] = num[5][5];
  num[5][5] = x;
}
printf("\n");
for (t=0; t<5; ++t)
{
printf("\n");
for (i=0; i<5; ++i)
printf("%4d  ",num[t][i]);
printf ("\n");
}
}
system("PAUSE");
return 0;
}
