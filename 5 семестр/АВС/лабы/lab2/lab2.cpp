#include <iostream>
#include <time.h>
#include <windows.h>
#include <fstream> 
#include <math.h>

#define eps 0.00000000000001
#define N 1000000
#define M 10

using namespace std;

double exp_(double x) 
{
	double s = 1;  
	double n = 1; 
	double a = 1; 
	while (1)     
	{
		a = a * x / n;  
		if (fabs(a) <= eps) break;
		s = s + a;    
		n++;       
	}
	return s; 
}

void Clock(int x);
void TSC(int x);
void pogr(int x);
void table(int x);

int main()
{
	double x;
	cout.precision(13); 
	do {
		cout << "exp(x)\nx = "; 
		cin >> x;              
	} while (x > 700);
	cout << "exp(" << x << ")=" << exp_(x) << endl; 

	int enter = 0;
	cout << "Pogreshnost (1), table (2): ";
	cin >> enter;

	switch (enter)
	{
	case 1:
		pogr(x);
		break;
	case 2:
		table(x);
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}

void pogr(int x) {
	int enter = -1;
	while (enter != 0) {
		cout << "Clock (1), TSC (2), (0): ";
		cin >> enter;
		switch (enter)
		{
		case 1:
			Clock(x);
			break;
		case 2:
			TSC(x);
			break;
		default:
			break;
		}
	}
}

void Clock(int x) {
	unsigned int start, stop, result = 0;
	for (int i = 0; i < M; i++) {
		start = (double)clock();
		for (int j = 0; j < N; j++)
			exp_(x);
		stop = (double)clock();
		result += stop - start;
	}
	cout << "Clock: " << (double)(stop - start) / CLOCKS_PER_SEC << "seconds" << endl;
	cout << "Absolute infelicity: " << fabs((result / M - (double)(stop - start)) / CLOCKS_PER_SEC) << endl;
	cout << "Relative infelicity: " << fabs((result / M - (double)(stop - start)) / CLOCKS_PER_SEC) / ((double)(stop - start) / CLOCKS_PER_SEC) * 100 << "%" << endl << endl;
}

void TSC(int x) {
	unsigned __int64 r, s, result3 = 0;
	for (int j = 0; j < M; j++) {
		r = __rdtsc();
		for (int i = 0; i < N; i++) {
			exp_(x);
		}
		s = __rdtsc();
		result3 += s - r;
	}
	cout << "TSC: " << ((double)(s - r)) / 2000000000 << "seconds" << endl;
	cout << "Absolute infelicity: " << fabs((result3 / M - (double)(s - r)) / 2000000000) << endl;
	cout << "Relative infelicity: " << fabs((result3 / M - (double)(s - r)) / 2000000000) / (((double)(s - r)) / 2000000000) * 100 << "%" << endl;
}

void table(int x) {
	cout << "Clock" << endl;
	unsigned int start, stop, result = 0;
	for (int i = 1; i < M; i++) {
		start = (double)clock();
		for (int j = 0; j < N*i; j++)
			exp_(x);
		stop = (double)clock();
		cout << i*N << "   " << (double)(stop - start) / CLOCKS_PER_SEC / i << endl;
	}
	cout << endl;
}
