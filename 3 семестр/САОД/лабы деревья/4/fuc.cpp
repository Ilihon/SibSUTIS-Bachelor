#define YES true
#define NO false


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

int SDP(int data, vertex* &p)
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
		return 0;
	}
}

vertex* ISDP(int l, int r, int *m)
{
	if (l > r) {
		return NULL;
	}
	else {
		int k = (l + r) / 2;
		vertex *p;
		p = new vertex;
		p->data = m[k];
		p->left = ISDP(l, k - 1, m);
		p->right = ISDP(k + 1, r, m);
		return p;
	}
}

int TreeSize(vertex *p)
{
	if (p == NULL) {
		return 0;
	}
	else {
		return 1 + TreeSize(p->left) + TreeSize(p->right);
	}
}

int Max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int TreeHeight(vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + Max(TreeHeight(x->left), TreeHeight(x->right));
	}
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
