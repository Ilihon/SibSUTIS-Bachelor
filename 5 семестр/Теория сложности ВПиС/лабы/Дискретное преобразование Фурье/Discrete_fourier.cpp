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
	cout << "Прямое преобразование:" << endl;
	for (int i = 0; i < N; i++) {
		Print_complex_number(X[i]);
	}
	cout << endl << oper << endl;
	oper =0;
	cout << "\nОбратное преобразование:" << endl;
	complex_number *x = Back(X, N);
	for (int i = 0; i < N; i++) {
		Print_complex_number(x[i]);
	}
	cout << endl << oper << endl;
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
			cout << "k="<< k << " - n=" << n << " - Re=" << direct[k].Re << " - Im=" << direct[k].Im << endl;
			oper+=5;
		}
		direct[k].Re /= N;
		direct[k].Im /= N;
		cout << endl;
	}
	return direct;
}

complex_number *Back(complex_number *mas, int N) {
	complex_number *back = new complex_number[N];
	complex_number tmpcompl;
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

void Print_complex_number(complex_number num) {
	printf("%8.4f  + (%12.10f) * i \n", num.Re, num.Im);
}
