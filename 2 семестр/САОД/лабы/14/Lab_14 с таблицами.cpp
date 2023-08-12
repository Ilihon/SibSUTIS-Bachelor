#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

const int m = 5;

struct spis{
	spis *next;
	int x;
} *head[m];

int hf(int *a, int i, int m){
	return  a[i] % m;
}

void FillRand (int *a, int *b, int *c, int n) 
{
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100 + 1;
		b[i] = 0;
		c[i] = 0;
	}
	for(int i = 0; i < m; i++)
		head[i] = NULL;
}

void FillSpis (int *a, int n)
{	
for (int i = 0; i < n; i++)
	{
	int j = hf(a, i, m);
	spis *el = new spis;
	el -> x = a[i];
	el -> next = head[j];
	head[j]=el;
	}
}

void PrintSpis ()
{	
     spis *p;
	 for (int i = 0; i < m; i++)
	 {
		 cout<<i; 
		 for(p = head[i]; p != NULL; p = p -> next)
		 cout<<" "<<p -> x;
		 cout<<"\n";
	 }
}

void SearchSpis (int *a)
{ 
	int status = 0, elem;
	spis *p;
	while (!status)
	{
		 cout<<"\n\nВведите значение для поиска:";
		 cin>>elem;
		 int j = elem % m;
		 for (p = head[j]; p; p = p -> next)
		 {
				if (p -> x == elem) 
				{
					 cout<<"Элемент найден\n";
					 break;
				}
				else 
					 if (p -> next == NULL) 
					 	cout<<"Элемент не найден\n";
		 }
		 cout<<"Продолжить? (0 - Да, 1 - Hет)";
		 cin>>status; 
	}
}

int Square (int *a, int *b, int n)
{
	int kol = 0;
	for (int i = 0; i < n; i++)
	{
		 int j = hf(a, i, n);
		 int d = 1;
		 while (1)
		 {
			if (b[j] == a[i]) break;
			if (b[j] == 0)
			{	
				b[j] = a[i];
				break;
			}
			if (d >= n) return kol;
			j += d;
			kol++;
			if (j >= n) j -= n;
			d += 2;
		}
	}
	return kol;
}

int Line (int *a, int *c, int n)
{
	int kol = 0;
	for (int i = 0; i < n; i++)
	{
		int j = hf(a, i, n);
		while (1)
		{
			if (c[j] == a[i]) break;
			if (c[j] == 0)
			{	
				 c[j] = a[i];
				 break;
			}
			j++;
			if (j >= n) j -= n;
			kol++;
		}
	}
	return kol;
}

void PrintMas(int *a, int b)
{
	for(int i = 0;i < b;i++)
	cout<<a[i]<<"\t";
}

void PrintMark(int n)
{
	 for(int i = 0;i < n;i++)
	 cout<<i<<"\t";
}

int main()
{     
     setlocale(LC_ALL, "Russian");
     srand(time(NULL));
     int n;
	 cout<<"Количество элементов:";
	 cin>>n;
	 int a[n], b[n], c[n];
	 FillRand (a, b, c, n);
	 FillSpis(a, n); 
	 int kolS = Square (a, b, n);
	 int kolL = Line (a, c, n);
	 cout<<"\nИсходный массив:\n";PrintMas(a, n);cout<<"\n";
	 //cout<<"\nМетод прямого связывания:\n";PrintSpis();
	 cout<<"\nКвадратичные пробы:\n";
	 PrintMark(n);
	 cout<<"\n"; 
 	 PrintMas(b, n); 
	 cout<<"\n";
	 cout<<"\nЛинейные пробы:\n";
	 PrintMark(n);
	 cout<<"\n"; 
 	 PrintMas(c, n); 
	 cout<<"\n\n";
	 cout<<" Размер хеш   Колич. Исходных         Количество коллизий        \n"; 
	 cout<<"  таблицы        символов        линейные        квадратичные    \n\n"; 
	 cout<<n<<"\t\t"<<n<<"\t\t"<<kolL<<"\t\t"<<kolS<<"\t";
	 SearchSpis (a); 
	 getch();
}
