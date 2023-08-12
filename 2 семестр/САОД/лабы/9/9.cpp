#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <graphics.h>


int random (int N) { return rand()%N; }
int mprak=0, cprak=0;

void FillInc(int n, int *A);
void FillDec(int n, int *A);
void FillRand(int n, int *A); 
void PrintMas(int n, int *A); 
void CheckSum (int n, int *A);
void RunNumber (int n, int *A);

void Swap (int &x, int &y);
void Result (int n);
void ResultTabl (int n);

void HeapBuild (int *A, int l, int r);
void HeapSort (int n, int *A);

void ShellSort (int n, int *A);
int K_Sort (int n);

void FunkDec (int n, int i);
void FunkInc (int n, int i);
void FunkRand (int n, int i);


main() {
	int n, m, x;
	printf ("Vvedite razmer massiva: ");
	scanf("%d", &n);
	int A[n];
	
	FillRand (n, A);
	PrintMas (n, A);
	CheckSum (n, A);
	RunNumber (n, A);
	
	HeapSort (n, A);
	PrintMas (n, A);
	CheckSum (n, A);
	RunNumber (n, A);
	
	Result (n);
	printf ("\n\n");
	ResultTabl (100);
	printf ("\n\n");
	
	/*
	//////////////5+

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
 outtextxy(95,45,"n");
 
 
 moveto(200,700);
 lineto(200,710);
 outtextxy(180,715,"3000");
 moveto(300,700);
 lineto(300,710);
 outtextxy(280,715,"6000");
 moveto(400,700);
 lineto(400,710);
 outtextxy(380,715,"9000");
 moveto(500,700);
 lineto(500,710);
 outtextxy(480,715,"12000");
 moveto(600,700);
 lineto(600,710);
 outtextxy(580,715,"15000"); 
 
 outtextxy(660,715,"C(prak)+M(prak)"); 
  
 moveto(100,700);
 
 for(int i=0;i<500;i++)
{
FunkRand(i,0);
lineto(100+((cprak+mprak)/30),700-i);      
}

moveto(100,700);
setcolor(GREEN); 
for(int i=0;i<500;i++)
{
FunkRand(i,1);
lineto(100+((cprak+mprak)/30),700-i);      
}
	
*/
	system("PAUSE");
	return 0;
}

void FillInc (int n, int *A) 
{
	int i;
	for ( i = 0; i < n; i ++ ) A[i] = i+1;
}

void FillDec (int n, int *A)
{
	int i;
	for ( i = 0; i < n; i ++ ) A[i] = n-i;
}

void FillRand (int n, int *A) 
{
	int i, a = 0, b = 10;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}

void CheckSum (int n, int *A) {
	int i, s;
	for (s=0, i=0; i< n; i++) s+=A[i];
	printf ("\n CheckSum=%d", s);
}

void RunNumber (int n, int *A) {
	int i, c;
	for (c=1, i=1; i< n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n RunNumber=%d\n\n", c);
}

void PrintMas (int n, int *A) {
	int i;
	for (i=0; i<n; i++) {
		if(i%20==0 && i!=0) printf ("\n");
		printf ("%3d ", A[i]);
	}
}

void Swap (int &x, int &y) {
	int t=x; x=y; y=t;
}

void Result (int n) {
	printf ("\nCteor=%.0f, Mteor=%.0f", 2*n*log2(n)+n+2, n*log2(n)+6.5*n-4);
	printf ("\nCprak=%d, Mprak=%d", cprak, mprak);
}



void HeapBuild (int *A, int l, int r) {
	int i=l, j, x=A[l];
	mprak++;
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		if (j<=r && (cprak++, A[j+1]<=A[j])) j++;
		if (cprak++, x<=A[j]) break;
		A[i]=A[j];
		mprak++;
		i=j;
	}
	A[i]=x;
	mprak++;
}


void ResultTabl (int n) {
	int i;  
	printf ("|  n   |          HeapSort        |");
	printf ("\n|      |   Inc  |   Dec  |  Rand  |");
	for (; n<=500; n+=100) {
		printf ("\n| %4d |", n);
		FunkInc (n, 0);
		printf (" %6.d |", cprak+mprak);
		FunkDec (n, 0);
		printf (" %6.d |", cprak+mprak);
		FunkRand (n, 0);
		printf (" %6.d |", cprak+mprak);
	}
}

void HeapSort (int n, int *A) {
	int l=n/2, r=n;
	while (l+1>0) {
		HeapBuild (A, l, r);
		l--;
	}
	while (r>1) {
		Swap (A[0], A[r-1]);
		mprak+=3;
		r--;
		HeapBuild (A, 0, r-1);
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
			t=A[i]; mprak++;
			j=i-k;
			while (j>=0 && (cprak++, t<A[j])) 
			{
				A[j+k]=A[j];
				mprak++;
				j-=k;
			}
			A[j+k]=t; mprak++;
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


void FunkDec (int n, int i) {
	mprak=0; cprak=0;
	int A[n];
	FillDec (n, A);
	switch (i) {
		case 0: HeapSort (n, A);
			break;
	}
}

void FunkInc (int n, int i) {
	mprak=0; cprak=0;
	int A[n];
	FillInc (n, A);
	switch (i) {
		case 0: HeapSort (n, A);
			break;
	}
}

void FunkRand (int n, int i) {
	mprak=0; cprak=0;
	int A[n];
	FillRand (n, A);
	switch (i) {
		case 0: HeapSort (n, A);
			break;
		case 1: ShellSort (n,A);
			break; 
	}
}

