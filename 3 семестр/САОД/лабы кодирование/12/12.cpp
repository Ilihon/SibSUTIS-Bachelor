
#define YES true
#define NO false
#pragma warning(disable : 4996)
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cmath>
using namespace std;

const int n = 256;
const int M = 4+1;
const int count =5+1;


struct code {
	char a;
	float p;
	float q;
	float l;
	float h;
	float r;
};

void Arifm();
void CodeBase();

code A[n];
code B[M];
code V[count];
FILE *f;	
int sum=0;

int main()
{
	setlocale(LC_ALL, "Russian");
	int i;
	f = fopen("text.txt", "r");
	for (i = 0; i < n; i++) {
		A[i].a = (char)(i-128);
		A[i].p = 0;
		A[i].q = 0;
		A[i].l = 0;
		A[i].h = 0;
		A[i].r = 0;
	}
	while (!feof(f)) {
		char c;
		fscanf(f, "%c", &c);
		//cout << c<<endl;
		A[c+128].p++;
		sum++;
	}
	fclose(f);
	int j=1;
	for (i=0;i<n;i++){
		if(A[i].p!=0){
			A[i].p/=sum;
			B[j]=A[i];
			j++;
		}
	}
	for(i=0;i<M;i++){
		B[i].q=B[i-1].q+B[i].p;
	}
	
	Arifm();
	for (int i = 1; i < M; i++) {
		printf("| %10c |   %10.8f    |   %10.8f  |\n", B[i].a, B[i].p, B[i].q);
	}
	
	cout<<endl;
	
	for (int i = 1; i < count; i++) {
		printf("| %10c |   %10.15f    -  %10.15f   -   %10.15f|\n", V[i].a, V[i].l, V[i].h, V[i].r);
	}
	CodeBase();
	system("pause");
	return 0;
}

void Arifm() {
	int m=0;
	V[0].l = 0;			
	V[0].h = 1;
	V[0].r = 1;
	int i=1;
	f = fopen("text.txt", "rb");
	while (!feof(f)) {
		char c;
		fscanf(f, "%c", &c);
		//cout << c;
		for (int j = 1; j < M; j++) {
			if (c == B[j].a) {
			//cout << "spidor";	
			m = j;
			}
		}
		V[i].a = B[m].a;
		V[i].l = V[i - 1].l + V[i - 1].r * B[m - 1].q;
		V[i].h = V[i - 1].l + V[i - 1].r * B[m].q;
		V[i].r = V[i].h - V[i].l;
		i++;
		if (i==count) break;
	}
	fclose(f);
}

void CodeBase() {
	FILE *fcoded;
    fcoded = fopen("BaseCoded.txt", "wb");
	for(int i=1; i <count; i++){
		float buffer = floor(log(V[i].r) / log(2));
		putc(buffer, fcoded);
	}
	fclose(fcoded);
}
