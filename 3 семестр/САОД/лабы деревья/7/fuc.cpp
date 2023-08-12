
#include "fuc.h"

extern vertex *root;
extern int *mas, *W;
extern int *h;
extern int c;
extern int  AW[N+1][N+1], AP[N+1][N+1], AR[N+1][N+1];

void AW_count() {
	for (int i = 0; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			AW[i][j] = AW[i][j - 1] + W[j - 1];
}

void AP_AR_count() {
	int min, m, x, j;
	for (int i = 0; i < N; i++) {
		j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for (int H = 2; H <= N; H++) {
		for (int i = 0; i <= N - H; i++) {
			j = i + H;
			m = AR[i][j - 1];
			min = AP[i][m - 1] + AP[m][j];
			for (int k = m + 1; k <= AR[i + 1][j]; k++) {
				x = AP[i][k - 1] + AP[k][j];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void add(vertex *&p, int x, int w) {
	if (p == NULL)
	{
		p = new vertex;
		p->data = mas[x - 1];
		p->w = w;
		p->left = NULL;
		p->right = NULL;
		//cout << p->data << " ";
	}
	else
		if (x < p->data) {
			add(p->left, x, w);
		}
		else
			if (x >= p->data) {
				add(p->right, x, w);
			}
}

void create_tree(int L, int R) {
	int k;

	if (L < R) {
		k = AR[L][R];
		//cout << k << " ";
		add(root, k, W[k-1]);
		create_tree(L, k - 1);
		create_tree(k, R);
	}
}

void LRprint(vertex *&x) {//Обход слева направо
	if (x == NULL) return;
	LRprint(x->left);
	cout << x->data << ' ' << x->w << " " << x->h << endl;
	LRprint(x->right);
}

int size(vertex *p) // Вычисляет размер дерева
{
	if (p == NULL)
		return 0;
	return 1 + size(p->left) + size(p->right);
}

long summ(vertex *p) // Вычисляет контрольную сумму данных в вершинах дерева
{
	if (p == NULL)
		return 0;
	return p->data + summ(p->left) + summ(p->right);
}

void seth(vertex *p)
{
	if (p) {
		if (p->left) {
			p->left->h = p->h + 1;
		}
		if (p->right) {
			p->right->h = p->h + 1;
		}
		seth(p->left);
		seth(p->right);
	}
}

void midh(vertex *p) 
{
	if (p) {
		c += p->w*p->h;
		midh(p->left);
		midh(p->right);
	}
}
