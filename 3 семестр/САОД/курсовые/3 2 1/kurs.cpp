
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
void Print_sort_index_mas(list **mas);
int BSearch (list **A, int deposit);

int compare_deposit(int a, int b);
int compare_date(char a[], char b[]);

void HeapBuild (list **A, int l, int r, int sort);
void HeapSort (int n, list **A, int sort);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	FILE *fp;
	
	fp=fopen("testBase3.dat", "rb");
	list *base = new list;
	list *base_index =new list;
	Read_base(fp,base);
	fclose(fp);
	copy_base(base, base_index);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=base_index;
		base_index=base_index->next;
	}
	for(int i=0; i<2;i++)
		HeapSort(N, mas, i);
	
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
		cout << "\t2. Просмотр отсортированной базы данных (Heap sort)" << endl;
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
			Print_sort_index_mas(mas);
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
	if(a>=b){
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

void HeapBuild (list **A, int l, int r, int sort) {
	int i=l, j;
	list *x=A[l];
	
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		int result = 0;
		if(j<r){
			if (sort == 0){
				result = compare_date(A[j+1]->data->date, A[j]->data->date);
			}
			else{
				result = compare_deposit(A[j+1]->data->deposit, A[j]->data->deposit);
			}
			if(result > -1){
				j++;
			}
		}
		
		result = 0;
		if (sort == 0){
			result = compare_date(x->data->date, A[j]->data->date);
		}
		else{
			result = compare_deposit(x->data->deposit, A[j]->data->deposit);
		}
		if(result > -1){
			break;
		}
		
		A[i]=A[j];
		i=j;
	}
	A[i]=x;
}

void HeapSort (int n, list **A, int sort) {
	int l=n/2, r=n;
	while (l+1>0) {
		HeapBuild (A, l, r, sort);
		l--;
	}
	while (r>1) {
		list* t=A[0];
		A[0]=A[r-1];
		A[r-1]=t;
		r--;
		HeapBuild (A, 0, r-1, sort);
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

void Print_sort_index_mas(list **mas){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i<<"  "<<mas[i]->data->depositor<<"  "<<mas[i]->data->deposit<<"  "<<mas[i]->data->date<<"  "<<mas[i]->data->lawyer <<endl;
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
    if(n=='2'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
	    		cout<<i+g<<"  "<<mas[i+g]->data->depositor<<"  "<<mas[i+g]->data->deposit<<"  "<<mas[i+g]->data->date<<"  "<<mas[i+g]->data->lawyer <<endl;
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
