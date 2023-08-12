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

struct record
{
	char depositor[30];
	unsigned short int deposit;
	char date[10];
	char lawyer[22];
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
bool VR = true;
bool HR = true;

struct SN_code {
	float p;
	float q;
	int l;
	char a;
};
SN_code A[M];

void Print_original_base(record *base);
int compare(record *a, record *b);
int BSearch (record **A, char *depositor);

void QuickSort(record* mas[], int left, int right);
void Print_sort_index_mas(record **mas);

void DBD(record* data, vertex*& p); 
void TreePrint(vertex*);
void TreeSearch (vertex* p, int data);

void delete_tree(vertex *&p);
int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);

void shanon();
void Code();
void CodePrint();

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	
	f=fopen("testBase3.dat", "rb");
    record base[N];
    record* mas[N];
    fread(base, sizeof(record), 4000, f);
	fclose(f);
	for(int i=0;i<N;i++){
		mas[i]=&base[i];
	}
    QuickSort(mas,0,N-1);
	Code();
	
	int enter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		int search_start=0;
		int search=N-1;
		int j=0;
		int deposit = 0;
		
		SetConsoleCP(866);
		cout << "  1. Посмотреть базу данных" << endl;
		cout << "  2. Просмотр отсортированной базы данных (Quick sort)" << endl;
		cout << "  3. Поиск в отсортированной базе по ключу (Вкладчик)" << endl;
		cout << "  4. Поиск в дереве по ключу (Вклад)" << endl;
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
				Print_original_base(base);
				break;
			case 50:
				Print_sort_index_mas(mas);
				break;
			case 51:
				cout <<endl;
				SetConsoleCP(866);
				cout << "Введите 3 первых буквы фамилии вкладчика"<<endl;
				char depositor[3];
				cin >> depositor;
				if(depositor!=0){
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
					    	if(strncmp(mas[search]->depositor,depositor,3)!=0){
					    		search++;
					    		break;
							}
						}
						while(1);
					    
						search_start=search;
						
						do{
							search++;
							if(search==N){
								break;
							}
							if(strncmp(mas[search]->depositor,depositor,3)!=0){
					    		break;
							}
						}
						while(1);
						if (root != NULL) {
							delete_tree(root);
							root = NULL;
						}
						cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
						for(int i=search_start;i<search;i++){
							cout << i <<" "<<mas[i]->depositor<<"  "<<mas[i]->deposit<<"  "<<mas[i]->date<<"  "<<mas[i]->lawyer<<endl;
							DBD(mas[i], root);
						}
					}
				}
				break;
			case 52:
				SetConsoleCP(866);
				cout << endl << "АВЛ дерево (Вклад)"<<endl;
				SetConsoleCP(1251);
				TreePrint(root);
				cout<<endl;
				printf("|  AVL | Size | Height | Mid. height |\n");
				printf("|%6d|%3d   |%5d   |%9.2f    |\n", N, size(root),  height(root), (double)sdp(root, 1) / size(root));
				cout<<endl<< "Element find: "<< endl;
				cin >> deposit;
				TreeSearch(root,deposit);
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

void shanon()
{
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

void TreePrint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		TreePrint(x->left);  
    		cout << "  " << x->data->depositor << "  " << x->data->deposit << "  " << x->data->date << "  " << x->data->lawyer << endl;
		TreePrint(x->next);
		TreePrint(x->right); 
	}
}


void DBD(record* data, vertex*& p) {
	if (p == NULL) {
		p = new vertex;
		p->data = data;
		p->bal = 0;
		p->next = NULL;
		p->left = NULL;
		p->right = NULL;
		VR = true;
	}
	else if (p->data->deposit == data->deposit) {
		DBD(data, p->next);
		VR = false;
	}
	else if (p->data->deposit > data->deposit) {
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
	else if (p->data->deposit < data->deposit) {
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

void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->next);
		delete_tree(p->right);
		delete p;
	}
}

void TreeSearch(vertex* p, int data){
	if(p!=NULL)           
    {
        if (data == p->data->deposit) {
			cout << p->data->depositor << "\t" << p->data->deposit << "\t" <<  p->data->date << "\t"<< p->data->lawyer << endl;
			TreeSearch(p->next, data);
		}
		else if (data<p->data->deposit) {
			TreeSearch(p->left, data);
		}
		else if (data>p->data->deposit) {
			TreeSearch(p->right, data);
		}
	}
}

int compare(record *a, record *b) 
{ 
	char bufferA[30];
	char bufferB[30];
	strcpy(bufferA, a->depositor);
	strcpy(bufferB, b->depositor);
	//находим позицию первого пробела
	int space_pos_a = strchr(a->depositor,' ') - a->depositor;
	int space_pos_b = strchr(b->depositor,' ') - b->depositor;
	
	//минимальное количество символов в фамилии 3
	int count =0;
	//если сравниваемые фамилии разных размеров выбираем меньший размер для сравнений
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	
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
	strcpy(bufferA, a->depositor);
	strcpy(bufferB, b->depositor);
	bufferA[space_pos_a]='-';
	bufferB[space_pos_b]='-';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	//если сравниваемые имена разных размеров выбираем меньший размер для сравнений
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	
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
	bufferA[space_pos_a]='-';
	bufferB[space_pos_b]='-';
	int space_pos_a_second = strchr(bufferA,' ') - bufferA;
	int space_pos_b_second = strchr(bufferB,' ') - bufferB;
	
	SetConsoleCP(1251);
	//cout << bufferA << " - " << space_pos_a << " - " << bufferB << " - " << space_pos_b << endl;
	SetConsoleCP(866);
	
	//если сравниваемые отчества разных размеров выбираем меньший размер для сравнений
	if(space_pos_a_second < space_pos_b_second){
		count = space_pos_a_second;
	}
	else{
		count = space_pos_b_second;
	}
	
	//сравниваем отчества
	if(strncmp(&bufferA[space_pos_a], &bufferB[space_pos_b],count) > 0){
		return 1;
	}
	if(strncmp(&bufferA[space_pos_a], &bufferB[space_pos_b],count) < 0){
		return -1;
	}
	if (a->deposit >= b->deposit) {
		return 1;
	}
	else if(a->deposit < b->deposit){
		return -1;
	}
}

void QuickSort(record* mas[], int left, int right)
{

  register int i, j;
  record *x;
  record *temp;

  i = left; j = right;
  x = mas[left];

  while(i <= j){
    while((compare(mas[i],x) < 0) && (i < right)) i++;
    while((compare(mas[j],x) > 0) && (j > left)) j--;
    if(i <= j) {
      temp = mas[i];
      mas[i] = mas[j];
      mas[j] = temp;
      i++; j--;
    }
  } 

  if(left < j) QuickSort(mas, left, j);
  if(i < right) QuickSort(mas, i, right);
}

int BSearch (record **A, char *depositor) {
	int l = 0, r = N, m = 0;
	while (l <= r) {
		m=(l+r)/2;
		
		if (strncmp(A[m]->depositor,depositor,3) == 0) {
			return m;
		}
		if (strncmp(A[m]->depositor,depositor,3) < 0) 
			l = m+1;
		else r = m-1;
	}
	return -1;
}

void Print_original_base(record base[]){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i<<"  "<<base[i].depositor<<"  "<<base[i].deposit<<"  "<<base[i].date<<"  "<<base[i].lawyer <<endl;
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
	    		cout<<i+g<<"  "<<base[i+g].depositor<<"  "<<base[i+g].deposit<<"  "<<base[i+g].date<<"  "<<base[i+g].lawyer <<endl;
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

void Print_sort_index_mas(record *mas[]){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i<<"  "<<mas[i]->depositor<<"  "<<mas[i]->deposit<<"  "<<mas[i]->date<<"  "<<mas[i]->lawyer <<endl;
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
	    		cout<<i+g<<"  "<<mas[i+g]->depositor<<"  "<<mas[i+g]->deposit<<"  "<<mas[i+g]->date<<"  "<<mas[i+g]->lawyer <<endl;
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

