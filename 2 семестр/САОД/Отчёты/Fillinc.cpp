#include<stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include<math.h>

const int N=10;
int random (int N) { return rand()%N; }
void Fillinc(int A[N])
{
int i=0,j=0;
for (i = 0; i<N; i++,j++)
A[i]=j;
}



void FillDec(int A[N])
{
int i=0,j=N;
for (i = 0; i<N; i++,j--)
A[i]=j;
}


void FillRand(int A[N])
{
int i=0,j=0;
for (i = 0; i<N; i++)
A[i]=random(100-0+1)+0;
}


void CheckSum(int A[N])
{
int i=0,j=0;
for (i = 0; i<N; i++)
j+=A[i];
printf("\nChecksum = %d",j); 
}



void RunNumber(int A[N])
{	
int s=1;
for(int i=0;i<N;i++)
 if (A[i]>A[i+1]) s++;
 printf("\nRunNumber = %d",s);
}


void PrintMas(int A[N])
{
int i=0,j=0;
for (i = 0; i<N; i++)
printf("%d ",A[i]);

}


int main()
{
	 int A[N],s;
	 Fillinc(A);
	printf("FillInc\n");
	PrintMas(A);
	CheckSum(A);
	RunNumber(A);
	
	FillDec(A);
	printf("\n\nFillDec\n");
	PrintMas(A);
	CheckSum(A);
	RunNumber(A);
	
	FillRand(A);
	printf("\n\nFillRand\n");
	PrintMas(A);
	CheckSum(A);
	RunNumber(A);
}
