#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265359

using namespace std;

struct complex_number {
	double Re;
	double Im;
};


int A[] = {1,2,0,0};	
int n = 4;
//int A[] = {1,0,1,0,1};
//int n = 5;
//int A[] = {1,7,4};
//int n = 3;	
//int A[] = {1,2,3,4,5,6,7,8};
//int n = 8;	
//int* A;
//int n = 512;
int B[] = {1,2,3,4};		
int m = 4;
//int B[] = {1,0,1,0,1};
//int m = 5;
//int B[] = {0,9,4};
//int m = 3;	
//int B[] = {1,2,3,4,5,6,7,8};
//int m = 8;	
//int* B;
//int m = 512;
int oper = 0;

void Convolution();
void Print_complex_number(complex_number);
complex_number *Direct(int *, int);
complex_number *Back(complex_number *, int);
complex_number *PBDF_Direct(int *, int);
complex_number* PBDF_Back(complex_number *, int);

complex_number AddComplex(complex_number A, complex_number B) {
	complex_number C;
	C.Re = (A.Re * B.Re - A.Im * B.Im);
	C.Im = (A.Re * B.Im + A.Im * B.Re);
	return C;
}

int main()
{
	setlocale(LC_ALL, "");
/*
	A = new int[n]; B = new int[m];
	for (int i = 0; i < n; i++) {
		A[i] = rand() % (10 );
	}
	for (int i = 0; i < m; i++) {
		B[i] = rand() % (10 );
	}*/
	cout << "Массив A" <<endl;
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl << endl;
	cout << "Массив B" <<endl;
	for (int i = 0; i < m; i++)
		cout << B[i] << " ";
	cout << endl;
	Convolution();
	oper=0;
	int oper_res = 0;
	double *C = new double[2*n] {};

	int *longA = new int[2 * n]{};
	int *longB = new int[2 * n]{};
	for (int i = 0; i < n; i++) {
		longA[i] = A[i];
	}
	for (int i = 0; i < m; i++) {
		longB[i] = B[i];
	}
	
	//////////////////////////////////////////////////////////////////////Дискретное Фурье
	complex_number *fa = Direct(longA, 2 * n);
	cout << "F(a):" << endl;
	for (int i = 0; i < 2 * n; i++)
		Print_complex_number(fa[i]);
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl;
	oper=0;
	
	complex_number *fb = Direct(longB, 2 * n);
	cout << "F(b):" << endl;
	for (int i = 0; i < 2 * n; i++)
		Print_complex_number(fb[i]);
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl;
	oper=0;

	complex_number *fc = new complex_number[2 * n]{};
	for (int i = 0; i < 2*n; i++) {
		fc[i] = AddComplex(fa[i], fb[i]);
		fc[i].Re *= 2.0*n;
		fc[i].Im *= 2.0*n;
		oper+=1;
	}

	cout << "F(c):" << endl;
	for (int i = 0; i < 2 * n; i++)
		Print_complex_number(fc[i]);
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl;
	oper=0;
	cout << endl;
	fc = Back(fc, 2 * n);
	cout << "c:" << endl;
	for (int i = 0; i < 2 * n-1; i++)
		Print_complex_number(fc[i]);
	cout << endl << "Ответ: " << endl;
	for (int i = 0; i < 2*n-1; i++) {
		C[i] = fc[i].Re;
		cout << fixed << setprecision(4) << setw(5) << C[i] << " ";
	}
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl<< "oper_result=" << oper_res<<endl<<endl;
	//////////////////////////////////////////////////////////////////////Полу-быстрое Фурье
	oper=0;
	oper_res=0;
	complex_number *faPBDF = PBDF_Direct(longA, 2 * n);
	cout << "F(a):" << endl;
	for (int i = 0; i < 2 * n; i++)
		Print_complex_number(faPBDF[i]);
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl;
	oper=0;
	
	complex_number *fbPBDF = PBDF_Direct(longB, 2 * n);
	cout << "F(b):" << endl;
	for (int i = 0; i < 2 * n; i++)
		Print_complex_number(fbPBDF[i]);
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl;
	oper=0;

	complex_number *fcPBDF = new complex_number[2 * n]{};
	for (int i = 0; i < 2*n; i++) {
		fcPBDF[i] = AddComplex(faPBDF[i], fbPBDF[i]);
		fcPBDF[i].Re *= 2.0*n;
		fcPBDF[i].Im *= 2.0*n;
		oper+=1;
	}

	cout << "F(c):" << endl;
	for (int i = 0; i < 2 * n; i++)
		Print_complex_number(fcPBDF[i]);
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl;
	oper=0;
	cout << endl;
	fcPBDF = PBDF_Back(fcPBDF, 2 * n);
	cout << "c:" << endl;
	for (int i = 0; i < 2 * n-1; i++)
		Print_complex_number(fcPBDF[i]);
	cout << endl << "Ответ: " << endl;
	for (int i = 0; i < 2*n-1; i++) {
		C[i] = fcPBDF[i].Re;
		cout << fixed << setprecision(4) << setw(5) << C[i] << " ";
	}
	cout << endl<< "oper=" << oper<<endl;
	oper_res+=oper;
	cout << endl<< "oper_result=" << oper_res<<endl;
	
	system("pause");
	return 0;
}

complex_number *Direct(int *mas, int N) {
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

complex_number *PBDF_Direct(int* mas, int N)
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
				oper+=1;
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
				direct[k1 + p1 * k2].Re += (A[k1 + p1 * j2].Re * cos((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))) - A[k1 + p1 * j2].Im * sin((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))));
				direct[k1 + p1 * k2].Im += (A[k1 + p1 * j2].Re * sin((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))) + A[k1 + p1 * j2].Im * cos((double)(-2.0 * pi * j2 / N * (k1 + p1 * k2))));
				oper+=1;
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
				oper+=1;
			}
		}
	}
	
	complex_number *back = new complex_number[N]{};
	for (int k1 = 0; k1 < p1; k1++) {
		for (int k2 = 0; k2 < p2; k2++) {
			for (int j2 = 0; j2 < p2; j2++) {
				back[k1 + p1 * k2].Re += A[k1 + p1 * j2].Re * cos((double)(2.0 * pi * j2 / N * (k1 + p1 * k2))) - A[k1 + p1 * j2].Im * sin((double)(2.0 * pi * j2 / N * (k1 + p1 * k2)));
				back[k1 + p1 * j2].Im += A[k1 + p1 * j2].Im * cos((double)(2.0 * pi * j2 / N * (k1 + p1 * k2))) + A[k1 + p1 * j2].Re * sin((double)(2.0 * pi * j2 / N * (k1 + p1 * k2)));
				oper+=1;
			}
		}
	}
	return back;
}


void Convolution(){
	int t = n + m - 1;
	int C[t];
	for (int i = 0; i < t; i++)
		C[i] = 0;
	int tmp = 0;
	int k = 0;
	int l = 0;
	cout << endl << "0) ";
	for (int i = 0; i < t; i++) {
		l = 0;
		for (int j = 0; j < n; j++) {
			for (int e = 0; e < m; e++) {
				//if (e == 0 && j == 0 && i != 0)
				//	cout << "=" << C[i - 1] << endl << i << ") ";
				if (j + e == i) {
					l++;
					tmp = A[j] * B[e];
					oper++;
					C[i] += tmp;
					//cout << A[j] << "*" << B[e];
					if (j + 1 < n && l<=i){
						//cout << "+";	
						oper++;
					} 
					tmp = 0;
				}
			}
			
		}
	}
	//cout << "=" << C[t - 1] << endl;
	cout << endl << "oper = " << oper <<endl << "C: ";
	for (int i = 0; i < t; i++)
		cout << C[i] << " ";
	cout << endl << endl;
}


void Print_complex_number(complex_number num) {
	printf("%8.6f  + (%9.8f) * i \n", num.Re, num.Im);
}
