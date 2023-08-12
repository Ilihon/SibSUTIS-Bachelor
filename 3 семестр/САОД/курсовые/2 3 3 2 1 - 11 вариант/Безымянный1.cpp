#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <cmath>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;
const int n_symb = 256;

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#pragma warning(disable : 4996)

struct Base {
	char worker[30];
	short int number;
	char position[22];
	char birthdate[10];
};

struct list {
	Base* data;
	list* next;
};

struct list_t {
	int data;
	list_t* next;
};

list* list_map(Base* massiv, int size)
{
	list* head = new list;
	list* p = head;
	head->data = &massiv[0];

	for (int i = 1; i < size; i++) {
		p->next = new list;
		p = p->next;
		p->data = &massiv[i];
	}
	p->next = NULL;
	return head;
}

int CompareOutput(char* a, char* b) {
	if (a[6] < b[6]) return -1;
	else if (a[6] > b[6]) return 1;
	else {
		if (a[7] < b[7]) return -1;
		else if (a[7] > b[7]) return 1;
		else return 0;
	}
}

int CompareBin(char* a, char* b) {
	if (a[6] < b[0]) return -1;
	else if (a[6] > b[0]) return 1;
	else {
		if (a[7] < b[1]) return -1;
		else if (a[7] > b[1]) return 1;
		else return 0;
	}
}

int compare(char* a, char* b) {
	if (a[6] < b[6]) return -1;
	else if (a[6] > b[6]) return 1;
	else {
		if (a[7] < b[7]) return -1;
		else if (a[7] > b[7]) return 1;
		else {
			if (a[3] < b[3]) return -1;
			else if (a[3] > b[3]) return 1;
			else {
				if (a[4] < b[4]) return -1;
				else if (a[4] > b[4]) return 1;
				else {
					if (a[0] < b[0]) return -1;
					else if (a[0] > b[0]) return 1;
					else {
						if (a[1] < b[1]) return -1;
						else if (a[1] > b[1]) return 1;
						else return 0;
					}
				}
			}
		}
	}
}

int Compare0(char* str1, char* str2) {
	int temp = 0;
	for (int i = 0; str1[i] != '\0'; i++) {
		if (str1[i] == '_')
			str1[i] = ' ';
		if (str1[i] > str2[i]) {
			temp = 1;
			break;
		}
		else if (str1[i] < str2[i]) {
			temp = -1;
			break;
		}
		else
			temp = 0;
	}
	return temp;
}

void cut_next(list* p) {
	p->next = p->next->next;
}

void paste_next(list* p, list* a) {
	a->next = p->next;
	p->next = a;
}

//сливает очереди h1-t1 и h2-t2 в очередь hr-tr
void merge(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr) {
	if (compare(h1->data->birthdate, h2->data->birthdate) < 0) {
		hr = h1;
		h1 = h1->next;
	}
	else {
		hr = h2;
		h2 = h2->next;
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2) {
		if (compare(h1->data->birthdate, h2->data->birthdate) < 0) {
			tr->next = h1;
			h1 = h1->next;
			tr = tr->next;
		}
		else {
			tr->next = h2;
			h2 = h2->next;
			tr = tr->next;
		}
	}
	if (t1->next != h1) {
		tr->next = h1;
		tr = t1;
	}
	else if (t2->next != h2) {
		tr->next = h2;
		tr = t2;
	}
	tr->next = NULL;
}

void merge_t(list_t* h1, list_t* t1, list_t* h2, list_t* t2, list_t*& hr, list_t*& tr) {
	if (h1->data < h2->data) {
		hr = h1;
		h1 = h1->next;
	}
	else {
		hr = h2;
		h2 = h2->next;
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2) {
		if (h1->data < h2->data) {
			tr->next = h1;
			h1 = h1->next;
			tr = tr->next;
		}
		else {
			tr->next = h2;
			h2 = h2->next;
			tr = tr->next;
		}
	}
	if (t1->next != h1) {
		tr->next = h1;
		tr = t1;
	}
	else if (t2->next != h2) {
		tr->next = h2;
		tr = t2;
	}
	tr->next = NULL;
}

void merge_sort(list*& head) {

	list* t = new list;
	t->data = NULL;
	t->next = head;
	int k = 1;
	int e = 0;
	list* hp, * tp, * h1, * t1, * h2, * t2, * hr, * tr;
	while (k < 4000) {
		hp = t;
		while (hp != NULL) {
			if (hp->next == NULL) {
				break;
			}
			h1 = hp->next;
			t1 = h1;
			for (int i = 1; i < k; i++) {
				if (t1->next == NULL) {
					break;
				}
				t1 = t1->next;
			}
			if (t1->next == NULL) {
				break;
			}
			h2 = t1->next;
			t2 = h2;
			t1->next = NULL;
			for (int i = 1; i < k; i++) {
				char z = t2->data->birthdate[0];
				if (t2->next == NULL) {
					break;
				}
				t2 = t2->next;
			}
			tp = t2->next;
			t1->next = NULL;
			t2->next = NULL;
			char z2 = h2->data->birthdate[0];
			merge(h1, t1, h2, t2, hr, tr);
			hp->next = hr;
			head = hr;
			tr->next = tp;
			hp = tr;
		}
		k *= 2;
	}
}

void OutputList(list* head) {
	list* p = head->next;
	int i = 0;
	while (p != NULL) {
		printf("%2d) %-32s %-5d %-24s %-10s\n", i + 1, p->data->worker, p->data->number, p->data->position, p->data->birthdate);
		i++;
		p = p->next;
	}
}

list* AddList(Base* bd, int size, int R)
{
	list* head = new list;
	list* p = head;
	head->data = &bd[0];
	do {
		R++;
		p->next = new list;
		p = p->next;
		p->data = &bd[R];
		if (R >= size) break;
	} while (R < size && CompareOutput(bd[R].birthdate, bd[R + 1].birthdate) == 0);
	p->next = NULL;
	return head;
}

list* BinSearch(list* p) {
	list* q = p;
	char key[2];
	cout << "Enter search key: ";
	cin >> key;
	int L = 0, R = 4000 - 1;
	int m;
	Base* index = new Base[4000];
	for (int i = 0;  q != NULL; i++) {
		strcpy(index[i].worker, q->data->worker);
		index[i].number = q->data->number;
		strcpy(index[i].birthdate, q->data->birthdate);
		strcpy(index[i].position, q->data->position);
		q = q -> next;
	}
	while (L < R) {
		m = (L + R) / 2;
		if (CompareBin(index[m].birthdate, key) < 0) L = m + 1;
		else R = m;
	}
	if (CompareBin(index[R].birthdate, key) == 0) {
		q = AddList(index, 4000 - 1, R - 1);
	}
	else
		cout << "Record with created key not found in directory \n";
	return q;
}

/*------------------------Vertex----------------------------------*/

bool VR = true;
bool HR = true;

struct Vertex {
	char worker[30];
	short int number;
	char position[22];
	char birthdate[10];
	int Data = 0;
	int Bal = 0;
	Vertex* Left = NULL;
	Vertex* Right = NULL;
};

void AddData(Vertex *p, list *binList) {
	strcpy(p->worker, binList->data->worker);
	p->number = binList->data->number;
	strcpy(p->position, binList->data->position);
	strcpy(p->birthdate, binList->data->birthdate);
	p->Left = NULL;
	p->Right = NULL;
	p->Bal = 0;
}

void ObhodLeft(Vertex* p, int& count) {
	if (p != NULL) {
		ObhodLeft(p->Left, count);
		printf("%2d) %-32s %-5d %-24s %-10s\n", count + 1, p->worker, p->number, p->position, p->birthdate);
		count++;
		ObhodLeft(p->Right, count);
	}
}

void addDBD(list* binList, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		AddData(p, binList);
		VR = true;
	}
	else if (Compare0(p->position, binList->data->position) > 0) {
		addDBD(binList, p->Left);
		if (VR) {
			if (p->Bal == 0) {
				Vertex* q = p->Left;
				p->Left = q->Right;
				q->Right = p;
				p = q;
				q->Bal = 1;
				VR = 0;
				HR = 1;
			}
			else {
				p->Bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else HR = 0;
	}
	else if (Compare0(p->position, binList->data->position) <= 0) {
		addDBD(binList, p->Right);
		if (VR) {
			p->Bal = 1;
			HR = 1;
			VR = 0;
		}
		else if (HR) {
			if (p->Bal == 1) {
				Vertex* q = p->Right;
				p->Bal = 0;
				q->Bal = 0;
				p->Right = q->Left;
				q->Left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else HR = 0;
		}
	}
}

void TreeSearch(char* str, Vertex*& p, int& count, bool& tree_find) {
	if (p) {
		int temp = Compare0(str, p->position);                       // Поиск в дереве проходит по этому полю
		if (temp == 0) {
			TreeSearch(str, p->Left, count, tree_find);
			tree_find = 1;
			printf("%2d) %-32s %-5d %-24s %-10s\n", count + 1, p->worker, p->number, p->position, p->birthdate);
 			count++;
			TreeSearch(str, p->Right, count, tree_find);
		}
		else if (temp < 0)
			TreeSearch(str, p->Left, count, tree_find);
		else if (temp > 0)
			TreeSearch(str, p->Right, count, tree_find);
	}
}
/*--------------------------Coding----------------------------------*/

// Функция сдравнения для сортировки массива структур pair
double cmp(pair<char, double> a, pair<char, double> b) {
	return a.second > b.second;
}

// Функция кодирования Хаффмена, переписана с лекции
int Up(int n, double q, pair<char, double>* p) {
	int j = 1;
	for (int i = n - 1; i >= 2; i--) {
		if (p[i - 1].second <= q) p[i].second = p[i - 1].second;
		else {
			j = i;
			break;

		}
	}
	p[j].second = q;
	return j;
}

// Функция кодирования Хаффмена, переписана с лекции
void Down(int n, int j, int* l, int** c) {
	int *S = new int [n + 1];
	for (int i = 0; i <= n; i++) S[i] = c[ j][i];
	int tempL = l[j];
	for (int i = j; i <= n - 2; i++) {
		for (int k = 0; k <= n; k++) c[i][k] = c[i + 1][k];
		l[i] = l[i + 1];
	}
	for (int i = 0; i <= n; i++) {
		c[n - 1][i] = S[i];
		c[n][i] = S[i];
	}
	c[n - 1][tempL + 1] = 0;
	c[n][tempL + 1] = 1;
	l[n - 1] = tempL + 1;
	l[n] = tempL + 1;
}

// Функция кодирования Хаффмена, переписана с лекции
void Huffman(int n, pair<char, double>* p, int* l, int** c) {
	double q = 0;
	int j = 0;
	if (n == 2) {
		c[1][1] = 0;
		l[1] = 1;
		c[2][1] = 1;
		l[2] = 1;
	}
	else {
		q = p[n - 1].second + p[n].second;
		j = Up(n, q, p);
		Huffman(n - 1, p, l, c);
		Down(n, j, l, c);
	}
}

double Huffman(int n, pair<char, double>* p) {
	// Массив длинн кодов
	int* l = new int[n + 1];
	for (int i = 0; i <= n; i++)
		l[i] = 0;
	// Матрица кодов
	int** c = new int* [n + 1];
	for (int i = 0; i <= n; i++)
		c[i] = new int[n + 1];
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			c[i][j] = 0;
	// Временный массив для запоминания вероятностей
	double *tmp = new double [n + 1];
	for (int i = 1; i <= n; i++) {
		tmp[i] = p[i].second;
	}
	// Рекурсивная функция кодирования Хаффмена(по лекции)
	Huffman(n, p, l, c);
	// Средняя длина кодового слова
	double Ls = 0;
	// Вывод таблицы
	cout << "Coding: " << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << "  -  ";
		printf("%2c | %10f | ", p[i].first, p[i].second);
		for (int j = 1; j <= l[i]; j++) {
			cout << c[i][j];
		}
		cout << " | " << l[i] << endl;
		Ls += l[i] * tmp[i];
	}
	return Ls;
}

void CodeHF() {

	// Создаём динамический массив структур pair, который хранит 2 переменные, first - элемент, second - его вероятность
	pair<char, double>* p = new pair<char, double>[n_symb + 1];

	// Открываем файл для считывания символов
	FILE* f;
	f = fopen("testBase2.dat", "rb");
	
	// Масив a создаём, чтобы записать в него все повторения определённого символа
	int* a = new int[n_symb + 1];
	for (int i = 0; i < n_symb; i++) {
		a[i] = 0;
	}
	// unic - количество символов которые есть в базе данных. !ПРИМЕР. Допустим, что символ 'й'  ни раз не попадётся в БД, то мы его не храним в структуре pair
	int unic = 0;
	// sum - общее количеств осимволов в БД
	int sum = 0;
	// Cчитываемый символ
	char c;
	// Производим считывание из файла
	while (!feof(f)) {
		char c = getc(f);
		if (c != -1) a[(int)c + 128]++; // Когда встретили символ с, то увеличиваем переменную
		if (a[(int)c + 128] == 1) {
			unic++;                     // Чтобы узнать сколько различных символов есть в БД используем счётчик
		}
	}
	fclose(f);
	for (int i = 0; i < n_symb; i++) {
		sum += a[i];
	}
	cout << "Count symbols: " << unic << endl;
	int j = 0;
	// Заполним массив структур pair. а[i] делим на sum - получаем дробнуб вероятность
	for (int i = 0; i < n_symb; i++) {
		if (a[i] != 0) {
			p[j + 1].first = i;
			p[j + 1].second = a[i] / (double)sum;
			j++;
		}
	}
	// Посчитали энтропию
	double entr = 0;
	for (int i = 1; i <= unic; i++) {
		entr += p[i].second * log2(p[i].second);
	}
	entr = -entr;
	// Сортируем структуру встроенной функцие сортировки (трудоёмкость как у QuickSort)
	sort(p + 1, p + unic + 1, cmp);
	// Наконец-то запускаем функцию кодирования, которую показывали на лекции
	double hf = Huffman(unic, p);
	cout << "Entropy: " << entr << "\nHuffman: " << hf << endl;
}
/*----------------------------------------------------------------*/

void print_list(list* p)
{
	Vertex* Root = NULL;
	list *q, *l = p;
	int count = 0;
	bool tree_find = 0;
	while (1) {
		q = p;
		int k;
		system("cls");
		cout << "1.Conclusion to 20" << endl;
		cout << "2.Scroling" << endl;
		cout << "3.BinSearch" << endl;
		cout << "4.Tree" << endl;
		cout << "5.Coding" << endl;
		cout << "6.Exit" << endl;
		cin >> k;
		switch (k) {
		case 1:
			int answer;
			for (int i = 0, temp = 0; i < 4000; i++) {
				cout << i + 1 << "\t" << q->data->worker << "\t" << q->data->number << "\t\t" << q->data->position << "\t" << q->data->birthdate << endl;
				temp++;
				if (temp % 20 == 0) {
					cout << "Print next page ?! 1=yes, 0=no " << endl;
					cin >> answer;
					if (answer == 1) {
						continue;
					}
					if (answer == 0) {
						cout << "Stop" << endl;
						system("PAUSE");
						break;
					}
					if ((answer != 1) && (answer != 0)) {
						cout << "Input Error" << endl;
						break;
					}
				}
				q = q->next;
			}
			break;
		case 2:
			for (int i = 0; i < 4000; i++) {
				cout << i + 1 << "\t" << q->data->worker << "\t" << q->data->number << "\t\t" << q->data->position << "\t" << q->data->birthdate << endl;
				if (_kbhit())
					if (_getch() == 13) {
						cout << "Stop" << endl;
						cout << "To exit press esc" << endl;
						if (_getch() == 27) {
							break;
						}
					}
				if (i == 3999) {
					cout << "End of file" << endl;
					system("PAUSE");
				}
				q = q->next;
			}
			break;
		case 3:
			l = BinSearch(q);
			OutputList(l);
			system("PAUSE");
			break;
		case 4:
			for (list *k = l->next; k != NULL; k = k->next)
			{
				addDBD(k, Root);
			}
			ObhodLeft(Root, count);
			cout << endl << "Input key: ";
			char S[30];
			cin >> S;
			cout << endl;
			count = 0;
			TreeSearch(S, Root, count, tree_find);
			if (!tree_find) {
				cout << "Element was not find\n";
			}
			count = 0;
			system("Pause");
			Root = NULL;
			break;
		case 5:
			system("CLS");
			CodeHF();
			system("PAUSE");
			break;
		case 6:
			exit(1);
			break;
		}
	}
}

int main()
{
	FILE* fp;
	fp = fopen("testBase2.dat", "rb");
	Base* massiv = new Base[4000];
	fread(massiv, sizeof(Base), 4000, fp);
	list* head = list_map(massiv, 4000);
	merge_sort(head);
	print_list(head);
	return 0;
}
