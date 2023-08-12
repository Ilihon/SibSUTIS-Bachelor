#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <locale>

using namespace std;

void zad_a(int **A, int N, int *&B);
void zad_b(int **A, int N, int *&B);
void zad_d(int** A, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n);
void zad_c(int** A, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n);


const int N = 5;

int main()
{
	setlocale(LC_ALL, "Russian");
	
 	cout<<" Задание 1"<<endl;
	int **A, *B;
	A = new int *[N];
	B = new int[N*N];
	for(int i = 0; i < N; i++){
		A[i] = new int[N];
		for(int j = 0; j < N; j++){
			A[i][j] =  rand() % 10 + 1;
			cout<<A[i][j]<<"\t";
 		}
		cout<<endl;
	}
	
	zad_a(A, N, B);
	cout << endl<<"a) ";
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	
	zad_b(A, N, B);
	cout << endl<<"b) ";
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	
	zad_c(A, N, B, 0, N - 1, 0, N - 1, N * N - 1);
	cout << endl<<"c) ";
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	
	zad_d(A, N, B, 0, N, 0, N, 0);
	cout << endl<<"д) ";
	for(int i = 0; i < N*N; i++) cout<<B[i]<<" ";
	
	//Задание 2
	int **P = new int*[5];
	cout<<endl<<endl<<endl<<" Задание 2"<<endl;
	for(int i = 0; i < N; i++){	
		int g = rand() % 10+1;
		P[i] = new int[g];
		for(int j = 0; j < g; j++){
			P[i][j] = rand() % 10+1;
			cout<<P[i][j]<<"\t";
		}
		cout<<endl;
	}
	////////////////////////////////////////
	
	system("PAUSE");
	return 1;
}

void zad_a(int **A, int N, int *&B){
	int k = 0, j = 0, pos = 0;
	for(int i = N - 1; i >= 0; i--){
		k = i;
		j = 0;
		while(1)
		{
			if(k >= N || j >= N) break;
			B[pos++] = A[j][k];
			k++;
			j++;
		}
	}
	for(int i = 1; i < N; i++){
		k = 0;
		j = i;
		while(1)
		{
			if(k >= N || j >= N) break;
			B[pos++] = A[j][k];
			k++;
			j++;
		}
	}
}

void zad_b(int **A, int N, int *&B){
	int k = 0, j = 0, pos = 0;
	for(int i = 0; i < N; i++){
		k = i;
		j = 0;
		while(1)
		{
			if(k < 0 || j >= N) break;
			B[pos++] = A[j][k];
			k--;
			j++;
		}
	}
	for(int i = 1; i < N; i++){
		k = N - 1;
		j = i;
		while(1)
		{
			if(k < 0 || j >= N) break;
			B[pos++] = A[j][k];
			k--;
			j++;
		}
	}
}

void zad_c(int** A, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n)
{
	if((i_left > i_right) && (j_up > j_down)) return;
	zad_c(A, N, B, i_left + 1, i_right - 1, j_up + 1, j_down - 1, n - 2 * ((j_down - j_up) + (i_right - i_left)));
	for(int i = i_left; i <= i_right; i++){
		B[n--] = A[j_up][i];
	}
	for(int i = j_up + 1; i <= j_down; i++){
		B[n--] = A[i][i_right];
	}
	for(int i = i_right - 1; i >= i_left; i--){
		B[n--] = A[j_down][i];
	}
	for(int i = j_down - 1; i > j_up; i--){
		B[n--] = A[i][i_left];
	}
}

void zad_d(int** A, int N, int *&B, int i_left, int i_right, int j_up, int j_down, int n){
	if(j_up >= j_down && i_left >= i_right) return;
	for(int i = i_left; i < i_right; i++){
		B[n++] = A[j_up][i];
	}
	j_up++;
	for(int i = j_up; i < j_down; i++){
		B[n++] = A[i][i_right - 1];
	}
	i_right--;
	for(int i = i_right - 1; i >= i_left; i--){
		B[n++] = A[j_down-1][i];
	}
	j_down--;
	for(int i = j_down - 1; i >= j_up; i--){
		B[n++] = A[i][i_left];
	}
	i_left++;
	zad_d(A, N, B, i_left, i_right, j_up, j_down, n);
}

