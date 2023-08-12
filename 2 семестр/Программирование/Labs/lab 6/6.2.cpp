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
	printf("������� ���-�� �����: ");
	scanf("%d",&n);
	printf("���-�� ������� ��� ��������� �� ������ �����: ");
	scanf("%d",&m);
	if (m > n)
		return 1;
	function(n,m,pd,pm);
	printf("����������� ����, ��� �� %d ����� ����� %d ��������(��) = %.3f ��� %d �������(��) = %.3f",n,m,pm,m,pd);
	return 0;
}

void function(int n, int m, float &pd, float &pm) {
	float q,p,c;
	p=0.45; // ��� �������
	q=1-p; // ��� ��������
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
