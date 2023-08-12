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
void BubbleSort (int A[], int n);
void FunkDec (int n, int i);
void FunkInc (int n, int i);
void FunkRand (int n, int i);
void TablResult (int n);

int Mprak = 0, Cprak = 0;

main() 
{
	int n = 10, A[n];

	FillRand (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf ("M(teor)=%d, C(teor)=%d \n\n", 3*(n*n-n)/2, (n*n-n)/2);
	BubbleSort (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf ("M(prak)=%d, C(prak)=%d \n", Mprak, Cprak);
	printf ("\n");
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

void BubbleSort (int A[], int n) {
	Mprak=0, Cprak=0;
	int i,j,t;
	for (i = 0; i < n-1; i++) 
	{ 
		for (j=n-1; j>i; j--) 
		{ 
			Cprak++; 
			if (A[j]<A[j-1]) 
			{
				t=A[j];
				A[j]=A[j-1];
				A[j-1]=t;
				Mprak+=3; 
			}
		}
	}
}

void TablResult (int n) 
{
	int i;
	printf ("| Bubble,n | Ct+Mt  |  Cp+Cp |");
	for (; n<=600; n+=100) 
	{
		printf ("\n|    %3d   |", n);
		for (i=0; i<1; i++) 
		{
			FunkRand (n, i);
			printf (" %6.d |", (3*(n*n-n)/2)+((n*n-n)/2));
			printf (" %6.d |", Cprak+Mprak);
		}
	}
}

void FunkDec (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillDec (A, n);
	switch (i) 
	{
		case 0: BubbleSort (A, n);
			break;
	}
}

void FunkInc (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillInc (A, n);
	switch (i) 
	{
		case 0: BubbleSort (A, n);
			break;
	}
}

void FunkRand (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillRand (A, n);
	switch (i) 
	{
		case 0: BubbleSort (A, n);
			break;
	}
}

