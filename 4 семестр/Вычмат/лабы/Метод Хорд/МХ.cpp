#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define urav pow(x,2)-3


int main()
{
	setlocale(LC_ALL, "rus");
	double a=1,b=2,c=0;
	double E =pow(10,-7);
	double fa=0,fb=0,fc=0;
	double x=0;
	
	//cout << "["<<a <<" ; "<<b<<"]"<<endl;
	x=a;
	fa=urav;
	//cout << fa<<endl;
	x=b;
	fb=urav;
	//cout << fb<<endl;
	if((fa*fb)>=0){
		cout << "Нет корней";
		return 0;
	}
	c=fa;
	//cout << "======================";
	int i=0;
	while( fabs(b-a)>E){
		i++;
		//cout<<endl<< "|b-a|: " << fabs(b-a);
		x=b;
		fb = urav;
		c=(a*fb-b*fa)/(fb-fa);
	//	cout<<endl<< "c: " << c;		
		x=c;
		fc=urav;
	//	cout <<endl<< "f(c): " <<fc;
		if(fa*fc>0){
			a=c;
			fa=fc;
		}
		else{
			b=c;
		}
	//	cout << endl << "Iteration: [" << a << " ; "<< b<<"]"<<endl;
		
	}
	//cout <<endl<<"==================="<<endl;
	printf("[%5.15f ; %5.15f]\n",a,b);
	
	printf("|b-a|<E \t :\t%5.15f < %f\n",fabs(b-a),E);
	
	printf("c: %5.15f\n",c);
	printf("f(c): %5.15f\n",fc);
	
	printf("Количество шагов: %d\n",i);

	system("PAUSE");
	return 0;
}




