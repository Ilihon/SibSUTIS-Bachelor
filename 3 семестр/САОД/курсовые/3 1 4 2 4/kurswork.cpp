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

int n = 0;
int sum =0;
int code[M][M];
float entropy = (float)(0);
float midlength = (float)(0);
int sim_cf = 0, sim_f = 0;
int bsearch_tail = 0;

struct record
{
	char depositor[30];
	unsigned short int deposit;
	char date[10];
	char lawyer[22];
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

struct vertex
{
	record *data;
	vertex *next;
	int bal;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;
bool VR = true;
bool HR = true;

list *base, *sbase;
queue *stack;
queue Q;

struct GM_code {
	unsigned char a;
	float p;
	float q;
	int l;
};

GM_code A[M];
GM_code B[M];


void read_base(FILE *, list *);

void print_record(record *);
void print_base(list *);
void print_stak(queue *);

void copy_base(list *, list *);
void prior(list *);
void DigitalSort(list *&, bool );

void masiving(list *, list *[N]);
int compare(char *, char *);
void binary_search(char *, list *[N], queue *&);

void DBD(record* data, vertex*& p); 
void TreePrint(vertex*);
void TreeSearch (vertex* p, int data);
void delete_tree(vertex *&p);

void reading();
int shanon();
void code_file();
void print();


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(866);
	FILE *Base1;
	Base1 = fopen("testBase3.dat", "rb");
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
	//shanon();
	code_file();
	///-menu-///
	int enter = 0, x =0, bsearch_counter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		x = 0;
		SetConsoleCP(866);
		cout << "\t------------------------------МЕНЮ------------------------" << endl;
		cout << "\t1. Посмотреть базу данных (< - назад, esc - выйти)" << endl;
		cout << "\t2. Просмотр отсортированной базы данных (Digital sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (вкладчик)" << endl;
		cout << "\t4. Поиск в дереве (вклад)" << endl;
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
			cout << "Введите ключ (три буквы вкладчика): ";
			cin >> X;
			masiving(sbase, mas_sbase);
			binary_search(X, mas_sbase, stack);
			if (stack->head != stack->tail){
				print_stak(stack);
				if (root != NULL) {
					delete_tree(root);
					root = NULL;
				}
				bsearch_counter = 0;
				while(bsearch_counter <= bsearch_tail){
					bsearch_counter++;
					DBD(stack->head->data, root);
					stack->head = stack->head->next;
				}
			}
			else
				cout << "Такой записи нет";
			_getch();
			break;
		case 52:
			if (mas_sbase[0] == NULL) break;
			cout << "Посмотреть дерево (1/0) ";
			cin >> x;
			if (x == 1) {
				SetConsoleCP(1251);
				TreePrint(root);
			}
			SetConsoleCP(866);
			cout << "Какой вклад ищем?" << endl;
			cin >> x;
			TreeSearch(root, x);
			_getch();
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
	cout << t->depositor;
	cout << " | ";
	cout << t->deposit;
	cout << " | ";
	cout << t->date;
	cout << " | ";
	cout << t->lawyer;
	cout << " | " << endl;
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
		while ((i < M) && (num <= N) && (l != NULL)) {
			cout << "|";
			cout << setw(4) << num << ")|";
			print_record(l->data);
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
	int i, flag = 1, num = 0;
	int c = 0;
	i = 1;
	system("cls");
	while ((i < M) && (p->tail != l)) {
		cout << "|";
		cout << setw(4) << i << ")|";
		print_record(l->data);
		num++;
		i++;
		if ((l->next == NULL) || (p->tail == l->next)) {
			num--;
			break;
		}
		else
			l = l->next;
	}
	bsearch_tail = num;
	SetConsoleCP(866);///Возвращаем кодировку
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
	for (int j = 30; j >= 0; j--) {
		for (int i = 0; i < 257; i++) {
			Q[i].tail = Q[i].head = NULL;
		}

		while (head) {
			int d;
			if (flag == 0) {
				if (head->data->deposit == 0)
					d = 0;
				else
					d = head->data->deposit/1000;
			}
			else {
				if (head->data->depositor[j] == ' ')
					d = 0;
				else
					d = head->data->depositor[j] + 129;
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
	int L = 0;
	int R = N;
	int m, h, t;
	int sravn;
	turn = new queue();
	turn->head = turn->tail;
	while (L <= R) {
		m = (L + R) / 2;
		sravn = compare(l[m]->data->depositor, x);
		if (sravn == 1) {
			L = m + 1;
		}
		else {
			if (sravn == -1) {
				R = m-1;
			}
			else
				if (sravn == 0) {
					h = m;
					t = m;
					while (compare(l[h - 1]->data->depositor, x) == 0) {
						h--;
						if (h - 1 == -1)
							break;
					}
					while (compare(l[t + 1]->data->depositor, x) == 0) {
						t++;
						if (t + 1 == 4000){
							break;
						}
					}
					//if (t + 1 != 4000){
						t++;
					//}
					turn->head = l[h];
					turn->tail = l[t];
					return;
				}
		}
	}
}

void TreePrint(vertex* p){
	if (p != NULL) {
		TreePrint(p->left);  
    		cout << "  " << p->data->depositor << "  " << p->data->deposit << "  " << p->data->date << "  " << p->data->lawyer << endl;
		TreePrint(p->next);
		TreePrint(p->right); 
	}
}

void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

void TreeSearch(vertex* p, int data){
	SetConsoleCP(1251);
	if(p!=NULL)           
    {
        if (data == p->data->deposit) {
			cout << p->data->depositor << "\t" << p->data->deposit << "\t" <<  p->data->date << "\t"<< p->data->lawyer << endl;
			TreeSearch(p->next, data);
		}
		else if (data<p->data->deposit) {
			TreeSearch(p->left, data);
		}
		else if (data>p->data->deposit) {
			TreeSearch(p->right, data);
		}
	}
	SetConsoleCP(866);
}

void DBD(record* data, vertex*& p) {
	if (p == NULL) {
		p = new vertex;
		p->data = data;
		p->bal = 0;
		p->next = NULL;
		p->left = NULL;
		p->right = NULL;
		VR = true;
	}
	else if (p->data->deposit == data->deposit) {
		DBD(data, p->next);
		VR = false;
	}
	else if (p->data->deposit > data->deposit) {
		DBD(data, p->left);
		if (VR) {
			if (p->bal == 0) {
				vertex* q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->bal = 1;
				VR = 0;
				HR = 1;
			}
			else {
				p->bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else HR = 0;
	}
	else if (p->data->deposit < data->deposit) {
		DBD(data, p->right);
		if (VR) {
			p->bal = 1;
			HR = 1;
			VR = 0;
		}
		else if (HR) {
			if (p->bal == 1) {
				vertex* q = p->right;
				p->bal = 0;
				q->bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else HR = 0;
		}
	}
}

void reading() {
	for (int i = 0; i < M; i++) {
		A[i].a = i;
		A[i].p = 0;
		A[i].q = (float)(0);
		A[i].l = 0;
	}
	FILE *f;
	f = fopen("testBase3.dat", "rb");
	while (!feof(f)) {
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		A[c+128].p +=1;
		sum++;
	}
	fclose(f);	
	for (int i = 0, j=0; i < M; i++){
		if(A[i].p!=0){
			n++;
			A[i].p /=sum;
			B[j]=A[i];
			entropy += A[i].p * abs(log(A[i].p) / log(2));
			j++;
		}
	}
	for (int i = 0; i < n; i++){
		B[i].q = B[i-1].q + B[i].p/2;
		B[i].l = ceil(-log(B[i].p) / log(2)) + 1;
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= B[i].l; j++)
		{
			B[i].q *= float(2);
			code[i][j] = floor(B[i].q);
			while (B[i].q >= 1)
				B[i].q -= 1;
		}
	}
}

void code_file() {
	FILE *f, *cf;
	f = fopen("testBase3.dat", "rb");
	cf = fopen("CodeBase.dat", "wb");
	char sim;
	while (!feof(f)) {
		fscanf(f, "%c", &sim);
		sim_f++;
		for (int i = 0; i < n; i++) {
			if (sim == B[i].a) {
				for (int j = 0; j < B[i].l; j++) {
					putc(code[i][j], cf);
					sim_cf++;
				}
			}
		}
	}
	_fcloseall();
}

void print() {
	int j;
	int i;
	float check = 0;
	midlength =0;
	for (i = 0; i < n; i++) {
		midlength += B[i].l * B[i].p;
	}

	//SetConsoleCP(1251);
	for (i = 0; i < n; i++) {
		printf("|  %12d |    %c   |  %2.6f   |  %7d    | ",i, (char)B[i].a, B[i].q, B[i].l);
		for (j = 1; j <= B[i].l; ++j)
			cout << code[i][j];
		cout << endl;
	}
	SetConsoleCP(866);
	cout << endl;
	cout << setw(8) << "Средняя длина: " << midlength << endl;
	cout << setw(8) << "Энтропия: " << entropy << endl;
	cout << setw(8) << entropy + 2 << " > " << midlength << endl << endl;
	cout << setw(8) << "Коэфициент сжатия: " << (float) sim_f / sim_cf << endl;
	_getch();
}
