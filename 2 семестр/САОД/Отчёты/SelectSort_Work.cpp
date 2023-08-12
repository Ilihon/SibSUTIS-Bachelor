#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const int n = 10;

int A[n], i, M = 0, C = 0;

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

void FillRand (int A[], int a) {
    for (i = 0; i < n; i++) {
        A[i] = random(a);
    }
}

int CheckSum (int A[], int n) {
    int Sum=0;
    for (i = 0; i < n; i++) {
        Sum+=A[i];
    }
    return Sum;
}

int RunNumber(int A[n])
{	
int s=1;
for(int i=0;i<n;i++)
 if (A[i]>A[i+1]) s++;
return s;
}

void PrintMas (int A[], int n) {
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}

void SelectSort (int A[], int n) {
    int j, min, temp;
    M=0; C=0;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            C += 1;
            if (A[j] < A[min]) {
                min = j;
            }
        }
        
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
            M += 3;
        
        
    }
}

int main () {
    int Sum,ser;
  setlocale(LC_ALL, "Russian");
   
    printf("Возрастающий массив: ");
    FillInc(A, n);
     PrintMas(A,n);
     printf("\n ");
     printf("Сумма элементов: ");
    Sum=CheckSum(A, n);
    printf("%d ", Sum);
    printf("Число серий: ");
    ser=RunNumber (A);
    printf("%d ",ser);
    printf("\n ");
    
    
    printf("\n ");
    printf("Отсортированный массив: ");
    SelectSort(A, n);
    PrintMas(A,n);
    printf("\n ");
    printf("Сумма элементов: ");
    Sum=CheckSum(A, 10);
    printf("%d ", Sum);
    printf("Число серий: ");
    ser=RunNumber (A);
    printf("%d ",ser);
    
    printf("\n ");
    printf("M=%d  C=%d", M, C);
    
    printf("\n\n");
    printf("Убывающий массив: ");
    FillDec(A,n);
    PrintMas(A,n);
     printf("\n ");
     printf("Сумма элементов: ");
    Sum=CheckSum(A, n);
    printf("%d ", Sum);
    printf("Число серий: ");
    ser=RunNumber (A);
    printf("%d ",ser);
    printf("\n ");
    
    printf("\n ");
    printf("Отсортированный массив: ");
    SelectSort(A, n);
    PrintMas(A,n);
    printf("\n ");
    printf("Сумма элементов: ");
    Sum=CheckSum(A, 10);
    printf("%d ", Sum);
    printf("Число серий: ");
    ser=RunNumber (A);
    printf("%d ",ser);
    printf("\n ");
    printf("M=%d  C=%d", M, C);

    printf("\n\n");
    
    printf("Массив случайных чисел: ");
    FillRand(A,n);
    PrintMas(A,n);
     printf("\n ");
     printf("Сумма элементов: ");
    Sum=CheckSum(A, n);
    printf("%d ", Sum);
    printf("Число серий: ");
    ser=RunNumber (A);
    printf("%d ",ser);
    printf("\n ");
    
    printf("\n ");
    printf("Отсортированный массив: ");
    SelectSort(A, n);
    PrintMas(A,n);
    printf("\n ");
    printf("Сумма элементов: ");
    Sum=CheckSum(A, 10);
    printf("%d ", Sum);
    printf("Число серий: ");
    ser=RunNumber (A);
    printf("%d ",ser);
    
    printf("\n ");
    printf("M=%d  C=%d", M, C);
    
    printf("\n\n");
    
   
    system("PAUSE");
    

}

