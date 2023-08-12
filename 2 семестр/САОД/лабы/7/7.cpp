#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
//#include <graphics.h>

int random (int N) { return rand()%N; }
int Mprak = 0, Cprak = 0;

void FillRand (int A[], int n) 
{
	int i, a = 0, b = 10;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}

void PrintMas (int A[], int n) 
{
	int i;
	for (i = 0; i < n; i++) printf ("%d ", A[i]);
}

void CheckSum (int A[], int n) 
{
	int i, s;
	for (s=0, i=0; i < n; i++) s+=A[i];
	printf ("\n CheckSum=%d", s); 
}

void RunNumber (int A[], int n) 
{
	int i, c;
	for (c = 1, i = 1; i < n; i++) 
		if (A[i-1]>A[i]) c++;
		printf ("\n RunNumber=%d\n", c); 
}


void ShakerSort (int A[], int n) {
	int l = 0;
	int r = n;
	int k = n;
	int z = 0;
	int j = 0;
do {
	for (j = r; j > l; j--) {
		if (A[j] < A[j-1]) {
			z=A[j];
			A[j]=A[j-1];
			A[j-1]=z;
			k=j;
		}
	}
	l=k;
	for (j = l; j < r; j++) {
		if (A[j]>A[j+1]) {
			z=A[j];
			A[j]=A[j+1];
			A[j+1]=z;
			k=j;	
		}
	}
	r=k;
}
while (l<r);
}

BSearch1 (int A[], int n, int X) {
	int l = 0;
	int r = n;
	int m = 0;
	int find = 0;
	while (l <= r) {
		m=(l+r)/2;
		Cprak++;
		if ( A[m] == X ) {
			find = 1;
			break;
		}
		Cprak++;
		if ( A[m] < X) l = m+1;
		else r = m-1;
	}
//	printf("%d", find);
}

BSearch2 (int A[], int n, int X) {
	int l = 0;
	int r = n;
	int m = 0;
	int find = 0;
	while ( l < r ) {
		m=(l+r)/2;
		Cprak++;
		if ( A[m] < X) l = m+1;
		else r = m;
	}
	Cprak++;
	if (A[r] == X) find = 1;
	else find = 0;
//	printf("%d", find);
}

void FunkRand (int n, int i)
{
	Mprak=0; Cprak=0;
	int A[n], X;
	FillRand (A, n);
	ShakerSort (A, n);
	switch (i) 
	{
		case 0: {;
		BSearch1 (A, n, X);
			break; }
		case 1: {
		BSearch2 (A, n, X);
			break;	}
	}
}

void TablResult (int n) 
{
	int i;
	printf ("|  n   | BSearch1 | BSearch2 |");
	for (; n<=1000; n+=100) 
	{
		printf ("\n| %4d |", n);
		for (i=0; i<2; i++) 
		{
			FunkRand (n, i);
			printf (" %8.d |", Cprak);
		}
	}
}

int main() {
	int n = 100, A[n], X=5;
	/*
	initwindow (600,600);
	moveto(100,500);
	lineto(100,95);
	moveto(100,500);
	lineto(510,500);
	moveto(510,500);
	lineto(495,490);
	moveto(510,500);
	lineto(495,510);
	moveto(100,95);
	lineto(90,110);
	moveto(100,95);
	lineto(110,110);
	*/	
	FillRand (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	ShakerSort (A, n);
	printf ("\n"); 
	PrintMas (A, n);
	printf ("\n\n");
	BSearch1 (A, n, X);
	printf ("C(prak)=%d \n", Cprak);
	BSearch2 (A, n, X);
	printf ("C(prak)=%d \n", Cprak);
	TablResult(100);
	printf ("\n");
	system("PAUSE");
	return 0;
}
