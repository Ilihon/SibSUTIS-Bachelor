#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int N = 10;
int *a;

struct vertex
{
	vertex *left;
	vertex *right;
	int data;
};

vertex *root = NULL;

//случайное рекусрсивно
void SDP(int data, vertex*& p);
//Вычисление размера дерева
int TreeSize(vertex* p);
//Вычисление высоты дерева
int TreeHeight(vertex* p);
//Выбор максимальной
int Max(int l, int r);
//Вычисление средней высоты
int SumDlinPutey(vertex*, int L);
//Вычисление контрольной суммы
long Sum(vertex* p);
//Обход слева направо
void PrintLR(vertex* x);
//удалить вершину из СДП
void delSDP(vertex *&Root, int point);

int main()
{
	int i,x;
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	a = new int[N];
	
	for (i = 0; i < N; i++) {
		a[i] = rand() % 100;
	}
	for (i = 0; i < N; i++) {
		SDP(a[i], root);
	}	
	while(1){	
		for (i = 0; i < N; i++) {
			cout << a[i] << " ";
		}
		cout<<"- изначальный массив" <<endl << "---" << endl;
	
		PrintLR(root);
		cout << "- обход слева-направо" << endl << "---" << endl;
		
		cout <<"Укажите вершину которую хотите удалить: ";
        cin>>x;
		delSDP(root,x);
        int j=0;
        for(int i=0; i<N; i++){
            if(a[i]==x){
                j=1;
            }
        }
        if(j) cout <<"CДП без вершины '"<<x<<"':"<<endl;
            else cout <<"Такой вершины нет, СДП осталось без изменений:"<<endl;
        PrintLR(root);
				
	    cout <<endl<<endl<<"Продолжить? 1/0: ";
        cin>>i;
        system("cls");
        if(i==0) break;
	}
    return 0;	   
}

void SDP(int data, vertex* &p) //рекурсвивная СДП
{
	if (!p) {
		p = new vertex;
		p->data = data;
		p->left = NULL;
		p->right = NULL;

	} 
	else if (data < p->data) {
			SDP(data, p->left);
	     }
		 else if (data > p->data) {
				  SDP(data, p->right);
		      }
			  else {
				  return;
			  }
}

void delSDP(vertex *&Root, int point){
        vertex **p = &Root;
        vertex *S;
        vertex *r;

        while((*p)!=NULL)                 ///Поиск элемента
        {
            if(point<((*p)->data)){
                    p=&((*p)->left);
            }else{
                    if(point>((*p)->data)){
                        p=&((*p)->right);
                }else break;
            }
        }

        if((*p)!=NULL){
            vertex *q=(*p);
            if(q->left==NULL) {(*p)=q->right;
            }else{
            /*2*/if(q->right==NULL){
				(*p)=q->left;
                }else{                           ///2 поддерева
                r = q->left; S=q;

                /*1*/if(r->right == NULL){
                        r->right=q->right;
                        (*p)=r;
                    }else{
                        while(r->right!=NULL){
                            S=r; r=r->right;
                        }
                        S->right=r->left;
                        r->left=q->left;
                        r->right=q->right;
                        (*p)=r;
                /*1*/}
            /*2*/}
            free(q);
            }
        }
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
