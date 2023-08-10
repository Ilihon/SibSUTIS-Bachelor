#include <iostream>

double math_sample_expectation(double *X, int n, int k){
	double M = 0;
	for(int i=0; i < k; i++){
		M += X[i]/n;
	}
	return M;
}

int main(){
	setlocale(0, "");
	int k = 5;
	double X[k] = {2,6,10,12,14};
	int n = 20;
	double result = math_sample_expectation(X,n,k);
	printf(" ��������� �������������� ��������: 2,2\n");
	printf(" ��������� ������ ���������: %f", result);
	return 0;
}
