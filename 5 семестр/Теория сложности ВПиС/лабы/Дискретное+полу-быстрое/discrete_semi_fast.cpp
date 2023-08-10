#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>

#define pi  3.14159265359
int oper = 0;

using namespace std;

struct complex_number {
	double Re;
	double Im;
};

void Print_complex_number(complex_number);
complex_number *Direct(double *, int);
complex_number *Back(complex_number *, int);
complex_number *PBDF_Direct(double *, int);
complex_number* PBDF_Back(complex_number *, int);

int main()
{
	setlocale(0, "");
	int N;
	printf ("Введите размер массива: ");
	scanf("%d", &N);
	double mas[N];
	for (int i=0;i<N;i++){
    	cin >> mas[i];
	}
	cout << "Оригинальный массив:\n(";
	for (int i = 0; i < N; i++) {
		cout << mas[i] << " ";
	}
	cout << ")" << endl;
	complex_number *X = Direct(mas, N);
	cout << "Прямое преобразование (дискретное Фурье):" << endl;
	for (int i = 0; i < N; i++) {
		Print_complex_number(X[i]);
	}
	cout << "oper=" << oper << endl << endl;
	oper =0;
	cout << "\nОбратное преобразование (дискретное Фурье):" << endl;
	complex_number *x = Back(X, N);
	for (int i = 0; i < N; i++) {
		Print_complex_number(x[i]);
	}
	cout << "oper=" << oper << endl << endl;
	
	oper = 0;
	X = PBDF_Direct(mas, N);
	cout << "Прямое преобразование (полу-быстрое Фурье):" << endl;
	for (int i = 0; i < N; i++) {
		Print_complex_number(X[i]);
	}
	cout << "oper=" << oper << endl << endl;	

	
 	oper = 0;
	x = PBDF_Back(X, N);
	cout << "\nОбратное преобразование (полу-быстрое Фурье):" << endl;
	for (int i = 0; i < N; i++) {
		Print_complex_number(x[i]);
	}	
	cout << "oper=" << oper << endl << endl;
	
	
	system("pause");
	return 0;
}

complex_number *Direct(double *mas, int N) {
	complex_number *direct = new complex_number[N];
	for (int k = 0; k < N; k++) {
		direct[k].Re = 0;
		direct[k].Im = 0;
		for (int n = 0; n < N; n++) {
			direct[k].Re += mas[n] * cos((double)(-2.0 * pi * k * n / N));
			direct[k].Im += mas[n] * sin((double)(-2.0 * pi * k * n / N));
			//cout << "k="<< k << " - n=" << n << " - Re=" << direct[k].Re << " - Im=" << direct[k].Im << endl;
			oper+=5;
		}
		direct[k].Re /= N;
		direct[k].Im /= N;
		//cout << endl;
	}
	return direct;
}


complex_number *Back(complex_number *mas, int N) {
	complex_number *back = new complex_number[N];
	for (int k = 0; k < N; k++) {
		back[k].Im = 0;
		back[k].Re = 0;
		for (int n = 0; n < N; n++) {
			back[k].Re += mas[n].Re * cos((double)(2.0 * pi*n*k / N)) - mas[n].Im * sin((double)(2.0*pi*k*n / N));
			back[k].Im += mas[n].Im * cos((double)(2.0 * pi*n*k / N)) + mas[n].Re * sin((double)(2.0*pi*k*n / N));
			oper+=5;
		}
	}
	return back;
}


complex_number* PBDF_Direct(double* mas, int N)
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
			//cout << k1 << ") " << "Re=" << A[k1 + p1 * j2].Re << " - Im=" << A[k1 + p1 * j2].Im << endl;
		}
	}
	cout << endl;
	complex_number *direct = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++){
		for (int k2 = 0; k2 < p2; k2++){
			for (int j2 = 0; j2 < p2; j2++) {
				direct[k1 + p1 * k2].Re += (A[k1 + p1 * j2].Re * cos((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))) - A[k1 + p1 * j2].Im * sin((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))));
				direct[k1 + p1 * k2].Im += (A[k1 + p1 * j2].Re * sin((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))) + A[k1 + p1 * j2].Im * cos((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))));
				oper+=5;
			}
			direct[k1 + p1 * k2].Re /= p2;
			direct[k1 + p1 * k2].Im /= p2;
		}
	}
	return direct;
}

complex_number* PBDF_Back(complex_number *mas, int N)
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
	for (int k1 = 0; k1 < p1; k1++){
		for (int j2 = 0; j2 < p2; j2++){
			for (int j1 = 0; j1 < p1; j1++) {
				A[k1 + p1 * j2].Re += (mas[j2 + p2 * j1].Re * cos((double)(2.0 * pi * j1 * k1 / p1)) - mas[j2 + p2 * j1].Im * sin((double)(2.0 * pi * j1 * k1 / p1)));
				A[k1 + p1 * j2].Im += (mas[j2 + p2 * j1].Re * sin((double)(2.0 * pi * j1 * k1 / p1)) + mas[j2 + p2 * j1].Im * cos((double)(2.0 * pi * j1 * k1 / p1)));
				oper+=5;
			}
		}
	}
	
	complex_number *back = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++) {
		for (int k2 = 0; k2 < p2; k2++) {
			for (int j2 = 0; j2 < p2; j2++) {
				back[k1 + p1 * k2].Re += A[k1 + p1 * j2].Re * cos((double)(2.0 * pi * j2 / N * (k1 + p1 * k2))) - A[k1 + p1 * j2].Im * sin((double)(2.0 * pi * j2 / N * (k1 + p1 * k2)));
				back[k1 + p1 * k2].Im += A[k1 + p1 * j2].Im * cos((double)(2.0 * pi * j2 / N * (k1 + p1 * k2))) + A[k1 + p1 * j2].Re * sin((double)(2.0 * pi * j2 / N * (k1 + p1 * k2)));
				oper+=5;
			}
		}
	}
	return back;
}

void Print_complex_number(complex_number num) {
	printf("%8.6f  + (%9.8f) * i \n", num.Re, num.Im);
}
