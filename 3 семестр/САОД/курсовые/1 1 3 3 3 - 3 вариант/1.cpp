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
#include <algorithm>

#define n 4000

using namespace std;
const int M=256;
const int N=4000;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;

struct zap {
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};

struct list {
	zap* data;
	list* next;
};

struct tree {
	list* next;
	int balance;
	int weight;
	tree* left, * right;
};

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

		if (compare(arr[midd]->title, key) >= 0)     
			right = midd;							
		else if (compare(arr[midd]->title, key))			
			left = midd + 1;						

		if (left >= right)						
			break;
	}
	return midd;
}

void dop_a1(tree*& root, zap* data, int weight) {
	if (root == NULL) {
		root = new tree;
		root->left = NULL;
		root->right = NULL;
		root->next = new list;
		root->next->data = data;
		root->next->next = NULL;
		root->weight = weight;
		return;
	}
	if (data->year < root->next->data->year) {
		dop_a1(root->left, data, weight);
	}
	else if (data->year > root->next->data->year) {
		dop_a1(root->right, data, weight);
	}
	else if (root != NULL) {
		list* temp = root->next;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new list;
		temp->next->next = NULL;
		temp->next->data = data;
	}
}

list* tree_search(tree* root, int key_year) {
	if (key_year > root->next->data->year) {
		return tree_search(root->right, key_year);
	}
	if (key_year < root->next->data->year) {
		return tree_search(root->left, key_year);
	}

	if (root->next->data->year == key_year) {
		return root->next;
	}
}

void tree_print(tree* root) {
	if (root->left != NULL) {
		tree_print(root->left);
	}
	cout << root->next->data->year << endl;
	if (root->right != NULL) {
		tree_print(root->right);
	}
}

int main() {
	srand(time(NULL));
	int a, b, c = 0;
	cout << "enter 1" <<endl;
	cin >> b;
	if(b==1){
		FILE* fp;
		fp=fopen("testBase1.dat", "rb");
		zap* arr = new zap[n];
		fread(arr, sizeof(zap), n, fp);
		cout << "output of 20 entries/full list? (1/2) : ";
		cin >> b;
		if (b == 1) {
			for (int i = 0; i < n; i += 20) {
				while (c < 20) {
					cout << c + i << "\t" << arr[c + i].author << "\t" << &arr[c + i] << "\t" << arr[c + i].title << "\t\t" << arr[c + i].publisher << "\t" << arr[c + i].year << "\t\t" << arr[c + i].num_of_page << endl;
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
	
	
		zap** index = new zap * [n];
		for (int i = 0; i < n; i++) {
			index[i] = &arr[i];
		}
		
		system("pause");
	
		MergSort(index, 0, n - 1);
	
		cout << index[1]->year << endl;
		cout << endl << endl;
	
		for (int i = 0; i < n; i++) {
			cout << i + 1 << "\t" << index[i]->author << "\t" << index[i] << "\t" << index[i]->title << "\t\t" << index[i]->publisher << "\t" << index[i]->year << "\t\t" << index[i]->num_of_page << endl;
		}
	
		char key[6];
		cout << endl << "Enter key: ";
		cin >> &key[2];
		key[0] = ' ';
		key[1] = ' ';
		cout << endl << endl;
	
		int index_element = Search_Binary(index, 0, n, key);
	
		list* head = new list;
		head->data = index[index_element];
		head->next = NULL;
		index_element++;
		list* p = head;
	
		char* mass_char = index[index_element]->title;
	
		int tmp_queue = 0;
		while (compare(index[index_element]->title, mass_char) == 0) {
			p->next = new list;
			p = p->next;
			p->data = index[index_element];
			p->next = NULL;
			tmp_queue++;
			cout << index[index_element]->author << "\t" << index[index_element]->title << "\t\t" << index[index_element]->publisher << "\t" << index[index_element]->year << "\t\t" << index[index_element]->num_of_page << endl;
			index_element++;
		}
	
		cout << endl << endl;
	
		p = head;
		while (p != NULL) {
			cout << p->data->author << "\t" << p->data->title << "\t\t" << p->data->publisher << "\t" << p->data->year << "\t\t" << p->data->num_of_page << endl;
			p = p->next;
		}
	
		cout << endl << endl;
	
		int* mass_random = new int[tmp_queue];
		for (int i = 0; i < tmp_queue; i++) {
			mass_random[i] = rand() % 100;
		}
	
		sort(mass_random, mass_random + tmp_queue - 1, greater<int>());
	
		p = head;
		int i = 0;
		tree* root;
		root = NULL;
	
		while (p != NULL) {
			dop_a1(root, p->data, mass_random[i]);
			p = p->next;
			i++;
		}
	
		cout << endl << endl;
	
		tree_print(root);
	
		int key_year = 0;
		cout << "Enter key_year" << endl;
		cin >> key_year;
	
		list* p2 = tree_search(root, key_year);
	
		/*p = head;
		while (p != NULL) {
			cout << p->data->author << "\t" << p->data->title << "\t\t" << p->data->publisher << "\t" << p->data->year << "\t\t" << p->data->num_of_page << endl;
			p = p->next;
		}*/
	
		while (p2 != NULL) {
			cout << p2->data->author << "\t" << p2->data->title << "\t\t" << p2->data->publisher << "\t" << p2->data->year << "\t\t" << p2->data->num_of_page << endl;
			p2 = p2->next;
		}
	
		delete[] index;
		delete[] arr;
	}
	
	BaseCoding();
	CodeBase();
	CodePrint();
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
	
	printf("________________________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |  Коэф сжатия  |\n");
	printf("|____________|_________________|_______________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression/cfcompression);
	printf("|____________|_________________|_______________|\n");
	
}

void BaseCoding(){
	
	int i,j;
	FILE *fp;	
	fp=fopen("testBase1.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
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

