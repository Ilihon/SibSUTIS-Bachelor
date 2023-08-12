#include <stdio.h>
#include <stdlib.h>
const int M = 5; 
const int N = 5;
int random (int i) {return rand()%i; }
int main()
{ int t,i, A[M][N],a=-10,b=10,x=0,k=0;
/* вывод матрицы*/
for(t=0; t<M; ++t)
for (i=0; i<N; ++i)
A[t][i] = random(b-a+1) + a;
/* «агрузка чисел*/
printf("Matrica do \n");
printf("\n");
for (t=0; t<M; ++t)
{
printf("\n");
for (i=0; i<N; ++i)
printf("%4d  ",A[t][i]);
printf ("\n");
}
//нова€ матрица//
printf ("\n");
printf("Matrica posle \n");
printf ("\n");
for (t=0; t<M; ++t)
{
printf("\n");
for (i=0; i<N; ++i)
printf("%4d  ",A[i][t]);
printf ("\n");
}
system("PAUSE");
return 0;
}
