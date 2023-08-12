#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int random (int N) { return rand()%N; }
int mp=0, cp=0, rec=0;

void FillInc (int A[], int n);
void FillDec (int A[], int n);
void FillRand (int A[], int n);
void CheckSum (int A[], int n);
void RunNumber (int A[], int n);
void PrintMas (int A[], int n);
void Swap (int &x, int &y);
void ResultOld (int n);
void ResultTabl (int n);
void QuickSort (int A[], int l, int r, int k);
void WorkDec (int n, int i);
void WorkInc (int n, int i);
void WorkRand (int n, int i);
void HeapBuild (int A[], int l, int r);


main() {
	int n, m, x;
	printf ("Vvedite razmer massiva: ");
	scanf("%d", &n);
	int A[n];
	FillRand (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	QuickSort (A, 0, n-1, 0);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	ResultOld (n);
	printf ("\n\n");
	ResultTabl (100);
	printf ("\n\n");
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
	int i, a=0, b=2*n;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}

void CheckSum (int A[], int n) {
	int i, s;
	for (s=0, i=0; i< n; i++) s+=A[i];
	printf ("\n%d", s);
}

void RunNumber (int A[], int n) {
	int i, c;
	for (c=1, i=1; i< n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n%d\n", c);
}

void PrintMas (int A[], int n) {
	int i;
	for (i=0; i<n; i++) {
		if(i%20==0 && i!=0) printf ("\n");
		printf ("%3d ", A[i]);
	}
}

void Swap (int &x, int &y) {
	int t=x; x=y; y=t;
}

void ResultOld (int n) {
	printf ("\nT(t)=%f", n*log2(n));
	printf ("\nC(p)=%d, M(p)=%d, T(p)=%d", cp, mp, cp+mp);
}


void HeapBuild (int A[], int l, int r) {
	int i=l, j, x=A[l];
	mp++;
	while (1) {
		j=2*i;
		if (j>r) break;
		if (j<r && (cp++, A[j+1]<=A[j])) j++;
		if (cp++, x<=A[j]) break;
		A[i]=A[j];
		mp++;
		i=j;
	}
	A[i]=x;
	mp++;
}

void ResultTabl (int n) {
	int i;
	printf ("|  n   |   QuickSort (m(f)+c(f))  |");
	printf ("\n|      |   Inc  |   Dec  |  Rand  |");
	for (; n<=1000; n+=100) {
		printf ("\n| %4d |", n);
		WorkInc (n, 0);
		printf (" %6.d |", cp+mp);
		WorkDec (n, 0);
		printf (" %6.d |", cp+mp);
		WorkRand (n, 0);
		printf (" %6.d |", cp+mp);
	}
}



void QuickSort (int A[], int l, int r, int k) {
	int x=A[l], i=l, j=r;
	mp++;
	k++;
	while (i<=j) {
		while (cp++, A[i]<x) i++;
		while (cp++, A[j]>x) j--;
		if (i<=j) {
			Swap (A[i], A[j]);
			mp+=3;
			i++;
			j--;
		}
	}
	if (l<j) QuickSort (A, l, j, k);
	if (i<r) QuickSort (A, i, r, k);
	if (rec<k) rec=k;
}


void WorkDec (int n, int i) 
{
	mp=0; cp=0;
	int A[n];
	FillDec (A, n);
	switch (i) 
	{
		case 0: QuickSort (A, 0, n-1, 0);
			break;
	}
}

void WorkInc (int n, int i) {
	mp=0; cp=0;
	int A[n];
	FillInc (A, n);
	switch (i) {
		case 0: QuickSort (A, 0, n-1, 0);
			break;
	}
}

void WorkRand (int n, int i) 
{
	mp=0; cp=0;
	int A[n];
	FillRand (A, n);
	switch (i) 
	{
		case 0: QuickSort (A, 0, n-1, 0);
			break;
	}
}


