#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int function(int a,int b,int c,int *P,int *S);

int main() {
	setlocale(LC_ALL,"RUS");
	int a,b,c,P,S; P=0; S=1;
	printf("Стороны треугольника: ");
	scanf("%d%d%d",&a,&b,&c);
	if (function(a,b,c,&P,&S) == 0)
		printf("Такого треугольника не существует");
	else	
		printf("P = %d\nS = %d",P,S);
}


int function(int a,int b,int c,int *P,int *S) {
//	printf(" %d %d %d",a,b,c);

	if((a+b) > c and ((a+c)>b) and ((b+c)>a))
		{*P=a+b+c;
		*S=sqrt(*P/2*(*P/2-a)*(*P/2-b)*(*P/2-c));}
		else
		return 0;
		return 1;
}
