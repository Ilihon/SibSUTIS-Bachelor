
#define YES true
#define NO false
#include "fuc.h"



bool up = NO;
bool um = NO;

extern int turn;//поворот

vertex *q = NULL;


void LRprint(vertex* x)
{
	if (x) {
		LRprint(x->left);
		cout << x->data << ' ';
		LRprint(x->right);
	}
}

void addAVL(int data, vertex *&point)
{
	if (point == NULL) {
		point = new vertex;
		point->data = data;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		up = YES;
	}
	else
		if (point->data >= data) { 
			addAVL(data, point->left);
			if (up == YES) {
				if (point->bal > 0) {
					point->bal = 0;
					up = NO;
				}
				else
					if (point->bal == 0) {
						point->bal = -1;
						up = YES;
					}
					else
						if (point->left->bal < 0) {
							ll(point);
							up = NO;
						}
						else {
							lr(point);
							up = NO;
						}
			}
		}
		else {
			if (point->data < data) {
				addAVL(data, point->right);
				if (up == YES) {
					if (point->bal < 0) {
						point->bal = 0;
						up = NO;
					}
					else {
						if (point->bal == 0) {
							point->bal = 1;
							up = YES;
						}
						else {
							if (point->right->bal > 0) {
								rr(point);
								up = NO;
							}
							else {
								rl(point);
								up = NO;
							}
						}
					}
				}
			}
		}
}

void ll(vertex* &point)
{
	turn++;
	vertex *current = point->left;
	point->bal = 0;
	current->bal = 0;
	point->left = current->right;
	current->right = point;
	point = current;
}

void rr(vertex* &point)
{
	turn++;
	vertex *current = point->right;

	point->bal = 0;
	current->bal = 0;
	point->right = current->left;
	current->left = point;
	point = current;
}

void lr(vertex* &point)
{
	turn++;
	vertex *current = point->left;
	vertex *reva = current->right;

	if (reva->bal < 0) {
		point->bal = 1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal > 0) {
		current->bal = -1;
	}
	else {
		current->bal = 0;
	}
	reva->bal = 0;
	current->right = reva->left;
	point->left = reva->right;
	reva->left = current;
	reva->right = point;
	point = reva;
}

void rl(vertex* &point)
{
	turn++;
	vertex *current = point->right;
	vertex *reva = current->left;

	if (reva->bal < 0) {
		point->bal = 1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal > 0) {
		current->bal = -1;
	}
	else {
		current->bal = 0;
	}
	reva->bal = 0;
	current->left = reva->right;
	point->right = reva->left;
	reva->right = current;
	reva->left = point;
	point = reva;
}


void DeleteAVL(int x, vertex*&p) {
	if (p == NULL) {
		cout << "Ключа в дереве нет" << endl;
		return;
	}
	else
		if (x < p->data) {
			DeleteAVL(x, p->left);
			if (um == YES) BL(p);
		}
		else 
			if (x > p->data) {
				DeleteAVL(x, p->right);
				if (um == YES) BR(p);
			}
			else {
				q = p;
				if (q->left == NULL) {
					p = q->right;
					um = YES;
				}
				else
					if (q->right == NULL) {
						p = q->left;
						um = YES;
					}
					else {
						del(q->left);
						if (um == YES)
							BL(p);
					}
				delete(q);
			}
}

void del(vertex *&r) {
	if (r->right != NULL) {
		del(r->right);
		if (um == YES)
			BR(r);
	}
	else {
		q->data = r->data;
		q = r;
		r = r->left;
		um = YES;
	}
}

void BL(vertex *&p) {
	if (p->bal == -1) {
		p->bal = 0;
		um = YES;
	}
	else
		if (p->bal == 0) {
			p->bal = 1;
			um = NO;
		}
		else
			if (p->bal == 1) 
				if (p->right->bal >= 0) {
					RR1(p);
				}
				else {
					rl(p);
				}
			
}

void BR(vertex *&p) {
	if (p->bal == 1) {
		p->bal = 0;
		um = YES;
	}
	else
		if (p->bal == 0) {
			p->bal = -1;
			um = NO;
		}
		else
			if (p->bal == -1) {
				if (p->left->bal <= 0) {
					LL1(p);
				}
				else {
					lr(p);
				}
			}
}

void LL1(vertex *&p) {
	turn++;
	q = p->left;
	if (q->bal == 0) {
		q->bal = 1;
		p->bal = -1;
		um = NO;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR1(vertex *&p) {
	turn++;
	q = p->right;;
	if (q->bal == 0) {
		q->bal = -1;
		p->bal = 1;
		um = NO;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->right = q->left;
	q->left = p;
	p = q;
}

int TreeSize(vertex *p) // Вычисляет размер дерева
{
	if (p == NULL)
		return 0;
	return 1 + TreeSize(p->left) + TreeSize(p->right);
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

int  SumDlinPutey(vertex *x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + SumDlinPutey(x->left, l + 1) + SumDlinPutey(x->right, l + 1);
	}
}

int Sum(vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return x->data + Sum(x->left) + Sum(x->right);
	}
}
