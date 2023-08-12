#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define urav pow(x,2)-3
#define urav_pr 2*x


int main()
{
	setlocale(LC_ALL, "rus");
	double E =pow(10,-7);
	double fx=0;
	double x=2;
	double v=(urav)/(urav_pr);
	
	cout << "x0 = "<<x<<endl;
	int i=-1;
	while(v>E){
		v=(urav)/(urav_pr);	
		i++;
		printf("x%d = %11.15f - %11.15f = %11.15f\n",i,x,v,x-v);
		x=x-v;	
	}
	printf("\nКоличество шагов: %d\n",i);
	printf("x: %5.15f\n",x);

	system("PAUSE");
	return 0;
}




