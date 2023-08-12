#include <fstream>
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <cstdio> 
#include <conio.h>
#include <cstring> 
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <Windows.h>
using namespace std;


const int N = 4000;
const int M = 256;
int sum = 0;
int sym_count = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int sim_cf = 0, sim_f = 0;

struct Base {
	char name[30];
	unsigned short sum;
	char date[10];
	char lawyer[22];
};
Base Arr[N];
Base* Arr_sort[N];

struct List {
	List *next;
	Base record;
};

struct Queue {
	List *head;
	List *tail;
} Q;

struct vertex
{
	Base *data;
	vertex *next;
	int bal;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;
bool VR = true;
bool HR = true;

struct SN_code {
	float p;
	float q;
	int l;
	char a;
};
SN_code A[M];

void readDB();
void printDB();

				
void QuickSort(int L, int R);
int compare(Base record1, Base record2);
void printDB_sort();

void printQueue();
int BSearch(int n, unsigned short X);

void DBD(Base* data, vertex*& p); 
int compare_date(Base *a, Base *b);
int compare_tree_date(Base *a, char *b);
void TreePrint(vertex*);
void TreeSearch (vertex* p, char *data);

void TreeDelete(vertex *&p);
int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);

void shanon();
void Code();
void code_file();
void CodePrint();

int main() {
	
	setlocale(LC_ALL, "Russian");
	
	readDB();
	QuickSort(0, N - 1);
	Code();
	code_file();
	
	int enter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		int idx = -1;
		int record = -1;
		int j=0;
		
		SetConsoleCP(866);
		cout << "  1. Посмотреть базу данных" << endl;
		cout << "  2. Просмотр отсортированной базы данных (Quick sort)" << endl;
		cout << "  3. Поиск в отсортированной базе по ключу (Вклад)" << endl;
		cout << "  4. Поиск в дереве по ключу (Дата вклада)" << endl;
		cout << "  5. Кодирование" << endl;
		cout << "Esc. Выход " << endl;
		while ((enter != 27) && (enter != 49) && (enter != 50) && (enter != 51) && (enter != 52) && (enter != 53)) {
			if (_kbhit()) {
				enter = _getch();
			}
		}
		switch (enter) {
			case 27: return 0;
			case 49:
				printDB();
				break;
			case 50:
				printDB_sort();
				break;
			case 51:
				
				unsigned short X;
				printf("Enter key: ");
				scanf("%d", &X);
				idx = BSearch(N, X);
				record = idx;
				
				if (idx >= 0) {
					Q.tail = (List *)&Q.head;
					while (idx < N && Arr_sort[idx]->sum == X) {
						List *p = new List;
						p -> record = *Arr_sort[idx++];
						p -> next = NULL;
						Q.tail -> next = p;
						Q.tail = p;
					}
					
					if (root != NULL) {
						TreeDelete(root);
						root = NULL;
					}
					
					SetConsoleCP(1251);
					printf("| Record | \t\tName\t\t |  Sum  |   Date   |\t     Lawyer\t   |\n");
					List *p = Q.head;
					while (p != NULL) {
						printf("|%-8d|%-31s|%-7d|%10s|%22s|\n", record + 1, (p -> record).name, (p -> record).sum, (p -> record).date, (p -> record).lawyer);
						DBD(&p->record, root);
						p = p -> next;
						record++;
					}
				} else {
					printf("No such record!");
				}			
						
				break;
			case 52:
				SetConsoleCP(866);
				cout << endl << "ДБД дерево (Дата вклада)"<<endl;
				SetConsoleCP(1251);
				TreePrint(root);
				cout<<endl;
				printf("|  DBD | Size | Height | Mid. height |\n");
				printf("|%6d|%3d   |%5d   |%9.2f    |\n", N, size(root),  height(root), (double)sdp(root, 1) / size(root));
				cout<<endl<< "Element find: "<< endl;
				char date[2];
				cin >> date;
				TreeSearch(root,date);
				break;
			case 53:
				CodePrint();
				break;
		}
		_getch();
	}
	system ("Pause");
	return 0;
}


void readDB() {
	FILE *f;
	f = fopen("testBase3.dat", "rb");
	Base record;
	int n = 0;
		
	while (fread(&record, sizeof(record), 1, f)) {
		strcpy(Arr[n].name, record.name);
		Arr[n].sum = record.sum;
		strcpy(Arr[n].date, record.date);
		strcpy(Arr[n].lawyer, record.lawyer);
		
		Arr_sort[n] = &Arr[n];
		n++;
		
	}
	
	fclose(f);
}

void printDB() {
	int i;
	char choice;
	SetConsoleCP(1251);
	cout << "1 - all records / 2 - 20 records / 3 - exit"<< endl;
    cin>>choice;
    if(choice == '1'){
    	i=0;
		printf("| Record | \t\tName\t\t |  Sum  |   Date   |\t     Lawyer\t   |\n");
    	while(i<N){
			printf("|%-8d|%-31s|%-7d|%10s|%22s|\n", i + 1, Arr[i].name, Arr[i].sum, Arr[i].date, Arr[i].lawyer);
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
		}
	}
    if(choice == '2'){
		for (int i = 0; i < N; i += 20) {
			printf("| Record | \t\tName\t\t |  Sum  |   Date   |\t     Lawyer\t   |\n");
			for (int record = i; record < i + 20; record++) {
				printf("|%-8d|%-31s|%-7d|%10s|%22s|\n", record + 1, Arr[record].name, Arr[record].sum, Arr[record].date, Arr[record].lawyer);
			}
			printf("Continue? y/n : ");
			choice = fgetc(stdin);
			fgetc(stdin);
			if (choice == 'n') {
				break;
			}
			system("CLS");
		}
	}
}

void printDB_sort() {
	int i;
	char choice;
	SetConsoleCP(1251);
	cout << "1 - all records / 2 - 20 records / 3 - exit"<< endl;
    cin>>choice;
    if(choice == '1'){
    	i=0;
		printf("| Record | \t\tName\t\t |  Sum  |   Date   |\t     Lawyer\t   |\n");
    	while(i<N){
			printf("|%-8d|%-31s|%-7d|%10s|%22s|\n", i + 1, Arr_sort[i]->name,  Arr_sort[i]->sum,  Arr_sort[i]->date,  Arr_sort[i]->lawyer);
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
		}
	}
    if(choice == '2'){
		for (int i = 0; i < N; i += 20) {
			printf("| Record | \t\tName\t\t |  Sum  |   Date   |\t     Lawyer\t   |\n");
			for (int record = i; record < i + 20; record++) {
				printf("|%-8d|%-31s|%-7d|%10s|%22s|\n", record + 1,  Arr_sort[record]->name,  Arr_sort[record]->sum,  Arr_sort[record]->date,  Arr_sort[record]->lawyer);
			}
			printf("Continue? y/n : ");
			choice = fgetc(stdin);
			fgetc(stdin);
			if (choice == 'n') {
				break;
			}
			system("CLS");
		}
	}
}

int compare(Base *record1, Base *record2) {
	char data1[10], data2[10];
	int sum1 = record1->sum, sum2 = record2->sum;
	strcpy(data1, record1->date);
	strcpy(data2, record2->date);
	
	char *day1, *day2, *month1, *month2, *year1, *year2;
	day1 = strtok(data1, "-");
	month1 = strtok(NULL, "-");
	year1 = strtok(NULL, "-");
	
	day2 = strtok(data2, "-");
	month2 = strtok(NULL, "-");
	year2 = strtok(NULL, "-");
	if (sum1 > sum2) {
		return 1;
	} else if (sum1 < sum2) {
		return 0;
	} else if (strcmp(year1, year2) > 0) {
		return 1;
	} else if (strcmp(year1, year2) < 0) {
		return 0;
	} else if (strcmp(month1, month2) > 0) {
		return 1;
	} else if (strcmp(month1, month2) < 0) {
		return 0;
	} else if (strcmp(day1, day2) > 0) {
		return 1;
	} else {
		return 0;
	}
}

void QuickSort(int L, int R) {
 	Base *x;
 	Base *tmp;
 	
	while (L < R) {
		x = Arr_sort[L];
		int i = L, j = R;
		while (i <= j) {
			while (compare(x, Arr_sort[i])) {
				i++;
			}
			while (compare(Arr_sort[j], x)) {
				j--;
			}
			if (i <= j) {
				tmp = Arr_sort[i];
				Arr_sort[i] = Arr_sort[j];
				Arr_sort[j] = tmp;
				i++;
				j--;
			}
		}
		if ((j - L) < (R - i)) {
			QuickSort(L, j);
			L = i;
		} else {
			QuickSort(i, R);
			R = j;
		}
	}
}

int BSearch(int n, unsigned short X) {
	int L = 0, R = n - 1, find = -1;
	
	while (L < R) {
		int m = (L + R) / 2;
		if (X > Arr_sort[m]->sum) {
			L = m + 1;
		} else {
			R = m;
		}
	}
	
	if (X == Arr_sort[R]->sum) {
		find = R;
	}
	
	return find;
}

void TreePrint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		TreePrint(x->left);  
    	printf("|  %-31s|%-7d|%10s|%22s|\n", x->data->name, x->data->sum, x->data->date, x->data->lawyer);
		TreePrint(x->next);
		TreePrint(x->right); 
	}
}

void DBD(Base* data, vertex*& p) {
	if (p == NULL) {
		p = new vertex;
		p->data = data;
		p->bal = 0;
		p->next = NULL;
		p->left = NULL;
		p->right = NULL;
		VR = true;
	}
	else if (compare_date(p->data, data) == 0) {
		DBD(data, p->next);
	}
	else if (compare_date(p->data, data) > 0) {
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
	else if (compare_date(p->data, data) < 0) {
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

int compare_date(Base *a, Base *b) {
	if(strcmp(&a->date[6], &b->date[6]) != 0){
		return strcmp(&a->date[6], &b->date[6]);
	}
	return 0;
}

int compare_tree_date(Base *a, char *b) {
	if(strncmp(&a->date[6], b,2) != 0){
		return strcmp(&a->date[6], b);
	}
	return 0;
}

void TreeDelete(vertex *&p) {
	if (p != NULL) {
		TreeDelete(p->left);
		TreeDelete(p->right);
		delete p;
	}
}

void TreeSearch(vertex* p, char *data){
	if(p!=NULL)           
    {
        if (compare_tree_date(p->data, data) == 0) {
    		printf("|  %-31s|%-7d|%10s|%22s|\n", p->data->name, p->data->sum, p->data->date, p->data->lawyer);
			TreeSearch(p->next, data);
		}
		else if (compare_tree_date(p->data, data) > 0) {
			TreeSearch(p->left, data);
		}
		else if (compare_tree_date(p->data, data) < 0) {
			TreeSearch(p->right, data);
		}
	}
}

int size(vertex *x){
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->left) + size(x->right);
	}
}

int max(int x, int y){
	if (x > y) return x;
	return y;
}

int height(vertex *x){
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->left), height(x->right));
	}
}

int sdp(vertex *x, int l){
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->left, l + 1) + sdp(x->right, l + 1);
	}
}

void CodePrint(){
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nКод Шенона: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M && A[i].p != 0; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].q);
		for (int j = 0; j < A[i].l+1; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("   |  %7d      |\n", A[i].l+1);
		lgm += A[i].p * A[i].l;
	}	
	printf("-------------------------------------------------------------------------------\n");
	SetConsoleCP(866);
	printf("  Энтропия: \t %10f \n", entropy);
	printf("  Средняя длина: %9.5f \n", lgm);
	cout << setw(8) << entropy + 2 << " > " << lgm << endl << endl;
	cout << setw(8) << "Коэфициент сжатия: " << (float) sim_f / sim_cf << endl;
}

void Code(){
	
	int i,j;
	FILE *f;	
	f=fopen("testBase3.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].q = 0;
		A[i].a = (char)(i-128); 
	}
	while (!feof(f)) {
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		A[c+128].p +=1;
		sum++;
	}
	fclose(f);
	printf("\n");
	//сортировка по количеству повторений символов
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				SN_code B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	for (i = 0; i < M && A[i].p != 0; i++){
		A[i].p /=sum;
		A[i].q = A[i].p;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
		sym_count++;
	}
	shanon();
}

void code_file() {
	FILE *f, *cf;
	f = fopen("testBase3.dat", "rb");
	cf = fopen("CodeBase.dat", "wb");
	char sim;
	while (!feof(f)) {
		fscanf(f, "%c", &sim);
		sim_f++;
		for (int i = 0; i < M; i++) {
			if (sim == A[i].a) {
				for (int j = 0; j < A[i].l; j++) {
					putc(code[i][j], cf);
					sim_cf++;
				}
			}
		}
	}
	_fcloseall();
}

void shanon(){
	for (int i = 0; i < M && A[i].p!=0; i++)
	{
		A[i].q = A[i - 1].q + A[i].p;
		A[i].l = ceil(-log(A[i].p) / log(2));
	}
	for (int i = 1; i < M && A[i].p!=0; i++)
	{
		for (int j = 1; j <= A[i].l; j++)
		{
			A[i - 1].q *= 2;
			code[i][j] = floor(A[i - 1].q);
			while (A[i - 1].q >= 1)
				A[i - 1].q -= 1;
		}
	}
}


