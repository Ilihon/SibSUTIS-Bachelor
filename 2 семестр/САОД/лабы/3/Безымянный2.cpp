#include <iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <graphics.h>

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
	printf ("M(teor)=%d, C(teor)=%d \n\n", 3*(n*n-n)/4, (n*n-n)/2);
	BubbleSort (n,A);
	PrintMas (n,A);
	CheckSum (n,A);
	RunNumber (n,A);
	printf ("M(prak)=%d, C(prak)=%d \n", Mprak, Cprak);
	printf ("\n");
	TablResult(100);
	printf ("\n\n");
	
	initwindow(800,800);
 moveto(100,700);         
 lineto(100,60);     
 lineto(95,65);	
lineto(100,60);     
 lineto(105,65);	
 moveto(100,700);
 lineto(700,700);
 lineto(695,695);
 moveto(700,700);
 lineto(695,705);
 
 moveto(100,600);
 lineto(90,600);
 outtextxy(65,592,"100");
 moveto(100,500);
 lineto(90,500);
 outtextxy(65,492,"200");
 moveto(100,400);
 lineto(90,400);
 outtextxy(65,392,"300");
 moveto(100,300);
 lineto(90,300);
 outtextxy(65,292,"400");
 moveto(100,200);
 lineto(90,200);
 outtextxy(65,192,"500");
 moveto(100,100);
 lineto(90,100);
 outtextxy(65,92,"600");
 outtextxy(95,45,"n");
 
 
 moveto(200,700);
 lineto(200,710);
 outtextxy(180,715,"100000");
 moveto(300,700);
 lineto(300,710);
 outtextxy(280,715,"200000");
 moveto(400,700);
 lineto(400,710);
 outtextxy(380,715,"300000");
 moveto(500,700);
 lineto(500,710);
 outtextxy(480,715,"400000");
 moveto(600,700);
 lineto(600,710);
 outtextxy(580,715,"500000"); 
 
 outtextxy(660,715,"C(prak)+M(prak)"); 
  
 moveto(100,700);
for(int i=0;i<600;i++)
{
     
FunkRand(i);
lineto(100+((Cprak+Mprak)/1000),700-i);      
}


 
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


