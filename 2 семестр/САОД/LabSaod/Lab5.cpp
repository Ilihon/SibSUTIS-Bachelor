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
void SelectSort (int A[], int n);
void BubbleSort (int A[], int n);
void ShakerSort (int A[], int n);
void InsertSort (int A[], int n);
void FunkDec (int n, int i);
void FunkInc (int n, int i);
void FunkRand (int n, int i);
void TablResult (int n);

int Mprak = 0, Cprak = 0;


main() {
	int n = 10, A[n];
	
	FillRand (A, n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf ("M(teor)=%d, C(teor)=%d \n", ((n*n-n)/2)+2*n-2, (n*n-n)/2); 
	InsertSort (A,n);
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	printf ("M(prak)=%d, C(prak)=%d \n", Mprak, Cprak);
	printf ("\n\n");
	TablResult (100);
	printf ("\n\n");
	system("PAUSE");

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
	int i, a = 0, b = 10;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}

void CheckSum (int A[], int n) {
	int i, s;
	for (s=0, i=0; i < n; i++) s+=A[i];
	printf ("\n CheckSum=%d", s); 
}

void RunNumber (int A[], int n) {
	int i, c;
	for (c = 1, i = 1; i < n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n RunNumber=%d\n", c); 
}

void PrintMas (int A[], int n) {
	int i;
	for (i = 0; i < n; i++) printf ("%d ", A[i]);
}

void BubbleSort (int A[], int n) {
	Mprak=0, Cprak=0;
	int i,j,t;
	for (i = 0; i < n-1; i++) {
		for (j=n-1; j>i; j--) {
			Cprak++;
			if (A[j]<A[j-1]) {
				t=A[j];
				A[j]=A[j-1];
				A[j-1]=t;
				Mprak+=3;
			}
		}
	}
}




void TablResult (int n) {
	int i;
	printf ("|  n  | Select | Bubble | Shaker | Insert |");
	for (; n<=600; n+=100) {
		printf ("\n| %3d |", n);
		for (i=0; i<4; i++) {
			FunkRand (n, i);
			printf (" %6.d |", Cprak+Mprak);
		}
	}
}

void FunkDec (int n, int i) {
	Mprak=0; Cprak=0;
	int A[n];
	FillDec (A, n);
	switch (i) {
		case 0: SelectSort (A, n);
			break;
		case 1: BubbleSort (A, n);
			break;
		case 2: ShakerSort (A, n);
			break;
		case 3: InsertSort (A, n);
			break;
	}
}

void FunkInc (int n, int i) {
	Mprak=0; Cprak=0;
	int A[n];
	FillInc (A, n);
	switch (i) {
		case 0: SelectSort (A, n);
			break;
		case 1: BubbleSort (A, n);
			break;
		case 2: ShakerSort (A, n);
			break;
		case 3: InsertSort (A, n);
			break;
	}
}

void FunkRand (int n, int i) {
	Mprak=0; Cprak=0;
	int A[n];
	FillRand (A, n);
	switch (i) {
		case 0: SelectSort (A, n);
			break;
		case 1: BubbleSort (A, n);
			break;
		case 2: ShakerSort (A, n);
			break;
		case 3: InsertSort (A, n);
			break;
	}
}

void ShakerSort (int A[], int n) {
	Mprak=0, Cprak=0;
	int left,right,i,j,k,w;
	left=0;
	right=n-1;
	k=n-1;
	do {
		for(j=right; j>left; j-- ){ // ot pravogo k levomu
			Cprak++;
			if (A[j]<A[j-1]) { // obmen
				w=A[j];
		  	 	A[j]=A[j-1];
			  	A[j-1]=w;
		  	 	k=j;
		  	 	Mprak+=3;
			}
		}
		left=k;
		for(j=left; j<right; j++ ){ // ot levogo k pravomu
			Cprak++;
	   		if(A[j]>A[j+1]){ // obmen 
	   			w=A[j];
	  	 		A[j]=A[j+1];
	   			A[j+1]=w;
	   			k=j;
	   			Mprak+=3;
			}
		}
		right=k;
	}
	while( left<right );
}

void InsertSort (int A[], int n) {
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

void SelectSort (int A[], int n) 
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

