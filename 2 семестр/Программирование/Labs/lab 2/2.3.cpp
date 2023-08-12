#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
int q,f,i=1;
using namespace std;

int fun(int f)
{ 	if (f) 
		{
		//	printf ("%d\n",f);
    		q+=f%2*i, i*=10;
			if (f%2) return fun((f-1)/2);
			else return fun(f/2);
		}
	else return q;			
	}

int main ()

{setlocale (LC_ALL,"Rus");
    int p,sum;
printf("Написать рекурсивную функцию для перевода числа из десятичной системы счисления в двоичную\n");
printf("\nВведите число ");
scanf("%d",&p);
printf ("%d",fun(p));
    system ("PAUSE");
}
