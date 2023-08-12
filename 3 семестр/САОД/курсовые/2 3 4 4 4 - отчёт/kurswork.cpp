
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
#include <algorithm>
using namespace std;


const int N=4000;
const int M=256;
const int alphabet_num=81;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int *W;

struct record
{
	char FIO[30];
	short int Department;
	char Position[22];
	char Date[10];
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

struct vertex
{
	record *data;
	vertex *next;
	int weight;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;

struct GM_code {
	float p;
	float q;
	int l;
	char a;
};
GM_code A[M];
GM_code B[alphabet_num];

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);
void Print(list *base);
void DigitalSort (list *&head);
int BSearch (list **A, char year[2]);

void A2(int L, int R, list **mas);
void add_vertex(vertex *&p, list* mas, int w);
void LRprint(vertex*);
void TreeSearch (vertex* p, char *data);

void delete_tree(vertex *&p);
int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);

void GilbertMoorCode();
void CodePrint();

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	FILE *fp;
	W = new int[N];
	int enter = 0;
	
    fp = fopen("testBase2.dat", "rb");
	list *base = new list;
	list *base_sort= new list;
	list *base_index =new list;
	Read_base(fp,base);
	fclose(fp);
	
	copy_base(base, base_sort);
	DigitalSort(base_sort);
	copy_base(base_sort, base_index);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=base_index;
		base_index=base_index->next;
	}
	GilbertMoorCode();
	while (true) {
		system("CLS");
		enter = 0;
		char *spc = " ";
		int search_start=0;
		int search=N-1;
		
		SetConsoleCP(866);
		cout << "\t\t\t\tМЕНЮ" << endl;
		cout << "\t1. Посмотреть БД" << endl;
		cout << "\t2. Просмотр отсортированной БД (Digital sort по дате рождения и должности)" << endl;
		cout << "\t3. Поиск в отсортированной БД по ключу (год рождения)" << endl;
		cout << "\t4. Поиск в дереве по ключу (должность)" << endl;
		cout << "\t5. Результаты кодирования" << endl;
		cout << "\tEsc. Выход " << endl;
		cout << endl;
		while ((enter != 27) && (enter != 49) && (enter != 50) && (enter != 51) && (enter != 52) && (enter != 53)) {
			if (_kbhit()) {
				enter = _getch();
			}
		}
		switch (enter) {
		case 27: return 0;
		case 49:
			Print(base);
			_getch();
			break;
		case 50:
			Print(base_sort);
			_getch();
			break;
		case 51:
			cout <<endl;
			cout << "Enter year"<<endl;
			char year[2];
			cin >> year;
			search=BSearch(mas,year);
			if(search == -1){
				cout << "No data" << endl;
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
					
				   	if(strncmp(&mas[search]->data->Date[6],year,2) != 0){
				   		search++;
				   		break;
					}
				}
				while(true);
				   
				search_start=search;
				
				do{
					search++;
					if(search==N){
						search--;
						break;
					}
					if(strncmp(&mas[search]->data->Date[6],year,2) != 0){
				   		break;
					}
				}
				while(true);
								
				int* mass_random = new int[N];
				for (int i = 0; i < N; i++) {
					mass_random[i] = rand() % 100;
				}
				sort(mass_random, mass_random + N - 1, greater<int>());
				if (root != NULL) {
					delete_tree(root);
					root = NULL;
				}
				cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
				for(int i=search_start;i<search;i++){
					cout<<i<<"  "<<mas[i]->data->FIO<<" "<<mas[i]->data->Department<<"\t"<<mas[i]->data->Position<<"  "<<mas[i]->data->Date<<endl;
					W[i] = rand() % 99 + 1;
				}
				A2(search_start, search,mas);
			}
			_getch();
			break;
			
		case 52:
			cout << endl << "LR-print - должность"<<endl;
			LRprint(root);
			cout<<endl;
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|%6d|   Size   |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|  A2  |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			SetConsoleCP(866);
			cout<<endl<< "Поиск в дереве: "<< endl;
			char j[22];
			cin.sync();
			cin.getline(j,22);
			SetConsoleCP(1251);
			for(int i = strlen(j); i<21;i++){
				strcat(j, spc);
			}
			if(strcmp(j,"0")!=0){
				TreeSearch(root,j);
			}
			_getch();
			break;
		case 53:
			CodePrint();
			_getch();
			break;
		}
	}
	system ("Pause");
	return 0;
}

void CodePrint(){
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nКод Гилберта-Мура: \n\n");
	printf("|  № | Symbol | Propability |     Code word    | Length |\n");
	SetConsoleCP(1251);
	for (int i = 0; i < alphabet_num; i++)
	{
		printf("| %2d |    %c   |  %2.6f   | ",i, B[i].a, B[i].q);
		for (int j = 1; j <= B[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = B[i].l + 1; j < 14; j++)
			printf(" ");
		printf("    |  %4d  |\n", B[i].l);
		lgm += B[i].p * B[i].l;
	}	
	SetConsoleCP(866);
	
	printf("\n   Энтропия \t Средняя длина\n");
	printf(" %10f      %10.5f    \n", entropy, lgm);
	
	cout << endl << endl << entropy+2 <<" > "<< lgm <<endl <<endl;
	
}


void GilbertMoorCode(){
	int i,j;
	FILE *fp;	
    fp = fopen("testBase2.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].q = 0;
		A[i].l = 0;
		A[i].a = (char)(i-128);
	}
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		//printf("%c",c);
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		A[c+128].a = c;
		sum++;
	}
	fclose(fp);	
	for (i = 0, j = 0; i < M; i++){
		if(A[i].p!=0){
			A[i].p /=sum;
			B[j]=A[i];
			entropy += A[i].p * abs(log(A[i].p) / log(2));
			j++;
		}
	}
	
	for (i = 0; i < alphabet_num; i++){
		B[i].q = B[i-1].q + B[i].p/2;
		B[i].l = ceil(-log(B[i].p) / log(2)) + 1;
	}
	
	for (i = 0; i < alphabet_num; i++)
	{
		for (j = 0; j <= B[i].l; j++)
		{
			B[i].q *= float(2);
			code[i][j] = floor(B[i].q);
			while (B[i].q >= 1)
				B[i].q -= 1;
		}
	}
}

void TreeSearch (vertex* p, char *data){
	if(p!=NULL)                 ///Поиск элемента
    {
        if(strcmp(p->data->Position,data) > 0){
        //	cout << data << "-l" << endl << p->data->Position << "-l" << endl << endl;
            TreeSearch(p->left,data);
        }else{
            if(strcmp(p->data->Position,data) < 0){
        //		cout << data << "-r" << endl << p->data->Position << "-r" << endl << endl;
              	TreeSearch(p->right,data);
            }else{
				cout<<" "<<p->data->FIO<<" "<<p->data->Department<<"\t"<<p->data->Position<<"  "<<p->data->Date<<endl;
				TreeSearch(p->next,data);
			}
        }
    }
}



int BSearch (list **A, char year[2]) {
	int l = 0, r = N, m = 0, fam_pos=0;
	char buffer[32];
	while (l < r) {
		m=(l+r)/2;
		if (strncmp(&A[m]->data->Date[6],year,2) == 0){
			return m;
		}
		if (strncmp(&A[m]->data->Date[6],year,2) < 0)
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


void Print(list *base){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=-1;
    	while(i<N){
    		i++;
    		cout<<i<<"  "<<base->data->FIO<<" "<<base->data->Department<<"\t"<<base->data->Position<<"  "<<base->data->Date<<endl;
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
		i=-1;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
	    		cout<<i+g<<"  "<<base->data->FIO<<" "<<base->data->Department<<"\t"<<base->data->Position<<"  "<<base->data->Date<<endl;
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

int DateMatch(record *a, record *b) 
{ 
	if(strcmp(&a->Date[6], &b->Date[6]) != 0){
		return strcmp(&a->Date[6], &b->Date[6]);
	}
	else if (a->Date[3] - b->Date[3] != 0) {
		return a->Date[3] - b->Date[3];
	}
	else if (a->Date[4] - b->Date[4] != 0) {
		return a->Date[4] - b->Date[4];
	}
	else if (a->Date[0] - b->Date[0] != 0) {
		return a->Date[0] - b->Date[0];
	}
	else if (a->Date[1] - b->Date[1] != 0) {
		return a->Date[1] - b->Date[1];
	}
	else if (strncmp(a->Position, b->Position,3) != 0) {
		return strncmp(a->Position, b->Position,3);
	}
	return 0;
}


void DigitalSort (list *&head) {
	int i, j, k, l=10;
	char buffer[32];
	int d;
	list *p, *tail;
	queue q[256]; 									//вводим очереди
	
	//сортируем по должности
	for (j=0; j<=21; j++) 							
    {
    	d=0;
		for (i=0; i<256; i++)
		{
			q[i].tail=q[i].head=NULL; 				//обнуляем очереди
		}
		p=head;
		while (p!=NULL) 							//пока не конец списка
        {
        	k=0;
        	
			if(p->data->Position[j] == ' '){
				d=0;
			}
			else
			{
			d=p->data->Position[j]+129;				//считываем индекс для q[i] очереди по букве
			}
				
			if(q[d].tail==NULL){ 					//если такая буква не встречалась
				k=1;
			}
			
			q[d].head=p;
			if(k==1){ 
				q[d].tail=q[d].head;
				q[d].tail->prev=NULL;
			}
			else{ 									//если такая буква встречалась
				q[d].tail->next=q[d].head;
				q[d].tail->next->prev=q[d].tail;
				q[d].tail=q[d].tail->next;
			}
			q[d].head=q[d].head->next;
			p=p->next;
		}
		for (i=0; i<256; i++)						//отматываем указатели tail на начало очереди 
		{				
			if(q[i].tail !=NULL){
				q[i].tail->next=NULL;
				while(q[i].tail->prev != NULL){
					q[i].tail=q[i].tail->prev;
				}
			}
			
		}
	
		tail=NULL;
		for(i=0;i<256;i++)							//связываем все очереди по порядку i в список если очередь не пустая  
		{
			if(q[i].tail!=NULL){
				head=q[i].tail;
				head->prev=tail;
				if(tail!=NULL)
					head->prev->next=head;
				while(q[i].tail!=NULL){
					tail=head;
					head=head->next;
					q[i].tail=q[i].tail->next;
				}
			}
		}
		while(tail->prev!=NULL){					//отматываем tail на начало
			tail=tail->prev;
		}
		head=tail;
	}
	//сортируем по дате
	for (j=1; j>-1; j--) 							
    {
    	d=0;
		for (i=0; i<256; i++)
		{
			q[i].tail=q[i].head=NULL; 				//обнуляем очереди
		}
		p=head;
		while (p!=NULL) 							//пока не конец списка
        {
        	k=0;
        	if(p->data->Date[j]=='-'){
				d=0;
			}
			else
			{
			d=p->data->Date[j]+129;				//считываем индекс для q[i] очереди по букве
			}
				
			if(q[d].tail==NULL){ 					//если такая буква не встречалась
				k=1;
			}
			
			q[d].head=p;
			if(k==1){ 
				q[d].tail=q[d].head;
				q[d].tail->prev=NULL;
			}
			else{ 									//если такая буква встречалась
				q[d].tail->next=q[d].head;
				q[d].tail->next->prev=q[d].tail;
				q[d].tail=q[d].tail->next;
			}
			q[d].head=q[d].head->next;
			p=p->next;
		}
		for (i=0; i<256; i++)						//отматываем указатели tail на начало очереди 
		{				
			if(q[i].tail !=NULL){
				q[i].tail->next=NULL;
				while(q[i].tail->prev != NULL){
					q[i].tail=q[i].tail->prev;
				}
			}
			
		}
	
		tail=NULL;
		for(i=0;i<256;i++)							//связываем все очереди по порядку i в список если очередь не пустая  
		{
			if(q[i].tail!=NULL){
				head=q[i].tail;
				head->prev=tail;
				if(tail!=NULL)
					head->prev->next=head;
				while(q[i].tail!=NULL){
					tail=head;
					head=head->next;
					q[i].tail=q[i].tail->next;
				}
			}
		}
		while(tail->prev!=NULL){					//отматываем tail на начало
			tail=tail->prev;
		}
		head=tail;
		if(j==0){
			j=5;
		}
		if(j==3){
			j=8;
		}
		if(j==6){
			break;
		}
	}
}


void add_vertex(vertex *&p, list* mas, int w) {
	if (p == NULL) {
		p = new vertex;
		p->data = mas->data;
        p->weight = w;
		p->next = NULL;
		p->left = NULL;
		p->right = NULL;
	}
	else if (strcmp(p->data->Position,mas->data->Position) == 0) {
		add_vertex(p->next, mas, w);
	}
	else if (strcmp(p->data->Position,mas->data->Position)  > 0) {
		add_vertex(p->left, mas, w);
	}
	else if (strcmp(p->data->Position,mas->data->Position)  < 0) {
		add_vertex(p->right, mas, w);
	}
}

void A2(int L, int R, list **mas) {
	int wes = 0, sum = 0;
	int i;
	if (L <= R) {
		for (i = L; i <= R; i++) {
			wes = wes + W[i];
		}
		for (i = L; i < R; i++) {
			if ((sum < (wes / 2)) && (sum + W[i]) > (wes / 2)) {
				break;
			}
			sum = sum + W[i];
		}
		//cout << L << " - " << R << " - " << wes << " - " << i  << " - " << W[i] << endl;
		add_vertex(root, mas[i], W[i]);
		A2(L, i - 1,mas);
		A2(i + 1, R,mas);
	}
}


void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

void LRprint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		LRprint(x->left);  
    		cout<<"  "<<x->data->FIO<<" "<<x->data->Department<<"\t"<<x->data->Position<<"  "<<x->data->Date<<endl;
		LRprint(x->next);
		LRprint(x->right); 
	}
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

