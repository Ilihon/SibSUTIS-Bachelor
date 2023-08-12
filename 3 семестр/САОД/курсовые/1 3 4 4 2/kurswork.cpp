#include <fstream> 
#include <time.h>
#include <cmath>
#include <iostream> ///Для работы с клавиатурой
#include <conio.h>///для getch
#include <Windows.h>///Для русских букв
#include <iomanip>/// для установки кол-ва символов при выводе
#include <cstdio> ///Например для fread()
#include <cstring> ///Для работы со строками
#include <cstdlib>


using namespace std;

const int N = 4000;
const int M = 256;
int *w;
int num_h = 0, num_t = 0;

long int n = 0;
float entropy = (float)(0);
float midlength = (float)(0);
int sim_cf = 0, sim_f = 0;


struct record
{
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};

struct list {
	record *data;
	list *next; 
	list *prior;
};

struct queue {
	list *head;
	list *tail;
};

struct vertex {
	list *fact;
	vertex *left;
	vertex *right;
};

list *base, *sbase;
queue *stack;
queue Q;

struct code {
	unsigned char a;
	float q;
	int w[30];
	int l;
};

code A[M];


void read_base(FILE *, list *);

void print_record(record *);
void print_base(list *);
void print_stak(queue *);
void print_tree(vertex *&);

void copy_base(list *, list *);
void prior(list *);
void DigitalSort(list *&, bool );

void masiving(list *, list *[N]);
int compare(char *, char *);
void binary_search(char *, list *[N], queue *&);

void add(vertex *&, record *x);
void DOP_A2(vertex *&, list *[N], int , int);
void QuickSort(int *, list *[N], int , int );
void weight(list *mas[N]);
void tree_search(vertex *&, short int);
void delete_tree(vertex *&);

void reading();
int shanon();
void code_file();
void print();


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(866);
	FILE *Base1;
	Base1 = fopen("Base1.dat", "rb");
	base = new list();
	read_base(Base1, base);
	_fcloseall();

	///sort///
	sbase = new list();
	copy_base(base, sbase);
	DigitalSort(sbase, 0);
	list *mas_sbase[N] = {};
	///tree///
	vertex *root = NULL;
	///code//
	SetConsoleCP(1251);
	reading();
	shanon();
	code_file();
	///-menu-///
	int enter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		SetConsoleCP(866);
		cout << "\t------------------------------МЕНЮ------------------------" << endl;
		cout << "\t1. Посмотреть базу данных (< - назад, esc - выйти)" << endl;
		cout << "\t2. Просмотр отсортированной базы данных (Digital sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (публикация)" << endl;
		cout << "\t4. Поиск в дереве (год)" << endl;
		cout << "\t5. Кодирование статистика" << endl;
		cout << "\tEsc. Выход " << endl;
		cout << "\t----------------------------------------------------------" << endl;
		while ((enter != 27) && (enter != 49) && (enter != 50) && (enter != 51) && (enter != 52) && (enter != 53)) {
			if (_kbhit()) {
				enter = _getch();
			}
		}
		switch (enter) {
		case 27: return 0;
		case 49:
			print_base(base);
			break;
		case 50:
			print_base(sbase);
			break;
		case 51:
			stack = NULL;
			root = NULL;
			char X[3];
			SetConsoleCP(866);
			cout << "Введите ключ (три буквы публикации): ";
			cin >> X;
			masiving(sbase, mas_sbase);
			binary_search(X, mas_sbase, stack);
			if (stack->head != stack->tail)
				print_stak(stack);
			else
				cout << "Такой записи нет";
			_getch();
			break;
		case 52:
			if (mas_sbase[0] == NULL) break;
			if (root != NULL) {
				delete_tree(root);
				root = NULL;
			}
			short int x;
			weight(mas_sbase);
			DOP_A2(root, mas_sbase, num_h, num_t);
			cout << "Посмотреть дерево (1/0) ";
			cin >> x;
			if (x == 1) {
				print_tree(root);
			}
			while (true) {
				SetConsoleCP(866);
				cout << "Книги какого года хотите увидеть? (ext = 1)" << endl;
				cin >> x;
				if (x == 1) break;
				tree_search(root, x);
			}
			break;
		case 53:
			print();
			break;
		}
	}
	return 0;
}


void read_base(FILE *f, list *l) {
	record* tmp = new record();
	list* tmpl;
	fread((record *)tmp, sizeof(record), 1, f);
	l->data = tmp;
	l->prior = NULL;
	l->next = NULL;
	for (int i = 1; i < N; i++) {
		tmp = new record();
		fread((record *)tmp, sizeof(record), 1, f);
		tmpl = l;
		l = l->next = new list();
		l->data = tmp;
		l->prior = tmpl;
		l->next = NULL;
	}
}

void print_record(record *t) {
	SetConsoleCP(1251);///Меняем кодировку
	for (int j = 0; j < 12; j++)
		cout << t->author[j];
	cout << "|";
	for (int j = 0; j < 32; j++)
		cout << t->title[j];
	cout << "|";
	for (int j = 0; j < 16; j++)
		cout << t->publisher[j];
	cout << "| ";
	cout << t->year;
	cout << " | ";
	cout << t->num_of_page << " |" << endl;
}

void print_base(list *l) {
	int M = 20; ///По столько элементов выводится на экран
	int i, flag = 1, num = 1, broke = 0;
	int c = 0;
	cout << "1-вывести по 20"<< endl <<"2-вывести весь список" << endl;
	while ((c != 49) && (c != 27) && (c != 50)) {
			if (_kbhit()) {///Пользоавтель нажал на 1 / 2 / ESc
				c = _getch();
			}
	}
	if (c == 27) { ///Пользоавтель нажал на кнопку = ESC
		return;
	}else{
		if (c == 50){
			M = N;
			broke =1;
		}
	}
	while (flag) {
		i = 0;
		system("cls");
		cout << "+-----+------------+--------------------------------+----------------+------+-----+" << endl;
		while ((i < M) && (num <= N) && (l != NULL)) {
			cout << "|";
			cout << setw(4) << num << ")|";
			print_record(l->data);
			cout << "+-----+------------+--------------------------------+----------------+------+-----+" << endl;
			num++;
			i++;
			if (l->next == NULL)
				break;
			else
				l = l->next;
		}
		SetConsoleCP(866);///Возвращаем кодировку
		if(broke == 0){
			c = 0;
			while ((c != 49) && (c != 27) && (c != 50)) {
				if (_kbhit()) {///Пользоавтель нажал на 1 / 2 / ESc
					c = _getch();
				}
			}
			if (c == 49) {///Пользоавтель нажал на кнопку = 1
				for (int j = 0; j < i + M; j++) {
					if (l->prior == NULL) break;
					l = l->prior;
					num--;
				}
			}
			else
				if (c == 27) { ///Пользоавтель нажал на кнопку = ESC
					flag = 0;
					return;
				}
		}
		else{
			flag = 0;
			system("pause");
		}
	}
}

void print_stak(queue *p) {
	list *l = p->head;
	int M = N; ///По столько элементов выводится на экран
	int i, flag = 1, num = 1;
	int c = 0;
	i = 0;
	system("cls");
	cout << "+-----+------------+--------------------------------+----------------+------+-----+" << endl;
	while ((i < M) && (p->tail != l)) {
		cout << "|";
		cout << setw(4) << num << ")|";
		print_record(l->data);
		cout << "+-----+------------+--------------------------------+----------------+------+-----+" << endl;
			num++;
		i++;
		if ((l->next == NULL) || (p->tail == l->next)) {
			num--;
			break;
		}
		else
			l = l->next;
	}
	SetConsoleCP(866);///Возвращаем кодировку
	system("pause");
}

void print_tree(vertex *&p) {
	if (p == NULL) return;
	list *tmp = p->fact;
	print_tree(p->left);
	tmp = p->fact;
	while (tmp != NULL) {
		print_record(tmp->data);
		tmp = tmp->next;
	}
	cout << "---------------------------------------------------------------------------" << endl;
	print_tree(p->right);
}


void copy_base(list *a, list *b) {
	b->prior = NULL;
	b->data = a->data;
	for (int i = 1; i < N; i++) {
		a = a->next;
		b->next = new list;
		b->next->prior = b;
		b = b->next;
		b->data = a->data;
	}
	b->next = NULL;
}

void prior(list *p) {
	p->prior = NULL;
	for (int i = 1; i < N; i++) {
		p->next->prior = p;
		p = p->next;
	}
}

void DigitalSort(list *&head, bool flag) {

	queue Q[257];

	for (int i = 0; i < 257; i++) {
		Q[i].tail = (list*)&(Q[i].head);
	}

	list *p;
	SetConsoleCP(1251);
	for (int j = 10; j >= 0; j--) {
		for (int i = 0; i < 257; i++) {
			Q[i].tail = Q[i].head = NULL;
		}

		while (head) {
			int d;
			if (flag == 0) {
				if (head->data->author[j] == ' ')
					d = 0;
				else
					d = head->data->author[j] + 129;
			}
			else {
				if (head->data->publisher[j] == ' ')
					d = 0;
				else
					d = head->data->publisher[j] + 129;
			}
			p = Q[d].tail;
			if (Q[d].head == NULL)
				Q[d].head = head;
			else
				p->next = head;

			p = Q[d].tail = head;
			head = head->next;
			p->next = NULL;
		}
		cout << endl << endl;
		head = NULL;

		int i;
		for (i = 0; i < 256; i++) {
			if (Q[i].head != NULL)
				break;
		}
		head = Q[i].head;
		p = Q[i].tail;
		for (int k = i + 1; k < 256; k++) {
			if (Q[k].head != NULL) {
				p->next = Q[k].head;
				p = Q[k].tail;
			}
		}
	}
	if (flag == 0)
		DigitalSort(head, 1);
	else
		prior(head);
}


void masiving(list *l, list *r[N]) {
	for (int i = 0; i < N; i++) {
		r[i] = l;
		l = l->next;
	}
}

int compare(char *a, char *b) {
	for (int i = 0; i < 3; i++) {
		if ((int)a[i] < (int)b[i]) return 1;
		else
			if ((int)a[i] > (int)b[i]) return -1;
	}
	return 0;
}

void binary_search(char *x, list *l[N], queue *&turn) {
	int L = 1;
	int R = N;
	int m, h, t;
	int sravn;
	turn = new queue();
	turn->head = turn->tail;
	while (L < R) {
		m = (L + R) / 2;
		sravn = compare(l[m]->data->publisher, x);
		if (sravn == 1) {
			L = m + 1;
		}
		else {
			if (sravn == -1) {
				R = m;
			}
			else
				if (sravn == 0) {
					h = m;
					t = m;
					while (compare(l[h - 1]->data->publisher, x) == 0) {
						h--;
						if (h - 1 == 0)
							break;
					}
					while (compare(l[t + 1]->data->publisher, x) == 0) {
						t++;
						if (t + 1 == 4000)
							break;
					}
					turn->head = l[h];
					num_h = h;
					turn->tail = l[t];
					num_t = t;
					return;
				}
		}
	}
}


void add(vertex *&point, record *x) {
	vertex **p = &point;
	list *tmp;

	while (*p) {
		if ((*x).year < (*p)->fact->data->year) {
			p = &((*p)->left);
		}
		else
			if ((*x).year > (*p)->fact->data->year) {
				p = &((*p)->right);
			}
			else
				if ((*x).year == (*p)->fact->data->year) {
					tmp = (*p)->fact;
					while (tmp->next != NULL) {
						tmp = tmp->next;
					}
					tmp->next = new list();
					tmp->next->data = x;
					tmp->next->prior = (*p)->fact;
					tmp->next->next = NULL;
					return;
				}
	}
	if ((*p) == NULL) {
		(*p) = new vertex();
		(*p)->fact = new list();
		(*p)->fact->data = x;
		(*p)->fact->next = NULL;
		(*p)->fact->prior = NULL;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
}

void DOP_A2(vertex *&q, list *mas[N], int L, int R) {
	int wes = 0, summa = 0;
	int i;
	L = L - num_h;
	R = R - num_h;
	if (L <= R)
	{
		for (i = L; i <= R; i++)
			wes = wes + w[i];
		for (i = L; i <= R; i++)
		{
			if ((summa <= (wes / 2)) && ((summa + w[i]) >= (wes / 2)))
				break;
			summa = summa + w[i];
		}
		add(q, mas[i + num_h]->data);
		DOP_A2(q, mas, L + num_h, i - 1 + num_h);
		DOP_A2(q, mas, i + 1 + num_h, R + num_h);
	}
}

void weight(list *mas[N]) {
	w = new int[num_t - num_h + 1];
	for (int i = 0; i < (num_t - num_h + 1); i++) {
		w[i] = rand() % 999 + 1;
	}
	QuickSort(w, mas, 0, num_t - num_h);
}

void QuickSort(int *a, list *mas[N],  int left, int right) {
	int current, i, j, t;
	list *tmp;
	current = mas[left + num_h]->data->year; 
	i = left; 
	j = right;

	while (i <= j) {
		while (mas[i + num_h]->data->year < current) {
			i++;
		}
		while (mas[j + num_h]->data->year > current) {
			j--;
		}
		if (i <= j) {
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			tmp = mas[i + num_h];
			mas[i + num_h] = mas[j + num_h];
			mas[j + num_h] = tmp;
			i++; j--;
		}
	}

	if (left < j) {
		QuickSort(a, mas, left, j);
	}
	if (i < right) {
		QuickSort(a, mas, i, right);
	}
}

void tree_search(vertex *&p, short int x) {
	vertex *tmp = p;
	while (tmp != NULL) {
		if (tmp->fact->data->year == x) {
			print_base(tmp->fact);
			return;
		}
		else
			if (tmp->fact->data->year > x)
				tmp = tmp->left;
			else
				if (tmp->fact->data->year < x)
					tmp = tmp->right;
	}
	cout << "Книга не найдена" << endl;
}

void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}


void reading() {
	int i, j = 0, e;
	FILE *f;
	f = fopen("Base1.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].a = i;
		A[i].q = (float)(0);
		A[i].l = 0;
	}
	int flag = 100;
	unsigned char ac;
	while (!feof(f)) {
		fscanf(f, "%c", &ac);
		A[ac].q = A[ac].q + 1.0;
		n++;
	}
	fclose(f);
	for (i = 0; i < M; i++)
		if (A[i].q != (float)(0)) {
			A[i].q /= (float)n;
			j++;
		}
	n = (unsigned long int)(j);
	code tmp;
	for (i = 1; i < M - 1; i++) {
		e = 1;
		if (A[i].q == (float)(0))
			for (j = i + 1; j < M; j++)
				if (e)
					if (A[j].q != (float)(0)) {
						tmp = A[i];
						A[i] = A[j];
						A[j] = tmp;
						e = 0;
					}
	}
	i = 0;
	while (A[i].q != 0.0) i++;
	n = (unsigned long int)(i);
	for (i = 0; i < n; ++i)
		for (j = 1; j < n; ++j) {
			if (A[j].q > A[j - 1].q) {
				tmp = A[j - 1];
				A[j - 1] = A[j];
				A[j] = tmp;
			}
		}
}

int shanon() {
	float q[M];
	q[0] = 0;
	for (int i = 1; i < n; i++)
	{
		q[i] = q[i - 1] + A[i].q;
		A[i].l = ceil(-log(A[i].q) / log(2));
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= A[i].l; j++)
		{
			q[i - 1] *= 2;
			A[i].w[j] = floor(q[i - 1]);
			if (q[i - 1] > 1) q[i - 1] -= 1;

		}
	}
	return 0;
}

void code_file() {
	FILE *f, *cf;
	f = fopen("Base1.dat", "rb");
	cf = fopen("CodeBase.dat", "wb");
	char sim;
	while (!feof(f)) {
		fscanf(f, "%c", &sim);
		sim_f++;
		for (int i = 0; i < n; i++) {
			if (sim == A[i].a) {
				for (int j = 0; j < A[i].l; j++) {
					putc(A[i].w[j], cf);
					sim_cf++;
				}
			}
		}
	}
	_fcloseall();
}

void print() {
	entropy = (float)(0);
	midlength = (float)(0);
	int j;
	int i;
	float check = 0;
	for (i = 1; i < n; i++) {
		entropy += -A[i].q * log(A[i].q) / log(2);
		midlength += A[i].l * A[i].q;
	}

	SetConsoleCP(1251);
	for (i = 1; i < n; i++) {
		printf("|  %12d |    %c   |  %2.6f   |  %7d    | ",i, (char)A[i].a, A[i].q, A[i].l);
		for (j = 1; j <= A[i].l; ++j)
			cout << A[i].w[j];
		cout << endl;
	}
	SetConsoleCP(866);
	cout << endl;
	cout << setw(8) << "Средняя длина: " << midlength << endl;
	cout << setw(8) << "Энтропия: " << entropy << endl;
	cout << setw(8) << entropy + 1 << " > " << midlength << endl << endl;
	cout << setw(8) << "Коэфициент сжатия: " << (float) sim_f / sim_cf << endl;
	_getch();
}
