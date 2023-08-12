#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int random (int N) { return rand()%N; }

void FillInc(int n, int *A);
void FillDec(int n, int *A);
void FillRand(int n, int *A); 
void PrintMas(int n, int *A); 
int CheckSum(int n, int *A);
int RunNumber(int n, int *A);
void ShellSort (int n, int *A);
void InsertSort (int n, int *A);
void FunkDec (int n, int i);
void FunkInc (int n, int i);
void FunkRand (int n, int i);
void TablResult (int n);
int K_Sort (int n);

int Mprak = 0, Cprak = 0;



main() {
	int n = 10, A[n];
	
	FillRand (n,A);
	PrintMas (n,A);
	CheckSum (n,A);
	RunNumber (n,A);
	printf ("M(teor)=%d, C(teor)=%d \n", ((n*n-n)/2)+2*n-2, (n*n-n)/2); 
	ShellSort (n,A);
	PrintMas (n,A);
	CheckSum (n,A);
	RunNumber (n,A);
	printf ("M(prak)=%d, C(prak)=%d \n", Mprak, Cprak);	
	printf ("\n\n");
	TablResult (100);
	printf ("\n\n");
	system("PAUSE");
	return 0;
}

void FillInc(int n, int *A)
{    
     for (int i=0;i<n;i++)
     {
         A[i]=i;
     }
}

void FillDec(int n, int *A)
{    
     for (int i=0;i<n;i++)
     {
         A[i]=n-1-i;
     }
} 
   
void FillRand(int n, int *A)
{    
     for (int i=0;i<n;i++)
     {
         A[i]=rand() % 10;
     }
}

void PrintMas(int n, int *A)
{
     for(int i=0;i<n;i++)
  {
  printf("%d \n",A[i]);
  } 
}

int CheckSum(int n, int *A)
{
     int sum=0;
     for(int i=0;i<n;i++)
  {
  sum=sum+A[i];
  } 
  printf ("\n CheckSum=%d", sum); 
  return sum;
} 

int RunNumber(int n, int *A)
{
     int i=1;
	 int v;
     for (v=1;v<n;v++ )
     {
	           if(A[v-1]>A[v]) 
               {
               i++;
               }
            
     }
     printf ("\n RunNumber=%d\n", i); 
     return i;
         
}

void TablResult (int n) 
{
	int i;
	printf ("|  n  | K-Sort | Insert |  Shell |");
	for (; n<=600; n+=100) 
	{
		printf ("\n| %3d |", n);
		printf ("   %2.d   |", K_Sort(n));
		for (i=0; i<2; i++) 
		{
			FunkRand (n, i);
			printf (" %6.d |", Cprak+Mprak);
		}
	}
}

void FunkDec (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillDec (n, A);
	switch (i) 
	{
		case 0: InsertSort (n, A);
			break;
		case 1: ShellSort (n, A);
			break;
	}
}

void FunkInc (int n, int i)
{
	Mprak=0; Cprak=0;
	int A[n];
	FillInc (n, A);
	switch (i) 
	{
		case 0: InsertSort (n, A);
			break;
		case 1: ShellSort (n, A);
			break;
	}
}

void FunkRand (int n, int i) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillRand (n, A);
	switch (i) 
	{
		case 0: InsertSort (n, A);
			break;
		case 1: ShellSort (n, A);
			break;
	}
}

void InsertSort (int n, int *A) 
{
	Mprak=0, Cprak=0;
	int i,t,j;
	for(i=1; i<n; i++) {
		Mprak++;
		t=A[i];
		j=i-1;
		while(j>=0 && (Cprak++, t<A[j])) { // poka element menshe, smeshaem
			Mprak++;
			A[j+1]=A[j];
			j=j-1;
		}
		Mprak++;
		A[j+1]=t;
	}
}


void ShellSort (int n, int *A) 
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
