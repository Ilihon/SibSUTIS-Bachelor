#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include "funkzy.h"

using namespace std;

const int N = 100;
int L, R, a[N];
using namespace std;

struct vertex
{
	int data;
	vertex *left;
	vertex *right;
};

vertex *root, *p;

//��������-�����������������
vertex* ISDP(int L, int R);
//���������� ������� ������
int TreeSize(vertex*);
//���������� ������ ������
int TreeHeight(vertex*);
//����� ������������
int Max(int l, int r);
//���������� ������� ������
int SumDlinPutey(vertex*, int);
//���������� ����������� �����
long Sum(vertex* p);
//����� ����� �������
void PrintLR(vertex* x);

int main()
{
	setlocale(LC_ALL,"Russian");
	for (int i = 0; i < N; i++) {
		a[i] = i;
	}	
	int m = (0 + N-1) / 2;
	vertex *root = new vertex; 
    root->data = a[m];
	root->left = ISDP(0, m - 1);
	root->right = ISDP(m + 1, N-1);
		
	PrintLR(root);
	printf("\n������ ������ = %d\n", TreeSize(root)); 
	printf("����������� ����� = %d\n", Sum(root)); 
	printf("������ ������ = %d\n", TreeHeight(root));
	printf("������� ������ ������ = %f\n", (double)SumDlinPutey(root, 1)/TreeSize(root));
    system("PAUSE");
}

vertex * ISDP (int L, int R) //����
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

void PrintLR(vertex *x) // ������� ���������� ������ ������� ����� �������
{ 
	if (x == NULL) return;
	PrintLR(x->left);
	cout << x->data << ' ';
	PrintLR(x->right);
}

int TreeSize(vertex *p) // ��������� ������ ������
{
    if (p == NULL)
    return 0;
    return 1 + TreeSize(p->left) + TreeSize(p->right);
}

long Sum(vertex *p) // ��������� ����������� ����� ������ � �������� ������
{
    if (p == NULL)
    return 0;
    return p->data + Sum(p->left) + Sum(p->right);
}

int Max(int l, int r) // ���������� ������������ ����� ����� l � r
{
    if (l > r)
    return l;
    return r;
}

int TreeHeight(vertex *p) // ��������� ������ ������
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
