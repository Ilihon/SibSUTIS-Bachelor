#include <iostream>
#include <stdlib.h>
#include <stdio.h>  

void FillInc(int n, int *A);
void FillDec(int n, int *A);
void FillRand(int n, int *A); 
void PrintMas(int n, int *A); 
int CheckSum(int n, int *A);
int RunNumber(int n, int *A);
void SelectSort (int n, int *A); 
void BubbleSort (int n, int *A);
void TablResult (int n);
void FunkDec (int n);
void FunkRand (int n);
void FunkInc (int n);


int Mprak = 0, Cprak = 0; 

 
int main()
{ 
    const int n=10;
    int A[n];
	FillRand (n,A);
	PrintMas (n,A);
	CheckSum (n,A);
	RunNumber (n,A);
	printf ("M(teor)=%d, C(teor)=%d \n\n", 3*(n*n-n)/2, (n*n-n)/2);
	BubbleSort (n,A);
	PrintMas (n,A);
	CheckSum (n,A);
	RunNumber (n,A);
	printf ("M(prak)=%d, C(prak)=%d \n", Mprak, Cprak);
	printf ("\n");
	TablResult(100);
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
 
 void SelectSort (int n, int *A) 
{
	Mprak = 0, Cprak = 0;
	int i,j,k,t;
	for (i = 0; i < n-1; i++ ) { 
		k = i;
		for( j=i+1; j<n; j++){ 
			Cprak++;
	   		if (A[j]<A[k])k=j;
		}
		t=A[i];
		A[i]=A[k];
		A[k]=t; 
		Mprak+=3;
	}
}

void BubbleSort (int n, int *A) {
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
	printf ("|   n   | Ct+Mt  |        | Cp+Mp  |        |\n");
	printf ("|       |        |   Dec  |  Rand  |  Inc   |");
	for (;n<=600; n+=100) 
	{
		printf ("\n|  %3d  |", n);
		FunkDec (n);
		printf (" %6.d |", (3*(n*n-n)/4)+((n*n-n)/2));
		printf (" %6.d |", Cprak+Mprak);
		FunkRand(n);
		printf (" %6.d |", Cprak+Mprak);
		FunkInc(n);
		printf (" %6.d |", Cprak+Mprak);
	}
}

void FunkDec (int n) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillDec (n,A);
	BubbleSort (n,A);
}

void FunkRand (int n) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillRand (n,A);
	BubbleSort (n,A);
}

void FunkInc (int n) 
{
	Mprak=0; Cprak=0;
	int A[n];
	FillInc (n,A);
	BubbleSort (n,A);
}


