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




main() {
	int n = 10, A[n];

	FillRand (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf (" - Rand ");
	FillDec (A, n);
	printf("\n");
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf (" - Dec ");
	FillInc (A, n);
	printf("\n");
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf (" - Inc ");
	printf("\n");
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
	int i, a = 0, b = 10;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}

void CheckSum (int A[], int n) {
	int i, s;
	for (s=0, i=0; i < n; i++) s+=A[i];
	printf ("\n CheckSum = %d", s); 
}

void RunNumber (int A[], int n) {
	int i, c;
	for (c = 1, i = 1; i < n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n RunNumber = %d", c); 
}

void PrintMas (int A[], int n) {
	int i;
	for (i = 0; i < n; i++) printf ("%d ", A[i]);
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
