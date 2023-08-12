#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    srand((int)time(NULL));
    int n = 35000;
    int A[n], time;
    float B[n];
    FillRand(n, A);
    FillRand(n, B);
    time = integerTimer(SelectSort, n, A);
    printf("Integer Array | SelectSort %d seconds\n", time);
    time = floatTimer(SelectSort, n, B);
    printf("Float Array   | SelectSort %d seconds\n", time);
    
    
    
    FillRand(n, A);
    FillRand(n, B);
    time = integerTimer(BubbleSort, n, A);
    printf("Integer Array | BubbleSort %d seconds\n", time);
    time = floatTimer(BubbleSort, n, B);
    printf("Float Array   | BubbleSort %d seconds\n", time);
   
    FillRand(n, A);
    FillRand(n, B);
    time = integerTimer(InsertSort, n, A);
    printf("Integer Array | InsertSort %d seconds\n", time);
    time = floatTimer(InsertSort, n, B);
    printf("Float Array   | InsertSort %d seconds\n", time);
    
     system("pause");
    return 0;
}
