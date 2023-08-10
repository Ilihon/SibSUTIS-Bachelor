#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int oper_add = 0;
int oper_mult = 0;
int n;

void Matrix_Initialization(long int**, long int**, int);
long int** Simple_multiplication_matrix(long int**, long int**, int);
long int** add(long int**, long int**, int, int);
long int** Fast_multiplication_matrix(long int**, long int**, int);
void Print_matrix(long int**, int);

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Размер матриц: ";
	cin >> n;
	long int** A = new long int* [n];
	long int** B = new long int* [n];
	long int** C = new long int* [n];
	Matrix_Initialization(A, B, n);
	cout << "\nМатрица A:" << endl;
	Print_matrix(A, n);
	cout << "\nМатрица B:" << endl;
	Print_matrix(B, n);
	cout << endl;

	cout << "Обычное умножение:";
	C = Simple_multiplication_matrix(A, B, n);
	cout << "\nМатрица C:" << endl;
	Print_matrix(C, n);
	cout << "Трудоемкость: " << oper_add + oper_mult << "\nСложений: " << oper_add << "\nУмножений: " << oper_mult << endl << endl;
	oper_add = 0;
	oper_mult = 0;
	cout << "Быстрое умножение:";
	C = Fast_multiplication_matrix(A, B, n);
	cout << "\nМатрица C:" << endl;
	Print_matrix(C, n);
	cout << "Трудоемкость: " << oper_add + oper_mult << "\nСложений: " << oper_add << "\nУмножений: " << oper_mult << endl << endl;
	system("pause");
	return 0;
}

void Matrix_Initialization(long int** A, long int** B, int n) {
	for (int i = 0; i < n; i++) {
		A[i] = new long int[n];
		B[i] = new long int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = pow(-1,i + j);
			B[i][j] = i - j;
		}
	}
}

long int** Simple_multiplication_matrix(long int** A, long int** B, int n) {
	long int** C = new long int* [n];
	for (int i = 0; i < n; i++) {
		C[i] = new long int[n] {};
		for (int j = 0; j < n; j++)
			C[i][j] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
				oper_add++;
				oper_mult++;
			}
		}
	}
	return C;
}

long int** add(long int** A, long int** B, int n, int k) {
	long int** C = new long int* [n];
	for (int i = 0; i < n; i++) {
		C[i] = new long int[n] {};
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] + k * B[i][j];
			oper_add++;
		}
	}
	return C;
}

long int** Fast_multiplication_matrix(long int**A, long int**B, int n) {
	int h = n / 2;
	long int** C = new long* [n];
	for (int i = 0; i < n; i++) {
		C[i] = new long int[n] {};
	}
	if(n % 2 ==1 ){
		return Simple_multiplication_matrix(A,B,n);
	}
	else {
		/*
		cout << endl << endl;
		Print_matrix(A, n);
		cout << endl << endl;
		Print_matrix(B, n);
		cout << endl << endl;*/
		long int*** Ak  = new long int** [4];
		long int*** Bk = new long int** [4];
		long int*** Ck = new long int** [4];
		long int*** M = new long int** [7];
		long int** rA = new long int* [n];
		long int** rB = new long int* [n];
		for (int i = 0; i < n; i++) {
			rA[i] = A[i] + h;
			rB[i] = B[i] + h;
		}
		Ak[0] = A;
		Ak[1] = rA;
		Ak[2] = A + h;
		Ak[3] = rA + h;
		Bk[0] = B;
		Bk[1] = rB;
		Bk[2] = B + h;
		Bk[3] = rB + h;
		M[0] = Fast_multiplication_matrix(add(Ak[1], Ak[3], h, -1), add(Bk[2], Bk[3], h, 1), h);
		M[1] = Fast_multiplication_matrix(add(Ak[0], Ak[3], h, 1), add(Bk[0], Bk[3], h, 1), h);
		M[2] = Fast_multiplication_matrix(add(Ak[0], Ak[2], h, -1), add(Bk[0], Bk[1], h, 1), h);
		M[3] = Fast_multiplication_matrix(add(Ak[0], Ak[1], h, 1), Bk[3], h);
		M[4] = Fast_multiplication_matrix(Ak[0], add(Bk[1], Bk[3], h, -1), h);
		M[5] = Fast_multiplication_matrix(Ak[3], add(Bk[2], Bk[0], h, -1), h);
		M[6] = Fast_multiplication_matrix(add(Ak[2], Ak[3], h, 1), Bk[0], h);
		Ck[0] = add(add(add(M[0], M[1], h, 1), M[3], h, -1), M[5], h, 1);
		Ck[1] = add(M[3], M[4], h, 1);
		Ck[2] = add(M[5], M[6], h, 1);
		Ck[3] = add(add(add(M[1], M[2], h, -1), M[4], h, 1), M[6], h, -1);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < h; j++) {
				C[i][j] = Ck[0][i][j];
				C[i][j + h] = Ck[1][i][j];
				C[i + h][j] = Ck[2][i][j];
				C[i + h][j + h] = Ck[3][i][j];
			}
		}
		return C;
	}
}

void Print_matrix(long int** matrix, int n) {
	int otstup = 3;
	if (n <= 15) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(otstup) << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		int col = 5;
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < col; j++) {
				cout << setw(otstup) << matrix[i][j] << " ";
			}
			cout << setw(otstup) << "..." << " ";
			cout << setw(otstup) << matrix[i][n - 1] << endl;
		}
		for (int j = 0; j < col + 2; j++) {
			cout << setw(otstup) << "..." << " ";
		} cout << endl;
		for (int j = 0; j < col; j++) {
			cout << setw(otstup) << matrix[n - 1][j] << " ";
		}
		cout << setw(otstup) << "..." << " ";
		cout << setw(otstup) << matrix[n - 1][n - 1] << endl;
	}
}

