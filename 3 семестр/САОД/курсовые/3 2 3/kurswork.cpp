
#define YES true
#define NO false

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
using namespace std;

const int N=4000;

struct record
{
	char depositor[30];
	unsigned short int deposit;
	char date[10];
	char lawyer[22];
};

struct list
{
	record *data;
	list* prev;
	list* next;	
};

struct queue {
	list *head;
	list *tail;
};

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);
void Print_base(list *base);
int BSearch (list **A, int deposit);

int compare_deposit(int a, int b);
int compare_date(char a[], char b[]);

void merge(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr, int sort);
void merge_sort(list*& head, int sort);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	FILE *fp;
	
	fp=fopen("testBase3.dat", "rb");
	list *base = new list;
	list *base_sort= new list;
	list *base_index =new list;
	Read_base(fp,base);
	fclose(fp);
	copy_base(base, base_sort);
	for(int i=0; i<2;i++)
		merge_sort(base_sort, i);
	copy_base(base_sort, base_index);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=base_index;
		base_index=base_index->next;
	}
	
	int enter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		int search_start=0;
		int search=N-1;
		int j=0;
		SetConsoleCP(866);
		cout << "\t------------------------------МЕНЮ------------------------" << endl;
		cout << "\t1. Посмотреть базу данных" << endl;
		cout << "\t2. Просмотр отсортированной базы данных (Merge sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (Сумма вклада)" << endl;
		cout << "\tEsc. Выход " << endl;
		cout << "\t----------------------------------------------------------" << endl;
		while ((enter != 27) && (enter != 49) && (enter != 50) && (enter != 51)) {
			if (_kbhit()) {
				enter = _getch();
			}
		}
		switch (enter) {
		case 27: return 0;
		case 49:
			Print_base(base);
			_getch();
			break;
		case 50:
			Print_base(base_sort);
			_getch();
			break;
		case 51:
			cout <<endl;
			cout << "Chto budem iskat(deposit)"<<endl;
			int deposit = -1;
			SetConsoleCP(866);
			cin >> deposit;
			if(deposit >= 0){
				search = BSearch(mas,deposit);
				int fam_pos=0;
				char buffer[32];
				if(search == -1){
					cout << "Deposit doesn't exists''" << endl;
				}
				else{	
					SetConsoleCP(1251);
					do{
						if(search==0){
							break;
						}
						else{
							search--;
						}
				    	if(mas[search]->data->deposit != deposit){
				    		search++;
				    		break;
						}
					}
					while(YES);
				    
					search_start=search;
					
					do{
						search++;
						if(search==N){
							break;
						}
						if(mas[search]->data->deposit != deposit){
				    		break;
						}
					}
					while(YES);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout << "Deposit has been founded: "<<i<<" "<<mas[i]->data->depositor<<"  "<<mas[i]->data->deposit<<"  "<<mas[i]->data->date<<"  "<<mas[i]->data->lawyer<<endl;
					}
				}
			}
			_getch();
			break;
		}
	}
	system ("Pause");
	return 0;
}

int compare_deposit(int a, int b) {
	if(a>b){
		return 1;
	}
	else{
		return -1;
	}
}

int compare_date(char* a, char* b) {
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

//сливает очереди h1-t1 и h2-t2 в очередь hr-tr
void merge(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr, int sort) {
	int result = 0;
	if (sort == 0){
		result = compare_date(h1->data->date, h2->data->date);
	}
	else{
		result = compare_deposit(h1->data->deposit, h2->data->deposit);
	}
	if (result < 0) {
		hr = h1;
		h1 = h1->next;
	}
	else {
		hr = h2;
		h2 = h2->next;
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2) {
		if (sort == 0){
			result = compare_date(h1->data->date, h2->data->date);
		}
		else{
			result = compare_deposit(h1->data->deposit, h2->data->deposit);
		}
		if (result < 0) {
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

void merge_sort(list*& head, int sort) {
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
				if (t2->next == NULL) {
					break;
				}
				t2 = t2->next;
			}
			tp = t2->next;
			t1->next = NULL;
			t2->next = NULL;
			merge(h1, t1, h2, t2, hr, tr, sort);
			hp->next = hr;
			head = hr;
			tr->next = tp;
			hp = tr;
		}
		k *= 2;
	}
}

int BSearch (list **A, int deposit) {
	int l = 0, r = N, m = 0, fam_pos=0;
	while (l <= r) {
		m=(l+r)/2;
		
		
		if (A[m]->data->deposit == deposit) {
			return m;
		}
		if (A[m]->data->deposit < deposit) 
			l = m+1;
		else r = m-1;
	}
	return -1;
}

void Read_base(FILE *fp, list *base){
	record *mas = new record();
	fread((record *)mas, sizeof(record), 1, fp);
	base->data=mas;
	base->prev=NULL;
	base->next=NULL;
	
	for (int i = 1; i < N; i++) {
        mas = new record();
        list *base_prev;
        fread((record*)mas, sizeof(record), 1, fp);
        base_prev = base;
        base = base->next = new list();
        base->data = mas;
        base->prev = base_prev;
        base->next = NULL;
    }
}


void Print_base(list *base){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i<<"  "<<base->data->depositor<<"  "<<base->data->deposit<<"  "<<base->data->date<<"  "<<base->data->lawyer <<endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
			base=base->next;
		}
	}
    if(n=='2'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
	    		cout<<i+g<<"  "<<base->data->depositor<<"  "<<base->data->deposit<<"  "<<base->data->date<<"  "<<base->data->lawyer <<endl;
				base=base->next;
			}
			if(g>=20){
		   		cout << "y for continue" << endl;
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
	
		
}

void copy_base(list *a, list *b) {
	b->prev = NULL;
	b->data = a->data;
	for (int i = 1; i < N; i++) {
		a = a->next;
		b->next = new list;
		b->next->prev = b;
		b = b->next;
		b->data = a->data;
	}
	b->next = NULL;
}
