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

using namespace std;

const int N = 4000;
const int M=256;
int sum=0, v=0;
int code[M][M];
float entropy = 0, lgm = 0;
int k=0;

struct Base {
	char fio[32];
	char street[18];
	short int number_home;
	short int number_door;
	char date[10];
};
Base* Info;
Base* Index = new Base[N];
Base* mas[N];

struct list {
	Base* data;
	list* prev;
	list* next;
};
list *new_base = NULL;
list* p;

struct queue {
    list* head;
    list* tail;
};
queue Q;

struct vertex {
	Base* data;
	int bal;
	int Data;
	vertex* left;
	vertex* next;
	vertex* right;
};
vertex* root = NULL;


struct Moor{
	float p;
	float q;
	int l;
	char a;
};
Moor A[M];
Moor B[166];

bool up = false;
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);


int Size(vertex*);
int Height(vertex*);
int Max(int, int);
float Sum_Paths(vertex* p, float);
int Sum_Tree(vertex* p);

void readBase(Base*& info)
{
	int d;
	FILE* fp;
	fp = fopen("testBase4.dat", "rb");
	info = new struct Base[N];
	d = fread((Base*)info, sizeof(Base), N, fp);
} 

void MasToList(Base* a, list* b)
{
    b->prev = NULL;
    b->data = &a[0];
    for (int i = 1; i < N; i++) {
        b->next = new list;
        b->next->prev = b;
        b = b->next;
        b->data = &a[i];
    }
    b->next = NULL;
}

void ListToMas(Base* a, list* b)
{
    for (int i = 0; i < N; i++) {
        a[i] = *b->data;
        b = b->next;
    }
}



void print_base(Base* Index)
{
	SetConsoleCP(1251);
	int v;
	system("cls");
	cout << "1.Conclusion to 20" << endl;
	cout << "2.Scroling" << endl;
	cout << "3.Exit" << endl;
	cin >> v;

	if (v > 3) {
		cout << "Wrong input" << endl;
		system("PAUSE");
		print_base(Index);
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

void DigitalSort(list*& head)
{
    queue Q[256];

    for (int i = 0; i < 255; i++) {
        Q[i].tail = Q[i].head = NULL;
    }
    for (int g = 17; g >= 0; g --) {
            for (int i = 0; i < 255; i++) {
                Q[i].tail = Q[i].head = NULL;
            }
            while (head) {
                int d;
                d = head->data->street[g] +128;
                p = Q[d].tail;
                if (Q[d].head == NULL) {
                    Q[d].head = head;
                }
                else {
                    p->next = head;
                }
                p = Q[d].tail = head;
                head = head->next;
                p->next = NULL;
            }
            head = NULL;
            int i;
            for (i = 0; i < 255; i++) {
                if (Q[i].head != NULL) {
                    break;
                }
            }
            head = Q[i].head;
            p = Q[i].tail;
            for (int k = i + 1; k < 255; k++) {
                if (Q[k].head != NULL) {
                    p->next = Q[k].head;
                    p = Q[k].tail;
                }
            }
    }

    for (int j = 31; j >= 0; j--) {
        for (int i = 0; i < 255; i++) {
            Q[i].tail = Q[i].head = NULL;
        }
        while (head) {
            int d;
            d = head->data->fio[j] + 128;
            p = Q[d].tail;
            if (Q[d].head == NULL) {
                Q[d].head = head;
            }
            else {
                p->next = head;
            }
            p = Q[d].tail = head;
            head = head->next;
            p->next = NULL;
        }
        head = NULL;
        int i;
        for (i = 0; i < 255; i++) {
            if (Q[i].head != NULL) {
                break;
            }
        }
        head = Q[i].head;
        p = Q[i].tail;
        for (int k = i + 1; k < 255; k++) {
            if (Q[k].head != NULL) {
                p->next = Q[k].head;
                p = Q[k].tail;
            }
        }
    }
}

int BSearch(Base** A, char fio[3])
{
	int l = 0, r = N, m = 0;
	while (l <= r) {
		m = (l + r) / 2;
		if (strncmp(A[m]->fio, fio, 3) == 0) {
			return m;
		}
		if (strncmp(A[m]->fio, fio, 3) < 0)
			l = m + 1;
		else
			r = m - 1;
	}
	return -1;
}


void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->next);
		delete_tree(p->right);
		delete p;
	}
}


void AVL(Base* data, vertex*& point) {
	if (point == NULL) {
		point = new vertex;
		point->data = data;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		point->next = NULL;
		up = true;
	}
	else {
		if (strcmp(point->data->street, data->street) == 0) {
			AVL(data, point->next);
			up = false;
		}
		else {
			if (strcmp(point->data->street, data->street) > 0) {
				AVL(data, point->left);
				if (up == true) {
					if (point->bal > 0) {
						point->bal = 0;
						up = false;
					}
					else
						if (point->bal == 0) {
							point->bal = -1;
							up = true;
						}
						else
							if (point->left->bal < 0) {
								ll(point);
								up = false;
							}
							else {
								lr(point);
								up = false;
							}
				}
			}
			else {
				if (strcmp(point->data->street, data->street) < 0) {
					AVL(data, point->right);
					if (up == true) {
						if (point->bal < 0) {
							point->bal = 0;
							up = false;
						}
						else {
							if (point->bal == 0) {
								point->bal = 1;
								up = true;
							}
							else {
								if (point->right->bal > 0) {
									rr(point);
									up = false;
								}
								else {
									rl(point);
									up = false;
								}
							}
						}
					}
				}
			}
		}
	}
}


void ll(vertex*& point)
{
	vertex* current = point->left;
	point->bal = 0;
	current->bal = 0;
	point->left = current->right;
	current->right = point;
	point = current;
}

void rr(vertex*& point)
{
	vertex* current = point->right;
	point->bal = 0;
	current->bal = 0;
	point->right = current->left;
	current->left = point;
	point = current;
}

void lr(vertex*& point)
{
	vertex* current = point->left;
	vertex* reva = current->right;

	if (reva->bal < 0) {
		point->bal = 1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal > 0) {
		current->bal = -1;
	}
	else {
		current->bal = 0;
	}
	reva->bal = 0;
	current->right = reva->left;
	point->left = reva->right;
	reva->left = current;
	reva->right = point;
	point = reva;
}

void rl(vertex*& point)
{
	vertex* current = point->right;
	vertex* reva = current->left;

	if (reva->bal < 0) {
		point->bal = 1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal > 0) {
		current->bal = -1;
	}
	else {
		current->bal = 0;
	}
	reva->bal = 0;
	current->left = reva->right;
	point->right = reva->left;
	reva->right = current;
	reva->left = point;
	point = reva;
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

float Sum_Paths(vertex* p, float depth) {
	if (p == NULL)
		return 0;
	else
		return (depth + Sum_Paths(p->left, depth + 1) +
			Sum_Paths(p->right, depth + 1));
}

int Sum_Tree(vertex* p) {
	if (p == NULL)
		return 0;
	else
		return (p->data->number_door + Sum_Tree(p->left) + Sum_Tree(p->right));
}

void Tree_Search(vertex* p, char *street) {
	if (p != NULL)
	{
		if (strncmp(p->data->street,street,3) > 0) {
			Tree_Search(p->left, street);
		}
		else {
			if (strncmp(p->data->street,street,3) < 0) {
				Tree_Search(p->right, street);
			}
			else {
				cout << " " << p->data->fio << "\t" << p->data->street << "\t" << p->data->number_home << "\t" << p->data->number_door << "\t" << p->data->date << endl;
				Tree_Search(p->next, street);
			}
		}
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
	printf("\n");
	fclose(fp);
	for (i = 0; i < M; i++) {
        A[i].p /= sum;
        if(A[i].p!=0){
        	v++;
        	entropy += A[i].p * abs(log(A[i].p) / log(2));
		}
    }
	j=0;
	for(i=0;i<M;i++){
		if(A[i].p!=0){
			B[j]=A[i];
			j++;
		}
	}
	

    for (i = 0; i < v; i++) {
        B[i].q = B[i - 1].q + B[i].p / 2;
        B[i].l = ceil(-log(B[i].p) / log(2)) + 1;
    }

    for (i = 0; i < v; i++) {
        for (j = 0; j <= B[i].l; j++) {
            B[i].q *= float(2);
            code[i][j] = floor(B[i].q);
            while (B[i].q >= 1)
                B[i].q -= 1;
        }
    }
}

void CodePrint(){
	SetConsoleCP(866);
	printf("\n\nГилберт-Мур: \n\n");
	printf("|  № | Символ | Вероятность |     Кодовое слово    | Длина код. слова |\n");
	for (int i = 0; i < v; i++)
	{
		printf("|%3d |    %c   |  %2.6f   | ",i, B[i].a, B[i].p);
		for (int j = 1; j <= B[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = B[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |    %7d       |\n", B[i].l);
		lgm += B[i].p * B[i].l;
	}	
	printf(" Entropy\t Av length\n");
	printf(" %6f    %10.5f\n", entropy, lgm);
	
}


void menu()
{
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
				print_base(Info);
			}
			if (v == 2) {
				print_base(Index);
			}
			if (v == 3) {
				system("cls");
				cout << "Search by first three letters of a surname" << endl;
				SetConsoleCP(866);
				char fio[3];
				cin >> fio;
				SetConsoleCP(1251);
	
				int search = 0;
				int search_start = 0;
				search = BSearch(mas, fio);
	
				if (search == -1) {
					SetConsoleCP(866);
					cout << "Ничего не найдено" << endl;
				}
				else {
					do {
						if (search == 0) {
							break;
						}
						else {
							search--;
						}
						if (strncmp(mas[search]->fio, fio, 3) != 0) {
							search++;
							break;
						}
					} while (true);
	
					search_start = search;
	
					do {
						cout << search + 1 << " " << mas[search]->fio << "  " << mas[search]->street << "  " << mas[search]->number_home << "  " << mas[search]->number_door << "  " << mas[search]->date << endl;
						search++;
						if (search == N) {
							break;
						}
						if (strncmp(mas[search]->fio, fio, 3) != 0) {
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
						if (root != NULL) {
							delete_tree(root);
							root = NULL;
						}
						cout << "\t\t\tBuilding a tree" << endl;
						for (int i = search_start; i < search; i++) {
							AVL(mas[i], root);;
						}
						system("cls");
						cout << endl << "\t\t\tLR-print - street" << endl;
						LRprint(root);
						cout << endl;
						cout << "--------------------------------------------" << endl;
						cout << "" << N << " |Size Tree" << "|Height" << "|Contl Sum" << "|Mid height|" << endl;
						cout << "--------------------------------------------" << endl;
						cout << "AVL  " << "|" << setw(7) << Size(root) << "  |" << setw(5) << Height(root) << " |" << setw(6) << Sum_Tree(root) << "   |" << setw(8) << Sum_Paths(root, 1) / Size(root) << "  |" << endl;
						cout << "--------------------------------------------" << endl;
						cout << "What will look for a tree" << endl;
						
						char C[18];
						char *space = " ";
						SetConsoleCP(866);
						cin.sync();
						cin.getline(C,18);
						SetConsoleCP(1251);
						for(int i = strlen(C); i<17;i++){
							strcat(C, space);
						}
						if(strcmp(C,"0")!=0){
							Tree_Search(root, C);
			        	}
					}
	
				}
			}
				
			if(v==4){
				CodePrint();
				
			}
			if(v==5){
				return;
			}
		}
		system("PAUSE");
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	readBase(Info);
	new_base = new list;
	MasToList(Info, new_base);
	DigitalSort(new_base);
	ListToMas(Index, new_base);
	for (int i = 0; i < N; i++) {
		mas[i] = &Index[i];
	}
	Coding();
	menu();
}
