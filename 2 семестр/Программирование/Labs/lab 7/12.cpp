#include <iostream>
#include <clocale>
#include <stdlib.h>
#include <math.h>

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
cout << endl;
	cout << "Введите элмемент, который хотите найти: ";
	cin >> X;
	BSearch2(X, A, n);
	cout << "Количество сравнений = " << C << endl;
	C = 0;
	perebor(X, A, n);
cout << endl;
	cout << "Введите элмемент, который хотите найти: ";
	cin >> X;
	BSearch2(X, B, m);
	cout << "Количество сравнений = " << C << endl;
	C = 0;
	perebor(X, B, m);
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
void BSearch2(int X, int *A, int n) {
	int L = 0, R = n-1, m;
	while (L <= R) {
		m = int((L + R) / 2);
		C++;
		if (A[m] > X)	L = m + 1;
		else if (A[m] < X)	
			R = m-1;
			else {cout << "Элемент найден (бин)" << endl; return ;}
	}
	C++;
	
	if (A[R] == X) {
		cout << "Элемент найден" << endl;
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
			cout << "Элемент найден (перебор)" << endl;
			cout << "Количество сравнений = " << C << endl;;
			break;
		}
		else {
			continue;
		}
	}
 }
 

