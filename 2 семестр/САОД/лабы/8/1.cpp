#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>

using namespace std;

void SelectSort (int *A, int n, int z);
int Srav (struct spravka x, struct spravka y, int z);
void BSearch_name(struct spravka A[], int *arr, int size, char *key);
void BSearch_city(struct spravka A[], int *arr, int size, char *key);
void BSearch_surname(struct spravka A[], int *arr, int size, char *key);
void BSearch_phone(struct spravka A[], int *arr, int size, char *key);


struct spravka 
{
	char sir[10];
	char name[13];
	char city[12];
	char phone[16];
};
struct spravka abonent[5];

int Cprak=0;

void Swap (int &x, int &y)
{
	int t=x; x=y; y=t;
}

void spis () 
{
	strcpy (abonent[0].sir, "Stoyak");
	strcpy (abonent[1].sir, "Koloss");
	strcpy (abonent[2].sir, "Burdukovskiy");
	strcpy (abonent[3].sir, "Vedington");
	strcpy (abonent[4].sir, "Cartman");
	
	strcpy (abonent[0].name, "Yri");
	strcpy (abonent[1].name, "Yana");
	strcpy (abonent[2].name, "Ilia");
	strcpy (abonent[3].name, "Jonathan");
	strcpy (abonent[4].name, "Erick");
	
	strcpy (abonent[0].city, "Novosibirsk");
	strcpy (abonent[1].city, "Ufa");
	strcpy (abonent[2].city, "Novosibirsk");
	strcpy (abonent[3].city, "LA");
	strcpy (abonent[4].city, "South park");
	
	strcpy (abonent[0].phone, "8-913-980-32-01");
	strcpy (abonent[1].phone, "8-913-548-53-76");
	strcpy (abonent[2].phone, "8-897-177-90-61");
	strcpy (abonent[3].phone, "8-916-208-92-65");
	strcpy (abonent[4].phone, "8-917-918-19-20");
}

main() 
{
	setlocale(LC_ALL, "russian");
	spis ();
	int i, n=5;
	int A[n], B[n], C[n], V[n];
	for (i=0; i<n; i++) 
	{
	A[i]=i;
	B[i]=i;
	C[i]=i;
	V[i]=i;
	}
	SelectSort (A,n,0);
	SelectSort (B,n,1);
	SelectSort (C,n,2);
	SelectSort (V,n,3);
	for (i=0; i<n; i++) 
	{
		printf ("%s ", abonent[i].sir);
		printf ("%s ", abonent[i].name);
		printf ("%s ", abonent[i].city);
		printf ("%s ", abonent[i].phone);
		printf("\n");
	}
	printf("\n Отсортированная запись по именам\n\n");
	for (i=0; i<n; i++) 
	{
		printf ("%s ", abonent[A[i]].name);
		printf ("%s ", abonent[A[i]].sir);
		printf ("%s ", abonent[A[i]].city);
		printf ("%s ", abonent[A[i]].phone);
		printf("\n");
	}
	printf("\n Отсортированная запись по городам\n\n");
	for (i=0; i<n; i++) 
	{
		printf ("%s ", abonent[B[i]].city);
		printf ("%s ", abonent[B[i]].sir);
		printf ("%s ", abonent[B[i]].name);
		printf ("%s ", abonent[B[i]].phone);
		printf("\n");
	}	
	
	
		///////////////////// 5 +
	
	printf("\n\n");
	char key1[5],key2[16];
	cout << "Введите первый ключ: ";
	cin >> key1;
	cout << "\nВведите " << key1 << ": ";
	cin >> key2;
	
	
	n=5;
	if(strcmp ("name",key1)==0)
	{
		BSearch_name(abonent,A,n,key2); 
	}
	if(strcmp ("city",key1)==0)
	{
		BSearch_city(abonent,B,n,key2); 
	}
	if(strcmp ("surname",key1)==0)
	{
		BSearch_surname(abonent,C,n,key2); 
	}
	if(strcmp ("phone",key1)==0)
	{
		BSearch_phone(abonent,V,n,key2); 
	}
	
	system("PAUSE");
	return 0;
}

void BSearch_name(struct spravka A[], int *arr, int size, char *key){
	int L=0, R=size-1;
	int m;
	while (L < R){
		m = (L+R)/2;
		if (strcmp(A[arr[m]].name, key)<0) L = m+1;
		else R = m;
	}
	if (strcmp(A[arr[R]].name, key) == 0){
		printf ("%s ", A[arr[R]].name);
		printf ("%s ", A[arr[R]].sir);
		printf ("%s ", A[arr[R]].city);
		printf ("%s ", A[arr[R]].phone);
		printf("\n");
	}
	else 
	cout << "Запись с зданным ключом не найдена в справочнике \n";
}

void BSearch_city(struct spravka A[], int *arr, int size, char *key){
	int L=0, R=size-1;
	int m;
	while (L < R){
		m = (L+R)/2;
		if (strcmp(A[arr[m]].city, key)<0) L = m+1;
		else R = m;
	}
	if (strcmp(A[arr[R]].city, key) == 0){
		printf ("%s ", A[arr[R]].city);
		printf ("%s ", A[arr[R]].name);
		printf ("%s ", A[arr[R]].sir);
		printf ("%s ", A[arr[R]].phone);
		printf("\n");
	}
	else 
	cout << "Запись с зданным ключом не найдена в справочнике \n";
}	

void BSearch_surname(struct spravka A[], int *arr, int size, char *key){
	int L=0, R=size-1;
	int m;
	while (L < R){
		m = (L+R)/2;
		if (strcmp(A[arr[m]].sir, key)<0) L = m+1;
		else R = m;
	}
	if (strcmp(A[arr[R]].sir, key) == 0){
		printf ("%s ", A[arr[R]].sir);
		printf ("%s ", A[arr[R]].name);
		printf ("%s ", A[arr[R]].city);
		printf ("%s ", A[arr[R]].phone);
		printf("\n");
	}
	else 
	cout << "Запись с зданным ключом не найдена в справочнике \n";
}	

void BSearch_phone(struct spravka A[], int *arr, int size, char *key){
	int L=0, R=size-1;
	int m;
	while (L < R){
		m = (L+R)/2;
		if (strcmp(A[arr[m]].phone, key)<0) L = m+1;
		else R = m;
	}
	if (strcmp(A[arr[R]].phone, key) == 0){
		printf ("%s ", A[arr[R]].phone);
		printf ("%s ", A[arr[R]].name);
		printf ("%s ", A[arr[R]].sir);
		printf ("%s ", A[arr[R]].city);
		printf("\n");
	}
	else 
	cout << "Запись с зданным ключом не найдена в справочнике \n";
}		


void SelectSort (int *A, int n, int z) {
	int i, j ,k, t;
	for (i=0; i<(n-1); i++) {
		k=i;
		for (j=i+1; j<n; j++) {
			if (Srav(abonent [A[j]], abonent [A[k]], z)) k=j;
		}
		if (k!=i) {
			Swap (A[i], A[k]);
		}
	}
}

int Srav (struct spravka x, struct spravka y, int z) {
	int i;
	switch (z)
    {
	case 0: i=strcmp (x.name, y.name); if (i<0) return 1;
    else return 0; break;
	
    case 1: i=strcmp (x.city, y.city); if (i<0) return 1;
	else return 0; break;
	
	case 2: i=strcmp (x.sir, y.sir); if (i<0) return 1;
	else return 0; break;
	
	case 3: i=strcmp (x.phone, y.phone); if (i<0) return 1;
	else return 0; break;
	}
}	