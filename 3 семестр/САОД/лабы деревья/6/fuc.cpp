#include "fuc.h"

extern int vr, hr;
extern bool up;

void binSert(int data, vertex* &p)
{
	vertex *q;

	if (p == NULL) {
		p = new vertex;
		p->data = data;
		p->bal = 0;
		p->left = p->right = NULL;
		vr=1;
	}
	else if (p->data > data) {
		binSert(data, p->left);
		if (vr == 1) {
			if (p->bal == 0) {
				q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->bal = 1;
				vr = 0, hr = 1;
			}
			else {
				p->bal = 0;
				vr = 1, hr = 0;
			}
		}
		else {
			hr = 0;
		}
	}
	else if (p->data <= data) {
		binSert(data, p->right);
		if (vr == 1) {
			p->bal = 1;
			hr = 1, vr = 0;
		}
		else if (hr == 1) {
			if (p->bal == 1) {
				q = p->right;
				p->bal = 0;
				q->bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				q->bal = 1;
				vr = 1, hr = 0;
			}
			else {
				hr = 0;
			}
		}
	}
}

void LR(vertex* x)
{
	if (x == NULL) return;
	LR(x->left);
	cout << x->data << ' ';
	LR(x->right);
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
		if (point->data > data) { // править  
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
			if (point->data <= data) {
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
	vertex *current = point->left;
	point->bal = 0;
	current->bal = 0;
	point->left = current->right;
	current->right = point;
	point = current;
}

void rr(vertex* &point)
{
	vertex *current = point->right;

	point->bal = 0;
	current->bal = 0;
	point->right = current->left;
	current->left = point;
	point = current;
}

void lr(vertex* &point)
{
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


int size(vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->left) + size(x->right);
	}
}

int max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int height(vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->left), height(x->right));
	}
}

int sdp(vertex *x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->left, l + 1) + sdp(x->right, l + 1);
	}
}

int summ(vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return x->data + summ(x->left) + summ(x->right);
	}
}


