
#include <iostream>
#include <cctype>
#include <locale.h>
#include <stdlib.h>
#include <ctime>

struct ver
{
	int v;
	int w;
	bool use;
	ver() { v = w = 0; use = false; }
};

struct tr //// структура  узла деревьев
{
	int h;
	ver val;
	tr* l;
	tr* r;
	tr(ver k) { val = k; h = 1; l = r = NULL; }
};

int n_ind(ver*, int, int);				//// Функция определения индекса элемента - корня поддерева (алгоритм А2)
tr* insert_A2(ver* x, int L, int R);			//// Функция построения оптимального дерева поиска по алгоритму А2
void insert_A1(tr*&, ver*, int);			//// Функция построения оптимального дерева поиска по алгоритму А1
void insert_SDP(tr*&, ver);				  //// Функция построения СДП
int irand(int, int);					//// генерация случайных чисел из диапазона a..b
int* r_mas(int);					 //// Массив случайных уникальных чисел заданной размерности
void b_sort(ver* M, int n_m);				 //// Сортировка 
void obhod(tr*);					//// Обход: левое поддерево, корень, правое поддерево. 
int dim_t(tr*);						//// Определение размера дерева
double s_height(tr*);					//// Определение средней высоты дерева
int SDP(tr*, int);					////сумма длин путей от корня до каждой вершины. 
int cont_s(tr*);					  //// Определение контрольной суммы для дерева

void f_h(tr* );							////**************************
int height(tr*);						//// Расчет средневзвешенной
int vysota(tr*);						////     высоты
void sred_vz(tr*, int, int&, int&);				////*****************************

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned)time(0));

	tr* tree = NULL;
	tr* tree1 = NULL;

	int n;	
	cout << endl << "Введите число узлов   n = ";
	cin >> n;

	ver* x = new ver[n];
	int* mas = r_mas(n);

	//////

	for (int i = 0; i < n; i++)
	{
		x[i].v = mas[i];
		x[i].w = irand(1, 20);
	}

	////    A1    ////

	int W = 0;
	int P = 0;
	double Hcp;

	insert_A1(tree, x, n);


	int vh = vysota(tree);

	sred_vz(tree, vh, P, W);

	Hcp = (double)P / (double)W;

	cout << endl << "Алгоритм А1, обход  дерева  слева направо:  " << endl << endl;
	obhod(tree);
	cout << endl << endl;
	cout << "Средневзвешенная высота(А1) :   " << Hcp << endl;
	cout << "Размер   дерева(А1),  узлов :   " << dim_t(tree) << endl;
	cout << "Средняя  высота  дерева (А1):   " << s_height(tree) << endl;
	cout << "Контрольная сумма дерева(А1):   " << cont_s(tree) << endl;

	//////  A2 /////



	b_sort(x, n); /// сортировка - подготовка исходных данных

	int W1 = 0;
	int P1 = 0;
	double Hcp1;

	tree1=insert_A2(x, 0, n - 1);

	int vh1 = vysota(tree1);

	sred_vz(tree1, vh1, P1, W1);

	Hcp1 = (double)P1 / (double)W1;



		

	cout << endl << "Алгоритм А2, обход  дерева  слева направо:  " << endl << endl;
	obhod(tree1);
	cout << endl << endl;
	cout << "Средневзвешенная высота(А2) :   " << Hcp1 << endl;
	cout << "Размер   дерева(А2),  узлов :   " << dim_t(tree1) << endl;
	cout << "Средняя  высота  дерева (А2):   " << s_height(tree1) << endl;
	cout << "Контрольная сумма дерева(А2):   " << cont_s(tree1) << endl;


	system("pause");

	return 0;
}

int n_ind(ver*x, int L, int R)
{
	if (L < R)
	{
		double wes = 0;
		int sum = 0;

		for (int i = L; i <= R; i++)
			wes = wes + x[i].w;

		for (int i = L; i <= R - 1; i++)
		{
			if (sum < wes / 2 && sum + x[i].w >= wes / 2)
			{
				return i;
				break;
			}
			sum = sum + x[i].w;
		}
	}
	else
		return L;
}

tr* insert_A2(ver* x, int L, int R)
{

	if (L > R)
		return NULL;
	else
	{
		int m = n_ind(x, L, R);

		tr* p = new tr(x[m]);

		p->l = insert_A2(x, L, m - 1);
		p->r = insert_A2(x, m + 1, R);

		f_h(p);
		return p;

	}
}

void insert_A1(tr*& p, ver* k, int n)
{
	for (int i = 0; i < n; i++)
	{
		int max = 0;
		int index = 0;

		for (int j = 0; j < n; j++)
			if (k[j].w> max &&k[j].use == false)
			{
				max = k[j].w;
				index = j;
			}
		k[index].use = true;
		insert_SDP(p, k[index]);
	}
}

void insert_SDP(tr*& p, ver k)
{
	if (!p)
		p = new tr(k);
	else
		if (k.v < p->val.v)
			insert_SDP(p->l, k);
		else
			insert_SDP(p->r, k);
	f_h(p);
}

void b_sort(ver* M, int n_m)
{
	for (int i = 0; i<n_m; ++i)
		for (int j = i + 1; j<n_m; ++j)
			if (M[j].v<M[i].v)
				swap(M[i], M[j]);
}

int* r_mas(int n_m)
{
	int* M = new int[n_m];
	M[0] = irand(0, 999);
	for (int i = 1; i < n_m; i++)
	{

		int r;
		bool f = true;
		while (f)
		{
			r = irand(0, 999);

			for (int j = 0; j < i; j++)
				if (M[j] == r)
				{
					f = true;
					break;
				}
				else
					f = false;
		}
		M[i] = r;
	}

	return M;
}

int irand(int a_m, int b_m)
{
	return rand() % (b_m - a_m + 1) + a_m;
}

int cont_s(tr* p)
{
	if (p == NULL)
		return 0;
	else
		return p->val.v + cont_s(p->l) + cont_s(p->r);
}

double s_height(tr* p)
{
	return (double)SDP(p, 1) / (double)dim_t(p);
}

int SDP(tr* p, int L_m)
{
	if (p == NULL)
		return 0;
	else
		return L_m + SDP(p->l, L_m + 1) + SDP(p->r, L_m + 1);
}

int dim_t(tr* p)
{
	if (p == NULL)
		return 0;
	else
		return 1 + dim_t(p->l) + dim_t(p->r);
}

void obhod(tr* p)
{
	if (p != NULL)
	{
		obhod(p->l);
		cout << " " << p->val.v;
		obhod(p->r);
	}
}

int height(tr* p)
{
	return p ? p->h : 0;
}

void f_h(tr* p)
{
	int hl = height(p->l);
	int hr = height(p->r);
	p->h = (hl>hr ? hl : hr) + 1;
}

int vysota(tr* p)
{
	if (!p)
		return 0;
	else
		return 1 + (vysota(p->l) > vysota(p->r) ? vysota(p->l) : vysota(p->r));
}

void sred_vz(tr* p, int l, int& hs, int& ws)
{
	if (p != NULL)
	{
		sred_vz(p->l, l, hs, ws);
		hs = hs + (l - p->h + 1)*p->val.w;
		ws = ws + p->val.w;
		sred_vz(p->r, l, hs, ws);
	}
}
