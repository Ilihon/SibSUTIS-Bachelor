#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h> 


int  i, M = 0, C = 0;


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

void FillRand (int A[], int n) {
    for (i = 0; i < n; i++) {
        A[i] = random(n);
    }		
}


void PrintMas (int A[], int n) {
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}

void BubbleSort (int A[], int n) {
    int j, min, temp;
    M=0; C=0;
    for (i=0; i<n-1; i++) {
        for (j=n-2; j>=i; j--) {
            C += 1;
            if (A[j]>A[j+1]) {
            	M += 3;
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }  
    }
}

int main () {
    int Sum,ser,n,y;
    int w;
    setlocale(LC_ALL,"RUS");
  
    n=10;
    int A[n];

    
    
    printf("Убывающий массив: ");
    FillDec(A, n);
    PrintMas(A,n);
     printf("\n ");
     
    
    
    printf("\n ");
    printf("Отсортированный массив: ");
    BubbleSort(A, n);
    PrintMas(A,n);
  
    
    
    printf("\n ");
    printf("M=%d  C=%d", M, C);
    printf("\n ");
    printf("M+C=%d", M+C);
    printf("\n\n");
    
    for(n=100;n<501;n+=100) { 
int B[n]; 
C=0;M=0;
 
w=5*(n*n-n)/4; 
printf("n=%d",n);
printf("  теоретически:%d",w);
FillDec(B,n); 
BubbleSort(B,n); 
printf("  Убывающий:%d",M+C); 
M=0;C=0; 
FillInc(B,n); 
BubbleSort(B,n);
printf("  Возрастающий:%d",M+C); 
M=0;C=0; 
FillRand(B,n); 
BubbleSort(B,n); 
printf("  Случайным образом:%d",M+C);
printf("\n\n");
 
} 
    
   
    system("PAUSE");
    
    initwindow(700, 700); 
line(50,50,50,650); 
line(650,650,50,650); 
moveto(50, 650); 
M=0;C=0;
setcolor(2);
for(n=2;n<30;n++){ 
int E[n]; 
FillRand(E,n); 
BubbleSort(E,n); 
lineto(n*25,650-(M+C)); 
M=0; C=0; 
} 
getch(); 
closegraph(); 
return 0;
    

}
