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

const int N = 4000;
const int M = 256;
int sum = 0;
int sym_count = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int *W;

struct record {
	char author[12]; // ФИО автора книги
	char title[32];		// ФИО того, о ком написанна книга
	char publisher[16]; // издательство
	short int year;     // год издания
	short int num_of_page;	// кол-во страниц
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

struct HF_code {
	float p; 
	float q; 
	char a; 
	int l;
};
HF_code A[M];

void Print_base(record *mas);
void Print(record **mas);

int compare(record *AR, record *BR); 
int BSearch (record **A, int year);

void HeapBuild (record **A, int l, int r);
void HeapSort (int n, record **A);


void A2(int L, int R, record **mas);
void add_vertex(vertex *&p, record* mas, int w);
int compare_auth(char *AR, char *BR); 
void LRprint(vertex*);
void A2Search (vertex* p, char *data);

void delete_tree(vertex *&p);
int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);


int Up(int n, float q);
void Down(int n, int j);
void Huffman(int n);
void BaseCoding();
void CodePrint();

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	W = new int[N];
	
	f=fopen("Base1.dat", "rb");
	record *base = new record[N];;
	fread(base, sizeof(record), N, f);
	fclose(f);
	record **mas = new record * [N];;
	for(int i=0;i<N;i++){
		mas[i] = &base[i];
	}
	HeapSort(N, mas);
	BaseCoding();
	
	int enter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		int search_start=0;
		int search=N-1;
		int year;
		char *space = " ";
		
		SetConsoleCP(866);
		cout << "\t------------------------------МЕНЮ------------------------" << endl;
		cout << "\t1. Не отсортированная БД" << endl;
		cout << "\t2. Отсортированная БД (Heap sort)" << endl;
		cout << "\t3. Поиск в отсортированной БД по году" << endl;
		cout << "\t4. Поиск в дереве по фамилии автора" << endl;
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
			Print(mas);
			break;
		case 51:
			cout <<endl;
			SetConsoleCP(866);
			cout << "Введите искомый год"<<endl;
			cin >> year;
			search = BSearch(mas,year);
			if(search == -1){
				cout << "Такого года в БД нет" << endl;
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
			    	if(mas[search]->year != year){
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
					if(mas[search]->year != year){
			    		break;
					}
				}
				while(true);
				
				int* mass_random = new int[N];
				for (int i = 0; i < N; i++) {
					W[i] = rand() % 100;
				}
				sort(W, W + N - 1, greater<int>());
				if (root != NULL) {
					delete_tree(root);
					root = NULL;
				}
				
				SetConsoleCP(866);
				cout <<endl <<endl<<"Найдено "<<search-search_start <<" записей: "<< search_start<< " - "<< search-1 <<endl;
				SetConsoleCP(1251);
				for(int i=search_start;i<search;i++){
    				cout<<i+1<<"  "<<mas[i]->author <<"  "<<mas[i]->title <<"  "<<mas[i]->publisher <<"  "<<mas[i]->year << "  " << mas[i]->num_of_page <<endl;
				}
				A2(search_start, search,mas);
			}
			break;
		case 52:
			cout << endl << "LR-print - deposit"<<endl;
			LRprint(root);
			cout<<endl;
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|%6d|   Size   |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|  A2  |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			SetConsoleCP(866);
			cout<<endl<< "Поиск в дереве: "<< endl;
			char j[12];
			cin.sync();
			cin.getline(j,12);
			SetConsoleCP(1251);
			for(int i = strlen(j); i<11;i++){
				strcat(j, space);
			}
			if(strcmp(j,"0")!=0){
				A2Search(root,j);
			}
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
	printf("_______________________________\n");
	printf("|  Энтропия  |  Средняя длина  |\n");
	printf("|____________|_________________|\n");
	printf("| %10f |   %10.5f    |\n", entropy, lgm);
	printf("|____________|_________________|\n\n\n");
	
	printf(" entropy + 1 >   Lsr\n");
	printf("____________________________\n");
	printf("| %8f   > %8.5f    |\n", entropy+1, lgm);
	printf("|__________________________|\n");
}

void BaseCoding(){
	
	int i,j;
	FILE *f;	
	f=fopen("Base1.dat", "rb");
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


void LRprint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		LRprint(x->left);  
    		cout << "  " << x->data->author << "  " << x->data->title << "  " << x->data->publisher << "  " << x->data->year << "  " << x->data->num_of_page << endl;
		LRprint(x->next);
		LRprint(x->right); 
	}
}

void add_vertex(vertex *&p, record* mas, int w) {
	int check;
	if (p == NULL) {
		p = new vertex;
		p->data = mas;
        p->weight = w;
		p->next = NULL;
		p->left = NULL;
		p->right = NULL;
	}
	else {
		check = compare_auth(p->data->author,mas->author);
		if (check == 0) {
			add_vertex(p->next, mas, w);
		}
		else if (check  > 0) {
			add_vertex(p->left, mas, w);
		}
		else if (check< 0) {
			add_vertex(p->right, mas, w);
		}
	}
}

void A2(int L, int R, record **mas) {
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

void A2Search (vertex* p, char *data){
	int check;
	if(p!=NULL)                 ///Поиск элемента
    {
		check = compare_auth(p->data->author, data);
        if(check > 0){
        //	cout << data << "-l" << endl << p->data->Position << "-l" << endl << endl;
            A2Search(p->left,data);
        }else{
            if(check < 0){
        //		cout << data << "-r" << endl << p->data->Position << "-r" << endl << endl;
              	A2Search(p->right,data);
            }else{
    			cout << "  " << p->data->author << "  " << p->data->title << "  " << p->data->publisher << "  " << p->data->year << "  " << p->data->num_of_page << endl;
				A2Search(p->next,data);
			}
        }
    }
}

void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->next);
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

int compare(record *AR, record *BR) {
	
	if(AR->year > BR->year){
		return 1;
	}
	if(AR->year < BR->year){
		return -1;
	}
	char bufferA[12];
	char bufferB[12];
	strcpy(bufferA, AR->author);
	strcpy(bufferB, BR->author);
	//находим позицию первого пробела
	int space_pos_a = strchr(AR->author,' ') - AR->author;
	int space_pos_b = strchr(BR->author,' ') - BR->author;
	
	int count =4;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	strcpy(bufferA, AR->author);
	strcpy(bufferB, BR->author);
	bufferA[space_pos_a]='-';
	bufferB[space_pos_b]='-';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}

	bufferA[space_pos_a]='-';
	bufferB[space_pos_b]='-';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -=1;
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	return 0;
}

int compare_auth(char *AR, char *BR) {
	
	char bufferA[12];
	char bufferB[12];
	strcpy(bufferA, AR);
	strcpy(bufferB, BR);
	//находим позицию первого пробела
	int space_pos_a = strchr(AR,' ') - AR;
	int space_pos_b = strchr(BR,' ') - BR;
	
	int count =4;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	strcpy(bufferA, AR);
	strcpy(bufferB, BR);
	bufferA[space_pos_a]='-';
	bufferB[space_pos_b]='-';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}

	bufferA[space_pos_a]='-';
	bufferB[space_pos_b]='-';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -=1;
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	return 0;
}

void HeapBuild (record **A, int l, int r) {
	int i=l, j;
	record *x = A[l];
	
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		int result = 0;
		if(j<r){
			result = compare(A[j+1], A[j]);
			if(result > -1){
				j++;
			}
		}
		
		result = 0;
		result = compare(x, A[j]);
		if(result > -1){
			break;
		}
		
		A[i]=A[j];
		i=j;
	}
	A[i]=x;
}

void HeapSort (int n, record *A[N]) {
	int l=n/2, r=n;
	while (l+1>0) {
		HeapBuild (A, l, r);
		l--;
	}
	while (r>1) {
		record* t = A[0];
		A[0]=A[r-1];
		A[r-1]=t;
		r--;
		HeapBuild (A, 0, r-1);
	}
}

int BSearch (record **A, int year) {
	int l = 0, r = 4000, m = 0;
	while (l < r) {
		m = (int)((l + r) / 2);
		if (A[m] -> year == year) {
			return m;
		}
		if (A[m] -> year < year) {
			l = m + 1;
		} else r = m - 1;
	}
	return -1;
}

void Print_base(record *mas){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i<<"  "<<mas[i].author <<"  "<<mas[i].title <<"  "<<mas[i].publisher <<"  "<<mas[i].year << "  " << mas[i].num_of_page <<endl;
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
	    		cout<<i+g<<"  "<<mas[i+g].author <<"  "<<mas[i+g].title <<"  "<<mas[i+g].publisher <<"  "<<mas[i+g].year << "  " << mas[i+g].num_of_page <<endl;
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

void Print(record **mas){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i<<"  "<<mas[i]->author <<"  "<<mas[i]->title <<"  "<<mas[i]->publisher <<"  "<<mas[i]->year << "  " << mas[i]->num_of_page <<endl;
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
	    		cout<<i+g<<"  "<<mas[i+g]->author <<"  "<<mas[i+g]->title <<"  "<<mas[i+g]->publisher <<"  "<<mas[i+g]->year << "  " << mas[i+g]->num_of_page <<endl;
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

