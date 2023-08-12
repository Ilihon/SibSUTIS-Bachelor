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
#include <locale.h>

#define n 4000

using namespace std;
int Vr, Hr;
bool Rost = false;
const int M = 256;
int sum = 0;
int v = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int *W;
int *h;


struct settlement {
	char FIO[32];
	char street_name[18];
	short int house_number;
	short int flat_number;
	char date[10];
};


struct vertex {
	settlement* data; 
    int w;
    int h;
    vertex* next;
    vertex* left;
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

int compare_deposit(int a, int b) {
	if(a > b) {
		return 1;
	} else if (a == b) {
		return 0;
	} else
		return -1;
}

void Merg(settlement* index[n], int begin, int end, int sort_ord) {
	int i = begin, t = 0, mid = begin + (end - begin) / 2, j = mid + 1;
	settlement* d[n];
	while(i <= mid && j <= end) {
		int comp_res = 0;
		if(sort_ord == 0){
			comp_res = compare_deposit(index[i]->house_number, index[j]->house_number);
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
				comp_res = compare_deposit(index[right]->house_number, index[left]->house_number);
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
		if (strncmp(A[m]->street_name, search_key, 3) == 0) {
			return m;
		}
		if (strncmp(A[m]->street_name, search_key, 3) < 0) {
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
	fp = fopen("testBase4.dat", "rb");
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		A[c+128].p += 1;
		sum++;
	}
	printf("\n");
	fclose(fp);
	bool b = true;
	while (b) {
		b = false;
		for (int i = 1; i < M; i++) {
			if (A[i - 1].p < A[i].p) {
				F_code B = A[i-1];
				A[i-1] = A[i];
				A[i] = B;
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

void fano(int L, int R, int k) {
	if (L < R) {
		k++;
		int m = med(L, R);
		for (int i = L; i <= R; i++) {
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
	while (sl >= sr) {
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
		for (int i = 0; i < M; i++) {
			if (buffer == (char)(i-128)) {
				for (int j = 0; j < A[i].l; j++) {
					putc(code[i][j], fcoded);
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
	for (int i = 0; i < v; i++) {
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].p);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |  %7d      |\n", A[i].l);
		printf("|-----------------------------------------------------------------------------|\n");
		lgm += A[i].p * A[i].l;
	}
	
	printf("________________________________\n");
	printf("|  Энтропия  |  Средняя длина  |\n");
	printf("|____________|_________________|\n");
	printf("| %10f |   %10.5f    |\n", entropy, lgm);
	printf("|____________|_________________|\n");
}

void addTree(vertex*& s, settlement* data, int w) {
    if (s == NULL) {
        s = new vertex;
        s->data = data;
        s->w = w;
        s->left = NULL;
        s->right = NULL;
        s->next = NULL;
    }
    else
    if(data->house_number == s->data->house_number){
			addTree(s->next, data, w);
		}
    else if (data->house_number < s->data->house_number) {
        addTree(s->left, data, w);
    }
    else if (data->house_number > s->data->house_number) {
        addTree(s->right, data, w);
    }
}

void delete_tree(vertex *&s) {
	if (s != NULL) {
		delete_tree(s->left);
		delete_tree(s->next);
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

void SearchTree(int key, vertex *s) {
	if(s!=NULL) {
        if(s->data->house_number > key){
			SearchTree(key,s->left);
        }else{
            if(s->data->house_number < key){
				SearchTree(key,s->right);
            } else{
				cout << s->data->FIO << "\t" << s->data->street_name << "\t\t" << s->data->house_number << "\t" << s->data->flat_number << "\t\t" << s->data->date << endl;
				SearchTree(key,s->next);
			}
        }
    }
}

void BubbleSort(int search_start, int search)
{
    int i, j,v;
    for (i = search_start; i < search - 1; i++) {
        for (j = search - 1; j > i; j--) {
            if (W[j] > W[j - 1]) {
                v = W[j];
                W[j] = W[j - 1];
                W[j - 1] = v;
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
	MergSort(index, 0, n - 1,0);
	MergSort(index, 0, n - 1,1);
	while(true) {
		int tree_key = 0;
		system("cls");
		cout << "1. View base" << endl << "2. Sort base" << endl << "3. Search by key" << endl << "4. Build tree and Search in tree" << endl << "5. Coding" << endl << "6. Exit" << endl << endl;
		char e = _getch();
		if (e == '1' || e == '2' || e == '3' || e == '4' || e == '5' || e == '6' || e == '7') {
			if(e == '1') {
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
			if(e == '2') {
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
			if(e == '3') {
				int search_start = 0;
				system("cls");
				settlement *skey[n];
				for(int i = 0; i < n; i++) {
					skey[i] = index[i];
				}
				char key[3];
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
						if(strncmp(skey[search]->street_name, key, 3) != 0) {
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
						if(strncmp(skey[search] -> street_name, key, 3) != 0) {
							break;
						}
					} while(true);
					
					if (root != NULL) {
						delete_tree(root);
						root = NULL;
					}
					W = new int[n];
                    for (int i = search_start; i < search; i++) {
                        W[i] = rand() % 99 + 1;
                    }
                    BubbleSort(search_start, search);
					cout << endl << endl<< "Founded "<< (search - search_start) << " pozitions (" << (search_start + 1) << " " << (search) << ")" <<endl;
					for (int i = search_start; i < search; i++) {
						cout << (i + 1) << "\t";
						cout << skey[i]->FIO  << "\t";
						cout << skey[i]->street_name << "\t";
						cout << skey[i]->house_number << "\t";
						cout << skey[i]->flat_number << "\t";
						cout << skey[i]->date << endl;
                        addTree(root, skey[i], W[i]);
					}
				}
			}
			if(e == '4') {
				LeftToRight(root);
				cout << "\nEnter the search key: ";
				cin >> tree_key;
				cout << tree_key;
        	    SearchTree(tree_key, root);
			}
			if(e == '5') {
				BaseCoding();
				CodeBase();
				CodePrint();
			}
			if(e == '6') {
				return 0;
			}
		}
		system("pause");
	}
}
