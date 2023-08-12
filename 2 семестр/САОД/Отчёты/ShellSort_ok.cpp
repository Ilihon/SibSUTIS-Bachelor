#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h> 
#include <time.h> 
#include <math.h>
using namespace std; 
int  i=0, M = 0, C = 0, k=0, r=0,z;


int random (int N) {
    return rand() % N;
}

void FillInc (int A[], int n) {
    for (i = 0; i < n; i++) {
        A[i] = i;
    }
}

void FillDec (int A[], int n) {
    for (i = 0; i < n; i++) {
        A[i] = n-i;
    }
}

void FillRand(int A[], int n) { 

int i; 
for (i = 0; i < n; i++) { 
A[i] = 0; 
} 
for (i = 0; i < n; i++) { 
A[i] = rand()% 10; 
} 
} 

void PrintMas (int A[], int n) {
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}


void InsertSort (int A[], int n) {
	int t=0, j=0;
	C=0; M=0;
	for (i=1; i<n; i++){
		t=A[i];
		j=i-1;
		M++;
		C++;
		if ( j>-1 && t<A[j]) C--;
		while (j>=0 && t<A[j]){
			
			A[j+1]=A[j];
			M++;
			j=j-1;
			C++;
		}
		A[j+1]=t;
		M++;
		
		
	}
}

int ShellSort (int A[], int n) {
	int  t=0, j=0;
		C=0; M=0; 	
	
	r=log2(n)-1;
	z=r;
	int *h=new int[r];
	h[0]=1;
	for(i=1; i<r; i++){
		h[i]=2*h[i-1]+1;
		printf("  h[%d]=%d  ",i, h[i]);
	}
		

		
	for (k=h[r-1]; k>=1; k=h[r-1],r--){
		for (i=k; i<=n; i++){
		     t=A[i];
		     j=i-k; 
		     M++;
		     C++;
		     while (j>=0 && t<A[j]){
		        A[j+k]=A[j]; 
		        j=j-k;   
		        M++;
		        C++;
		    }
		    A[j+k]=t; 
		    M++;    
	    }
    } 
}


int main () {
    setlocale(LC_ALL,"RUS");
	using namespace std; 	
    int Sum,ser,n,y;
    int w;
   srand(time(NULL)); 
    n=100;
    int A[n];

    
    
    printf("Убывающий массив: ");
    FillDec(A, n);
    PrintMas(A,n);
     printf("\n ");
     
    
    
    printf("\n ");
    printf("Отсортированный массив: ");
    ShellSort(A, n);
    PrintMas(A,n);
  
   
    printf("\n\n");
    
    printf("                К-сортировки           Shell            Insert\n"); 
    for(n=100;n<501;n+=100) { 
int B[n], S[n]; 
C=0;M=0;
printf("n=%d",n);
FillRand(B,n);
ShellSort(B,n);
printf("                k=%d",   z);
printf("               %d",M+C); 

C=0;M=0;  
FillRand(S,n); 
InsertSort(S,n); 
    printf("            %d",M+C);
printf("\n\n"); 
C=0;M=0;  
}
    return 0;

}
