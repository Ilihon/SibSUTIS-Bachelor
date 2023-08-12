#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int N = 100;
int *a;

struct vertex
{
	vertex *left;
	vertex *right;
	int data;
};

vertex *root1 = NULL, *root2 = NULL, *root3=NULL;

//идеально-сбалансировванное
vertex* ISDP(int L, int R);
//случайное рекусрсивно
int recSDP(int, vertex*&);
//случайное двойной косвенностью
int SDP(int, vertex*&);
//Вычисление размера дерева
int TreeSize(vertex*);
//Вычисление высоты дерева
int TreeHeight(vertex*);
//Выбор максимальной
int Max(int l, int r);
//Вычисление средней высоты
int SumDlinPutey(vertex*, int);
//Вычисление контрольной суммы
long Sum(vertex* p);
//Обход слева направо
void PrintLR(vertex* x);
//
int delTree(vertex*&);

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	a = new int[N];

	for (int i = 0; i < N; i++) {
		a[i] = i;
	}
	root1 = ISDP(0, N - 1);
	
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 2000;
	}
	for (int i = 0; i < N; i++) {
		recSDP(a[i], root2);
	}
	
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 2000;
	}
	for (int i = 0; i < N; i++) {
		SDP(a[i], root3);
	}

	PrintLR(root1);
	cout << endl << "---" << endl;
	PrintLR(root2);
	cout << endl << "---" << endl;
	PrintLR(root3);
	cout << endl << "---" << endl;
	printf("+------+----------+----------------+----------+----------------+\n");
	printf("|%6d|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", N);
	printf("+------+----------+----------------+----------+----------------+\n");
	printf("| ИСДП |%10d|%16d|%10d|%16.2f|\n", TreeSize(root1), Sum(root1), TreeHeight(root1), (double)SumDlinPutey(root1, 1) / TreeSize(root1));
	printf("|  СДП |%10d|%16d|%10d|%16.2f|\n", TreeSize(root2), Sum(root2), TreeHeight(root2), (double)SumDlinPutey(root2, 1) / TreeSize(root2));
	printf("+------+----------+----------------+----------+----------------+\n");

    return 0;
}

vertex * ISDP (int L, int R) //ИСДП
{
	if (L>R) return NULL;
	else {
		int m = (L + R) / 2;
		vertex *p = new vertex; 
    	p->data = a[m];
		p->left = ISDP(L, m - 1);
		p->right = ISDP(m + 1, R);
		return p;
	}
}

int recSDP(int data, vertex* &p) //рекурсвивная СДП
{
	if (!p) {
		p = new vertex;
		p->data = data;
		p->left = NULL;
		p->right = NULL;

	} 
	else if (data < p->data) {
			recSDP(data, p->left);
	     }
		 else if (data > p->data) {
				  recSDP(data, p->right);
		      }
			  else {
				  return 0;
			  }
}

int SDP(int data, vertex* &point) //СДП с двойной косвенностью
{
	vertex **p = &point;

	while (*p) {
		if (data < (*p)->data) {
			p = &((*p)->left);
		}
		else if (data > (*p)->data) {
			p = &((*p)->right);
		}
		else break;
	}

	if (*p == NULL) {
		*p = new vertex;
		(*p)->data = data;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}

	return 0;
}

void PrintLR(vertex *x) // Выводит содержимое дерева обходом слева направо
{ 
	if (x == NULL) return;
	PrintLR(x->left);
	cout << x->data << ' ';
	PrintLR(x->right);
}

int TreeSize(vertex *p) // Вычисляет размер дерева
{
    if (p == NULL)
    return 0;
    return 1 + TreeSize(p->left) + TreeSize(p->right);
}

long Sum(vertex *p) // Вычисляет контрольную сумму данных в вершинах дерева
{
    if (p == NULL)
    return 0;
    return p->data + Sum(p->left) + Sum(p->right);
}

int Max(int l, int r) // Определяет максимальное число среди l и r
{
    if (l > r)
    return l;
    return r;
}

int TreeHeight(vertex *p) // Вычисляет высоту дерева
{
    if (p == NULL)
    return 0;
    return 1 + Max(TreeHeight(p->left), TreeHeight(p->right));
}

int SumDlinPutey(vertex *x, int L)
{
	if (x == NULL) {
		return 0;
	} else {
		return L + SumDlinPutey(x->left, L + 1) + SumDlinPutey(x->right, L + 1);
	}
}
