#include <cstdlib>
#include <string.h>
#include <iostream>
#include <locale>
#include <windows.h>

using namespace std;

int const n=3;
struct abo{
	int index;
	char name[20];
	char phone[15];
};

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void ShakerSortName(struct abo A[], int *arr_name, int n) //Шейкерная сортировка индекса 
{
	int i, L=0, R=n-1, k=n;
	do{
		for(i=R; i>=L+1; i--)
			if(strcmp(A[arr_name[i]].name, A[arr_name[i-1]].name) < 0)
			{
				swap(&arr_name[i], &arr_name[i-1]);
				k=i;
			}
		L=k;
		for(i=L; i<=R-1; i++)
			if(strcmp(A[arr_name[i]].name, A[arr_name[i+1]].name) > 0)
			{ 
				swap(&arr_name[i], &arr_name[i+1]);
				k=i;
			} 
		R=k;
	}while(L<R);
}

void ShakerSortIndex(struct abo A[], int *arr_index, int n)// Шейкерная сортировка индекса 
{ 
	int i, L=0, R=n-1, k=n;
	do{
		for(i=R; i>=L+1; i--)
			if(A[arr_index[i]].index < A[arr_index[i-1]].index)
			{
				swap(&arr_index[i], &arr_index[i-1]);
				k=i;
			}
		L=k;
		for(i=L; i<=R-1; i++)
			if(A[arr_index[i]].index > A[arr_index[i+1]].index)
			{ 
				swap(&arr_index[i], &arr_index[i+1]);
				k=i;
			} 
		R=k;
	}while(L<R);
}

void Output1(struct abo A[], int *arr, int size, int R){
	cout << endl << "--------------------------------"<< endl;
	do{
		R++;
		printf(" %-5d", A[arr[R]].index);
		printf(" %-20s", A[arr[R]].name);
		printf(" %-15s", A[arr[R]].phone);
		printf("\n");
		if(R>=size) break;
	}
	while(R<size && strcmp(A[arr[R]].name, A[arr[R+1]].name)==0);
	cout << endl << "--------------------------------"<< endl;
}

void BSearch_name(struct abo A[], int *arr, int size, char *key){
	int L=0, R=size-1;
	int m;
	while (L < R){
		m = (L+R)/2;
		if (strcmp(A[arr[m]].name, key)<0) L = m+1;
		else R = m;
	}
	if (strcmp(A[arr[R]].name, key) == 0) Output1(A, arr, size-1, R-1);
	else 
	cout << "Запись с зданным ключом не найдена в справочнике \n";
}

void BSearch_index(struct abo A[], int *arr, int size, int key){
	int L=0, R=size-1;
	int m;
	while (L < R){
		m = (L+R)/2;
		if (A[arr[m]].index < key) L = m+1;
		else R = m;
	}
	if (A[arr[R]].index == key) Output1(A, arr, size-1, R-1);
	else 
	cout << "Запись с зданным ключом не найдена в справочнике \n";
}

main()
{
	setlocale(LC_ALL, "russian");
	int i,m, key2;
	abo A[n];
	char key1[20];
	int arr_name[n], arr_index[n];
	for(int i=0; i<n; i++){
    	arr_name[i] = i;
    	arr_index[i] = i;
	}
	printf("\n Введите информацию:\n");
	for (i=0;i<n;i++)
  	{
		printf("\n Индекс, фамилия, телефон:  ");
		SetConsoleCP(1251);
     	scanf("%d %s %s", &A[i].index, &A[i].name, &A[i].phone);
     	SetConsoleCP(866);
  	}
  	std::cout << std::endl;
  	for (i=0;i<n;i++)
  	{
  	printf(" %d %s %s",A[i].index,A[i].name,A[i].phone);
  	printf("\n");
  	}
  	cout << endl << "Отсортированная запись по фамилиям:" << endl;
	ShakerSortName(A, arr_name, n);
	cout << endl;
	for (i = 0; i < n; i++)
	{
  	printf(" %d %s %s\n",A[arr_name[i]].index,A[arr_name[i]].name,A[arr_name[i]].phone);
  	}
  	cout << endl << "Отсортированная запись по индексам:" << endl;
	ShakerSortIndex(A, arr_index, n);
	cout << endl;
	for (i = 0; i < n; i++)
	{
  	printf(" %d %s %s\n",A[arr_index[i]].index, A[arr_index[i]].name, A[arr_index[i]].phone);
  	}
  	cout << endl << "Ведите ключ имени:" << endl;
  	SetConsoleCP(1251);
    scanf("%s", &key1);
    SetConsoleCP(866);
  	BSearch_name(A, arr_name, n, key1);
  	cout << endl << "Ведите ключ ндекса:" << endl;
    scanf("%d", &key2);
  	BSearch_index(A, arr_index, n, key2);
  	return 0;
}
