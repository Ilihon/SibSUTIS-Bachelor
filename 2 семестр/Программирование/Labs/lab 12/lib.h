#include <stdlib.h>
#include <time.h>

int integerTimer(void (*f)(int, int*), int n, int* A) {
    int a = time(NULL);
    f(n, A);
    int b = time(NULL);
    return b - a;
}

int floatTimer(void (*f)(int, float*), int n, float* A) {
    int a = time(NULL);
    f(n, A);
    int b = time(NULL);
    return b - a;
}

void SelectSort(int n, int A[]) {
    int i, j, k, t;
    for (i = 1; i < n; i++) {
        k = i;
        for (j = i + 1; j <= n; j++) {
            if (A[k] > A[j])
                k = j;
        }
        t = A[i];
        A[i] = A[k];
        A[k] = t;
    }
}
void BubbleSort(int n, int A[]) {
    int i, j, t;
    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                t = A[j];
                A[j] = A[j - 1];
                A[j - 1] = t;
            }
        }
    }
}
void InsertSort(int n, int A[]) {
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = A[i];
        j = i - 1;
        while (j >= 0 && t < A[j]) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = t;
    }
}
void SelectSort(int n, float A[]){
    int i, j, k, t;
    for (i = 1; i < n; i++) {
        k = i;
        for (j = i + 1; j <= n; j++) {
            if (A[k] > A[j])
                k = j;
        }
        t = A[i];
        A[i] = A[k];
        A[k] = t;
    }
}
void BubbleSort(int n, float A[]){
    int i, j, t;
    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                t = A[j];
                A[j] = A[j - 1];
                A[j - 1] = t;
            }
        }
    }
}
void InsertSort(int n, float A[]){
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = A[i];
        j = i - 1;
        while (j >= 0 && t < A[j]) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = t;
    }
}
void FillRand(int n, int* A){
    for (int i = 0; i < n; i++)
        A[i] = rand() % 10 + 1;
}
void FillRand(int n, float* A) {
    for (int i = 0; i < n; i++)
        A[i] = rand() * 1.;
}
