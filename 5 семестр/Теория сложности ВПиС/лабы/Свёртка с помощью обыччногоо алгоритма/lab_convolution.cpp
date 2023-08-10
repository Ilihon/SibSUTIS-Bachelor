#include <iostream>

using namespace std;

int N;
int *C;					
int t;
int A[] = {1,2,3};	
int n = 3;
int B[] = {4,5,6,7,8};		
int m = 5;
int oper = 0;

int main()
{
	setlocale(0, "");
	cout << "Массив A" <<endl;
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl << endl;
	cout << "Массив B" <<endl;
	for (int i = 0; i < m; i++)
		cout << B[i] << " ";
	cout << endl << endl;
	t = n + m - 1;
	C = new int[t];
	for (int i = 0; i < t; i++)
		C[i] = 0;
	int tmp = 0;
	int k = 0;
	int l = 0;
	cout << "0) ";
	for (int i = 0; i < t; i++) {
		l = 0;
		for (int j = 0; j < n; j++) {
			for (int e = 0; e < m; e++) {
				if (e == 0 && j == 0 && i != 0)
					cout << "=" << C[i - 1] << endl << i << ") ";
				if (j + e == i) {
					l++;
					tmp = A[j] * B[e];
					oper++;
					C[i] += tmp;
					cout << A[j] << "*" << B[e];
					if (j + 1 < n && l<=i){
					cout << "+";	
					oper++;
					} 
					tmp = 0;
				}
			}
			
		}
	}
	cout << "=" << C[t - 1] << endl;
	cout << endl<< endl << "oper = " << oper <<endl << "C: ";
	for (int i = 0; i < t; i++)
		cout << C[i] << " ";
	return 0;
}
