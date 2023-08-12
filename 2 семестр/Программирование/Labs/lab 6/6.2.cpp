#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void function(int n, int m, float &pd, float &pm);
int fact(int x);

int main() {
	setlocale(LC_ALL,"RUS");
	int m,n; 
	float pd,pm;
	printf("Введите кол-во детей: ");
	scanf("%d",&n);
	printf("Кол-во девочек или мальчиков из общего числа: ");
	scanf("%d",&m);
	if (m > n)
		return 1;
	function(n,m,pd,pm);
	printf("Вероятность того, что из %d детей будет %d мальчика(ов) = %.3f или %d девочки(ек) = %.3f",n,m,pm,m,pd);
	return 0;
}

void function(int n, int m, float &pd, float &pm) {
	float q,p,c;
	p=0.45; // Для девочки
	q=1-p; // Для мальчика
	c=fact(n)/(fact(m)*fact(n-m));
	pd=c*pow(p,m)*pow(q,n-m);
	pm=c*pow(q,m)*pow(p,n-m);
}

int fact(int x)
{
	int f=1;
	for (int i=1; i<=x;i++)
		f*=i;
	return f;
}
