#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

float cosinus(float x)
{
    float Cos=1.0, eps;
    int i;

    for(i=1,eps=1;(eps>0.0001)or(eps<-0.0001);i++)
        {
        eps=1;
        for (int f=1;f<=i*2;f++) 
	eps*=x/f;
        

	if (i%2) eps*=(-1.0); 
	Cos+=eps;
        }
    return Cos;
}

int main()
{
    float x,y1,y2;
    cout << " x = ";
    cin >> x;
    y1=cos(x);
    cout << y1;
    y2=cosinus(x);
    cout << "cosinus x = " << y2;
    cout << "cos(x)-cosinus(x)= " << y2-y1;
    return 0;
}

