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

void Print_base(record *base);
int compare(record *a, record *b);
int BSearch (record **A, unsigned short int depositor);

void qs(record* mas[], int left, int right);
void Print_sort_index_mas(record **mas);

int compare_date(record *a, record *b);
void addDBD(record* data, vertex*& p); 
void LRprint(vertex*);
int compare_tree_date(record *a, char *b);
void TreeSearch (vertex* p, char *data);

int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);

void shanon();
void BaseCoding();
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
    qs(mas,0,N-1);
	BaseCoding();
	
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
		cout << "\t2. Просмотр отсортированной базы данных (Quick sort)" << endl;
		cout << "\t3. Поиск в отсортированной базе по ключу (Вклад)" << endl;
		cout << "\t4. Поиск в дереве (дате вклада)" << endl;
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
			cout << "Какой вклад ищем?"<<endl;
			unsigned short int deposit;
			cin >> deposit;
			if(deposit!=0){
				search = BSearch(mas,deposit);
				int fam_pos=0;
				char buffer[32];
				if(search == -1){
					cout << "Такого вклада не существует" << endl;
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
				    	if(mas[search]->deposit != deposit){
				    		search++;
				    		break;
						}
					}
					while(1);
				    
					search_start=search;
					
					do{
						search++;
						if(search==N){
							search--;
							break;
						}
						if(mas[search]->deposit != deposit){
				    		break;
						}
					}
					while(1);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout << i <<" "<<mas[i]->depositor<<"  "<<mas[i]->deposit<<"  "<<mas[i]->date<<"  "<<mas[i]->lawyer<<endl;
						addDBD(mas[i], root);
					}
				}
			}
			break;
		case 52:
			cout << endl << "LR-print - date"<<endl;
			LRprint(root);
			cout<<endl;
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|%6d|   Size   |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------------+----------+----------------+\n");
			printf("|  AVL |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
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

void CodePrint(){
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nКод Шенона: \n");
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
	printf("________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |\n");
	printf("|____________|_________________|\n");
	printf("| %10f |   %10.5f    |\n", entropy, lgm);
	printf("|____________|_________________|\n");
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

void LRprint(vertex* x){
	SetConsoleCP(1251);
	if (x) {
		LRprint(x->left);  
    		cout << "  " << x->data->depositor << "  " << x->data->deposit << "  " << x->data->date << "  " << x->data->lawyer << endl;
		LRprint(x->next);
		LRprint(x->right); 
	}
}


void addDBD(record* data, vertex*& p) {
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
		addDBD(data, p->next);
	}
	else if (compare_date(p->data, data) > 0) {
		addDBD(data, p->left);
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
		addDBD(data, p->right);
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

int compare_tree_date(record *a, char *b) {
	if(strncmp(&a->date[6], b,2) != 0){
		return strcmp(&a->date[6], b);
	}
	return 0;
}

void TreeSearch (vertex* p, char *data){
	if(p!=NULL)           
    {
        if (compare_tree_date(p->data, data) == 0) {
			cout << p->data->depositor << "\t" << p->data->deposit << "\t" <<  p->data->date << "\t"<< p->data->lawyer << endl;
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
int compare_date(record *a, record *b) {
	if(strcmp(&a->date[6], &b->date[6]) != 0){
		return strcmp(&a->date[6], &b->date[6]);
	}
	return 0;
}

int compare(record *a, record *b) 
{ 
	if (a->deposit > b->deposit) {
		return 1;
	}
	else if(a->deposit < b->deposit){
		return -1;
	}
	else if(strcmp(&a->date[6], &b->date[6]) != 0){
		return strcmp(&a->date[6], &b->date[6]);
	}
	else if (a->date[3] - b->date[3] != 0) {
		return a->date[3] - b->date[3];
	}
	else if (a->date[4] - b->date[4] != 0) {
		return a->date[4] - b->date[4];
	}
	else if (a->date[0] - b->date[0] != 0) {
		return a->date[0] - b->date[0];
	}
	else if (a->date[1] - b->date[1] != 0) {
		return a->date[1] - b->date[1];
	}
	return 0;
}

void qs(record* mas[], int left, int right)
{

  register int i, j;
  record *x;
  record *temp;

  i = left; j = right;
  x = mas[(left+right)/2];

  do {
    while((compare(mas[i],x) < 0) && (i < right)) i++;
    while((compare(mas[j],x) > 0) && (j > left)) j--;
    if(i <= j) {
      temp = mas[i];
      mas[i] = mas[j];
      mas[j] = temp;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs(mas, left, j);
  if(i < right) qs(mas, i, right);
}

int BSearch (record **A, unsigned short int deposit) {
	int l = 0, r = N, m = 0;
	while (l <= r) {
		m=(l+r)/2;
		
		if (A[m]->deposit==deposit) {
			return m;
		}
		if (A[m]->deposit<deposit) 
			l = m+1;
		else r = m-1;
	}
	return -1;
}

void Print_base(record base[]){
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

