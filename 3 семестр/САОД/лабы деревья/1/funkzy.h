#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
int heapSize;
int M=0,C=0,rek=0;

//Заполнение массива возрастающим раномом
void FillIncRand(int* A, int n){  
	int i;
	srand(time(NULL));
	A[0]=rand()%n;
	for (i=1; i<n; i++) {
		A[i]=rand()%n; while (A[i-1]>A[i]) A[i]+=rand()%n;
	}
}

//Заполнение массива возрастающими числами
void FillInc(int* A, int n){
	int i;
 	for (i=0;i<n+1;i++)
 	A[i]=i+1; 
} 

//Заполнение массива убывающим раномом
void FillDecRand(int* A, int n){
 int i;
    A[0]=rand()%n;
 	for (i=0;i<n+1;i++)
	{
 	A[i]=rand()%n; 
	while (A[i-1]<A[i]) A[i]-=rand()%n;
    }
}  

//Заполнение массива убывающими числами
void FillDec(int* A, int n){
 int i;
 	for (i=0;i<n+1;i++)
 	A[i]=n-i; 
} 

//Заполнение массива раномом
void FillRand(int* A, int n){
	int i;
	for (i=0;i<n;i++)
	A[i]=rand()%n+1;
}

//Контрольная сумма
void CheckSum(int* A, int n){
    int i,S=0;
	for (i=0; i<n; i++) 
	S+=A[i];
	printf("Контрольная сумма = %d",S);
}

//Количество серий
void RunNumber(int* A, int n){
	int i, q=1;
	for (i=0; i<n-1; i++)
	if (A[i]>A[i+1]) q++;
	printf("Серий - %d",q); printf("\n");
}

//Вывод массива
void PrintMas(int* A, int n){
	int i; 
	for (i=0; i<n; i++) 
	printf("%d ",A[i]);
}

//BubbleSotr
void BubbleSort(int A[], int n) { 
	int b,j,C,M,i; 
	C=0;M=0; 
	for(i=0; i<n-1; i++) { 
		for(j=n-1; j>i; j--) { 
			C+=1; 
			if (A[j]<A[j-1]) { 
				M+=3, b=A[j], A[j]=A[j-1], A[j-1]=b; 
			} 
		}	 
	} 
}

//ShakerSort
void ShakerSort(int *A, int n, int &Mf, int &Cf){
	int L=0, R=n-1, K=n-1, t, j;
	do {
    	for (j=R; j>L; j--) {
    		Cf++;
    		if (A[j]<A[j-1]) {
    			t=A[j];
    			A[j]=A[j-1];
    			A[j-1]=t;
    			K=j;
    			Mf=Mf+3;
			}
		}
		L=K;
		for (j=L; j<R; j++){
			Cf++;
			if (A[j]>A[j+1]){
				t=A[j];
    			A[j]=A[j+1];
    			A[j+1]=t;
    			K=j;
    			Mf=Mf+3;
			}
		}
		R=K;
	}
	while (L<R);
}

//ShellSort
void ShellSort(int num[], int n){
    int k,h,t,j,o,p;
    M=0;C=0;
    h=n/2;
    for(k=h;k>=1;)
    {
        for(o=k;o<n;o++)
        {
            C++;M++;t=num[o]; j=o-k;
            for(;j>=0&&t<num[j];)
            {
                C++;
				num[j+k]=num[j];M++;
				j=j-k;
            }
            num[j+k]=t;M++;
        }
        //printf("%d\n",k);
        k=k/2;
    }
}

void ShellSortKnut(int num[], int n){
    int k,h=0,t,j,o,p,u,y;
    float m;
    M=0;C=0;
    m=(log(n)/log(2))-1;
    for (y=1;y<=m;y++) h=2*h+1;
    for(k=h;k>=1;)
    {
        for(o=k;o<n;o++)
        {
            C++;M++;t=num[o]; j=o-k;
            for(;j>=0&&t<num[j];)
            {
                C++;
				num[j+k]=num[j];M++;
				j=j-k;
            }
            num[j+k]=t;M++;
        }
        m--;
        //printf("%d\n",k);
     k-=pow(2,(int)m);

    }

}

int Knut(int n){
    int m;
m=(log(n)/log(2))-1;
return m;
}

int neKnut(int n){
    int u=0;
while (n>1)
{n=n/2;u++;}
return u;
}

void ShellSortKnutdem(int num[], int n){
    int k,h=0,t,j,o,p,u,y;
    float m;
    M=0;C=0;
    m=(log(n)/log(2))-1; p=m;
    printf("|-Количество шагов = %d\n",Knut(n));
    for (y=1;y<=m;y++) h=2*h+1;
    for(k=h;k>=1;)
    {
        for(o=k;o<n;o++)
        {
            C++;M++;t=num[o]; j=o-k;
            for(;j>=0&&t<num[j];)
            {
                C++;
				num[j+k]=num[j];M++;
				j=j-k;
            }
            num[j+k]=t;M++;
        }
        m--;
        printf("|-h%d=%d\n",p,k);p--;
     k-=pow(2,(int)m);
     }

}

//HeapSotr
void Heapify(int* A, int i){
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int largest;
C++;
  if(l <= heapSize && A[l] > A[i])
    {largest = l;}
  else
    {largest = i;
    C++;
  if(r <= heapSize && A[r] > A[largest])
    largest = r;}

  if(largest != i)
    {
      int temp = A[i]; M++;
      A[i] = A[largest]; M++;
      A[largest] = temp; M++;
      Heapify(A, largest);
    }
}

void BuildHeap(int* A,int n){
  heapSize = n - 1;
  int i;
  for(i = (n - 1) / 2; i >= 0; i--)
    Heapify(A, i);
}

void HeapSort(int* A,int n){ C=0; M=0;
  BuildHeap(A,n);
  int i;
  for(i = n - 1; i > 0; i--)
    {
      int temp = A[heapSize];M++;
      A[heapSize] = A[0];M++;
      A[0] = temp;M++;
      heapSize--;
      Heapify(A, 0);
    }
}

//QuickSort
void QuickSort2(int *a, int l, int r, int rekk=0)
{
    int x, i, j, t;
    if (rekk>rek) {
        rek=rekk;
    }
    while (l<r) {
        i=l;
        j=r;
        x=a[l];
        while (i<=j) {
            while (i<=j && a[i]<x) {
                i++;
            }
            while (i<=j && a[j]>x) {
                j--;
            }
            if (i<=j) {
                t=a[i];
                a[i]=a[j];
                a[j]=t;
                i++; j--;
            }
        }
        if (j-l>r-i) {
            if (i<r) {
                rekk++;
                QuickSort2(a, i, r, rekk);
            }
            r=j;
        } else {
                if (l<j) {
                    QuickSort2(a, l, j, rekk++);
                }
                l=i;
        }
    }
}

void QuickSort(int *a, int left, int right, int rekk=0)
{
    if (rekk>rek) {
        rek=rekk;
    }
    int current, i, j, t;
    current=a[left]; i=left; j=right;
    while (i<=j) {
        while (a[i]<current) {
            i++;
        }
        while (a[j]>current) {
            j--;
        }
        if (i<=j) {
            M+=3;
            t=a[i];
            a[i]=a[j];
            a[j]=t;
            i++; j--;
        }
    }

    if (left<j) {
        QuickSort(a, left, j, rekk+1);
    }
    if (i<right) {
        QuickSort(a, i, right, rekk+1);
    }
}
