#include <iostream>
#include <math.h>
#include <time.h>
#include<stdlib.h>

using namespace std;

bool rost = 1;
const int N = 10;
int A[N] = { 0 };


struct Vertex {
	int data;
	int bal;
	struct Vertex* left;
	struct Vertex* right;
};

void LeftRightbalance(Vertex* p) {
	if (p != NULL) {
		LeftRightbalance(p->left);
		cout << p->data << ", bal= " << p->bal << "; ";
		LeftRightbalance(p->right);
	}
}

void LeftRight(Vertex* root)
{
	if (root == NULL)
		return;
	LeftRight(root->left);
	if (root->data)
		printf("%d ", root->data);
	LeftRight(root->right);
}

void FillRand(int* A, int n)
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

void LL(Vertex*& tree) {
	Vertex* q = tree->left;
	tree->bal = 0;
	q->bal = 0;
	tree->left = q->right;
	q->right = tree;
	tree = q;
	cout << " - " << tree->right->data  << " " << tree->data << " " << tree->left->data << endl;
}

void RR(Vertex*& tree) {
	Vertex* q = tree->right;
	tree->bal = 0;
	q->bal = 0;
	tree->right = q->left;
	q->left = tree;
	tree = q;
	cout << " - " << tree->left->data << " " << tree->data << " " << tree->right->data << endl;
}

void LR(Vertex*& tree) {
	Vertex* q = tree->left;
	Vertex* r = q->right;
	if (r->bal < 0)
		tree->bal = 1;
	else
		tree->bal = 0;
	if
		(r->bal > 0) q->bal = -1;
	else
		q->bal = 0; 
	r->bal = 0;
	q->right = r->left;
	tree->left = r->right;
	r->left = q;
	r->right = tree;
	tree = r;
	cout << " - " << tree->right->data << " " << tree->left->data << " " << tree->data  << " " << endl;
}

void RL(Vertex*& tree) {
	Vertex* q = tree->right;
	Vertex* r = q->left;
	if (r->bal < 0)
		tree->bal = 1;
	else
		tree->bal = 0;
	if (r->bal > 0)
		q->bal = -1;
	else
		q->bal = 0;
	r->bal = 0;
	q->left = r->right;
	tree->right = r->left;
	r->right = q;
	r->left = tree;
	tree = r;
	cout << " - "  << tree->left->data  << " " << tree->right->data << " " << tree->data << endl;
}

void Add_ABL(int X, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->data = X;
		p->left = NULL;
		p->right = NULL;
		p->bal = 0;
		rost = 1;
	}
	else if (p->data > X) {
		Add_ABL(X, *&p->left);
		if (rost == 1) {
			if (p->bal > 0) {
				p->bal = 0;
				rost = 0;
			}
			else if (p->bal == 0) {
				p->bal = -1;
			}
			else {
				if (p->left->bal < 0) {
					cout << "LL";
					LL(p);
					rost = 0;
				}
				else {
					cout << "LR";
					LR(p);
					rost = 0;
				}
			}
		}
	}
	else if (p->data < X) {
		Add_ABL(X, *&p->right);
		if (rost == 1) {
			if (p->bal < 0) {
				p->bal = 0;
				rost = 0;
			}
			else if (p->bal == 0) {
				p->bal = 1;
			}
			else {
				if (p->right->bal > 0) {
					cout << "RR";
					RR(p);
					rost = 0;
				}
				else {
					cout << "RL";
					RL(p);
					rost = 0;
				}
			}
		}
	}
	
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	Vertex* root = NULL;
	int Rand, X;
	FillRand(A,N);
	for (int i = 0; i < 10; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {

		Add_ABL(A[i], *&root);
		LeftRightbalance(root);
		cout << endl;
	}
	cout << endl;
	LeftRight(root);

}
