//#include "pch.h"
#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <algorithm>

#define YES true
#define NO false

using namespace std;

const int N = 4000;
const int M=256;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;
int k=0;

struct Base {
	char fio[32];
	char street[18];
	short int number_home;
	short int number_door;
	char date[10];
};
Base* Info;
Base* Index = new Base[N];

struct list {
	Base* data;
	list* prev;
	list* next;
};

struct vertex {
	Base* data;
	int bal;
	int Data;
	vertex* left;
	vertex* next;
	vertex* right;
};
vertex* root = NULL;


struct F_code {
	float p;
	int l;
	char a;
};

F_code A[M];

bool up = NO;
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);


int Size(vertex*);
int Height(vertex*);
int Max(int, int);
float Sum_Paths(vertex* p, float);
int Sum_Tree(vertex* p);

void readBase(Base*& info)
{
	int d;
	FILE* fp;
	fp = fopen("testBase4.dat", "rb");
	info = new struct Base[N];
	d = fread((Base*)info, sizeof(Base), N, fp);
} 

void Massiv(Base* index, Base* info)
{
	for (int i = 0; i < N; i++) {
		index[i] = info[i];
	}
}

void print_list(Base* Index)
{
	int v;
	system("cls");
	cout << "1.Conclusion to 20" << endl;
	cout << "2.Scroling" << endl;
	cout << "3.Exit" << endl;
	cin >> v;

	if (v > 3) {
		cout << "Wrong input" << endl;
		system("PAUSE");
		print_list(Index);
	}
	if (v == 1 or v == 2 or v == 3) {
		if (v == 1) {
			int temp = 0;
			int answer;
			system("cls");
			for (int i = 0; i < N; i++) {
				cout << i + 1 << "\t" << Index[i].fio << "\t" << Index[i].street << "\t" << Index[i].number_door << "\t" << Index[i].number_home << "\t" << Index[i].date << endl;
				temp++;
				if (temp % 20 == 0) {
					cout << "Continue? 1=yes, 0=no " << endl;
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
						system("PAUSE");
						break;
					}
				}
			}
		}
		if (v == 2) {
			for (int i = 0; i < N; i++) {
				cout << i + 1 << "\t" << Index[i].fio << "\t" << Index[i].street << "\t" << Index[i].number_door << "\t" << Index[i].number_home << "\t" << Index[i].date << endl;
				if (_kbhit()) {
					if (_getch() == 13) {
						cout << "Stop" << endl;
						cout << "To exit press esc" << endl;
						if (_getch() == 27) {
							break;
						}
						while (_getch() != 13) {
							cout << "nope" << endl;
						}
					}
				}
				if (i == 3999) {
					cout << "End of file" << endl;
					system("PAUSE");
				}
			}
		}
	}
}

int Compare(Base a, Base b)
{
	if (strcmp(a.fio, b.fio) != 0) {
		return strcmp(a.fio, b.fio);
	}
	else {
		return strcmp(a.street, b.street);
	}
}

void HeapSort(Base*& Com)
{
	int i, j;
	Base x;
	int L = 4000 / 2;
	while (L > 0) {
		i = L;
		for (;;) {
			x = Com[i - 1];
			j = 2 * i;
			if (j > 4000)
				break;
			if ((j < 4000 - 1) && (Compare(Com[j], Com[j - 1]) >= 0))
				j++;
			if (Compare(x, Com[j - 1]) >= 0)
				break;
			swap(Com[i - 1], Com[j - 1]);
			i = j;
		}
		L--;
	}

	int R = 4000;
	while (R > 0) {
		swap(Com[0], Com[R - 1]);
		R--;
		i = 1;
		for (;;) {
			x = Com[i - 1];
			j = 2 * i;
			if (j > R)
				break;
			if ((j < R) && (Compare(Com[j], Com[j - 1]) >= 0))
				j++;
			if (Compare(x, Com[j - 1]) > 0)
				break;
			swap(Com[i - 1], Com[j - 1]);
			i = j;
		}
	}
}

int BSearch(Base** A, char fio[3])
{
	int l = 0, r = N, m = 0, fam_pos = 0;
	while (l <= r) {
		m = (l + r) / 2;

		if (strncmp(A[m]->fio, fio, 3) == 0) {
			cout << A[m]->fio;
			return m;
		}
		if (strncmp(A[m]->fio, fio, 3) < 0)
			l = m + 1;
		else
			r = m - 1;
	}
	return -1;
}


void AVL(Base* data, vertex*& point) {
	if (point == NULL) {
		point = new vertex;
		point->data = data;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		point->next = NULL;
		up = YES;
	}
	else {
		if (point->data->number_door == data->number_door) {
			AVL(data, point->next);
		}
		else {
			if (point->data->number_door > data->number_door) {
				AVL(data, point->left);
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
								//lr(point);
								up = NO;
							}
				}
			}
			else {
				if (point->data->number_door < data->number_door) {
					AVL(data, point->right);
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
									//	rl(point);
									up = NO;
								}
							}
						}
					}
				}
			}
		}
	}
}


void ll(vertex*& point)
{
	vertex* current = point->left;
	point->bal = 0;
	current->bal = 0;
	point->left = current->right;
	current->right = point;
	point = current;
}

void rr(vertex*& point)
{
	vertex* current = point->right;
	point->bal = 0;
	current->bal = 0;
	point->right = current->left;
	current->left = point;
	point = current;
}

void lr(vertex*& point)
{
	vertex* current = point->left;
	vertex* reva = current->right;

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

void rl(vertex*& point)
{
	vertex* current = point->right;
	vertex* reva = current->left;

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

void LRprint(vertex* x) {
	if (x) {
		LRprint(x->left);
		cout << "  " << x->data->fio << "  " << x->data->street << "  " << x->data->number_home << "  " << x->data->number_door << "  " << x->data->date << endl;
		LRprint(x->next);
		LRprint(x->right);
	}
}

int Size(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + Size(x->left) + Size(x->right) + Size(x->next);
	}
}

int Max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int Height(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + Max(Height(x->left), Height(x->right));
	}
}

float Sum_Paths(vertex* p, float depth) {
	if (p == NULL)
		return 0;
	else
		return (depth + Sum_Paths(p->left, depth + 1) +
			Sum_Paths(p->right, depth + 1));
}

int Sum_Tree(vertex* p) {
	if (p == NULL)
		return 0;
	else
		return (p->data->number_door + Sum_Tree(p->left) + Sum_Tree(p->right));
}

void Tree_Search(vertex* p, int data) {
	if (p != NULL)
	{
		if (data < p->data->number_door) {
			Tree_Search(p->left, data);
		}
		else {
			if (data > p->data->number_door) {
				Tree_Search(p->right, data);
			}
			else {
				cout << " " << p->data->fio << "\t" << p->data->street << "\t" << p->data->number_home << "\t" << p->data->number_door << "\t" << p->data->date << endl;
				Tree_Search(p->next, data);
			}
		}
	}
}


int med(int L, int R)
{
	float sl = 0, sr;
	for (int i = L; i < R; i++)
		sl += A[i].p;
	sr = A[R].p;
	int m = R;
	while (sl >= sr)
	{
		m--;
		sl -= A[m].p;
		sr += A[m].p;
	}
	return m;
}

void fano(int L, int R, int k)
{
	if (L < R)
	{
		k++;
		int m = med(L, R);
		for (int i = L; i <= R; i++)
		{
			if (i <= m)
				code[i][k] = 0;
			else
				code[i][k] = 1;
			A[i].l++;
		}
		fano(L, m, k);
		fano(m + 1, R, k);
	}
}

void BaseCoding(){
	
	int i,j;
	FILE *fp;	
	fp=fopen("testBase4.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].a = (char)(i-128); 
	}
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		sum++;
	}
	printf("\n");
	fclose(fp);
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				F_code B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	k=0;
	for (i = 0; i < M; i++){
		A[i].p /=sum;
		if(A[i].p!=0){
			k++;
			entropy += A[i].p * abs(log(A[i].p) / log(2));
		}
	}
	fano(0, k - 1, 0);
}

void CodeBase() {
	FILE *fp, *fcoded;
    fp = fopen("testBase4.dat", "rb");
    fcoded = fopen("BaseCoded.dat", "wb");
	char buffer;
	while (!feof(fp)) {
		fscanf(fp, "%c", &buffer);
		fcompression++;
		for (int i = 0; i < M; i++) {
			if (buffer == (char)(i-128)) {
				for (int j = 0; j < A[i].l; j++) {
					putc(code[i][j], fcoded);
					cfcompression++;
				}
			}
		}
	}
	fclose(fp);
	fclose(fcoded);
}

void CodePrint(){
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(866);
	printf("\n\nКод Фано: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	for (int i = 0; i < M; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].p);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |  %7d      |\n", A[i].l);
		printf("|-----------------------------------------------------------------------------|\n");
		lgm += A[i].p * A[i].l;
	}	
	
	printf("________________________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |  Коэф сжатия  |\n");
	printf("|____________|_________________|_______________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression/cfcompression);
	printf("|____________|_________________|_______________|\n");
	
}


void menu()
{
	int v;
	system("cls");
	cout << "1.Without" << endl;
	cout << "2.Sorting" << endl;
	cout << "3.Search" << endl;
	cout << "4.Code" << endl;
	cout << "5.Exit" << endl;
	cin >> v;
	if (v == 1 || v == 2 || v == 3 || v==4) {
		if (v == 1) {
			readBase(Info);
			Massiv(Index, Info);
			print_list(Index);
			menu();
		}
		if (v == 2) {
			readBase(Info);
			Massiv(Index, Info);
			HeapSort(Index);
			print_list(Index);
			menu();
		}
		if (v == 3) {
			system("cls");
			Base* mas[N];
			readBase(Info);
			Massiv(Index, Info);
			HeapSort(Index);
			for (int i = 0; i < N; i++) {
				mas[i] = &Index[i];
			}
			cout << "Search by first three letters of a surname" << endl;
			char fio[4];
			cin >> fio;

			int search = BSearch(mas, fio);
			cout << endl;
			int search_start = 0;

			if (search == -1) {
				cout << "-" << endl;
			}
			else {
				do {
					if (search == 0) {
						break;
					}
					else {
						search--;
					}
					if (strncmp(mas[search]->fio, fio, 3) != 0) {
						search++;
						break;
					}
				} while (true);

				search_start = search;

				do {
					cout << "" << search + 1 << " " << mas[search]->fio << "  " << mas[search]->street << "  " << mas[search]->number_home << "  " << mas[search]->number_door << "  " << mas[search]->date << endl;
					search++;
					if (search == N) {
						break;
					}
					if (strncmp(mas[search]->fio, fio, 3) != 0) {
						break;
					}
				} while (true);

				cout << endl;
				cout << "Create Tree" << endl;
				cout << "1 - Yes;" << endl;
				cout << "2 - No;" << endl;
				int c;
				cin >> c;
				if (c == 1 or c == 2) {
					if (c == 1) {
						cout << "\t\t\tBuilding a tree" << endl;
						for (int i = search_start; i < search; i++) {
							cout << i + 1 << " " << mas[i]->fio << "  " << mas[i]->street << "  " << mas[i]->number_home << "  " << mas[i]->number_door << "  " << mas[i]->date << endl;
							AVL(mas[i], root);;
						}
						cout << endl << "\t\t\tLR-print - number_door" << endl;
						LRprint(root);
						cout << endl;
						cout << "--------------------------------------------" << endl;
						cout << "" << N << " |Size Tree" << "|Height" << "|Contl Sum" << "|Mid height|" << endl;
						cout << "--------------------------------------------" << endl;
						cout << "AVL  " << "|" << setw(7) << Size(root) << "  |" << setw(5) << Height(root) << " |" << setw(6) << Sum_Tree(root) << "   |" << setw(8) << Sum_Paths(root, 1) / Size(root) << "  |" << endl;
						cout << "--------------------------------------------" << endl;
						cout << "What will look for a tree" << endl;
						int C;
						cin >> C;
						Tree_Search(root, C);
						system("PAUSE");
						menu();
					}
					if (c == 2) {
						exit(0);
					}
				}

			}
		}
			
		if(v==4){
			BaseCoding();
			CodeBase();
			CodePrint();
			
		}
	}
}

int main()
{
	menu();
}
