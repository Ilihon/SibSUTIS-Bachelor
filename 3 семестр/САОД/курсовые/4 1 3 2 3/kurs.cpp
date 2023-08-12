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
int Vr, Hr;
bool Rost = false;
const int M = 256;
int sum = 0;
int v = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;


struct settlement { // Населенный пункт
	char FIO[32]; // ФИО
	char street_name[18]; // Название улицы
	short int house_number; // Номер Дома
	short int flat_number; // Номер Квартиры
	char date[10]; // Дата заселения
};

struct vertex {
	settlement* data;
	int bal;
	vertex* left;
	vertex* next;
	vertex* right;
};
vertex* root = NULL;

struct F_code {
	float p;
	int l;
	char a;
};

F_code A[M];

void fano(int L, int R, int k);
int med(int L, int R);

int compare(char* a_, char* b_) {
	int result = strcmp(a_, b_);
	return result;
}

void Merg(settlement* index[n], int begin, int end, int sort_ord) {
	int i = begin, t = 0, mid = begin + (end - begin) / 2, j = mid + 1;
	settlement* d[n];
	while(i <= mid && j <= end) {
		int comp_res = 0;
		if(sort_ord == 0){
			comp_res = compare(index[i]->FIO, index[j]->FIO);
		}
		else {
			comp_res = compare(index[i]->street_name, index[j]->street_name);
		}
		if (comp_res <= 0) {
			d[t] = index[i]; i++;
		}
		else {
			d[t] = index[j]; j++;
		}
		t++;
	}
	while(i <= mid) {
		d[t] = index[i]; i++; t++;
	}
	while (j <= end) {
		d[t] = index[j]; j++; t++;
	}
	for (i = 0; i < t; i++)
		index[begin + i] = d[i];
}

void MergSort(settlement* index[n], int left, int right,int sort_ord) {
	settlement* temp;
	if (left < right)
		if (right - left == 1) {
			int comp_res = 0;
			if (sort_ord == 0){
				comp_res = compare(index[right]->FIO, index[left]->FIO);
			}
			else{
				comp_res = compare(index[right]->street_name, index[left]->street_name);
			}
			if (comp_res < 0) {
				temp = index[left];
				index[left] = index[right];
				index[right] = temp;
			}
		}
		else {
			MergSort(index, left, left + (right - left) / 2, sort_ord);
			MergSort(index, left + (right - left) / 2 + 1, right, sort_ord);
			Merg(index, left, right,sort_ord);
		}
}

int bsearch(char *search_key, settlement **A) {
	int l = 0, r = 4000, m = 0;
	while (l <= r) {
		m = (int)((l + r) / 2);
		if (strncmp(A[m]->FIO, search_key, 3) == 0) {
			return m;
		}
		if (strncmp(A[m]->FIO, search_key, 3) < 0) {
			l = m + 1;
		}
		else r = m - 1;
	}
	return -1;
}


void BaseCoding(){
	
	int i,j;
	v = 0;
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].a = (char)(i-128); 
	}
	FILE *fp;	
	fp=fopen("testBase4.dat", "rb");
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
	//	cout << c<<" - " << (int)c <<endl; 
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
	
	for (i = 0; i < M && A[i].p != 0; i++){
		A[i].p /=sum;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
		v++;
	}
	fano(0, v - 1, 0);
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
	setlocale(LC_ALL, "Russian");
	printf("\n\nКод Фано: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	for (int i = 0; i < v; i++)
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

void addDbderevo(settlement* data, vertex*& s) {
	if (s == NULL) {
		s = new vertex;
		s->data = data;
		s->bal = 0;
		s->next = NULL;
		s->left = NULL;
		s->right = NULL;
		Vr = true;
	}
	else if (compare(s->data->street_name, data->street_name) == 0) {
		addDbderevo(data, s->next);
	}
	else if (compare(s->data->street_name, data->street_name) > 0) {
		addDbderevo(data, s->left);
		if (Vr) {
			if (s->bal == 0) {
				vertex* q = s->left;
				s->left = q->right;
				q->right = s;
				s = q;
				q->bal = 1;
				Vr = 0;
				Hr = 1;
			}
			else {
				s->bal = 0;
				Vr = 1;
				Hr = 0;
			}
		}
		else Hr = 0;
	}
	else if (compare(s->data->street_name, data->street_name) < 0) {
		addDbderevo(data, s->right);
		if (Vr) {
			s->bal = 1;
			Hr = 1;
			Vr = 0;
		}
		else if (Hr) {
			if (s->bal == 1) {
				vertex* q = s->right;
				s->bal = 0;
				q->bal = 0;
				s->right = q->left;
				q->left = s;
				s = q;
				Vr = 1;
				Hr = 0;
			}
			else Hr = 0;
		}
	}
}

void delete_tree(vertex *&s) {
	if (s != NULL) {
		delete_tree(s->left);
		delete_tree(s->right);
		delete s;
	}
}


void LeftToRight(vertex *s){
	if(s != NULL){
		LeftToRight(s -> left);
		cout << s->data->FIO << "\t" << s->data->street_name << "\t\t" << s->data->house_number << "\t" << s->data->flat_number << "\t\t" << s->data->date << endl;
		LeftToRight(s -> next);
		LeftToRight(s -> right);
	}
}

void SearchTree(char *street, vertex *s) {
	if(s!=NULL) {
        if(strncmp(s->data->street_name,street,3) > 0){
			SearchTree(street,s->left);
        }else{
            if(strncmp(s->data->street_name,street,3) < 0){
				SearchTree(street,s->right);
            } else{
				cout << s->data->FIO << "\t" << s->data->street_name << "\t\t" << s->data->house_number << "\t" << s->data->flat_number << "\t\t" << s->data->date << endl;
				SearchTree(street,s->next);
			}
        }
    }
}

int main() {
	int key, x;
	srand(time(NULL));
	int c = 0;
	char a;
	FILE* fp;
	fp=fopen("testBase4.dat", "rb");
	settlement *arr = new settlement[n];
	fread(arr, sizeof(settlement), n, fp);
	fclose(fp);
	settlement **index = new settlement * [n];
	for(int i = 0; i < n; i++) {
		index[i] = &arr[i];
	}
	MergSort(index, 0, n - 1,1);
	MergSort(index, 0, n - 1,0);
	while(true) {
		system("cls");
		cout << "1. View base" << endl << "2. Sort base" << endl << "3. Search by key" << endl << "4. Build tree and Search in tree" << endl << "5. Coding" << endl << "6. Exit" << endl << endl;
		char v = _getch();
		if (v == '1' || v == '2' || v == '3' || v == '4' || v == '5' || v == '6') {
			if(v == '1') {
				cout << "output of 20 entries/full list? (1/2)" << endl;
				char b = _getch();
				if (b == '1') {
					for (int i = 0; i < n; i += 20) {
						while (c < 20) {
							cout << c + i + 1 << "\t" << arr[c + i].FIO << "\t" << arr[c + i].street_name << "\t\t" << arr[c + i].house_number << "\t" << arr[c + i].flat_number << "\t\t" << arr[c + i].date << endl;
							c++;
						} c = 0;
						cout << "continue?(1/2)";
						a = _getch();
						if (a == '2') {
							break;
						}
					}
				}
				else if (b == '2') {
					for (int i = 0; i < n; i++) {
						cout << c + i + 1 << "\t" << arr[c + i].FIO << "\t" << arr[c + i].street_name << "\t\t" << arr[c + i].house_number << "\t" << arr[c + i].flat_number << "\t\t" << arr[c + i].date << endl;
						if (_kbhit()) {
							cout << "continue?(%/0)";
							cin >> a;
							if (!a) {
								break;
							}
						}
					}
				}
			}
			if(v == '2') {
				cout << "output of 20 entries/full list? (1/2)" << endl;
				int b = _getch();
				if (b == '1') {
					for (int i = 0; i < n; i += 20) {
						while (c < 20) {
							cout << c + i + 1 << "\t" << index[c + i]->FIO << "\t" << index[c + i]->street_name << "\t\t" << index[c + i]->house_number << "\t" << index[c + i]->flat_number << "\t\t" << index[c + i]->date << endl;
							c++;
						} c = 0;
						cout << "continue?(1/2)";
						a = _getch();
						if (a == '2') {
							break;
						}
					}
				}
				else if (b == '2') {
					for (int i = 0; i < n; i++) {
						cout << c + i + 1 << "\t" << index[c + i]->FIO << "\t" << index[c + i]->street_name << "\t\t" << index[c + i]->house_number << "\t" << index[c + i]->flat_number << "\t\t" << index[c + i]->date << endl;
						if (_kbhit()) {
							cout << "continue?(%/0) : ";
							a = _getch();
							if (!a) {
								break;
							}
						}
					}
				}
			}
			if(v == '3') {
				int search_start = 0;
				system("cls");
				settlement *skey[n];
				for(int i = 0; i < n; i++) {
					skey[i] = index[i];
				}
				char key[2];
				cout << "Enter the search key: ";
				gets(key);
				int search = bsearch(key, skey);
				if(search == -1) {
					cout << "Nothing found" << endl;
				} else {
					do {
						if(search == 0) {
							break;
						} else {
							search--;
						}
						if(strncmp(skey[search]->FIO, key, 3) != 0) {
							search++;
							break;
						}
					} while(true);
					search_start = search;
					do {
						search++;
						if(search == 4000) {
							break;
						}
						if(strncmp(skey[search] -> FIO, key, 3) != 0) {
							break;
						}
					} while(true);
					
					if (root != NULL) {
						delete_tree(root);
						root = NULL;
					}
					
					cout << endl << endl<< "Founded "<< (search - search_start) << " pozitions (" << (search_start + 1) << " " << (search) << ")" <<endl;
					for (int i = search_start; i < search; i++) {
						cout << "Deposit has been founded: " << (i + 1) << "\t";
						cout << skey[i]->FIO  << "\t";
						cout << skey[i]->street_name << "\t";
						cout << skey[i]->house_number << "\t";
						cout << skey[i]->flat_number << "\t";
						cout << skey[i]->date << endl;
						addDbderevo(skey[i], root);
					}
				}
			}
			if(v == '4') {
				LeftToRight(root);
				cout << "\nEnter the search key: ";
				char KeyH[32];
				char *space = " ";
				SetConsoleCP(866);
				cin.sync();
				cin.getline(KeyH,32);
				SetConsoleCP(1251);
				for(int i = strlen(KeyH); i<31;i++){
					strcat(KeyH, space);
				}
				if(strcmp(KeyH,"0")!=0){
        	       	SearchTree(KeyH, root);
        		}
			}
			if(v == '5') {
				BaseCoding();
				CodeBase();
				CodePrint();
			}
			if(v == '6') {
				return 0;
			}
		}
		system("pause");
	}
}
