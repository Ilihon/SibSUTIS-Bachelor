#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int random (int N) { return rand()%N; }

void FillInc (int A[], int n); 
void FillDec (int A[], int n); 
void FillRand (int A[], int n); 
void CheckSum (int A[], int n); 
void RunNumber (int A[], int n); 
void PrintMas (int A[], int n); 
void SelectSort (int A[], int n);




int Mprak = 0, Cprak = 0;

main() {
	int n = 10, A[n];

	FillDec (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf (" M(teor)=%d, C(teor)=%d \n", 3*(n-1), (n*n-n)/2);
	SelectSort (A, n);
	PrintMas (A, n);
	printf ("\n M(prak)=%d, C(prak)=%d", Mprak, Cprak);
	CheckSum (A, n);
	RunNumber (A, n);
	printf ("\n");
	
	printf ("\n");
	system("PAUSE");
	return 0;
}

void FillInc (int A[], int n) {
	int i;
	for ( i = 0; i < n; i ++ ) A[i] = i+1;
}

void FillDec (int A[], int n) {
	int i;
	for ( i = 0; i < n; i ++ ) A[i] = n-i;
}

void FillRand (int A[], int n) {
	int i, a = 0, b = n;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}

void CheckSum (int A[], int n) {
	int i, s;
	for (s=0, i=0; i < n; i++) s+=A[i];
	printf ("\n CheckSum=%d", s); 
}

void RunNumber (int A[], int n) {
	int i, c;
	for (c = 1, i = 1; i < n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n RunNumber=%d\n", c); 
}

void PrintMas (int A[], int n) {
	int i;
	for (i = 0; i < n; i++) printf ("%d ", A[i]);
}
void SelectSort (int A[], int n) 
{
	Mprak = 0, Cprak = 0;
	int i,j,k,t;
	for (i = 0; i < n-1; i++ ) { //nachalnoe znachenie min
		k = i;
		for( j=i+1; j<n; j++){ // nahodim index min
			Cprak++;
	   		if (A[j]<A[k])k=j;
		}
		t=A[i];
		A[i]=A[k];
		A[k]=t; //menyaem znacheniya
		Mprak+=3;
	}
}


