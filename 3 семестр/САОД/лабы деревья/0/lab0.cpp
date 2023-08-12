#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

struct Vertex {
	int Data;
	Vertex* Left = NULL;
	Vertex* Right = NULL;
};

// Левое, корень, правое
void ObhodLeft(Vertex* p) {
	if (p != NULL) {
		ObhodLeft(p->Left);
		cout << p->Data << ", ";
		ObhodLeft(p->Right);
	}
}

// Размер дерева
int sizeVertex(Vertex* p) {
	if (p == NULL)
		return 0;
	else
		return (1 + sizeVertex(p->Left) + sizeVertex(p->Right));
}

// Контрольная сумма дерева 
int checkSum(Vertex* p) {
	if (p == NULL)
		return 0;
	else
		return (p->Data + checkSum(p->Left) + checkSum(p->Right));
}

// Сумма длин путей
int SumPaths(Vertex* p, int depth) {
	if (p == NULL)
		return 0;
	else
		return (depth + SumPaths(p->Left, depth + 1) +
			SumPaths(p->Right, depth + 1));
}

int maxHeight(int a, int b) {
	if (a < b)
		return b;
	else
		return a;
}

// Высота дерева 
int heightVertex(Vertex* p) {
	if (p == NULL)
		return 0;
	else
		return (1 + maxHeight(heightVertex(p->Left), heightVertex(p->Right)));
}

// Средняя высота дерева
float middleHeight(Vertex* p) {
	return (float(SumPaths(p, 1)) / sizeVertex(p));
}

Vertex* Init() {
	Vertex* p = new Vertex;
	p->Data = rand() % 100;
	return p;
}

void genVertex(Vertex*& p) {
	p = Init();
	cout << p->Data << " ";
	p->Left = Init();
	cout << p->Left->Data << " ";
	p->Right = Init();
	cout << p->Right->Data<< " ";
	(p->Right)->Left = Init();
	cout << (p->Right)->Left->Data<< " ";
	((p->Right)->Left)->Left = Init();
	cout << ((p->Right)->Left)->Left->Data<< " ";
	((p->Right)->Left)->Right = Init();
	cout<< ((p->Right)->Left)->Right->Data<< " ";
}

int main(int argc, const char** argv) {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Vertex* Root;
	genVertex(Root);
	cout << endl;
	cout << "Обход - левое, корень, правое : ";
	ObhodLeft(Root);
	cout << endl << "_____________________";
	cout << endl << "Размер дерева: ";
	cout << sizeVertex(Root);
	cout << endl << "Высота дерева: ";
	cout << heightVertex(Root);
	cout << endl << "Средняя высота дерева: ";
	cout << middleHeight(Root);
	cout << endl << "Контрольная сумма: ";
	cout << checkSum(Root);
	return 0;
}
