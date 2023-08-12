
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

const int N = 4000;
const int M = 256;
int sum = 0;
int sym_count = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;
int *W;

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

struct vertex
{
	record *data;
	vertex *next;
    int w;
    int h;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;
bool up = NO;

struct HF_code {
	float p; 
	float q; 
	char a; 
	int l;
};
HF_code A[M];

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);
void Print_base(list *base);
void Print_sort_index_mas(list **mas);

int compare_deposit(int a, int b);
int compare_name(char a[], char b[]);
int BSearch (list **A, char* depositor);

void HeapBuild (list **A, int l, int r, int sort);
void HeapSort (int n, list **A);

void LRprint(vertex*);
void TRSearch (vertex* p, int data);
void A2(int L, int R, list **mas);
void seth(vertex *p);

int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);


int Up(int n, float q);
void Down(int n, int j);
void Huffman(int n);
void BaseCoding();
void CodePrint();
void CodeBase();

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	W = new int[N];
	
	f=fopen("testBase3.dat", "rb");
	list *base = new list;
	list *base_index =new list;
	Read_base(f,base);
	fclose(f);
	copy_base(base, base_index);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=base_index;
		base_index=base_index->next;
	}
	HeapSort(N, mas);
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
		cout << "\t2. Просмотр отсортированной базы данных (Heap sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (Вкладчик - 3 буквы Фамилии)" << endl;
		cout << "\t4. Поиск в дереве (сумма вклада)" << endl;
		cout << "\t5. Кодирование" << endl;
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
			break;
		case 50:
			Print_sort_index_mas(mas);
			break;
		case 51:
			cout <<endl;
			SetConsoleCP(866);
			cout << "Кого ищем?(вкладчик)"<<endl;
			char depositor[3];
			cin >> depositor;
			if(strcmp(depositor,"0")!=0){
				search = BSearch(mas,depositor);
				int fam_pos=0;
				char buffer[32];
				if(search == -1){
					cout << "Такого вкладчика не существует" << endl;
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
				    	if(strncmp(mas[search]->data->depositor,depositor,3)!=0){
				    		search++;
				    		break;
						}
					}
					while(YES);
				    
					search_start=search;
					
					do{
						search++;
						if(search==N){
							search--;
							break;
						}
						if(strncmp(mas[search]->data->depositor,depositor,3)!=0){
				    		break;
						}
					}
					while(YES);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout << i <<" "<<mas[i]->data->depositor<<"  "<<mas[i]->data->deposit<<"  "<<mas[i]->data->date<<"  "<<mas[i]->data->lawyer<<endl;
				        W[i] = rand() % 99 + 1;
					}
					A2(search_start, search,mas);
                    root->h = 1;
                    seth(root);
				}
			}
			break;
		case 52:
			cout << endl << "LR-print - deposit"<<endl;
			LRprint(root);
			cout<<endl;
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|%6d|   Size   |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|  AVL |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			cout<<endl<< "Element find: "<< endl;
			int deposit;
			cin >> deposit;
			TRSearch(root,deposit);
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

void CodePrint(){
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nОптимальный код Хафмана: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M && A[i].p != 0; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].q);
		for (int j = 0; j < A[i].l+1; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("   |  %7d      |\n", A[i].l+1);
		printf("|-----------------------------------------------------------------------------|\n");
		lgm += A[i].p * A[i].l;
	}	
	SetConsoleCP(866);
	printf("________________________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |  Коэф сжатия  |\n");
	printf("|____________|_________________|_______________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression/cfcompression);
	printf("|____________|_________________|_______________|\n\n\n");
	
	printf(" entropy + 1 >   Lsr\n");
	printf("____________________________\n");
	printf("| %8f   > %8.5f    |\n", entropy+1, lgm);
	printf("|__________________________|\n");
}

void CodeBase() {
	FILE *f, *fcoded;
    f = fopen("testBase3.dat", "rb");
    fcoded = fopen("BaseCoded.dat", "wb");
	char buffer;
	while (!feof(f)) {
		fscanf(f, "%c", &buffer);
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
	fclose(f);
	fclose(fcoded);
}

void BaseCoding(){
	
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
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		sum++;
	}
	printf("\n");
	fclose(f);
	//сортировка по количеству повторений символов
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				HF_code B = A[i-1];
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
	Huffman(sym_count-1);
}

int Up(int n, float q)
{
	int j = 0;
	for (int i = n-2; i >0 ; i--)
	{
		if (A[i - 1].q <= q)
			A[i].q = A[i - 1].q;
		else
		{
			j = i;
			break;
		}
	}
	A[j].q = q;
	return j;
}

void Down(int n, int j)
{
	int S[M];
	for (int i = 0; i < M; i++)
		S[i] = code[j][i];
	int L = A[j].l;
	for (int i = j; i < n - 1; i++)
	{
		for (int k = 0; k < M; k++)
			code[i][k] = code[i + 1][k];
		A[i].l = A[i + 1].l;
	}
	for (int i = 0; i < M; i++)
	{
		code[n - 1][i] = S[i];
		code[n][i] = S[i];
	}
	code[n - 1][L + 1] = 0;
	code[n][L + 1] = 1;
	A[n - 1].l = A[n].l = L + 1;
}

void Huffman(int n)
{
	if (n == 1)
	{		
		code[0][0] = 0;
		code[1][0] = 1;
		A[0].l = A[1].l = 1;
	}
	else
	{
		float q = A[n - 1].q + A[n].q;
		int j = Up(n, q); // Поиск и вставка суммы 
		Huffman(n - 1);
		Down(n, j); // Достраивание кодов
	}
}

void add_vertex(vertex *&p, list* mas, int w) {
	if (p == NULL) {
		p = new vertex;
		p->data = mas->data;
        p->w = w;
		p->next = NULL;
		p->left = NULL;
		p->right = NULL;
	}
	else if (p->data->deposit == mas->data->deposit) {
		add_vertex(p->next, mas, w);
	}
	else if (p->data->deposit > mas->data->deposit) {
		add_vertex(p->left, mas, w);
	}
	else if (p->data->deposit < mas->data->deposit) {
		add_vertex(p->right, mas, w);
	}
}

void seth(vertex *p)
{
	if (p) {
		if (p->next) {
			p->next->h = p->h +1;
		}
		if (p->left) {
			p->left->h = p->h + 1;
		}
		if (p->right) {
			p->right->h = p->h + 1;
		}
		seth(p->left);
		seth(p->right);
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


void LRprint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		LRprint(x->left);  
    		cout << "  " << x->data->depositor << "  " << x->data->deposit << "  " << x->data->date << "  " << x->data->lawyer << endl;
		LRprint(x->next);
		LRprint(x->right); 
	}
}

void TRSearch (vertex* p, int data){
		if(p!=NULL)                 ///Поиск элемента
        {
            if(data<p->data->deposit){
                    TRSearch(p->left,data);
            }else{
                    if(data>p->data->deposit){
                    	TRSearch(p->right,data);
                }else{
    				cout << "  " << p->data->depositor << "  " << p->data->deposit << "  " << p->data->date << "  " << p->data->lawyer << endl;
                	TRSearch(p->next,data);
				}
            }
        }
}

int compare_deposit(int a, int b) {
	if(a>=b){
		return 1;
	}
	else{
		return -1;
	}
}

int compare_name(char* a, char* b) {
	char bufferA[30];
	char bufferB[30];
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	//находим позицию первого пробела
	int space_pos_a = strchr(a,' ') - a;
	int space_pos_b = strchr(b,' ') - b;
	
	//минимальное количество символов в фамилии 3
	int count =4;
	//если сравниваемые фамилии разных размеров выбираем меньший размер для сравнений
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	//сравниваем фамилии
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	//если сравниваемые фамилии разных размеров выбираем меньший
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	//если фамилии одинаковы, то...
	//находим позицию второго пробела
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	bufferA[space_pos_a]='a';
	bufferB[space_pos_b]='a';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	count = 4;
	//если сравниваемые имена разных размеров выбираем меньший размер для сравнений
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	//сравниваем имена
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	//если сравниваемые имена разных размеров выбираем меньший
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	
	//если имена одинаковы, то...
	//находим позицию третьего пробела
	bufferA[space_pos_a]='a';
	bufferB[space_pos_b]='a';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	count = 4;
	//если сравниваемые отчества разных размеров выбираем меньший размер для сравнений
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	//сравниваем отчества
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	//если сравниваемые имена разных размеров выбираем меньший
	if(space_pos_a >= space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
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
				result = compare_deposit(A[j+1]->data->deposit, A[j]->data->deposit);
			}
			else{
				result = compare_name(A[j+1]->data->depositor, A[j]->data->depositor);
			}
			if(result > -1){
				j++;
			}
		}
		
		result = 0;
		if (sort == 0){
				result = compare_deposit(x->data->deposit, A[j]->data->deposit);
		}
		else{
				result = compare_name(x->data->depositor, A[j]->data->depositor);
		}
		if(result > -1){
			break;
		}
		
		A[i]=A[j];
		i=j;
	}
	A[i]=x;
}

void HeapSort (int n, list **A) {
	int l=n/2, r=n;
	while (l+1>0) {
		HeapBuild (A, l, r, 0);
		l--;
	}
	while (r>1) {
		list* t=A[0];
		A[0]=A[r-1];
		A[r-1]=t;
		r--;
		HeapBuild (A, 0, r-1, 0);
	}
	l=n/2, r=n;
	while (l+1>0) {
		HeapBuild (A, l, r, 1);
		l--;
	}
	while (r>1) {
		list* t=A[0];
		A[0]=A[r-1];
		A[r-1]=t;
		r--;
		HeapBuild (A, 0, r-1, 1);
	}
}

int BSearch (list **A, char *depositor) {
	int l = 0, r = N, m = 0, fam_pos=0;
	char buffer[30];
	while (l <= r) {
		m=(l+r)/2;
		
		strncpy(buffer, A[m]->data->depositor,3);
		if (strncmp(buffer,depositor,3)==0) {
			return m;
		}
		if (strncmp(buffer,depositor,3) <0) 
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
		int g=-1;
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

