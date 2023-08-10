#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <sstream>
#include <cmath>
#include <Windows.h>
#include <stdio.h>

using namespace std;

void Print(int** jm, int Up, int Down);

int main() {

    setlocale(LC_ALL, "Russian");
    int i, j, M;
    int n=0;
	ifstream input("input2 - пример методички.txt");
	input >> n;
	int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[2] {};
        input >> matrix[i][0];
        input >> matrix[i][1];
    }
    for (int i = 0; i < n; i++) {
        cout << " [" << matrix[i][0] << "x" << matrix[i][1] << "]";
    }
    cout << endl;
    int* r = new int[n + 1];
    int* mass = new int[n + 1];
    for (int i = 0; i < n; i++) {
        mass[i] = matrix[i][0];
    }
    mass[n] = matrix[n-1][1];

    for (i = 0; i < n + 1; ++i)
        r[i] = mass[i];

    int** f = new int* [n];

    for (i = 0; i < n; ++i) {
        f[i] = new int[n];
        for (j = 0; j < n; ++j)
            f[i][j] = -1;
    }
    for (i = 0; i < n; ++i)
        f[i][i] = 0;

    int t, k, Temp;
    int** jm = new int* [n];

    for (i = 0; i < n; ++i) {
        jm[i] = new int[n];
        for (j = 0; j < n; ++j)
            jm[i][j] = -1;
    }
    int g = 0; 
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << " f(" << i << "," << i << ")=" << g << endl;
    }
   	cout << endl;

    for (t = 1; t < n; t++) {
        for (k = 0; k < n - t; k++) {
            jm[k][k + t] = k;
            f[k][k + t] = f[k][k] + f[k + 1][k + t] + r[k] * r[k + 1] * r[k + t + 1];
            cout << " f(" << k + 1 << "," << k + t + 1 << ") = min(\n\tf[" << k + 1 << "," << k + 1 << "] + f[" << k + 2 << ", " << k + t + 1 << "] + " << r[k] << " * " << r[k+1] << " * " << r[k + t + 1];
            for (j = k + 1; j < k + t; j++) {
                cout << ";" << endl << "\tf[" << k + 1 << "," << j + 1 << "] + f[" << j + 2 << ", " << k + t + 1 << "] + " << r[k] << " * " << r[j + 1] << " * " << r[k + t + 1];
			//	cout << endl;
			//    cout << Temp;
                Temp = f[k][j] + f[j + 1][k + t] + r[k] * r[j + 1] * r[k + t + 1];
                if (Temp <= f[k][k + t]) {
                    jm[k][k + t] = j;
                    f[k][k + t] = Temp;
                }
            }
            cout << ")\n\t=  f[" << k + 1 << "," << j << "]+ f[" << j + 1 << "," << k + t + 1 << "] + " << r[k] << " * " << r[j] << " * " << r[k + t + 1] << " = " << f[k][k + t] << endl;
			/*cout << endl;
		    cout << Temp;
			cout << endl;
		    for (i = 0; i < n; ++i) {
		        for (j = 0; j < n; ++j)
		            //cout << " f[" << i + 1 << "," << j + 1 << "] = " << setw(5) << f[i][j] << setw(4) << "   ";
		            cout << setw(5) << jm[i][j] << " ";
		        cout << endl;
		    }*/
        }
   		cout << endl << "--------------------------------" << endl;
    }

    cout << endl;

    cout << endl;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            //cout << " f[" << i + 1 << "," << j + 1 << "] = " << setw(5) << f[i][j] << setw(4) << "   ";
            cout << setw(5) << f[i][j] << " ";
        cout << endl;
    }
	/*
    cout << endl;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            //cout << " f[" << i + 1 << "," << j + 1 << "] = " << setw(5) << f[i][j] << setw(4) << "   ";
            cout << setw(5) << jm[i][j] << " ";
        cout << endl;
    }
*/
2,3 * 3,5 * 5,2
    cout << endl;
    Print(jm, 0, n - 1);
    cout << endl;
    system("pause");
    return 0;
}

void Print(int** jm, int Up, int Down) {
    switch (Down - Up) {
	    case 0: {
	        cout << " M[" << Up + 1 << "] ";
	        return;
	    }
	    case 1: {
	        cout << "( ";
	        cout << "M[" << Up + 1 << "] * M[" << Down + 1 << "]";
	        cout << " )";
	        return;
	    }
	    default: {
	        cout << "( ";
	        Print(jm, Up, jm[Up][Down]);
	        Print(jm, jm[Up][Down] + 1, Down);
	        cout << " )";
	        return;
	    }
    }
}
