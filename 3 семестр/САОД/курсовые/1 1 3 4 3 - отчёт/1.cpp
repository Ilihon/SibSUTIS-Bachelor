#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

#define n 4000

using namespace std;
const int M=256;
const int N=4000;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;
int *W;

struct zap {
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};
/*
struct list {
	zap* data;
	list* next;
};
*/
struct tree {
	zap* data;
	int balance;
	int weight;
    int height;
	tree* left, *next, * right;
};
tree *root = NULL;

struct F_code {
	float p;
	int l;
	char a;
};

F_code A[M];


void fano(int L, int R, int k);
int med(int L, int R);
void BaseCoding();
void CodePrint();
void CodeBase();

int compare(char a[], char b[]) {
	int ind1 = 0, ind2 = 0;
	while (a[ind1] != ' ') {
		ind1++;
	}
	while (b[ind2] != ' ') {
		ind2++;
	}
	ind1++;
	ind2++;
	while (a[ind1] != ' ') {
		ind1++;
	}
	while (b[ind2] != ' ') {
		ind2++;
	}
	return strcmp(&a[ind1], &b[ind2]);
}

int compare2(char a[], char b[]) {
	int ind1 = 0, ind2 = 0;
	while (a[ind1] != ' ') {
		ind1++;
	}
	while (b[ind2] != ' ') {
		ind2++;
	}
	ind1++;
	ind2++;
	while (a[ind1] != ' ') {
		ind1++;
	}
	while (b[ind2] != ' ') {
		ind2++;
	}
	return strncmp(&a[ind1], &b[ind2],3);
}

void Merg(zap* index[n], int begin, int end)
{
	int i = begin,
		t = 0,
		mid = begin + (end - begin) / 2,
		j = mid + 1;

	zap* d[n];

	while (i <= mid && j <= end) {

		if (compare(index[i]->title, index[j]->title) <= 0) {
			d[t] = index[i]; i++;
		}
		else {
			d[t] = index[j]; j++;
		}
		t++;
	}

	while (i <= mid) {
		d[t] = index[i]; i++; t++;
	}

	while (j <= end) {
		d[t] = index[j]; j++; t++;
	}

	for (i = 0; i < t; i++)
		index[begin + i] = d[i];
}

void MergSort(zap* index[n], int left, int right)
{
	zap* temp;
	if (left < right)
		if (right - left == 1) {
			if (compare(index[right]->title, index[left]->title) < 0) {
				temp = index[left];
				index[left] = index[right];
				index[right] = temp;
			}
		}
		else {
			MergSort(index, left, left + (right - left) / 2);
			MergSort(index, left + (right - left) / 2 + 1, right);
			Merg(index, left, right);
		}
}

int Search_Binary(zap* arr[], int left, int right, char key[])
{
	int midd = 0;
	while (1)
	{
		midd = (left + right) / 2;

		if (compare2(arr[midd]->title, key) >= 0)     
			right = midd;							
		else if (compare2(arr[midd]->title, key))			
			left = midd + 1;						

		if (left >= right)						
			break;
	}
	return midd;
}

void add_vertex(tree *&p, zap* mas, int w) {
	if (p == NULL) {
		p = new tree;
		p->data = mas;
		p->weight = w;
		p->left = NULL;
		p->right = NULL;
		p->next = NULL;
	}
	else if (p->data->year == mas->year) {
		add_vertex(p->next, mas, w);
	}
	else if (p->data->year > mas->year) {
		add_vertex(p->left, mas, w);
	}
	else if (p->data->year < mas->year) {
		add_vertex(p->right, mas, w);
	}
}

void A2(int L, int R, zap** mas) {
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
		//cout << L << " - " << R << " - "<< i<< endl<< mas[i]->author << " - "<< mas[i]->num_of_page<< " - "<< mas[i]->publisher<< " - "<< mas[i]->title<< " - "<< mas[i]->year<< endl;
		add_vertex(root, mas[i], W[i]);
		A2(L, i - 1,mas);
		A2(i + 1, R,mas);
	}
}

void tree_search(tree* root, int key_year) {
	if(root!=NULL){
		if (root->data->year > key_year) {
			tree_search(root->left, key_year);
		}
		else{
			if (root->data->year < key_year) {
				tree_search(root->right, key_year);
			}
			else{
				if (root->data->year == key_year) {
					cout << root->data->author << "\t" << root->data->title << "\t\t" << root->data->publisher << "\t" << root->data->year << "\t\t" << root->data->num_of_page << endl;
					tree_search(root->next, key_year);
				}
			}
		}
	}
}

void tree_print(tree* root) {
	if(root!=NULL)               
    {
		tree_print(root->left);
		cout << root->data->author << "\t" << root->data->title << "\t\t" << root->data->publisher << "\t" << root->data->year << "\t\t" << root->data->num_of_page << endl;
		tree_print(root->next);
		tree_print(root->right);
	}
}

int main() {
	srand(time(NULL));
	int a, c = 0;
	W = new int[N];
	FILE* fp;
	fp=fopen("testBase1.dat", "rb");
	zap* arr = new zap[n];
	fread(arr, sizeof(zap), n, fp);
	fclose(fp);
	zap** index = new zap * [n];
	for (int i = 0; i < n; i++) {
		index[i] = &arr[i];
	}
	MergSort(index, 0, n - 1);
	
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
			if(v==1){
				int b =0;
				cout << "output of 20 entries/full list? (1/2) : ";
				cin >> b;
				if (b == 1) {
					for (int i = 0; i < n; i += 20) {
						while (c < 20) {
							cout << c + i << "\t" << arr[c + i].author << "\t" << arr[c + i].title << "\t\t" << arr[c + i].publisher << "\t" << arr[c + i].year << "\t\t" << arr[c + i].num_of_page << endl;
							c++;
						} c = 0;
						cout << "continue?(1/2)";
						cin >> a;
						if (a == 2) {
							break;
						}
					}
				}
				else if (b == 2) {
					for (int i = 0; i < n; i++) {
						cout << i + 1 << "\t" << arr[i].author << "\t" << arr[i].title << "\t\t" << arr[i].publisher << "\t" << arr[i].year << "\t\t" << arr[i].num_of_page << endl;
						if (_kbhit()) {
							cout << "continue?(%/0) : ";
							cin >> a;
							if (!a) {
								break;
							}
						}
					}
				}
			}
			if (v==2){
				for (int i = 0; i < n; i++) {
					cout << i + 1 << "\t" << index[i]->author << "\t" << index[i]->title << "\t\t" << index[i]->publisher << "\t" << index[i]->year << "\t\t" << index[i]->num_of_page << endl;
				}
			}
			if (v==3){
				char key[6];
				cout << endl << "Enter key: ";
				cin >> &key[2];
				key[0] = ' ';
				key[1] = ' ';
				cout << endl << endl;
			
				int index_element = Search_Binary(index, 0, n, key);
				char* mass_char = index[index_element]->title;
				if(index_element!=0){
					while (compare2(index[index_element-1]->title, mass_char) == 0) {
						index_element-=1;
						if(index_element==0){
							break;
						}
					}
				}
				int L = index_element;
				int tmp_queue = 0;
				while (compare2(index[index_element]->title, mass_char) == 0) {
					tmp_queue++;
					cout << index[index_element]->author << "\t" << index[index_element]->title << "\t\t" << index[index_element]->publisher << "\t" << index[index_element]->year << "\t\t" << index[index_element]->num_of_page << endl;
					index_element++;
					if(index_element==N){
						index_element--;
						break;
					}
				}
				system("pause");
				system("CLS");
				for (int i = 0; i < tmp_queue; i++) {
					W[i] = rand() % 99 +1;
				}
				int i = 0;
				A2(L,index_element,index);
				cout <<"LRprint: " << endl<< endl;
				tree_print(root);
			
				int key_year = 0;
				cout << "Enter key_year" << endl;
				cin >> key_year;
				tree_search(root,key_year);
			}
			if(v==4){
				BaseCoding();
				CodeBase();
				CodePrint();
			}
			if (v==5){
				return 0;
			}
			
		}
		system("pause");
	}
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
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(866);
	printf("\n\nКод Фано: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].p);
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
	
}

void BaseCoding(){
	
	int i,j;
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].a = (char)(i-128); 
	}
	FILE *fp;	
	fp=fopen("testBase1.dat", "rb");
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
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				F_code B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	
	for (i = 0; i < M; i++){
		A[i].p /=sum;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
	}
	fano(0, M - 1, 0);
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


int med(int L, int R)
{
	float sl = 0, sr;
	for (int i = L; i < R; i++)
		sl += A[i].p;
	sr = A[R].p;
	int m = R;
	while (sl >= sr)
	{
		m--;
		sl -= A[m].p;
		sr += A[m].p;
	}
	return m;
}

