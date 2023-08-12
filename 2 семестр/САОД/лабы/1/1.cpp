#include <iostream>
#include <stdlib.h>
#include <stdio.h>   
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
  printf("%d \n",A[i]);
  } 
 }  
 

int main()
{ 
  const int n=10;
  int i;
  int A[n];
  Fillinc(n,A);
  PrintMas(n,A);
  printf("\n");
  FillDec(n,A);
  PrintMas(n,A);
  printf("\n");
  FillRand(n,A);
  printf("\n");
  PrintMas(n,A);
  printf("\n");
  
  Fillinc(n,A);
  PrintMas(n,A);
  printf("\n");
  CheckSum(n,A);
  printf("\n");
  
  RunNumber(n,A);
  printf("\n");
  
  
  FillDec(n,A);
  PrintMas(n,A);
  printf("\n");
  RunNumber(n,A);
  printf("\n");
  
  
  FillRand(n,A);
  PrintMas(n,A);
  printf("\n");
  i=RunNumber(n,A);
  printf("%d",n/i);
  printf("\n");
  
  system("PAUSE");
  return 0;
}
