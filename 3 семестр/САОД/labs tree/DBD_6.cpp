#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

bool rost = 1;
const int N = 12;
int A[N] = {2, 16, 15 ,5, 1, 18, 6, 12, 20, 17, 3, 13};
bool VR = 0;//Вертикальный рост дерева
bool HR = 1;//Горизонтальный рост дерева
int levels = 0;


struct Vertex {
	int data;
	int bal;
	struct Vertex* left;
	struct Vertex* right;
};

void ObxodsLnR(Vertex* p) { // обход слева-направо с выводом баланса
	if (p != NULL) {
		ObxodsLnR(p->left);
		cout << p->data << ", bal= " << p->bal << "; ";
		ObxodsLnR(p->right);
	}
}

void LeftRight(Vertex* root) //обход слева-направо
{
	if (root == NULL)
		return;
	LeftRight(root->left);
	if (root->data)
		printf("%d ", root->data);
	LeftRight(root->right);
}

void FillRand(int* A, int n) //заполнение массива случайными значениями
{
	bool chislo;

	for(int i=0; i<n;)
	{
		chislo = false;
		int random = rand() % 22 + 1;

		for(int j=0; j<i; j++)
			{
				if (A[j] == random)
				{
				chislo = true;
				break;
				}
			}
	
		if (!chislo)
		{
			A[i] = random;
			i++;
		}
	}
}



void ObxodUnD(Vertex* p) //обход сверху-вниз с выводом балансровки
{
	if(p!=NULL){
		cout << p->data << ", bal= " << p->bal << "; ";
		ObxodUnD(p->left);
		ObxodUnD(p->right);
	}
}

void UpDown(Vertex* root) //обход сверху-вниз
{
    if (root == NULL)
        return;
    if (root->data)
        printf("%d ", root->data);
    UpDown(root->left);
    UpDown(root->right);
}


void B2Insert (int d,Vertex*& p) // вставака вершины в ДБД дерево
{
	Vertex* q = new Vertex;
	if(p == NULL) //ели вершины нет
	{
		p = new Vertex;
		p->data = d;
		p->left = NULL;
		p->right= NULL;
		p->bal = 0;
		VR = 1;
		levels++;
	}
	else if(p->data > d) // если значение меньше текужей вершины
	{
		B2Insert(d,p->left);
		if(VR == 1)  //балансировка дерева
		{
			if(p->bal == 0)
			{
				q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->bal = 1;
				VR = 0;
				levels--;
				HR = 1;	
				
			}
			else
			{
				p->bal = 0;
				VR = 1;
				levels++;
				HR = 0;	
			}
		}
		else
		{
			HR = 0;
		}
	}else if(p->data < d)
	{
		B2Insert(d,p->right);
		if(VR == 1)
		{
			p->bal = 1;
			HR = 1;
			VR = 0;
			levels--;
		}else if(HR==1)
		{
			if(p->bal == 1)
			{
				q= p->right;
				p->bal = 0;
				q -> bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				VR = 1;
				levels ++;
				HR = 0;	
			}else
			{
				HR = 0;
			}
			
		}
	}
}

//считает количество уровней по левой ветке
int countLevels(Vertex *root, int counter = 0) 
{
	if(root == nullptr)
	{
		return counter;//Счетчик возврата
	}
	
	return countLevels(root -> left, counter + 1);
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	Vertex* root = NULL;
	FillRand(A,N); //случайное заполнение массива

	for (int i = 0; i < 12; i++) {
		B2Insert(A[i],*&root); //вставка элемента массива в дерево
		LeftRight(root); //LR обход дерева
		cout << endl;
	}
	cout << endl;
	
	
	LeftRight(root);//LR обход дерева
	cout << endl;
	cout << countLevels(root, 0) << " - количество уровней" << endl; //количество уровней по левой ветке
	cout << levels << endl; //длина самой длинной вершины
}
