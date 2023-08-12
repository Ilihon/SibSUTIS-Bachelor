#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <random>
#include <chrono>
#include <set>
#include <algorithm>

using namespace std;

struct Vertex
{
	Vertex* left;
	Vertex* right;
	int data;
	int w;
};

Vertex* root{ nullptr };
Vertex* root2{ nullptr };
Vertex* root3{ nullptr };

void recursiveSDP(Vertex*& p, int D, int weight)  //добавление вершины
{
	if (p == nullptr)
	{
		p = new Vertex;
		p->data = D;
		p->w = weight;
		p->left = nullptr;
		p->right = nullptr;
	}
	else if (D < p->data)recursiveSDP(p->left, D, weight);
	else if (D > p->data)recursiveSDP(p->right, D, weight);
}

void leftToRight(Vertex* p) 
{
	if (p != nullptr) 
	{
		leftToRight(p->left);
		cout << p->data << "(" << p->w << ")" << " ";
		leftToRight(p->right);
	}
}


int* w;
int* V;
int* v = new int[10];
int* l;
int** Aw, ** Ap, ** Ar;
int N;


void AwCalculation(int n) //рассчёт матрицы весов поддеревьев
{
	Aw = new int*[n];
	for (size_t i = 0; i < n; ++i)
	{
		Aw[i] = new int[n];
	}
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			Aw[i][j] = 0;
		}
	}
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (i == j)Aw[i][j] = 0;
		}
	}
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			Aw[i][j] = Aw[i][j - 1] + w[j];
		}
	}
}

void ApAndArCalculation(int n) 	//рассчёт матрицы взвешенной высоты
{
	Ap = new int* [n];
	Ar = new int* [n];
	for (size_t i = 0; i < n; ++i)
	{
		Ap[i] = new int[n];
		Ar[i] = new int[n];
	}
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			Ap[i][j] = 0;
			Ar[i][j] = 0;
		}
	}

	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int h = j - i;
			if (h == 1)
			{
				for (int k = 0; k < n - 1; k++)
				{
					int t = k + 1;
					Ap[k][t] = Aw[k][t];
					Ar[k][t] = t;
				}
			}
			else if(h > 1)
			{
				for (h; h < n; h++)
				{
					for(int k = 0; k < n - h; k++)
					{
						int t = k + h;
						int m = Ar[k][t - 1];
						int min = Ap[k][m - 1] + Ap[m][t];
						for (int r = m + 1; r < Ar[k + 1][t]; r++)
						{
							int x = Ap[k][r - 1] + Ap[r][t];
							if (x < min)
							{
								m = r;
								min = x;
							}
						}
						Ap[k][t] = min + Aw[k][t];
						Ar[k][t] = m;
					}
				}
			}
		}
	}
}

void Vout(int n) // вывод значений вершин и весов
{
	for (size_t i = 1; i < n; ++i)
	{
		cout << V[i] << "(" << w[i] << ")" << " ";
	}
}

void out(int** a, int n)
{
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			cout << setw(4) << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}




void input() //генерация значений дерева и их веса
{
	cout << "Введите количество элементов"<<endl;
	cin >> N;
	N++;
	w = new int[N - 1];
	V = new int[N];
	w[0] = 0;
	V[0] = 0;
	for (size_t i = 0; i < N; i++)
	{
		int temp = rand() % 10 + 1;
		w[i] = rand() % 89 +10;
		V[i] = rand() % 89 + 1 ;
		int temp2 = V[i];
		for (int j = 0; j < N; j++)
		{
			if (V[j] == temp2)
			{
				V[i] += i + j;
			}
		}

	}
	//сортировка вершин
	for (size_t i = 1; i < N; ++i)
	{
		for (size_t j = i; j < N; ++j)
		{
			if (V[i] > V[j])
			{
				int tmp = V[j];
				V[j] = V[i];
				V[i] = tmp;
			}
		}
	}
}

void CreateTree(int L, int R) //создание дереве 
{
	int k;
	if (L < R)
	{
		k = Ar[L][R];
		recursiveSDP(root, V[k], w[k]); //добавление вершины
		CreateTree(L, k - 1);
		CreateTree(k, R);
	}
}

int SearchLevel(Vertex* p, int key) //нахождение уровня вершины
{
	int h = 1;
	while (p != nullptr)
	{
		if (key < p->data)
		{
			p = p->left;
			h++;
		}
		else if (key > p->data)
		{
			p = p->right;
			h++;
		}
		else return h;
	}
}



double TreeHeight(Vertex *root) //расчёт средневзвешенной высоты
{
	double W = 0;
	l = new int[N];
	int h = 0;
	for (size_t i = 1; i < N; ++i)
	{
		l[i] = SearchLevel(root, V[i]);
		W += w[i];
		h += w[i] * l[i];
	}
	return (double)h / W;
}

void A1(Vertex *&p) //создание дерева А1
{
    for (int i = 1; i < N; i++){
        recursiveSDP(*&p, V[i], w[i]);
    }
}

void A2(int L, int R) //создание дерева А2
{
    int wes = 0;
    int sum = 0;
    if(L <= R){
        for(int i = L + 1; i < R + 1; i++){
                wes = wes + w[i];
        }
        for(int i = L + 1; i < R + 1; i++){
            if((sum < (wes / 2)) && (sum + w[i] ) > (wes / 2)){
                sum = sum + w[i];
            }
			recursiveSDP(root3, V[i], w[i]);
            A2(L, i - 1);
            A2(i + 1, R);
        }
    }
}

int main()
{
	setlocale(LC_ALL,"Russian");
	srand((unsigned)time(NULL));
	input();
	
	cout << "Массив: ";
	Vout(N); //вывод весов и значений
	AwCalculation(N);
	ApAndArCalculation(N);
	cout <<endl<< "Aw:"<<endl;
	out(Aw, N); //вывод матрицы AW
	cout << "Ap:"<<endl;
	out(Ap, N); //вывод матрицы Ap
	cout << "Ar:"<<endl;
	out(Ar, N); //вывод матрицы Ar
	CreateTree(0, N - 1); // создание дерева
	cout <<endl<< "Дерево: ";
	leftToRight(root); // вывод дерева слева-направо
	cout << endl;
	cout << "Средневзвешенная высота дерева " << setprecision(4) << TreeHeight(root); 
	cout << endl << "Средневзвешенная высота дерева по матрице: " << setprecision(4) << (double)Ap[0][N - 1] / (double)Aw[0][N - 1];
	cout << endl;
	cout<<"результат алгоритма A1"<<endl;
	A1(root2); //генерация дерева А1
	leftToRight(root2); // вывод дерева А1
	cout << endl;
	cout << "Средневзвешенная высота дерева A1: " <<setprecision(4) << TreeHeight(root2)<<endl;
	cout << endl;
	cout<<"результат алгоритма A2"<<endl;
	A2(0, N - 1);//генерация дерева А2
	leftToRight(root3); // вывод дерева А2
	cout << endl;
	cout << "Средневзвешенная высота дерева A2: "<< setprecision(4) << TreeHeight(root3)<<endl;
	cout << endl;

	//очистка памяти
	delete[]l;4
	delete[]w;
	delete[]V;
	delete root;
	delete root2;
	delete root3;

	for (size_t i = 0; i < N; ++i)
	{
		delete Aw[i];
		delete Ar[i];
		delete Ap[i];
	}
	delete[]Ar;
	delete[]Ap;
	delete[]Aw;

	return 0;
}
