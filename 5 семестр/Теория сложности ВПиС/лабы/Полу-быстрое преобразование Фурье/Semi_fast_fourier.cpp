#include <iostream>
#include <iomanip>
#include <math.h>

#define pi 3.1415926

using namespace std;

int oper = 0;

struct complex_number {
	double Re;
	double Im;
};

void Print_complex_number(complex_number);
complex_number AddComplex(complex_number, complex_number);
complex_number *Direct(double *, int);
complex_number *Back(complex_number *, int);

int main()
{
	setlocale(0, "");
	int N;
	printf ("Введите размер вектора: ");
	scanf("%d", &N);
	cout << endl;
	double *mas = new double[N];
	for (int i=0;i<N;i++){
    	cin >> mas[i];
	}
	printf ("Начальные:\n(");
	for (int i = 0; i < N; i++) {
		cout << mas[i] << " ";
	}
	cout << ")" << endl;
	
	complex_number *X = Direct(mas, N);
	cout << "Прямое преобразование:" << endl;
	for (int i = 0; i < N; i++) {
		Print_complex_number(X[i]);
	}
	cout << "oper=" << oper << endl;	
	
	oper = 0;
	complex_number *x = Back(X, N);
	cout << "\nОбратное преобразование:" << endl;
	for (int i = 0; i < N; i++) {
		Print_complex_number(x[i]);
	}	
	cout << "oper=" << oper << endl;
	
	system("pause");
	return 0;
}

complex_number* Direct(double* mas, const int N)
{
	int p1 = 1, p2 = N;
	int p1_p2 = p2 - p1;
	for (int i = p1; i < sqrt(N)+1; i++) {
		if (N % i == 0 && N/i - i < p1_p2) {
			p1 = i;
			p2 = N / p1;
		}
	}
	cout << "p1 = " << p1 << endl << "p2 = " << p2 << endl;
	complex_number *A = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++) {
		for (int j2 = 0; j2 < p2; j2++) {
			for (int j1 = 0; j1 < p1; j1++) {
				A[k1 + p1 * j2].Re += mas[j2 + p2 * j1] * cos((double)(-2.0 * pi * j1 * k1 / p1));
				A[k1 + p1 * j2].Im += mas[j2 + p2 * j1] * sin((double)(-2.0 * pi * j1 * k1 / p1));
				oper+=5;
			}
			A[k1 + p1 * j2].Re /= p1;
			A[k1 + p1 * j2].Im /= p1; 
		}
	}
	cout << endl;
	complex_number *direct = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++){
		for (int k2 = 0; k2 < p2; k2++){
			for (int j2 = 0; j2 < p2; j2++) {
				direct[k1 + p1 * k2].Re += (A[k1 + p1 * j2].Re * cos((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))) 
				- A[k1 + p1 * j2].Im * sin((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))));
				direct[k1 + p1 * k2].Im += (A[k1 + p1 * j2].Re * sin((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))) 
				+ A[k1 + p1 * j2].Im * cos((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))));
				oper+=5;
			}
			direct[k1 + p1 * k2].Re /= p2;
			direct[k1 + p1 * k2].Im /= p2;
		}
	}
	return direct;
}

complex_number *Back(complex_number *mas, int N) {
	int p1 = 1, p2 = N;
	int p1_p2 = p2 - p1;
	for (int i = p1; i < sqrt(N)+1; i++) {
		if (N % i == 0 && N/i - i < p1_p2) {
			p1 = i;
			p2 = N / p1;
		}
	}
	cout << "p1 = " << p1 << endl << "p2 = " << p2 << endl;

	complex_number *A = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++){
		for (int k2 = 0; k2 < p2; k2++){
			for (int j2 = 0; j2 < p2; j2++) {
				A[k1 + p1 * k2].Re += (mas[k1 + p1 * j2].Re * cos((double)(2.0 * pi * j2 / N * (k1 + p1 * k2)))
				- mas[k1 + p1 * j2].Im * sin((double)(2.0 * pi * j2 / N * (k1 + p1 * k2))));
				A[k1 + p1 * k2].Im += (mas[k1 + p1 * j2].Re * sin((double)(2.0 * pi * j2 / N * (k1 + p1 * k2)))
				+ mas[k1 + p1 * j2].Im * cos((double)(2.0 * pi * j2 / N * (k1 + p1 * k2))));
				oper+=5;
			}
		}
	}
	
	complex_number *back = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++) {
		for (int j2 = 0; j2 < p2; j2++) {
			for (int j1 = 0; j1 < p1; j1++) {
				back[k1 + p1 * j2].Re += A[j2 + p2 * j1].Re * cos((double)(2.0 * pi * j1 * k1 / p1)) - A[j2 + p2 * j1].Im * sin((double)(2.0 * pi * j1 * k1 / p1));
				back[k1 + p1 * j2].Im += A[j2 + p2 * j1].Im * cos((double)(2.0 * pi * j1 * k1 / p1)) + A[j2 + p2 * j1].Re * sin((double)(2.0 * pi * j1 * k1 / p1));
				oper+=5;
			}
		}
	}
	return back;
}

void Print_complex_number(complex_number num) {
	printf("%8.4f  + (%12.6f) * i \n", num.Re, num.Im);
}
