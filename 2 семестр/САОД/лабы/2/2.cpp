#include <iostream>
#include <stdlib.h>
#include <stdio.h>  

int Mprak = 0, Cprak = 0;
 
void Fillinc(int n, int *A)
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
 
void PrintMas(int n, int *A)
{
     for(int i=0;i<n;i++)
  {
  printf("%d \t",A[i]);
  } 
 }  
 
 
 void SelectSort (int n, int *A) 
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
 
 
 
int main()
{ 
    const int n=10;
    int A[n];
	FillDec (n, A);
	PrintMas (n,A);
	CheckSum (n,A);
	RunNumber (n,A);
	printf (" M(teor)=%d, C(teor)=%d \n", 3*(n-1), (n*n-n)/2);
	SelectSort (n,A);
	PrintMas (n,A);
	printf ("\n M(prak)=%d, C(prak)=%d", Mprak, Cprak);
	CheckSum (n,A);
	RunNumber (n,A);
	printf ("\n");
	
	printf ("\n");
  system("PAUSE");
  return 0;
}
