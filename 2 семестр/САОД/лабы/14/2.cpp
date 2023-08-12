#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>

int random (int N) { return rand()%N; }
int mp=0, cp=0, rec=0;

void FillInc(int n, int *A);
void FillDec(int n, int *A);
void FillRand(int n, int *A); 
void Print(int n, int *A); 
void CheckSum (int n, int *A);
void RunNumber (int n, int *A);
void Hash (int n, int *A, int *B);

using namespace std;
main() {
	int i, n, m;
	
	printf (" Vvedite razmer ocheredi: ");
	scanf("%d", &n);
	
	int A[n];
	FillRand (n, A);
	printf("\n FillRand: ");
	Print(n, A);
	printf ("\n");
	
	int B[n];
	for(i=0;i<n;i++)
		B[i]=-1;
		
	Hash(n,A,B);
	
	cout << endl<< " Nomer yacheyki ";
	for(i=0;i<n;i++){
		printf("|%3d ",i);
	}
	cout<<"|" <<endl << "         Symbol ";
	for(i=0;i<n;i++){
		if(B[i]==-1)
			printf("|    ");
		else
			printf("|%3d ",B[i]);
	}
	cout << "|" << endl;


	int imem=-1;
	printf ("\n Vvedite kluch poiska: ");
	scanf("%d", &m);
	for(i=0;i<n;i++){
		if(B[i]==m){
			imem=i;
		}
	}
	if(imem==-1){
		printf("\n kluch %d ne naiden\n",m);
	}
	else{
		printf("\n kluch %d naiden na pozicii %d \n",m,imem);
	}
	
	system("PAUSE");
	return 0;
}

void Hash (int n, int *A, int *B){
	
	for(int i=0, j=0; i<n;i++){
		int chet=1;
		int chet2=0;
		
		j=A[i]%n;
		if(B[j]==-1){
			B[j]=A[i];		
		}
		else{
			if(B[j]==A[i]){
				B[j]=A[i];
			}
			else{
				while((B[j+chet-chet2]!=-1) && (B[j+chet-chet2]!=A[i])){
					j=j+chet;
					chet= chet+2;
					if(chet>=n){
						printf("tabl overflow\n");
						return;
					}
					if(chet+j>=n){
						chet2=n;
					}
					else
						chet2=0;
				}
					B[j+chet-chet2]=A[i];
			}
		}
	}
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
	srand(time(NULL));
	for (int i = 0; i < n; i ++ ) A[i] = random(n*2+1)+1;
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

void Print (int n, int *A) {
	int i;
	for (i=0; i<n; i++) {
		if(i%20==0 && i!=0) printf ("\n");
		printf ("%3d ", A[i]);
	}
}

