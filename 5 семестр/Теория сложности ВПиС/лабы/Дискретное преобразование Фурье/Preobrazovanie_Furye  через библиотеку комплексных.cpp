#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <complex>

using namespace std;
const double pi = 3.14;
const int n = 8;
complex <double> A[n];
complex <double> B[n];
complex <double> i (0, 1);

complex <double> Furye(double *f , int n){
	for (int k = 1; k <= n; k++){
		complex <double> sum = 0;
		for(int j = 1; j <= n; j++){
		sum += exp(- 2 * pi * i * (double)(k * j / (double)n)) * f[j];
		//cout << "k * j / n = " << k * j / (double)n << endl;
		}
		A[k] = (1 / (double)n) * sum;
		cout << A[k] << " " << endl;
	}
}

complex <double> Furye_reverse(complex <double> *A, int n){
		for (int k = 1; k <= n; k++){
		complex <double> sum = 0;
		for(int j = 1; j <= n; j++){
		sum += exp((2 * pi * i) * ((double)(k * j / (double)n))) * A[j];
		}
		B[k] = sum;
		cout << B[k] << " " << endl;
	}
}

int main(){
	double f[n];
	for (int j = 1; j <= n; j++){
		f[j] = j * j;
		cout << f[j] << " ";
	}
	cout << endl;
	Furye(f,n);
	cout << endl;
	Furye_reverse(A, n);
}
