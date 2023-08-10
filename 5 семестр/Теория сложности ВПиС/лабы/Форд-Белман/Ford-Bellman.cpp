#include <iostream>
#include <iomanip>
#include <fstream> 
#define inf 99999

using namespace std;

void puti_(int** A, int j, int k, int n);
void FordBellman(int** C, int n, int start);

int main() {
	int n, start;
	ifstream input("input.txt");
	input >> n;
	int **C = new int* [n];
	for (int i = 0; i < n; i++) {
		C[i] = new int[n] {};
	}
	for (int i = 0; i < n + 1; i++)
		cout << setw(4) << i;
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(4) << i + 1;
		for (int j = 0; j < n; j++) {
			input >> C[i][j];
			if (C[i][j] == inf)
				cout << setw(4) << "-";
			else cout << setw(4) << C[i][j]; 
		}
		cout << endl;
	}
	input.close();
	cout << "\nStart Node: ";
	cin >> start;
	start--;
	cout << endl;
	if (start >= 0 && start < n)
		FordBellman(C, n, start);
	return 0;
}

void puti_(int** A, int j, int k, int n){
	for (int s = 1; s < n; s++)
	{
		if (A[k][s] != (-1))
			A[j][s] = A[k][s];
		else
		{
			A[j][s] = j;
			break;
		}
	}
}

void FordBellman(int** C, int n, int start){
	int** D = new int* [n + 1];
	int** puti = new int* [n];
	int min;
	for (int i = 0; i < n; i++)
	{
		D[i] = new int[n] {};
		puti[i] = new int[n] {};
	}

	for (int i = 0; i < n; i++)
	{
		if (i == start)
			D[0][i] = 0;
		else
			D[0][i] = inf;
	}

	cout << "D(0)=(";
	for (int l = 0; l < n; l++)
	{
		if (D[0][l] == inf)
			cout << setw(4) << "-";
		else cout << setw(4) << D[0][l];
	}
	cout << ")" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			puti[i][j] = -1;
		puti[i][0] = start;
	}
	int path_ban = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			min = D[i - 1][j];
			for (int k = 0; k < n; k++)
			{
				if (min > D[i - 1][k] + C[k][j])
				{
					min = D[i - 1][k] + C[k][j];
					puti_(puti, j, k, n);
				}
			}
			D[i][j] = min;
		}
		cout << "D(" << i << ")=(";
		for (int l = 0; l < n; l++)
		{
			if (D[i][l] == inf)
				cout << setw(4) << "-";
			else cout << setw(4) << D[i][l];
			//cout << setw(4) << D[i][l];
		}
		cout << ")" << endl;
		int flag = 0;
		for (int j = 0; j < n; j++) {
			if (D[i - 1][j] == D[i][j]) flag++;
		}
		/*for (int v = 0; v < n; v++){
			for (int j = 0; j < n; j++){
				if (puti[v][j] > -1){
					cout << puti[v][j] + 1 << " ";
				}
			}
		cout << endl;
		}
		cout << endl;
		cout << endl;*/
		path_ban = i;
		if (flag == n) break;
	}
	cout << endl;
	for (int j = 0; j < n; j++) {
		cout << "path (" << start+1 << " -> " << j + 1 << ") - ";
		if(D[path_ban][j]==inf){
			cout << "no path" << endl;
		}
		else{
			for (int i = 0; i < n; i++)
			{
				if (puti[j][i] > -1)
				{
					cout << puti[j][i] + 1 << " ";
				}
			}
			cout << endl;
		}
	}
}
