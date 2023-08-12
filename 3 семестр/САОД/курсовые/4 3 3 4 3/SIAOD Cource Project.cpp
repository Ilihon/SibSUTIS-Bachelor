
#define YES true
#define NO false

#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cmath>
#include <iomanip>
using namespace std;

const int N=4000;
const int M=256;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;

int *W;
int *h;


struct country
{
	char FIO[32];
    char street[18];
    short int number_home;
    short int number_appart;
	char Date[10];
	
};

struct list {
	country *data;
	list* next;
	list* prev;
};


struct Vertex {
	country *data;
    int w;
    int h;
	Vertex *Next;
	Vertex* Left;
	Vertex* Right;
};
Vertex *root = NULL;


struct Fano {
	float p;
	float q;
	int l;
	char a;
};
Fano A[M];

int Menu();

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);

void Print(list *Base);
void Print_sort_index_mas(list **mas);

void merge_sort(list*& head);
void merge(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr);
int compare(char* a, char* b);
int compare_street(char* a,char* b); 

int BSearch (list **A, char* depositor);

void A2(int L, int R, list **mas);
void seth(Vertex *p);
void LR_print(Vertex* p, int& count);
void TreeSearch (Vertex* p, char* data);

int size(Vertex*);
int height(Vertex*);
int max(int, int);
int sdp(Vertex*, int);

void BaseCoding();
int med(int L, int R);
void fano(int L, int R, int k);
void CodePrint();
void CodeBase();

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

int Menu()
{
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	int search_start=0;
	int search=N-1;
	W = new int[N];
	
	fp = fopen("testBase4.dat", "rb");
	list* OriginBase = new list;
	list* SortBase = new list;
	Read_base(fp,OriginBase);
	fclose(fp);
	copy_base(OriginBase, SortBase);
	merge_sort(SortBase);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=SortBase;
		SortBase=SortBase->next;
	}
	BaseCoding();
	CodeBase();
	
	int SoD;
	cout << "1.Standard list\n2.Sorted list\n3.BSearch\n4.TreePrint\n5.Coding\n6.Exit" << endl;
	cin >> SoD;
	switch (SoD)
	{
		case 1:
		{
			Print(OriginBase);
			break;
		}
		case 2:
		{
			Print_sort_index_mas(mas);
			break;
		}
		case 3:
		{	
			cout <<endl;
			cout << "Enter date"<<endl;
			char date[2];
			SetConsoleCP(866);
			cin >> date;
			SetConsoleCP(1251);
			if(strcmp(date,"0")!=0){
				search = BSearch(mas,date);
				int fam_pos=0;
				if(search == -1){
					cout << "This date doesn't exists''" << endl;
				}
				else{	
					do{
						if(search==0){
							break;
						}
						else{
							search--;
						}
				    	if(strncmp(&mas[search]->data->Date[6],date,2)!=0){
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
						if(strncmp(&mas[search]->data->Date[6],date,2)!=0){
				    		break;
						}
					}
					while(YES);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " - "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout <<i<<" "<< mas[i]->data->FIO << "\t" << mas[i]->data->street << "\t" << mas[i]->data->number_home
						<< "\t"<< mas[i]->data->number_appart << "\t" << mas[i]->data->Date << endl;
				        W[i] = rand() % 99 + 1;
					}
					A2(search_start, search,mas);
                    root->h = 1;
                    seth(root);
				}
			}
			break;
		}
		case 4:
		{	
			//выводим дерево и инфу про него, затем ищем улицу
			int count =0;
			char street[18];
			LR_print(root, count);
			cout<<endl;
			printf("+------+----------+----------+----------------+\n");
			printf("|%6d| UniqSize |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------+----------------+\n");
			printf("|  A2  |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			printf("+------+----------+----------+----------------+\n");
			cout<<endl<< "Element find: "<< endl;
			SetConsoleCP(866);
			cin >> street;
			SetConsoleCP(1251);
			char *spc = " ";
			strcat(street, spc);
			if(strcmp(street,"0")!=0){
				TreeSearch(root,street);
			}
			break;
		}
		case 5:
		{
			CodePrint();
			break;
		}
		case 6:
		{
			system("PAUSE");
			return 0;
		}
		default:
		{
			cout << "Invalid number entered\nPlease enter numder again" << endl;
			system("PAUSE");
			system("cls");
			break;
		}
	}
	_getch();
	Menu();
	return 0;
}

int main()
{
	Menu();
	return 0;
}

void CodeBase() {
	FILE *fp, *fcoded;
    fp = fopen("testBase4.dat", "rb");
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
	printf("\n\nКод Фано: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M && A[i].l != 0; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].q);
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
	
	cout << endl << endl << entropy+1 <<" > "<< lgm <<endl <<endl;
	SetConsoleCP(1251);
}

void BaseCoding(){
	
	int i,j,v=0;
	entropy=0;
	fcompression=0;
	cfcompression=0;
	sum = 0;
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].q = 0;
		A[i].a = (char)(i-128); 
	}
	FILE *fp;	
	fp=fopen("testBase4.dat", "rb");
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		sum++;
	}
	printf("\n");
	fclose(fp);
	//сортировка по количеству повторений символов
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)  
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
	
	for (i = 0; i < M && A[i].p != 0; i++){
		A[i].p /=sum;
		A[i].q = A[i].p;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
        v++;
	}
	fano(0, v-1, 0);
}

void LR_print(Vertex* p, int& count) {
	if (p != NULL) {
		LR_print(p->Left, count);
		cout << count+1<<") "<< p->data->FIO << "\t" << p->data->street << "\t" <<  p->data->number_home
						<< "\t"<< p->data->number_appart << "\t" << p->data->Date << endl;
		count++;
		LR_print(p->Next, count);
		LR_print(p->Right, count);
	}
}

void add_vertex(Vertex *&p, list* mas, int w) {
	if (p == NULL) {
		p = new Vertex;
		p->data = mas->data;
        p->w = w;
		p->Next = NULL;
		p->Left = NULL;
		p->Right = NULL;
	}
	else if (compare_street(p->data->street, mas->data->street) == 0) {
		add_vertex(p->Next, mas, w);
	}
	else if (compare_street(p->data->street, mas->data->street) > 0) {
		add_vertex(p->Left, mas, w);
	}
	else if (compare_street(p->data->street, mas->data->street) < 0) {
		add_vertex(p->Right, mas, w);
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



void TreeSearch (Vertex* p, char* data){
	if(p!=NULL)                 ///Поиск улицы
    {
        if(compare_street(p->data->street,data) > 0){
    	    TreeSearch(p->Left,data);
    	}else{
    		if(compare_street(p->data->street,data) < 0){
            	TreeSearch(p->Right,data);
	        }else{
				if(compare_street(p->data->street,data) == 0){
					cout << p->data->FIO << "\t" << p->data->street << "\t" <<  p->data->number_home
						<< "\t"<< p->data->number_appart << "\t" << p->data->Date << endl;
	            	TreeSearch(p->Next,data);
	            }
			}
        }
    }
}

void seth(Vertex *p)
{
	if (p) {
		if (p->Next) {
			p->Next->h = p->h +1;
		}
		if (p->Left) {
			p->Left->h = p->h + 1;
		}
		if (p->Right) {
			p->Right->h = p->h + 1;
		}
		seth(p->Left);
		seth(p->Right);
		seth(p->Next);
	}
}

void Read_base(FILE *fp, list *base){
	country *mas = new country();
	fread((country *)mas, sizeof(country), 1, fp);
	base->data=mas;
	base->prev=NULL;
	base->next=NULL;
	
	for (int i = 1; i < N; i++) {
        mas = new country();
        list *base_prev;
        fread((country*)mas, sizeof(country), 1, fp);
        base_prev = base;
        base = base->next = new list();
        base->data = mas;
        base->prev = base_prev;
        base->next = NULL;
    }
}

int compare(country *a, country *b) {
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
	return 0;
}

int compare_street(char* a,char* b) {
	char bufferA[18];
	char bufferB[18];
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	//находим позицию первого пробела, чтоб понять какое слово короче
	int space_pos_a = strchr(a,' ') - a;
	int space_pos_b = strchr(b,' ') - b;
	//выбираем длину кратчайшего слова
	int count;
	if(space_pos_a <= space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	//если слова совпали то первее стоит то, что короче
	if(strncmp(a, b,count) == 0){
		if(space_pos_a == space_pos_b){
			return 0;
		}
		if(space_pos_a < space_pos_b){
			return 1;
		}
		return -1;
	}
	//если слова не совпали то в сортируем в нормальном порядке
	if(strncmp(a, b,count) > 0){
		return 1;
	}
	return -1;
}

int BSearch (list **A, char *Date) {
	int l = 0, r = N, m = 0, fam_pos=0;
	char buffer[10];
	while (l < r) {
		m=(l+r)/2;
		strcpy(buffer, A[m]->data->Date);
		//cout << &buffer[6] << endl;
		if (strncmp(&buffer[6],Date,2)==0) {
			return m;
		}
		if (strncmp(&buffer[6],Date,2) <0) 
			l = m+1;
		else r = m-1;
	}
	return -1;
}

//сливает очереди h1-t1 и h2-t2 в очередь hr-tr
void merge(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr) {
	if (compare(h1->data, h2->data) < 0) {
		hr = h1;
		h1 = h1->next;
	}
	else {
		hr = h2;
		h2 = h2->next;
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2) {
		if (compare(h1->data, h2->data) < 0) {
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
				if (t2->next == NULL) {
					break;
				}
				t2 = t2->next;
			}
			tp = t2->next;
			t1->next = NULL;
			t2->next = NULL;
			merge(h1, t1, h2, t2, hr, tr);
			hp->next = hr;
			head = hr;
			tr->next = tp;
			hp = tr;
		}
		k *= 2;
	}
}

void Print(list *Base)
{
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
			cout << i + 1 << "\t" << Base->data->FIO << "\t" << Base->data->street << "\t" << Base->data->number_home
			<< "\t"<< Base->data->number_appart << "\t" << Base->data->Date << endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
			Base = Base->next;
		}
	}
    if(n=='2'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
				cout << i + g << "\t" << Base->data->FIO << "\t" << Base->data->street << "\t" << Base->data->number_home
				<< "\t"<< Base->data->number_appart << "\t" << Base->data->Date << endl;
				Base = Base->next;
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
			cout << i + 1 << "\t" << mas[i]->data->FIO << "\t" << mas[i]->data->street << "\t" << mas[i]->data->number_home
			<< "\t"<< mas[i]->data->number_appart << "\t" << mas[i]->data->Date << endl;
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
				cout << i + g << "\t" << mas[i+g]->data->FIO << "\t" << mas[i+g]->data->street << "\t" << mas[i+g]->data->number_home
				<< "\t"<< mas[i+g]->data->number_appart << "\t" << mas[i+g]->data->Date << endl;
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

int size(Vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->Left) + size(x->Right);
	}
}

int max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int height(Vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->Left), height(x->Right));
	}
}

int sdp(Vertex *x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->Left, l + 1) + sdp(x->Right, l + 1);
	}
}


