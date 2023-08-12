#include <iostream>
#include <clocale>
#include <stdlib.h>

using namespace std;

const int p = 5, n = 20, m = 30;;
void SS(int **A, int n);


int main() {
	setlocale(0, "");
	int A[n], B[m], i, X;
	int m;
	int **Q = new int*[p];
	for (i = 0; i < p; i++) {
		cin >> m;
		Q[i] = new int[m + 1];
		Q[i][0] = m ;
		for (int j = 1; j < m + 1; j++) {
			Q[i][j] = rand() % 4;
		}
	}
	for (i = 0; i < p; i++) {  ///вывож
		for (int j = 1; j < Q[i][0] + 1; j++) {
			cout << Q[i][j] << " ";
		}
		cout << endl;
	}

	SS(Q, p);

	for (i = 0; i < p; i++) {
		delete[] Q[i];
	}
	system("pause");
	return 0;
}

void SS(int **A, int n) {
	int S = 0, i, j;
	cout << endl;
	for (i = 0; i < n; i++) {
		for (j = 1; j < A[i][0]+1; j++) {
			S += A[i][j];
		}
		cout << "Сумма элементов строк:  " << S << endl;
		S = 0;
	}
 }

