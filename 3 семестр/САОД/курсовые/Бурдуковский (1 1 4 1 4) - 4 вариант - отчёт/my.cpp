
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
const int M=256;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;

struct record
{
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
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
	int bal;
	vertex *left;
	vertex *right;
};

struct GM_code {
	float p;
	float q;
	int l;
};

vertex *root = NULL;
GM_code A[M];
bool up = NO;

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);
void Print_base(list *base);
void DigitalSort (list *&head);


void addAVL(list *mas, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);


int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);


void LRprint(vertex*);
int BSearch (list **A, char title[3]);
void TreeSearch (vertex* p, int data);

void BaseCoding();
void CodePrint();
void CodeBase();

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	FILE *fp;
	
	fp=fopen("testBase1.dat", "rb");
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
	BaseCoding();
	CodeBase();
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
		cout << "\t2. Просмотр отсортированной базы данных (Digital sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (Фамилия замечательных людей-3буквы)" << endl;
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
			Print_base(base);
			_getch();
			break;
		case 50:
			Print_base(base_sort);
			_getch();
			break;
		case 51:
			cout <<endl;
			cout << "Chto budem iskat(title fam)"<<endl;
			char title[3];
			SetConsoleCP(866);
			cin >> title;
			if(strcmp(title,"0")!=0){
				search=BSearch(mas,title);
				int fam_pos=0;
				char buffer[32];
				if(search == -1){
					cout << "Sirname hasn't been founded'" << endl;
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
						fam_pos=strchr(mas[search]->data->title, ' ')-mas[search]->data->title;
				   		strcpy(buffer,mas[search]->data->title);
				    	buffer[fam_pos]='a';
				    	fam_pos=strchr(buffer, ' ')-buffer;
				    	buffer[0]=mas[search]->data->title[fam_pos+1];
				    	buffer[1]=mas[search]->data->title[fam_pos+2];
				    	buffer[2]=mas[search]->data->title[fam_pos+3];
				    	if(strncmp(buffer,title,3)!=0){
				    		search++;
				    		break;
						}
					}
					while(YES);
				    
					search_start=search;
					
					do{
						//cout << "Sirname has been founded: "<<search<<" "<<mas[search]->data->author<<"  "<<mas[search]->data->title<<"  "<<mas[search]->data->publisher<<"  "<<mas[search]->data->year<<"  "<<mas[search]->data->num_of_page<<endl;
						search++;
						if(search==N){
							break;
						}
						fam_pos=strchr(mas[search]->data->title, ' ')-mas[search]->data->title;
				   		strcpy(buffer,mas[search]->data->title);
				    	buffer[fam_pos]='a';
				    	fam_pos=strchr(buffer, ' ')-buffer;
				    	buffer[0]=mas[search]->data->title[fam_pos+1];
				    	buffer[1]=mas[search]->data->title[fam_pos+2];
				    	buffer[2]=mas[search]->data->title[fam_pos+3];
				    	if(strncmp(buffer,title,3)!=0){
				    		break;
						}
					}
					while(YES);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout << "Sirname has been founded: "<<i<<" "<<mas[i]->data->author<<"  "<<mas[i]->data->title<<"  "<<mas[i]->data->publisher<<"  "<<mas[i]->data->year<<"  "<<mas[i]->data->num_of_page<<endl;
						addAVL(mas[i], root);
					}
				}
			}
			_getch();
			break;
		case 52:
			cout << endl << "LR-print - publisher"<<endl;
			LRprint(root);
			cout<<endl;
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|%6d|   Size   |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|  AVL |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			cout<<endl<< "Element find: "<< endl;
			cin >> j;
			TreeSearch(root,j);
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

void CodeBase() {
	FILE *fp, *fcoded;
    fp = fopen("testBase1.dat", "rb");
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
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nКод Гилберта-Мура: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, (char)(i-128), A[i].q);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |  %7d      |\n", A[i].l);
		printf("|-----------------------------------------------------------------------------|\n");
		lgm += A[i].p * A[i].l;
	}	
	SetConsoleCP(866);
	
	printf("________________________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |  Коэф сжатия  |\n");
	printf("|____________|_________________|_______________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression/cfcompression);
	printf("|____________|_________________|_______________|\n");
	
	cout << endl << endl << entropy+2 <<" > "<< lgm <<endl <<endl;
	
}


void BaseCoding(){
	int i,j;
	FILE *fp;	
	fp=fopen("testBase1.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].q = 0;
		A[i].l = 0;
	}
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		//printf("%c",c);
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		sum++;
	}
	fclose(fp);	
	for (i = 0; i < M; i++){
		A[i].p /=sum;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
	}
	
	for (i = 0; i < M; i++){
		A[i].q = A[i-1].q + A[i].p/2;
		A[i].l = ceil(-log(A[i].p) / log(2)) + 1;
	}
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j <= A[i].l; j++)
		{
			A[i].q *= float(2);
			code[i][j] = floor(A[i].q);
			while (A[i].q >= 1)
				A[i].q -= 1;
		}
	}
}

void TreeSearch (vertex* p, int data){
		if(p!=NULL)                 ///Поиск элемента
        {
            if(data<p->data->year){
                    TreeSearch(p->left,data);
            }else{
                    if(data>p->data->year){
                    	TreeSearch(p->right,data);
                }else{
					cout << "Sirname has been founded: "<<" "<<p->data->author<<"  "<<p->data->title<<"  "<<p->data->publisher<<"  "<<p->data->year<<"  "<<p->data->num_of_page<<endl;
                    TreeSearch(p->next,data);
				}
            }
        }
}



int BSearch (list **A, char title[3]) {
	int l = 0, r = N, m = 0, fam_pos=0;
	char buffer[32];
	while (l <= r) {
		m=(l+r)/2;
		
		fam_pos=strchr(A[m]->data->title, ' ')-A[m]->data->title;
   		strcpy(buffer,A[m]->data->title);
    	buffer[fam_pos]='a';
    	fam_pos=strchr(buffer, ' ')-buffer;
    	buffer[0]=A[m]->data->title[fam_pos+1];
    	buffer[1]=A[m]->data->title[fam_pos+2];
    	buffer[2]=A[m]->data->title[fam_pos+3];
    	
		if (strncmp(buffer,title,3)==0) {
			return m;
		}
		if ( strncmp(buffer,title,3)<0) 
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
    		cout<<i<<"  "<<base->data->author<<"  "<<base->data->title<<"  "<<base->data->publisher<<"  "<<base->data->year<<"  "<<base->data->num_of_page<<endl;
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
	    		cout<<i+g<<"  "<<base->data->author<<"  "<<base->data->title<<"  "<<base->data->publisher<<"  "<<base->data->year<<"  "<<base->data->num_of_page<<endl;
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

void DigitalSort (list *&head) {
	int i, j, k, l=10, fam_pos=0;
	char buffer[32];
	int d;
	list *p, *tail;
	queue q[256]; 									//вводим очереди
	for (j=l; j>=0; j--) 							 //сортирую первые 3 буквы (3->2->1)
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
        	
        	fam_pos=strchr(p->data->title, ' ')-p->data->title;
        	strcpy(buffer,p->data->title);
        	buffer[fam_pos]='a';
        	fam_pos=strchr(buffer, ' ')-buffer;
        	
			if(p->data->title[j+fam_pos]==' '){
				d=0;
			}
			else
			{
			d=p->data->title[j+fam_pos]+129;				//считываем индекс для q[i] очереди по букве
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
}


void LRprint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		LRprint(x->left);  
    		cout<<"  "<<x->data->author<<"  "<<x->data->title<<"  "<<x->data->publisher<<"  "<<x->data->year<<"  "<<x->data->num_of_page<<endl;
		LRprint(x->next);
		LRprint(x->right); 
	}
}
void addAVL(list *data, vertex *&point){
	if (point == NULL) {
		point = new vertex;
		point->data = data->data;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		point->next = NULL;
		up = YES;
	}
	else{
		//if(strcmp(point->data->title, data->data->title)==0){
		//if(strcmp(point->data->publisher, data->data->publisher)==0){
		if(point->data->year==data->data->year){
			addAVL(data, point->next);
			up = NO;
		}
		else{
			//if(strcmp(point->data->title, data->data->title)>0){
			//if(strcmp(point->data->publisher, data->data->publisher)>0) {
			if(point->data->year > data->data->year) {
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
			else{ 
				//if(strcmp(point->data->title, data->data->title)<0){
				//if(strcmp(point->data->publisher, data->data->publisher)<0) {
				if(point->data->year < data->data->year) {
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
	}
}


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

	if (reva->bal > 0) {
		point->bal = -1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal < 0) {
		current->bal = 1;
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

