#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int random (int N) { return rand()%N; }

void FillInc (int A[], int n); 
void FillDec (int A[], int n); 
void FillRand (int A[], int n); 
void CheckSum (int A[], int n); 
void RunNumber (int A[], int n); 
void PrintMas (int A[], int n); 
void ShellSort (int A[], int n);
void FunkDec (int n, int i);
void FunkInc (int n, int i);
void FunkRand (int n, int i);
void TablResult (int n);
void BSearch1 (int A[], int n, int X);
void BSearch2 (int A[], int n, int X);

int Mprak = 0, Cprak = 0;
int K_Sort (int n);


main() {
	int n = 10, A[n], X=3;
	
	FillRand (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	ShellSort (A, n);
	printf ("\n"); 
	PrintMas (A, n);
	printf ("\n\n");
	BSearch1 (A, n, X);
	printf ("C(prak)=%d \n", Cprak);
	BSearch2 (A, n, X);
	printf ("C(prak)=%d \n", Cprak);
	TablResult(100);
	printf ("\n\n");
	system("PAUSE");
	return 0;
}

void FillInc (int A[], int n) 
{
	int i;
	for ( i = 0; i < n; i ++ ) A[i] = i+1;
}

void FillDec (int A[], int n) 
{
	int i;
	for ( i = 0; i < n; i ++ ) A[i] = n-i;
}

void FillRand (int A[], int n) 
{
	int i, a = 0, b = 10;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
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
	for (c = 1, i = 1; i < n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n RunNumber=%d\n", c); 
}

void PrintMas (int A[], int n) 
{
	int i;
	for (i = 0; i < n; i++) printf ("%d ", A[i]);
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

void FunkDec (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n], X=3;
	FillDec (A, n);
	ShellSort (A, n);
	switch (i) 
	{
		case 0: {;
		BSearch1 (A, n, X);
			break; }
		case 1: {;
		BSearch2 (A, n, X);
			break;	}
	}
}

void FunkInc (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n], X;
	FillInc (A, n);
	ShellSort (A, n);
	switch (i) 
	{
		case 0: {
		BSearch1 (A, n, X);
			break; }
		case 1: {
		BSearch2 (A, n, X);
			break;	}
	}
}

void FunkRand (int n, int i)
{
	Mprak=0; Cprak=0;
	int A[n], X;
	FillRand (A, n);
	ShellSort (A, n);
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

void ShellSort (int A[], int n) 
{
	int i, j, k, l, t;
	l=K_Sort(n);
	int K[l];
	K[0]=1;
	for (i=1; i<l; i++) 
		K[i]=K[i-1]*2+1;
	for (; l>0; l--) 
	{
		k=K[l-1];
		for (i=k; i<n; i++) 
		{
			t=A[i]; Mprak++;
			j=i-k;
			while (j>=0 && (Cprak++, t<A[j])) 
			{
				A[j+k]=A[j];
				Mprak++;
				j-=k;
			}
			A[j+k]=t; Mprak++;
		}
	}
}

int K_Sort (int n)
{
	int i=2, j=0;
	while (i<=n) 
	{
		i*=2;
		j++;
	}
	j--;
	return j;
}

void BSearch1 (int A[], int n, int X)
{
	Cprak=0;
	int L=1, R=n, Find=0, m;
	while (L<=R)
	{
		m=(int)((L+R)/2);
		Cprak++;
		if (A[m]==X) 
		{
		Find=1;
		break;
		} 
		Cprak++;
		if (A[m]<X) L=m+1;
		else R=m-1;
	}
}

void BSearch2 (int A[], int n, int X)
{
	Cprak=0;
	int L=1, R=n, Find=0, m;
	while (L<R)
	{
		m=(int)((L+R)/2);
		Cprak++;
		if (A[m] < X) L=m+1;
		else R=m;
	}
	Cprak++;
	if (A[R]=X) Find = 1;
	else Find = 0;
}
