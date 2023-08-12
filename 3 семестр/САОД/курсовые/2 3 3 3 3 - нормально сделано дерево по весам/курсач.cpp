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
int code[n_symb][n_symb];
float entropy = 0, av_length = 0;
int sym_count = 0;

int bin_search_counter=0;
int *W;
int *h;
bool Rost = false;

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

struct Vertex {
	Base* data; 
    int w;
    int h;
    Vertex* Next = NULL;
	Vertex* Left = NULL;
	Vertex* Right = NULL;
};

struct Fano {
	float p;
	float q;
	int l;
	char a;
};
Fano A[n_symb];

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
	bin_search_counter = i;
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
	else{
		cout << "Record with created key not found in directory \n";
		return NULL;
	}
	return q;
}

/*------------------------Vertex----------------------------------*/

void addDOP(list* binList, Vertex*& p, int w) {
	//cout << "456";
	if (p == NULL) {
		p = new Vertex;
		p->data = binList->data;
		p->Left = NULL;
		p->Right = NULL;
		p->Next = NULL;
		p->w = w;
	//	cout << "789";
	}
	else if (Compare0(p->data->position, binList->data->position) == 0) {
		addDOP(binList, p->Next, w);
	}
	else if (Compare0(p->data->position, binList->data->position) > 0) {
		addDOP(binList, p->Left, w);
	}
	else if (Compare0(p->data->position, binList->data->position) < 0) {
		addDOP(binList, p->Right, w);
	}
}


void ObhodLeft(Vertex* p, int& count) {
	if (p != NULL) {
		ObhodLeft(p->Left, count);
		printf("%2d - %3d) %-32s %-5d %-24s %-10s\n", count + 1, p->w, p->data->worker, p->data->number, p->data->position, p->data->birthdate);
		count++;
		ObhodLeft(p->Next, count);
		ObhodLeft(p->Right, count);
	}
}

void TreeSearch(char* str, Vertex*& p, int& count, bool& tree_find) {
	if (p) {
		int temp = Compare0(str, p->data->position);                       // Поиск в дереве проходит по этому полю
		if (temp == 0) {
			tree_find = 1;
			printf("%2d - %3d) %-32s %-5d %-24s %-10s\n", count + 1, p->w, p->data->worker, p->data->number, p->data->position, p->data->birthdate);
 			count++;
			TreeSearch(str, p->Next, count, tree_find);
		}
		else if (temp < 0)
			TreeSearch(str, p->Left, count, tree_find);
		else if (temp > 0)
			TreeSearch(str, p->Right, count, tree_find);
	}
}

void delete_tree(Vertex *&p) {
	if (p != NULL) {
		delete_tree(p->Next);
		delete_tree(p->Left);
		delete_tree(p->Right);
		delete p;
	}
}
/*--------------------------Coding----------------------------------*/

int med(int L, int R)
{
	float sl = 0, sr;
	for (int i = L; i < R; i++)
		sl += A[i].q;
	sr = A[R].q;
	int m = R;
	while (sl >= sr)
	{
		m--;
		sl -= A[m].q;
		sr += A[m].q;
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

void CodeF() {
	
	int i,j,v=0;
	entropy=0;
	sym_count = 0;
	av_length = 0;
	for (i = 0; i < n_symb; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].q = 0;
		A[i].a = (char)(i-128); 
	}
	FILE *fp;	
	fp=fopen("testBase2.dat", "rb");
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		A[c+128].p +=1;
		sym_count++;
	}
	printf("\n");
	fclose(fp);
	//сортировка по количеству повторений символов
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < n_symb; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				Fano B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	
	for (i = 0; i < n_symb && A[i].p != 0; i++){
		A[i].p /= sym_count;
		A[i].q = A[i].p;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
        v++;
	}
	//кодирование по фано
	fano(0, v-1, 0);
	//вывод результатов
	printf("\n\nFano: \n\n");
	printf("| Num | Sym | Probability |       Code word      | Code word length|\n");
	printf("|------------------------------------------------------------------|\n");
	
	for (int i = 0; i < n_symb && A[i].l != 0; i++)
	{
		printf("|  %2d |  %c  |  %2.6f   | ",i, A[i].a, A[i].q);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |    %7d      |\n", A[i].l);
		av_length += A[i].p * A[i].l;
	}	
	
	printf("    Entropy    Average Length  \n");
	printf(" %10f    %10.5f    \n", entropy, av_length);
	
	cout << endl << endl << entropy+1 <<" > "<< av_length <<endl <<endl;
	
}

void Sort(list **mas, int end)
{
    int i, j;
	list *buf;
    for (i = 0; i < end - 1; i++) {
        for (j = end - 1; j > i; j--) {
            if (Compare0(mas[j]->data->position, mas[j-1]->data->position) < 0) {
                buf = mas[j];
                mas[j] = mas[j - 1];
                mas[j - 1] = buf;
            }
        }
    }
}

void WeightSort(list **mas, int end)
{
    int i, j,v;
	list *buf;
    for (i = 0; i < end - 1; i++) {
        for (j = end - 1; j > i; j--) {
            if (W[j] > W[j - 1]) {
                v = W[j];
                W[j] = W[j - 1];
                W[j - 1] = v;
				buf = mas[j];
                mas[j] = mas[j - 1];
                mas[j - 1] = buf;
            }
        }
    }
}

void print_list(list* p)
{
	Vertex* Root = NULL;
	list *q, *l = p;
	list* mas[200];
	int count = 0;
	int flag = 0;
	bool tree_find = 0;
	while (1) {
		q = p;
		int k;
		int counter, start, end;
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
			if(l != NULL){
				flag = 1;
				OutputList(l);
			}
			system("PAUSE");
			break;
		case 4:
			if(flag == 0){
				cout << "First of all find something with B-Search \n";
				system("PAUSE");
				continue;
			}
			if (Root != NULL) {
				delete_tree(Root);
				Root = NULL;
			}
			W = new int[4000];
            counter = 0;
            start = 0;
            end = 0;
			for (list *k = l->next; k != NULL; k = k->next)
			{
				mas[counter] = k;
				counter++;
			}
			//сортируем все найденные записи по должности
        	Sort(mas, counter);	
            for (int i = 0; i < counter-1; i++) {
            	cout << mas[i]->data->position << endl;
            	if(strcmp(mas[i]->data->position, mas[i+1]->data->position) != 0){
            		end = i;
            		cout << start << " - " << end << endl;
            		for(int j = start; j <= end; j++){
            			W[j] = end-start+1;
					}
					start = i+1;
				}
            }
			cout << start << " - " << counter-1 << endl;
			
            for(int j = start; j < counter; j++){
            	W[j] = counter-start;
			}
            //сортировка записей в массиве по весам
        	WeightSort(mas, counter);
			for (int i =0; i < counter; i++)
			{
            //	cout << mas[i]->data->position << endl;
				addDOP(mas[i], Root, W[i]);
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
			CodeF();
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
