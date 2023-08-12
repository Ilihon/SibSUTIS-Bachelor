
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

struct vertex
{
	record *data;
	vertex *next;
	int bal;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;
bool up = false;

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

int compare_deposit(int a, int b);
int compare_name(char a[], char b[]);
int compare_date(char a[], char b[]);
int BSearch (list **A, int Number);

void HeapBuild (list **A, int l, int r);
void HeapBuild2 (list **A, int l, int r, int offset);
void HeapSort (int n, list **A);
void Print_sort_index_mas(list **mas);

void LRprint(vertex*);
void AVLSearch(vertex* p, char* data);
void AVLNext(vertex* p);
void addAVL(list *mas, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);

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
	
	f=fopen("testBase2.dat", "rb");
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
		int dep_num = 0;
		
		SetConsoleCP(866);
		cout << "\t------------------------------МЕНЮ------------------------" << endl;
		cout << "\t1. Посмотреть базу данных" << endl;
		cout << "\t2. Просмотр отсортированной базы данных (Heap sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (Номер отдела)" << endl;
		cout << "\t4. Поиск в дереве (Дата рождения)" << endl;
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
				cout << "Введите номер отдела для поиска"<<endl;
			
				cin >> dep_num;
				if(dep_num>=0){
					search = BSearch(mas, dep_num);
					if(search == -1){
						cout << "Сотрудника из такого отдела не существует" << endl;
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
					    	if(mas[search]->data->Department != dep_num){
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
							if(mas[search]->data->Department != dep_num){
					    		break;
							}
						}
						while(true);
						SetConsoleCP(866);
						cout <<endl <<endl<<"Найдено "<<search-search_start <<" сотрудников ("<< search_start<< " "<< search-1<<")"<<endl;
						SetConsoleCP(1251);
						for(int i=search_start;i<search;i++){
							cout << i <<" "<<mas[i]->data->Date <<"\t"<<mas[i]->data->FIO <<"\t"<<mas[i]->data->Department <<"\t"<<mas[i]->data->Position <<endl;
							addAVL(mas[i], root);
						}
					}
				}
				break;
			case 52:
				cout << endl << "LR-print - department"<<endl;
				LRprint(root);
				cout<<endl;
				printf("+------+----------+----------------+----------+----------------+\n");
				printf("|%6d|   Size   |  Height  |   Mid. height  |\n", N);
				printf("+------+----------+----------------+----------+----------------+\n");
				printf("|  AVL |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
				cout<<endl<< "Element find: "<< endl;
				
				char temp_date[255];
				cin >> temp_date;
				char date[10];
				strncpy(date, temp_date, 10);
				
				AVLSearch(root, date);
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
	printf("\n\nОптимальный код Хаффмана: \n");
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
    f = fopen("testBase2.dat", "rb");
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
	f=fopen("testBase2.dat", "rb");
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

int Up(int n, float q){
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

void Down(int n, int j){
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

void Huffman(int n){
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
    		cout << "  " << x->data->Date << "\t" << x->data->FIO << "\t" << x->data->Department << "\t" << x->data->Position << endl;
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
		up = true;
	}
	else{
		if(compare_date(point->data->Date, data->data->Date) == 0){
			addAVL(data, point->next);
			up = false;
		}
		else{
			if(compare_date(point->data->Date, data->data->Date) > 0) {
				addAVL(data, point->left);
				if (up == true) {
					if (point->bal > 0) {
						point->bal = 0;
						up = false;
					}
					else
						if (point->bal == 0) {
							point->bal = -1;
						}
						else
							if (point->left->bal < 0) {
								ll(point);
								up = false;
							}
							else {
								lr(point);
								up = false;
							}
				}
			}
			else{
				if(compare_date(point->data->Date, data->data->Date) < 0) {
					addAVL(data, point->right);
					if (up == true) {
						if (point->bal < 0) {
							point->bal = 0;
							up = false;
						}
						else {
							if (point->bal == 0) {
								point->bal = 1;
							}
							else {
								if (point->right->bal > 0) {
									rr(point);
									up = false;
								}
								else {
									rl(point);
									up = false;
								}
							}
						}
					}
				}
			}
		}
	}
}

void ll(vertex* &point){
	vertex *current = point->left;
	point->bal = 0;
	current->bal = 0;
	point->left = current->right;
	current->right = point;
	point = current;
}

void rr(vertex* &point){
	vertex *current = point->right;
	point->bal = 0;
	current->bal = 0;
	point->right = current->left;
	current->left = point;
	point = current;
}

void lr(vertex* &point){
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

void rl(vertex* &point) {
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

void AVLSearch (vertex* p, char* data) {
	if(p!=NULL)
    {
        if(compare_date(p->data->Date, data) == 0){
            AVLNext(p);
        }else{
            if(compare_date(p->data->Date, data) > 0){
                AVLSearch(p->left, data);
            }else{
				AVLSearch(p->right, data);
			}
        }
    }
}

void AVLNext (vertex* p) {
	if(p!=NULL)
    {
		cout << "  " << p->data->Date << "\t" << p->data->FIO << "\t" << p->data->Department << "\t" << p->data->Position << endl;
        AVLNext(p->next);
	}
}

int compare_department(int a, int b) {
	if(a>=b){
		return 1;
	}
	else{
		return -1;
	}
}

int compare_name(char* a, char* b) {
	
	if (strcmp(a,b) == 0)
		return 0;
		
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
	return 0;
}

int compare_date(char a1[], char b1[]) {	
	char a[30];
	char b[30];
	strcpy(a, a1);
	strcpy(b, b1);
	
	if (strcmp(a, b) == 0) {
		return strcmp(a, b);
	}
	else if (a[6] - b[6] != 0) {
		return a[6] - b[6];
	}
	else if (a[7] - b[7] != 0) {
		return a[7] - b[7];
	}
	else if (a[3] - b[3] != 0) {
		return a[3] - b[3];
	}
	else if (a[4] - b[4] != 0) {
		return a[4] - b[4];
	}
	else if (a[0] - b[0] != 0) {
		return a[0] - b[0];
	}
	else if (a[1] - b[1] != 0) {
		return a[1] - b[1];
	}
	return 0; 
}

void HeapBuild (list **A, int l, int r) {
	int i=l, j;
	list *x=A[l];
	
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		int result = 0;
		if(j<r){
			result = compare_department(A[j+1]->data->Department, A[j]->data->Department);
			if(result > -1){
				j++;
			}
		}
		
		result = compare_department(x->data->Department, A[j]->data->Department);
		if(result > -1){
			break;
		}
		
		A[i]=A[j];
		i=j;
	}
	A[i]=x;
}

void HeapBuild2 (list **A, int l, int r, int offset) {
	int i = l, j = 2 * i;
	list *x=A[offset+l];
	
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		int result = 0;
		if(j<r){
			result = compare_name(A[offset+j+1]->data->FIO, A[offset+j]->data->FIO);
			if(result > -1){
				j++;
			}
		}
		
		result = compare_name(x->data->FIO, A[offset+j]->data->FIO);		
		if(result > -1){
			break;
		}
		A[offset+i] = A[offset+j];
		i = j;
	}
	A[offset+i]=x;
}

void HeapSort (int n, list **A) {

	// сортировка по первичному ключу - номер отдела
	int l=n/2, r=n;
	while (l+1>0) {
		HeapBuild (A, l, r);
		l--;
	}
	while (r>1) {
		list* t=A[0];
		A[0]=A[r-1];
		A[r-1]=t;
		r--;
		HeapBuild (A, 0, r-1);
	}
	
	// сортировка по вторичному ключу - ФИО
	// сорирует отдельно все ФИО для каждого из отделов
	int offset = 0;
	int counter_max = 0;
	while (offset + counter_max < n-1){
		if(A[offset+counter_max]->data->Department != A[offset+counter_max+1]->data->Department){
			l = counter_max / 2;
			r = counter_max+1;
			
			while (l + 1 > 0) {
				HeapBuild2 (A, l, r, offset);
				l--;
			}
			while (r > 1) {
				list* t = A[offset];
				A[offset]=A[offset+r-1];
				A[offset+r-1]=t;
				r--;
				HeapBuild2 (A, 0, r-1, offset);
			}
			offset = offset + counter_max + 1;
			counter_max = 0;		
		}
		else{
			counter_max += 1;
		}
	}
	
	// досортировка по ФИО для строк с максимальным номером отдела
	l = counter_max / 2;
	r = counter_max + 1;
	while (l + 1 > 0) {
		HeapBuild2 (A, l, r, offset);
		l--;
	}
	while (r > 1) {
		list* t = A[offset];
		A[offset]=A[offset+r-1];
		A[offset+r-1]=t;
		r--;
		HeapBuild2 (A, 0, r-1, offset);
	}
}

int BSearch (list **A, int Number) {
	int l = 0, r = N, m = 0;
	while (l < r) {
		m=(l+r)/2;
		if (A[m]->data->Department == Number) {
			return m;
		}
		if (A[m]->data->Department < Number) 
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
    		cout<<i<<"\t"<<base->data->Date<<"\t"<<base->data->FIO<<"\t"<<base->data->Department<<"\t"<<base->data->Position <<endl;
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
	    		cout<<i+g<<"\t"<<base->data->Date<<"\t"<<base->data->FIO<<"\t"<<base->data->Department<<"\t"<<base->data->Position <<endl;
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
    		cout<<i<<"\t"<<mas[i]->data->Date<<"\t"<<mas[i]->data->FIO<<"\t"<<mas[i]->data->Department<<"\t"<<mas[i]->data->Position <<endl;
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
	    		cout<<i+g<<"\t"<<mas[i+g]->data->Date<<"\t"<<mas[i+g]->data->FIO<<"\t"<<mas[i+g]->data->Department<<"\t"<<mas[i+g]->data->Position <<endl;
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

