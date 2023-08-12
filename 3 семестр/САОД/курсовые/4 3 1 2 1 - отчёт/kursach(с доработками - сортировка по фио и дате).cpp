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
#include <conio.h>
#include <ctime>

using namespace std;

const int N = 4000;
const int M=256;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int k=0;
bool VR = true;
bool HR = true;

struct Base {
	char fio[32];
	char street[18];
	short int number_home;
	short int number_door;
	char date[10];
};
Base* Info;
Base* Index = new Base[N];


struct vertex {
	Base* data;
	int bal;
	vertex* left;
	vertex* next;
	vertex* right;
};
vertex* root = NULL;


struct HF_code {
	float p;
	float q;
	int l;
	char a;
};

HF_code A[M];

void readBase(Base*& info);
void Massiv(Base* index, Base* info);
void print_list(Base* Index);

int Compare(Base a, Base b);
void HeapSort(Base*& Com);
int BSearch(Base** A, char dte[2]);

void addDBD(Base* data, vertex*& point);
void LRprint(vertex* x);
int Size(vertex*);
int Height(vertex*);
int Max(int, int);
float Sum_Paths(vertex* p, float);
void Tree_Search (vertex* point, char* data);

int Up(int N, float q);
void Down(int N, int j);
void Huffman(int N);
void Coding();
void CodePrint();

void menu();

void menu()
{
	readBase(Info);
	Massiv(Index, Info);
	HeapSort(Index);
	while(true){
		int v;
		system("cls");
		cout << "1.Without" << endl;
		cout << "2.Sorting" << endl;
		cout << "3.Search" << endl;
		cout << "4.Code" << endl;
		cout << "5.Exit" << endl;
		cin >> v;
		if (v == 1 || v == 2 || v == 3 || v==4 || v==5) {
			if (v == 1) {
				print_list(Info);
				system("PAUSE");
			}
			if (v == 2) {
				print_list(Index);
				system("PAUSE");
			}
			if (v == 3) {
				system("cls");
				Base* mas[N];
				for (int i = 0; i < N; i++) {
					mas[i] = &Index[i];
				}
				cout << "Search date (year)" << endl;
				char dte[2];
				cin >> dte;
	
				int search = BSearch(mas, dte);
				cout << endl;
				int search_start = 0;
	
				if (search == -1) {
					SetConsoleCP(866);
					cout << "Такого года нет " << endl;
					system("PAUSE");
				}
				else {
					SetConsoleCP(1251);
					do {
						if (search == 0) {
							break;
						}
						else {
							search--;
						}
						if (strncmp(&mas[search]->date[6], dte, 2) != 0) {
							search++;
							break;
						}
					} while (true);
	
					search_start = search;
	
					do {
						cout << "" << search + 1 << " " << mas[search]->fio << "  " << mas[search]->street << "  " << mas[search]->number_home << "  " << mas[search]->number_door << "  " << mas[search]->date << endl;
						search++;
						if (search == N) {
							break;
						}
						if (strncmp(&mas[search]->date[6], dte, 2) != 0) {
							break;
						}
					} while (true);
	
					cout << endl;
					cout << "Create Tree" << endl;
					cout << "1 - Yes;" << endl;
					cout << "2 - No;" << endl;
					int c;
					cin >> c;
					if (c == 1) {
						cout << "\t\t\tBuilding a tree" << endl;
						for (int i = search_start; i < search; i++) {
							//cout << i + 1 << " " << mas[i]->fio << "  " << mas[i]->street << "  " << mas[i]->number_home << "  " << mas[i]->number_door << "  " << mas[i]->date << endl;
							addDBD(mas[i], root);
						}
						cout << endl << "\t\t\tLR-print - street" << endl;
						SetConsoleCP(1251);
						LRprint(root);
						cout << endl;
						cout << "--------------------------------------------" << endl;
						cout << "" << N << " |Size Tree" << "|Height" << "|Mid height|" << endl;
						cout << "--------------------------------------------" << endl;
						cout << "AVL  " << "|" << setw(7) << Size(root) << "  |" << setw(5) << Height(root) << " |"  << setw(8) << Sum_Paths(root, 1) / Size(root) << "  |" << endl;
						cout << "--------------------------------------------" << endl;
						cout << "What street are you looking for?" << endl;
						char fam[32];
						SetConsoleCP(866);
						cin >> fam;
						SetConsoleCP(1251);
						char *spc = " ";
						strcat(fam, spc);
						if(strcmp(fam,"0")!=0){
							Tree_Search(root, fam);
						}
						system("PAUSE");
					}
				}
			}
				
			if(v==4){
				Coding();
				CodePrint();
				system("PAUSE");
			}	
			if(v==5){
				return;				
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	menu();
}


void readBase(Base*& info)
{
	int d;
	FILE* fp;
	fp = fopen("testBase4.dat", "rb");
	info = new struct Base[N];
	d = fread((Base*)info, sizeof(Base), N, fp);
	fclose(fp);
} 

void Massiv(Base* index, Base* info)
{
	for (int i = 0; i < N; i++) {
		index[i] = info[i];
	}
}

void print_list(Base* Index)
{
	int v;
	system("cls");
	SetConsoleCP(1251);
	cout << "1.Conclusion to 20" << endl;
	cout << "2.Scroling" << endl;
	cout << "3.Exit" << endl;
	cin >> v;

	if (v > 3) {
		cout << "Wrong input" << endl;
		system("PAUSE");
		print_list(Index);
	}
	if (v == 1 or v == 2 or v == 3) {
		if (v == 1) {
			int temp = 0;
			int answer;
			system("cls");
			for (int i = 0; i < N; i++) {
				cout << i + 1 << "\t" << Index[i].fio << "\t" << Index[i].street << "\t" << Index[i].number_door << "\t" << Index[i].number_home << "\t" << Index[i].date << endl;
				temp++;
				if (temp % 20 == 0) {
					cout << "Continue? 1=yes, 0=no " << endl;
					cin >> answer;
					if (answer == 1) {
						continue;
					}
					if (answer == 0) {
						cout << "Stop" << endl;
						system("PAUSE");
						break;
					}
					if ((answer != 1) && (answer != 0)) {
						cout << "Input Error" << endl;
						system("PAUSE");
						break;
					}
				}
			}
		}
		if (v == 2) {
			for (int i = 0; i < N; i++) {
				cout << i + 1 << "\t" << Index[i].fio << "\t" << Index[i].street << "\t" << Index[i].number_door << "\t" << Index[i].number_home << "\t" << Index[i].date << endl;
				if (_kbhit()) {
					if (_getch() == 13) {
						cout << "Stop" << endl;
						cout << "To exit press esc" << endl;
						if (_getch() == 27) {
							break;
						}
						while (_getch() != 13) {
							cout << "nope" << endl;
						}
					}
				}
				if (i == 3999) {
					cout << "End of file" << endl;
					system("PAUSE");
				}
			}
		}
	}
}

int Compare(Base a, Base b) 
{ 
	if(strcmp(&a.date[6], &b.date[6]) != 0){
		return strcmp(&a.date[6], &b.date[6]);
	}
	else if (a.date[3] - b.date[3] != 0) {
		return a.date[3] - b.date[3];
	}
	else if (a.date[4] - b.date[4] != 0) {
		return a.date[4] - b.date[4];
	}
	else if (a.date[0] - b.date[0] != 0) {
		return a.date[0] - b.date[0];
	}
	else if (a.date[1] - b.date[1] != 0) {
		return a.date[1] - b.date[1];
	}
	else if (strncmp(a.fio, b.fio,3) != 0) {
		return strncmp(a.fio, b.fio,3);
	}
	return 0;
}

int compare_name(char *A, char *B){
	char bufferA[32];
	char bufferB[32];
	strcpy(bufferA, A);
	strcpy(bufferB, B);
	//находим позицию первого пробела
	int space_pos_a = strchr(A,' ') - A;
	int space_pos_b = strchr(B,' ') - B;
	
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
	return 0;
}

void HeapSort(Base*& Com)
{
	int i, j;
	Base x;
	int L = 4000 / 2;
	while (L > 0) {
		i = L;
		for (;;) {
			x = Com[i - 1];
			j = 2 * i;
			if (j > 4000)
				break;
			if ((j < 4000 - 1) && (Compare(Com[j], Com[j - 1]) >= 0))
				j++;
			if (Compare(x, Com[j - 1]) >= 0)
				break;
			swap(Com[i - 1], Com[j - 1]);
			i = j;
		}
		L--;
	}

	int R = 4000;
	while (R > 0) {
		swap(Com[0], Com[R - 1]);
		R--;
		i = 1;
		for (;;) {
			x = Com[i - 1];
			j = 2 * i;
			if (j > R)
				break;
			if ((j < R) && (Compare(Com[j], Com[j - 1]) >= 0))
				j++;
			if (Compare(x, Com[j - 1]) > 0)
				break;
			swap(Com[i - 1], Com[j - 1]);
			i = j;
		}
	}
}

int BSearch(Base** A, char dte[2])
{
	int l = 0, r = N, m = 0, fam_pos = 0;
	while (l <= r) {
		m = (l + r) / 2;

		if (strncmp(&A[m]->date[6], dte, 2) == 0) {
			cout << A[m]->date;
			return m;
		}
		if (strncmp(&A[m]->date[6], dte, 2) < 0)
			l = m + 1;
		else
			r = m - 1;
	}
	return -1;
}

void addDBD(Base* data, vertex*& point) {
	if (point == NULL) {
		point = new vertex;
		point->data = data;
		point->bal = 0;
		point->next = NULL;
		point->left = NULL;
		point->right = NULL;
		VR = true;
	}
	else if (compare_name(point->data->fio, data->fio) == 0) {
		addDBD(data, point->next);
	}
	else if (compare_name(point->data->fio, data->fio) > 0) {
		addDBD(data, point->left);
		if (VR) {
			if (point->bal == 0) {
				vertex* q = point->left;
				point->left = q->right;
				q->right = point;
				point = q;
				q->bal = 1;
				VR = 0;
				HR = 1;
			}
			else {
				point->bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else HR = 0;
	}
	else if (compare_name(point->data->fio, data->fio) < 0) {
		addDBD(data, point->right);
		if (VR) {
			point->bal = 1;
			HR = 1;
			VR = 0;
		}
		else if (HR) {
			if (point->bal == 1) {
				vertex* q = point->right;
				point->bal = 0;
				q->bal = 0;
				point->right = q->left;
				q->left = point;
				point = q;
				VR = 1;
				HR = 0;
			}
			else HR = 0;
		}
	}
}


void LRprint(vertex* x) {
	if (x) {
		LRprint(x->left);
		cout << "  " << x->data->fio << "  " << x->data->street << "  " << x->data->number_home << "  " << x->data->number_door << "  " << x->data->date << endl;
		LRprint(x->next);
		LRprint(x->right);
	}
}

int Size(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + Size(x->left) + Size(x->right) + Size(x->next);
	}
}

int Max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int Height(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + Max(Height(x->left), Height(x->right));
	}
}

float Sum_Paths(vertex* point, float depth) {
	if (point == NULL)
		return 0;
	else
		return (depth + Sum_Paths(point->left, depth + 1) +
			Sum_Paths(point->right, depth + 1));
}

void Tree_Search (vertex* point, char* data){
	if(point!=NULL)                 ///Поиск улицы
    {
        if(compare_name(point->data->fio,data) > 0){
    	    Tree_Search(point->left,data);
    	}else{
    		if(compare_name(point->data->fio,data) < 0){
            	Tree_Search(point->right,data);
	        }else{
				cout << point->data->fio << "\t" << point->data->street << "\t" <<  point->data->number_home
					<< "\t"<< point->data->number_door << "\t" << point->data->date << endl;
	            Tree_Search(point->next,data);
			}
        }
    }
}


int Up(int N, float q)
{
	int j = 0;
	for (int i = N; i >=1 ; i--)
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

void Down(int N, int j)
{
	int S[M];
	for (int i = 0; i < M; i++)
		S[i] = code[j][i];
	int L = A[j].l;
	for (int i = j; i < N - 1; i++)
	{
		for (int k = 0; k < M; k++)
			code[i][k] = code[i + 1][k];
		A[i].l = A[i + 1].l;
	}
	for (int i = 0; i < M; i++)
	{
		code[N - 1][i] = S[i];
		code[N][i] = S[i];
	}
	code[N - 1][L + 1] = 0;
	code[N][L + 1] = 1;
	A[N - 1].l = A[N].l = L + 1;
}

void Huffman(int N)
{
	if (N == 1)
	{		
		code[0][0] = 0;
		code[1][0] = 1;
		A[0].l = A[1].l = 1;
	}
	else
	{
		float q = A[N - 1].q + A[N].q;
		int j = Up(N, q); // Поиск и вставка суммы 
		Huffman(N - 1);
		Down(N, j); // Достраивание кодов
	}
}

void Coding(){
	
	int i,j;
	FILE *fp;	
	fp=fopen("testBase4.dat", "rb");
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
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		sum++;
	}
	fclose(fp);
	printf("\n");
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
	k=0;
	for (i = 0; i < M; i++){
		A[i].p /= sum;
		A[i].q = A[i].p;
		if(A[i].p!=0){
			k++;
			entropy += A[i].q * abs(log(A[i].q) / log(2));
		}
	}
	Huffman(k-1);
}

void CodePrint(){
	lgm = 0;
	SetConsoleCP(866);
	printf("\n\nКод Хаффмана: \n\n");
	printf("| Sym num| Sym |   Probability  |      Codeword     | Codeword length |\n");
	printf("|---------------------------------------------------------------------|\n");
	SetConsoleCP(1251);
	for (int i = 1; i < k; i++)
	{
		printf("|  %5d |  %c  |  %2.9f   | ",i, A[i].a, A[i].q);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 15; j++)
			printf(" ");
		printf("    |    %7d      |\n", A[i].l);
	}
	printf("|---------------------------------------------------------------------|\n");	
	
	for (int i = 0; i < M; i++)
	{
		lgm += A[i].l * A[i].p;
	}
	SetConsoleCP(866);
	printf("\n________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |\n");
	printf("|____________|_________________|\n");
	printf("| %10f |   %10.5f    |\n", entropy, lgm);
	printf("|____________|_________________|\n");
	
}
