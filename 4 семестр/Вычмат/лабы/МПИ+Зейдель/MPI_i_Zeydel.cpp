#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


int main() {
	setlocale(LC_ALL, "RUS");
	int i, j, l, m, t, p, n = 3;
	double eps, Steps, Sum = 0, a, S = 0, b, temp = 0;
	double mas[n][n+1];
	double A[3][3];
	double B[3];
	double C[3][3];
	double E[3][3];
	double z[3];
	double x[3];
	double y[3];
	mas[0][0] = 5;
	mas[0][1] = -1;
	mas[0][2] = 2;
	mas[0][3] = 3;
	mas[1][0] = -2;
	mas[1][1] = -10;
	mas[1][2] = 3;
	mas[1][3] = -4;
	mas[2][0] = 1;
	mas[2][1] = 2;
	mas[2][2] = 5;
	mas[2][3] = 12;
	cout << "Матрица:"<<endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf (" %6.2f ", mas[i][j]);
		printf ("| %6.2f \n", mas[i][j]);
	}
	cout << endl << endl;
	
	int counter = 0;
	for(int i = 0; i < n; i++) {
		int zeros = 0;
		for(int j = 0; j < n+1; j++) {
			if(mas[i][j] == 0) {
				zeros++;
			}
		}
		if(zeros != n+1) {
			counter++;
		}
	}
	cout << "Ранг матрицы : " << counter << endl;
	
	cout << endl << "=========================================" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n + 1; j++) {
			if (i != j) {
				mas[i][j] = mas[i][j] / mas[i][i];
			}
		}
		mas[i][i] /= mas[i][i];
	}
	cout << endl;
	cout << "Единичная матрица" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf (" %6.2f ", mas[i][j]);
		printf ("| %6.2f \n", mas[i][j]);
	}
	cout << endl << "=========================================" << endl;
	for ( i = 0; i < 3; ++i) {
		for ( j = 0; j < 3; ++j) {
			A[i][j] = mas[i][j];
		}
	}

	cout << endl << "Матрица A" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf (" %6.2f ", A[i][j]);
		cout << endl;
	}
	cout << endl << "=========================================" << endl;

	cout << endl << "Матрица B" << endl;
	for ( t = 0; t < 3; t++) {
		B[t] = mas[t][3];
	}

	for ( i = 0; i < 3; ++i) {
		S = fabs(B[i]);
		if (S > b)
			b = S;
	}
	cout << "Норма b = " << b << endl;

	for (t = 0; t < 3; t++) {
		printf (" %6.2f ", B[t]);
		cout << endl;
	}
	cout << endl << "=========================================" << endl;

	cout << endl << "Матрица C" << endl;
	for ( i = 0; i < 3; i++) {
		for ( j = 0; j < 3; j++) {
			if (i != j) {
				C[i][j] = A[i][j];
			}
		}
		C[i][i] = 0;
	}

	for ( i = 0; i < 3; i++) {
		Sum = 0;
		for ( j = 0; j < 3; j++) {
			Sum += fabs(C[i][j]);
		}
		if (Sum > a)
			a = Sum;
	}
	cout << "Норма C = " << a << endl;

	for ( i = 0; i < n; i++) {
		for ( j = 0; j < n; j++)
			printf (" %6.2f ", C[i][j]);
		cout << endl;
	}
	cout << endl << "=========================================" << endl;

	cout << endl << "Матрица E" << endl;
	for ( i = 0; i < 3; i++) {
		for ( j = 0; j < 3; j++) {
			if (i != j) {
				E[i][j] = 0;
			}
		}
		E[i][i] = 1;
	}
	for ( i = 0; i < n; i++) {
		for ( j = 0; j < n; j++)
			printf (" %6.2f ", E[i][j]);
		cout << endl;
	}
	cout << endl << "=========================================" << endl;

	for (l = 0; l < 3; l++) {
		z[l] = 0;
	}
	cout << "Eps = ";
	cin >> eps;
	Steps = log((1 - a) / b * eps) / log(a) + 1;
	cout << "N = " << Steps << endl << endl;

	cout << "-----------------------" << endl;
	cout << "Метод простых итераций|" << endl;
	cout << "-----------------------" << endl;
	for (int j1 = 0; j1 < Steps; j1++) {    
		for ( i = 0; i < 3; i++) {
			for ( j = 0; j < 3; j++) {
				temp += C[i][j] * z[j];    //перемножение строки на столбец
			}
			x[i] = B[i] - temp;    // формула x = b - Cx0
			temp = 0;
		}
		for (int i1 = 0; i1 < 3; i1++) {
			z[i1] = x[i1];           // забиваем прошлую матрицу (z будет прошлой матрицой, чтобы посчитать следующую)
		}
		for ( m = 0; m < 3; m++) {
			cout << "x: " << x[m] << endl;
		}
		cout << endl;
	}
	
	
	for (l = 0; l < 3; l++) {
		y[l] = 0;
	}
	cout << "--------------" << endl;
	cout << "Метод Зейделя|" << endl;
	cout << "--------------" << endl;
	for (int j1 = 0; j1 < Steps; j1++) {    
		for ( i = 0; i < 3; i++) {
			for ( j = 0; j < 3; j++) {
				temp += C[i][j] * y[j];
			}
			y[i] = B[i] - temp;
			temp = 0;
		}
		for ( m = 0; m < 3; m++) {
			cout << "y: " << y[m] << endl;
		}
		cout << endl;
	}
	return 0;
}
