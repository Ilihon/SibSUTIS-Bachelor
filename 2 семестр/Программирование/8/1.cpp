#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <iostream>
#define n 6

struct schools{int number; int vipusk; int postup;};
struct schools array[n];

int less(schools x, schools y);
void InsertSort(schools *A, int *B);
void Print(schools *A, int *B);

int main() {
	setlocale(LC_ALL,"RUS");
	int B[n];
	array[0].number=69; array[0].vipusk=79; array[0].postup=49;
	array[1].number=228; array[1].vipusk=88; array[1].postup=14;
	array[2].number=15; array[2].vipusk=60; array[2].postup=60;
	array[3].number=1; array[3].vipusk=43; array[3].postup=1;
	array[4].number=2; array[4].vipusk=22; array[4].postup=15;
	array[5].number=3; array[5].vipusk=60; array[5].postup=34;
	InsertSort(array, B);
	Print(array, B);
	system("pause >> NULL");
	return 0;
}

int less(schools x, schools y) {
	if (x.postup > y.postup) {
		return 0;
	}
	else {
		return 1;
	}
}

void InsertSort(schools *A, int *B) {
	int j, i, t;
	
	for (i = 0; i < n; i++) {
		B[i] = i;
	}

	for (i = 1; i < n; i++) {
		t = B[i];
		j = i - 1;
		while ((j >= 0) && ((less(A[t], A[B[j]]))>0)) {
			B[j + 1] = B[j];
			j = j - 1;	
		}
		B[j + 1] = t;	
	}
}

void Print(schools *A, int *B) {
	for (int i = 0; i < n; i++) {
		float a=A[B[i]].vipusk;
		float b=A[B[i]].postup;
		float procent = b/(a/100);
		printf("Номер школы %-4d \nВыпускники: %-3d  \nПоступившие: %-4d",A[B[i]].number,A[B[i]].vipusk,A[B[i]].postup);
		printf("\nПроцент поступивших: %.2f", procent);
		std::cout << " % \n\n";
	}
}
