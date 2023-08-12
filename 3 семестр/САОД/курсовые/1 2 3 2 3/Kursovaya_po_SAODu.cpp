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
const int M = 256;  //Кол-во разных символов в базе данных
int sum = 0;        //Счётчик общего кол-во символов
int code[M][M];		//Двумерный массив для кодов слов каждого символа
float entropy = 0, lgm = 0;			//Счётчик длинны энтропии, общей длинны
int fcompression = 0, cfcompression = 0;

struct record {
	char author[12]; // ФИО автора книги
	char title[32];		// ФИО того, о ком написанна книга
	char publisher[16]; // издательство
	short int year;     // год издания
	short int num_of_page;	// кол-во страниц
};



struct vertex {
	record* data;
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

int compare_deposit(int a, int b) {
	if(a > b) {
		return 1;
	} else if (a == b) {
		return 0;
	} else
		return -1;
}

int compare(char* a, char* b) {
	int result = strcmp(a, b);
	if(result == 0) {
		return strcmp(a, b);
	} else return result;
}

void Merg(record* index[n], int begin, int end, int sort_ord) {
	int i = begin,
	    t = 0,
	    mid = begin + (end - begin) / 2,
	    j = mid + 1;

	record* d[n];

	while (i <= mid && j <= end) {
		int comp_res = 0;
		if (sort_ord == 0) {
			comp_res = compare_deposit(index[i]->year, index[j]->year);
		} else {
			comp_res = compare(index[i]->author, index[j]->author);
		}

		if (comp_res <= 0) {
			d[t] = index[i];
			i++;
		} else {
			d[t] = index[j];
			j++;
		}
		t++;
	}

	while (i <= mid) {
		d[t] = index[i];
		i++;
		t++;
	}

	while (j <= end) {
		d[t] = index[j];
		j++;
		t++;
	}

	for (i = 0; i < t; i++)
		index[begin + i] = d[i];
}

void MergSort(record* index[n], int left, int right,int sort_ord) {
	record* temp;
	if (left < right)
		if (right - left == 1) {
			int comp_res = 0;
			if (sort_ord == 0) {
				comp_res = compare_deposit(index[right]->year, index[left]->year);
			} else {
				comp_res = compare(index[right]->author, index[left]->author);
			}
			if (comp_res < 0) {
				temp = index[left];
				index[left] = index[right];
				index[right] = temp;
			}
		} else {
			MergSort(index, left, left + (right - left) / 2,sort_ord);
			MergSort(index, left + (right - left) / 2 + 1, right,sort_ord);
			Merg(index, left, right,sort_ord);
		}
}


int bsearch(int search_key, record **A) {
	SetConsoleCP(1251);
	int l = 0, r = 4000, m = 0;
	while (l <= r) {
		m = (int)((l + r) / 2);
		if (A[m] -> year == search_key) {
			return m;
		}
		if (A[m] -> year < search_key) {
			l = m + 1;
		} else r = m - 1;
	}
	return -1;
}


void addDbderevo(record* data, vertex*& s) {
	if (s == NULL) {
		s = new vertex;
		s->data = data;
		s->bal = 0;
		s->next = NULL;
		s->left = NULL;
		s->right = NULL;
		Vr = true;
	}
	else if (compare(s->data->author, data->author) == 0) {
		addDbderevo(data, s->next);
	}
	else if (compare(s->data->author, data->author) > 0) {
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
	else if (compare(s->data->author, data->author) < 0) {
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
		cout << s->data->author << "\t" << s->data->title << "\t\t" << s->data->publisher << "\t" << s->data->year << "\t\t" << s->data->num_of_page << endl;
		LeftToRight(s -> next);
		LeftToRight(s -> right);
	}
}

void SearchTree(char *author, vertex *s){
	if(s!=NULL)                 ///Поиск элемента
    {
        if(strcmp(s->data->author,author) > 0){
        //	cout << data << "-l" << endl << s->data->Position << "-l" << endl << endl;
            SearchTree(author,s->left);
        }else{
            if(strcmp(s->data->author,author) < 0){
        //		cout << data << "-r" << endl << s->data->Position << "-r" << endl << endl;
              	SearchTree(author,s->right);
            }else{
				cout << s->data->author << "\t" << s->data->title << "\t\t" << s->data->publisher << "\t" << s->data->year << "\t\t" << s->data->num_of_page << endl;
				SearchTree(author,s->next);
			}
        }
    }
}

	void BaseCoding() {

		int i,j;
		for (i = 0; i < M; i++) {
			A[i].p = 0;
			A[i].l = 0;
			A[i].a = (char)(i-128);
		}
		FILE *fp;
		fp = fopen("testBase1.dat", "rb");
		while (!feof(fp)) {
			char c;
			fscanf(fp, "%c", &c);
			if (feof(fp))
				break;
			//cout << c<<" - " << (int)c <<endl;
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

		for (i = 0; i < M; i++) {
			A[i].p /= sum;
			entropy += A[i].p * abs(log(A[i].p) / log(2));
		}
		fano(0, M - 1, 0);
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

	int med(int L, int R) {
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

	void CodePrint() {
		setlocale(LC_ALL, "Russian");
		SetConsoleCP(866);
		printf("\n\nКод Фано: \n");
		printf("-------------------------------------------------------------------------------\n");
		printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
		printf("|               |        |             |                      |     слова     |\n");
		printf("|-----------------------------------------------------------------------------|\n");
		SetConsoleCP(1251);
		for (int i = 0; i < M; i++) {
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

	int main() {
		srand(time(NULL));
		int a, c = 0;
		int key, x;
		FILE* fp;
		fp = fopen("testBase1.dat", "rb");
		record *arr = new record[n];
		fread(arr, sizeof(record), n, fp);
		fclose(fp);
		record** index = new record * [n];
		for (int i = 0; i < n; i++) {
			index[i] = &arr[i];
		}
		MergSort(index, 0, n - 1,1);
		MergSort(index, 0, n - 1,0);
		record **skey = new record * [n];
		for(int i = 0; i < n; i++) {
			skey[i] = index[i];
		}
		while(true) {
			system("cls");
			cout << "1. View base" << endl << "2. Sort base" << endl << "3. Search by key" << endl << "4. Tree" <<  endl << "5. Coding Base" << endl << "6. End" <<endl << endl;
			char v = _getch();
			if (v == '1' || v == '2' || v == '3' || v == '4' || v == '5' || v == '6') {
				if(v == '1') {
					cout << "output of 20 entries/full list? (1/2) : " << endl;
					char b = _getch();
					if (b == '1') {
						for (int i = 0; i < n; i += 20) {
							while (c < 20) {
								cout << c + i + 1 << "\t" << arr[c + i].author << "\t" << arr[c + i].title << "\t\t" << arr[c + i].publisher << "\t" << arr[c + i].year << "\t\t" << arr[c + i].num_of_page << endl;
								c++;
							}
							c = 0;
							cout << "continue?(1/2)";
							cin >> a;
							if (a == 2) {
								break;
							}
						}
					} else if (b == '2') {
						for (int i = 0; i < n; i++) {
							cout << c + i + 1 << "\t" << arr[c + i].author << "\t" << arr[c + i].title << "\t\t" << arr[c + i].publisher << "\t" << arr[c + i].year << "\t\t" << arr[c + i].num_of_page << endl;
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
				if (v == '2') {
					cout << "output of 20 entries/full list? (1/2) : " << endl;
					char b = _getch();
					if (b == '1') {
						for (int i = 0; i < n; i += 20) {
							while (c < 20) {
								cout << "\t " << c + i + 1 << "\t" << index[c + i] -> author << "\t" << index[c + i] -> title << "\t\t" << index[c + i] -> publisher << "\t" << index[c + i] -> year << "\t\t" << index[c + i] -> num_of_page << endl;
								c++;
							}
							c = 0;
							cout << "continue?(1/2)";
							cin >> a;
							if (a == 2) {
								break;
							}
						}
					} else if (b == '2') {
						for (int i = 0; i < n; i++) {
							cout << c + i + 1 << "\t" << index[c + i] -> author << "\t" << index[c + i] -> title << "\t\t" << index[c + i] -> publisher << "\t" << index[c + i] -> year << "\t\t" << index[c + i] -> num_of_page << endl;
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
				if (v == '3') {    // ключ поиска
					int search_start = 0;
					system("cls");
					record *skey[4000];
					for(int i = 0; i < n; i++) {
						skey[i] = index[i];
					}
					int key;
					cout << "Enter the search key: ";
					cin >> key;                  // 1900
					int search = bsearch(key, skey);   //search = 92
					if(search == -1) {          // если такого ключа не существует
						cout << "Nothing found" << endl;
					} else {
						do {                      //m = 92   search = 92   проверка на то, чтобы не выйти за левую границу
							if(search == 0) {
								break;
							} else {					// search = 81
								search--;
							}
							if(skey[search] -> year != key) {  // 1900 = 1900
								search++;    //search = 82
								break;
							}
						} while(true);
						search_start = search;   //search_start = 82
						do {            // нахождение правой границы
							search++;        //search = 123
							if(search == 4000) {       //search != 4000
								break;
							}
							if(skey[search] -> year != key) {  // 1900 =  1900
								break;
							}
						} while(true);
						
						if (root != NULL) {
							delete_tree(root);
							root = NULL;
						}
						cout << endl << endl << "Founded "<< (search - search_start + 1) << " pozitions (" << search_start + 1 << " " << search << ")" <<endl;
						for (int i = search_start; i < search; i++) {
							cout << i + 1 << "\t";
							cout << skey[i] -> author << "\t";
							cout << skey[i] -> title << "\t";
							cout << skey[i] -> publisher << "\t";
							cout << skey[i] -> year << "\t";
							cout << skey[i] -> num_of_page << endl;
							addDbderevo(skey[i], root);
						}
					}
				}
				if(v=='4') {
					LeftToRight(root);
					cout << "\nEnter the search key: ";
					char KeyH[12];
					char *space = " ";
					SetConsoleCP(866);
					cin.sync();
					cin.getline(KeyH,12);
					SetConsoleCP(1251);
					for(int i = strlen(KeyH); i<11;i++){
						strcat(KeyH, space);
					}
					if(strcmp(KeyH,"0")!=0){
        	        	SearchTree(KeyH, root);
        	        }
				}
				if (v=='5') {
					BaseCoding();
					CodeBase();
					CodePrint();
				}
				if (v=='6'){
					return 0;
				}
			}
			system("pause");
		}
	}
