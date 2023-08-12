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

bool VR = true;
bool HR = true;


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
	list* prev;
	list* next;
};


struct Vertex {
	country *data;
	int Bal = 0;
	Vertex *Next;
	Vertex* Left;
	Vertex* Right;
};
Vertex *root = NULL;


struct SN_code {
	float p;
	float q;
	int l;
	char a;
};
SN_code A[M];

int Menu();

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);

void Print(list *Base);
void Print_sort_index_mas(list **mas);

void QuickSort(list* mas[], int left, int right, int sort);
int compare_street(char* a,char* b); 
int compare_name(char* a, char* b);

int BSearch (list **A, char* depositor);


void LR_print(Vertex* p, int& count);
void addDBD(list* binList, Vertex*& p);
void TreeSearch (Vertex* p, char* data);

int size(Vertex*);
int height(Vertex*);
int max(int, int);
int sdp(Vertex*, int);

void Decode();
void shanon();
void CodePrint();
void Encode();


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

void addDBD(list* binList, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->data = binList->data;
		p->Bal = 0;
		p->Next = NULL;
		p->Left = NULL;
		p->Right = NULL;
		VR = true;
	}
	else if (compare_street(p->data->street, binList->data->street) == 0) {
		addDBD(binList, p->Next);
	}
	else if (compare_street(p->data->street, binList->data->street) > 0) {
		addDBD(binList, p->Left);
		if (VR) {
			if (p->Bal == 0) {
				Vertex* q = p->Left;
				p->Left = q->Right;
				q->Right = p;
				p = q;
				q->Bal = 1;
				VR = 0;
				HR = 1;
			}
			else {
				p->Bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else HR = 0;
	}
	else if (compare_street(p->data->street, binList->data->street) < 0) {
		addDBD(binList, p->Right);
		if (VR) {
			p->Bal = 1;
			HR = 1;
			VR = 0;
		}
		else if (HR) {
			if (p->Bal == 1) {
				Vertex* q = p->Right;
				p->Bal = 0;
				q->Bal = 0;
				p->Right = q->Left;
				q->Left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else HR = 0;
		}
	}
}

void TreeSearch (Vertex* p, char* data){
	if(p!=NULL)                 ///ѕоиск улицы
    {
        if(compare_street(p->data->street,data) > 0){
    	    TreeSearch(p->Left,data);
    	}else{
    		if(compare_street(p->data->street,data) < 0){
            	TreeSearch(p->Right,data);
	        }else{
				cout << "Street has been founded: "<< p->data->FIO << "\t" << p->data->street << "\t" <<  p->data->number_home
					<< "\t"<< p->data->number_appart << "\t" << p->data->Date << endl;
	            TreeSearch(p->Next,data);
			}
        }
    }
}

int Menu()
{
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	int search_start=0;
	int search=N-1;
	
	fp = fopen("testBase4.dat", "rb");
	list* OriginBase = new list;
	list* IndexBase = new list;
	Read_base(fp,OriginBase);
	fclose(fp);
	copy_base(OriginBase, IndexBase);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=IndexBase;
		IndexBase=IndexBase->next;
	}
	for(int i=0;i<2;i++)
		QuickSort(mas, 0, N - 1, i);
	
	Decode();
	Encode();
	while(true){
		system("cls");
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
				//ищем первые 3 буквы фамилии и строим по найденным данным дерево
				cout <<endl;
				cout << "Chto budem iskat(citizen's sirname')"<<endl;
				char sirname[3];
				SetConsoleCP(866);
				cin >> sirname;
				if(strcmp(sirname,"0")!=0){
					search = BSearch(mas,sirname);
					int fam_pos=0;
					char buffer[32];
					if(search == -1){
						cout << "Citizen doesn't exists''" << endl;
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
					    	if(strncmp(mas[search]->data->FIO,sirname,3)!=0){
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
							if(strncmp(mas[search]->data->FIO,sirname,3)!=0){
					    		break;
							}
						}
						while(1);
						cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " "<< search-1<<")"<<endl;
						for(int i=search_start;i<search;i++){
							cout << "Citizen has been founded: "<<i<<" "<< mas[i]->data->FIO << "\t" << mas[i]->data->street << "\t" << mas[i]->data->number_home
							<< "\t"<< mas[i]->data->number_appart << "\t" << mas[i]->data->Date << endl;
							addDBD(mas[i], root);
						}
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
				printf("+------+----------+----------------+----------+\n");
				printf("|%6d| UniqSize |  Height  |   Mid. height  |\n", N);
				printf("+------+----------+----------------+----------+\n");
				printf("|  DBD |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
				cout<<endl<< "Street find: "<< endl;
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
	}
	return 0;
}

int main()
{
	Menu();
	return 0;
}

void Encode() {
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
	printf("\n\n од Ўенона: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Ќомер —имвола | —имвол | ¬еро€тность |      одовое слово    | ƒлина кодового|\n");
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
	printf("________________________________________________\n");
	SetConsoleCP(866);
	printf("|  Ёнтропи€  |  —редн€€ длина  |   оэф сжати€  |\n");
	printf("|____________|_________________|_______________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression/cfcompression);
	printf("|____________|_________________|_______________|\n");
	
	cout << endl << endl << entropy+1 <<" > "<< lgm <<endl <<endl;
}

void Decode(){
	
	int i,j;
	FILE *fp;	
	fp=fopen("testBase4.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].q = 0;
		A[i].a = (char)(i-128); 
	}
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
				SN_code B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	
	for (i = 0; i < M && A[i].p != 0; i++){
		A[i].p /=sum;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
	}
	shanon();
}

void shanon()
{
	for (int i = 0; i < 166; i++)
	{
		A[i].q = A[i - 1].q + A[i].p;
		A[i].l = ceil(-log(A[i].p) / log(2));
	}
	for (int i = 1; i < M; i++)
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


int compare_street(char* a,char* b) {
	char bufferA[18];
	char bufferB[18];
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	//находим позицию первого пробела, чтоб пон€ть какое слово короче
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
	//если слова не совпали то в сортируем в нормальном пор€дке
	if(strncmp(a, b,count) > 0){
		return 1;
	}
	return -1;
}

int compare_name(char* a, char* b) {
	char bufferA[32];
	char bufferB[32];
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	//находим позицию первого пробела
	int space_pos_a = strchr(a,' ') - a;
	int space_pos_b = strchr(b,' ') - b;
	
	//минимальное количество символов в фамилии 3
	int count =4;
	//если сравниваемые фамилии разных размеров выбираем меньший размер дл€ сравнений
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
	//если сравниваемые имена разных размеров выбираем меньший размер дл€ сравнений
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
	//если сравниваемые отчества разных размеров выбираем меньший размер дл€ сравнений
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
	return -1;
}

void QuickSort(list* mas[], int left, int right, int sort)
{
	int i, j;
	list* x;
	list* temp;

	i = left; j = right;
	x = mas[(left + right) / 2];

	do {
		if(sort==0){
			while ((compare_street(mas[i]->data->street, x->data->street) < 0) && (i < right))
				i++;
			while ((compare_street(mas[j]->data->street, x->data->street) >= 0) && (j > left))
				j--;
		}else{
			while ((compare_name(mas[i]->data->FIO, x->data->FIO) < 0) && (i < right))
				i++;
			while ((compare_name(mas[j]->data->FIO, x->data->FIO) > 0) && (j > left))
				j--;
		}
		
		if (i <= j) {
			temp = mas[i];
			mas[i] = mas[j];
			mas[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (left < j)
		QuickSort(mas, left, j, sort);
	if (i < right)
		QuickSort(mas, i, right, sort);
}

int BSearch (list **A, char *FIO) {
	int l = 0, r = N, m = 0, fam_pos=0;
	char buffer[32];
	while (l <= r) {
		m=(l+r)/2;
		
		strncpy(buffer, A[m]->data->FIO,3);
		if (strncmp(buffer,FIO,3)==0) {
			return m;
		}
		if (strncmp(buffer,FIO,3) <0) 
			l = m+1;
		else r = m-1;
	}
	return -1;
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
				cout << i + 1 << "\t" << Base->data->FIO << "\t" << Base->data->street << "\t" << Base->data->number_home
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
				cout << i + 1 << "\t" << mas[i+g]->data->FIO << "\t" << mas[i+g]->data->street << "\t" << mas[i+g]->data->number_home
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


