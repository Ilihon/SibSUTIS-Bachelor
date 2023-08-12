#include <iostream>
#include <clocale>
#include <stdlib.h>

using namespace std;

const int n = 20, m = 30;


void SelectSort(int *A, int x);
void BSearch2(int X, int *A, int n);
void perebor(int X, int *A, int n);
void SS(int **A, int n);
int C = 0;

int main() {
	setlocale(0, "");
	int A[n], B[m], i, X;
	for (i = 0; i < n; i++) {
		A[i] = rand() % 10;
		cout << A[i] << " ";
	}
	cout << endl;
	SelectSort(A, n);
	for (i = 0; i < n; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
	cout << "¬ведите элмемент, который хотите найти: ";
	cin >> X;
	BSearch2(X, A, m);
	cout << " оличество сравнений = " << C << endl;
	C = 0;
	perebor(X, A, m);
	system("pause");
	return 0;
}



void BSearch2(int X, int *A, int n) {
	int L = 0, R = n, m;
	while (L < R) {
		m = (L + R) / 2;
		C++;
		if (A[m] > X)	L = m + 1;
		else if (A[m]>X)	
			R = m;
			else {cout << "Ёлемент найден" << endl; return ;}
	}
	C++;
	
	if (A[R] == X) {
		cout << "Ёлемент найден" << endl;
	}
	else {
		cout << "not found" << endl;
	}
}
void perebor(int X, int *A, int n) {
	int i,C = 0;
	for(i = 0;i < n; i++) {
		C++;
		if (A[i] == X) {
			cout << "Ёлемент найден" << endl;
			cout << " оличество сравнений = " << C << endl;;
			break;
		}
		else {
			continue;
		}
	}
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


