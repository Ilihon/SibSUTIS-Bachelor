#include <iostream>
#include <clocale>
#include <stdlib.h>

using namespace std;

const int n = 20, m = 30;


void SelectSort(int *A, int x);


int main() {
	setlocale(0, "");
	int A[n], B[m], i, X;
	for (i = 0; i < n; i++) {
		A[i] = rand() % 10;
		cout << A[i] << " ";
	}
	cout << endl;
	for (i = 0; i < m; i++) {
		B[i] = rand() % 10;
		cout << B[i] << " ";
	}
	SelectSort(B, m);
	SelectSort(A, n);
	cout << endl;
	for (i = 0; i < n; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
	for (i = 0; i < m; i++) {
		cout << B[i] << " ";
	}
system("pause");
return 0;
}

void SelectSort(int *A, int x)
{
	int k, t, f = 0;
	for (int i = 0; i < (x - 1); i++)
	{
		k = i;
		for (int j = i + 1; j < x; j++)
		{
			if (A[k]<A[j])   k = j;
		}
		t = A[i];
		A[i] = A[k];
		A[k] = t;
	}
}



