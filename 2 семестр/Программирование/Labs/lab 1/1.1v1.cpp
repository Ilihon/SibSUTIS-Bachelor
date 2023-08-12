#include <stdio.h>
#include <math.h>
#include <iostream>
float cosinus(float x) 
	{
		float Cos=1., eps; int i;
		for (i=1,eps=1;(eps>0.0001)or(eps<-0.0001); i++)
			{ 
				eps=1;
				for (int f=1;f<=i*2;f++) eps*=x/f;
				if (i%2) eps*=(-1.); Cos+=eps;
			}
		return Cos;
	}
	int fact(int n)
{
	if(n==0) return 1;
	int x=n;
	n--;
	while(n>0)
	{
		x=x*n;
		n--;
	}
	return x;
}
double cosinuss(int x, int n)
{double c;
	c=(pow(-1,n)*pow(x,2*n))/fact(2*n);
	
	return c;
}

int main()
{
	float x,y1,y2,r;
	int n=1;
	setlocale(LC_ALL,"Russian"); 
	printf("введите x = ");
	scanf("%f",&x);
	y1=cos(x); printf("cos x = %5.4f\n",y1);
	y2=cosinus(x); printf("cosinus x = %5.4f\n",y2);
}
