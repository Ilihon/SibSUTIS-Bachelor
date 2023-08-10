#include <iostream>

double math_sample_expectation(double *X, double *P, int n){
	double M = 0;
	double N = 0;
	for(int i=0; i < n; i++){
		N += P[i];
	}
	for(int i=0; i < n; i++){
		M += X[i]*P[i]/N;
	}
	return M;
}

int main(){
	setlocale(0, "");
	int n = 5;
	double X[n] = {2,6,10,12,14};
	double P[n] = {1,5,7,3,4};
	double result = math_sample_expectation(X,P,n);
	printf(" Расчётное математическое ожидание: 9,7\n");
	printf(" Результат работы процедуры: %f", result);
	return 0;
}
