#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <math.h>

const double p = 0.45;
const double q = 0.65;

fact(int n) {
	if (n == 0 || n == 1) return 1;
    return n * fact(n - 1);
}

girl(int n, int m, double &pd, double &pm, double c = 0) {
	c=fact(n)/(fact(m)*fact(n-m));
	pd=c*pow(p,m)*pow(q,(n-m));
	pm=c*pow(q,m)*pow(p,(n-m));
	printf("Probability for girls: %lf \n",pd);
	printf("Probability for boys: %lf \n",pm);
	return 0;
}


main() {
	int n = 0;
	int m = 0;
	double pd = 0;
	double pm = 0;
	double c = 0;
	printf("Number of children: ");
	scanf("%d",&n);
	printf("Number of girls or boys: ");
	scanf("%d",&m);
	//c=fact(n)/(fact(m)*fact(n-m));
	girl(n,m,pd,pm,c);
	//printf("%lf",c);
	system("pause");
	getch();
}
