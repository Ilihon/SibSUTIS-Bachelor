#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <conio.h>
#include <time.h>
char n,d,t=1;
int random(int b){return rand()%b;};


int fun(int *A, int n)
	{
		if (t) if ((n) and (A[n-1]>0)) {printf("%d ",A[n-1]); return fun(A,n-1);}
		else
			{
				if (!n) { t=0; n=d; printf("\n"); return fun(A,n);}
				return fun(A,n-1);
			}
		else if ((n) and (A[n-1]<0))
		 	{
				printf("%d ",A[n-1]); return fun(A,n-1);
			}	
		else 
			{
				if (!n) return t++; return fun(A,n-1); 
			}									
	}



int main ()
{setlocale (LC_ALL,"Rus");
int A[256];
char i;
printf("¬ведите размер массива:");
scanf("%d",&n);
srand(time(NULL));
for (i=0; i<n; i++){
  	A[i]=random(21)-10;
	/*if (A[i])*/ printf("%d ",A[i]);}
d=n;
printf("\n");
fun(A,d);
    system ("PAUSE");
}
