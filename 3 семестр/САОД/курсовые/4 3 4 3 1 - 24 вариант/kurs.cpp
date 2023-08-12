
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

using namespace std;
const int N = 4000;

struct Base {
    char name[32];
    char street[18];
    short int number;
    short int number1;
    char data[10];
};

struct list {
    Base* data1;
    list* prev;
    list* head;
    list* next;
};

struct queue {
    list* head;
    list* tail;
};

struct vertex {
	Base* data1; 
    int w;
    int h;
    vertex* next;
    vertex* left;
    vertex* right;
};

struct HF_code {
	float p;  // повторение символа
	float q; // величины
	char a; //
	int l; // длина
};

list *base, *new_base = NULL;
list* p;
queue Q;
Base **massiv;

int *W;
int *h;
int menu();
void BubbleSort(int, int);
void Add_Tree(vertex*&, Base*, int);
void seth(vertex*);
void LRprint(vertex*&);
int Size_Tree(vertex *);
long Sum_Tree(vertex *);
void TreeSearch (vertex* p, int data);

void list_map(FILE* fp, list* p)
{
    for (int i = 0; i < N; i++) {
        Base* massiv = new Base();
        fread((Base*)massiv, sizeof(Base), 1, fp);
        p->data1 = massiv;
        p = p->next = new list();
    }
}

void nbase(list* a, list* b)
{
    b->prev = NULL;
    b->data1 = a->data1;
    for (int i = 1; i < N; i++) {
        a = a->next;
        b->next = new list;
        b->next->prev = b;
        b = b->next;
        b->data1 = a->data1;
    }
    b->next = NULL;
}

void DigitalSort(list*& head)
{
    queue Q[256];

    for (int i = 0; i < 255; i++) {
        Q[i].tail = Q[i].head = NULL;
    }
    for (int g = 1; g <= 7; g += 3) {
        for (int l = g; l >= g - 1; l--) {
            for (int i = 0; i < 255; i++) {
                Q[i].tail = Q[i].head = NULL;
            }
            while (head) {
                int d;
                d = head->data1->data[l] + 48;
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

    for (int j = 17; j >= 0; j--) {
        for (int i = 0; i < 255; i++) {
            Q[i].tail = Q[i].head = NULL;
        }
        while (head) {
            int d;
            d = head->data1->street[j] + 128;
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

void DigtalSort2(list*& head)
{
    queue Q[256];

    for (int i = 0; i < 255; i++) {
        Q[i].tail = Q[i].head = NULL;
    }

    for (int g = 1; g <= 7; g += 3) {
        for (int l = g; l >= g - 1; l--) {
            for (int i = 0; i < 255; i++) {
                Q[i].tail = Q[i].head = NULL;
            }
            while (head) {
                int d;
                d = head->data1->data[l] + 48;
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
}

int BSearch(list** A, char data[2])
{
    int l = 0, r = N, m = 0, fam_pos = 0;
    ;
    char buffer[10];
    while (l <= r) {
        m = (l + r) / 2;
        fam_pos = strchr(A[m]->data1->data, '-') - A[m]->data1->data;
        strcpy(buffer, A[m]->data1->data);
        buffer[fam_pos] = 'a';
        fam_pos = strchr(buffer, '-') - buffer;
        buffer[0] = A[m]->data1->data[fam_pos + 1];
        buffer[1] = A[m]->data1->data[fam_pos + 2];
        if (strncmp(buffer, data, 2) == 0) {
            return m;
        }
        if (strncmp(buffer, data, 2) < 0)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void Add_Tree(vertex*& p, Base *mas, int w)
{
    if (p == NULL) {
        p = new vertex;
        p->data1 = mas;
        p->w = w;
        p->left = NULL;
        p->right = NULL;
        p->next = NULL;
    }
    else
    if(mas->number == p->data1->number){
			Add_Tree(p->next, mas, w);
		}
    else if (mas->number < p->data1->number) {
        Add_Tree(p->left, mas, w);
    }
    else if (mas->number > p->data1->number) {
        Add_Tree(p->right, mas, w);
    }
}

void LRprint(vertex*& x)
{
    if (x == NULL)
        return;
    LRprint(x->left);
    cout << " " << x->data1->name << "\t" << x->data1->street << "\t" << x->data1->data << "\t" << x->data1->number1<< "\t" << x->data1->number << '\t' << x->w << "\t" << x->h << endl;
    LRprint(x->next);
	LRprint(x->right);
}

void seth(vertex *p)
{
	if (p) {
		if (p->next) {
			p->next->h = p->h +1;
		}
		if (p->left) {
			p->left->h = p->h + 1;
		}
		if (p->right) {
			p->right->h = p->h + 1;
		}
		seth(p->left);
		seth(p->right);
		seth(p->next);
	}
}

int Size_Tree(vertex *p)
{
	if (p == NULL)
		return 0;
	return 1 + Size_Tree(p->left) + Size_Tree(p->right) + Size_Tree(p->next);
}

long Sum_Tree(vertex *p)
{
	if (p == NULL)
		return 0;
	return p->data1->number + Sum_Tree(p->left) + Sum_Tree(p->right);
}

void BubbleSort(int search_start, int search)
{
    int i, j,v;
    Base *t;
    t = new Base[search];
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

void TreeSearch (vertex* p, int data){
		if(p!=NULL)
        {
            if(data < p->data1->number){
                    TreeSearch(p->left,data);
            }else{
                    if(data > p->data1->number){
                    	TreeSearch(p->right,data);
                }else{
					cout <<" "<<p->data1->name<<"\t"<<p->data1->street<<"\t"<<p->data1->number<<"\t"<<p->data1->number1<<"\t"<<p->data1->data<<endl;
                    TreeSearch(p->next,data);
				}
            }
        }
}

void print_list(list* p)
{
    int v;
    system("cls");
    cout << "1.Conclusion to 20" << endl;
    cout << "2.Scroling" << endl;
    cout << "3.Exit" << endl;
    cin >> v;
    if (v > 3) {
        cout << "Wrong input" << endl;
        system("PAUSE");
        print_list(p);
    }
    if (v == 1 or v == 2 or v == 3) {
        if (v == 1) {
            int temp = 0;
            int answer;
            system("cls");
            for (int i = 0; i < N; i++) {
                cout << i + 1 << "\t" << p->data1->name << "\t" << p->data1->street << "\t\t" << p->data1->number << "\t" << p->data1->number1 << "\t" << p->data1->data << endl;
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
                p = p->next;
            }
        }
        if (v == 2) {
            for (int i = 0; i < N; i++) {
                cout << i + 1 << "\t" << p->data1->name << "\t" << p->data1->street << "\t\t" << p->data1->number << "\t" << p->data1->number1 << "\t" << p->data1->data << endl;
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
                p = p->next;
            }
        }
    }
}

const int n = 256; // количество символов исходного алфавита
int C[n][n]; // матрица элементарных кодов 
//int length[n]; // длина
int sum = 0;
//double P[n]; // массив вероятностей упорядоченных по убыванию
HF_code A[n];
float lhuffman = 0, entropy = 0;

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
	int S[n];
	for (int i = 0; i < n; i++)
		S[i] = C[j][i];
	int L = A[j].l;
	for (int i = j; i < N - 1; i++)
	{
		for (int k = 0; k < n; k++)
			C[i][k] = C[i + 1][k];
		A[i].l = A[i + 1].l;
	}
	for (int i = 0; i < n; i++)
	{
		C[N - 1][i] = S[i];
		C[N][i] = S[i];
	}
	C[N - 1][L + 1] = 0;
	C[N][L + 1] = 1;
	A[N - 1].l = A[N].l = L + 1;
}

void Huffman(int N)
{
	if (N == 1)
	{		
		C[0][0] = 0;
		C[1][0] = 1;
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

void Coding () {
	system("cls");
	FILE *f;
	f = fopen("testBase4.dat", "rb");
	for (int i = 0; i < n; i++){
		A[i].p = 0;
		A[i].q = 0;
		A[i].l = 0;
		A[i].a = (char)(i-128);
	}
	while (!feof(f))
	{
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		sum++;
		// cout <<sum << " - " << c<<endl; 
		A[c + 128].p += 1;
	}
	fclose(f); 	
    system("PAUSE");
	
	int v=0;
	for (int i = 0; i < n; i++)
	{
		//cout << i << " - " << A[i].p;
		A[i].p /= sum;
		A[i].q = A[i].p;
		//cout << " - " << A[i].p<<endl;
		cout <<i << " - " << entropy << endl;
		if(A[i].p != 0){
			entropy += A[i].p * abs(log(A[i].p) / log(2));
			v++;
		}
	}
	
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < n; i++)  /// Упорядочим символы исходного алфавита А
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
	cout <<v;
	cout <<endl <<sum;
	Huffman(v-1);
	cout << "   ----------------------------------------------------" << endl;
	cout << "   | Symbol | Probability | Codeword | Codeword length |\n";
	cout << "   -----------------------------------------------------" << endl;
	SetConsoleCP(1251);
	for (int i = 0; i <n; i++) // <n если нужно все / <=v сли только те, которые встречаются
	{
		//cout << "" << i << "| " << a[i] << setw(8) << "| " << P[i] << setw(6) << "| " ;
		printf ("%3d| %c      | %2.9f    |", i, A[i].a, A[i].q);
		for (int j = 1; j <= A[i].l; j++)
		//	cout << "" << C[i][j];
		printf("%d", C[i][j]);
		for (int j = A[i].l + 1; j < 11; j++)
			cout << " ";
		//cout << setw(4) << "|  " << length[i] << setw(16) << "|";
		printf ("|%10d",A[i].l);
		cout << "" << endl;
		lhuffman += A[i].l * A[i].p;
	}
	cout << "---------------------------------------------------------" << endl;
		
	//		lhuffman += A[i].l * A[i].p;
			cout << "Entropy= ";
			printf(" %10f\n", entropy);
			cout << "Huffman= " << lhuffman <<endl;
			system("PAUSE"); 
	//		exit(0);
}

int menu()
{
    int v;
    system("cls");
    cout << "1.No sorting" << endl;
    cout << "2.Sorting" << endl;
    cout << "3.Biserch" << endl;
    cout << "4.Coding" << endl;
    cout << "5.Exit" << endl;
    cin >> v;
    if (v > 5) {
        cout << "Wrong input " << endl;
        system("PAUSE");
        menu();
    }
    if (v == 1 or v == 2 or v == 3 or v == 4 or v == 5) {
        if (v == 1) {
            print_list(base);
            menu();
        }
        if (v == 2) {
            new_base = new list;
            nbase(base, new_base);
            DigitalSort(new_base);
            print_list(new_base);
            menu();
        }
        if (v == 3) {
            int choise;
            system("cls");
            cout << "1.search" << endl;
            cout << "2.exit" << endl;
            cin >> choise;
            if (choise == 1 or choise == 2) {
                if (choise == 1) {
                    system("cls");
                    new_base = new list;
                    nbase(base, new_base);
                    DigtalSort2(new_base);
                    list** mas;
                    list** index[N];
                    mas = new list*[N];
                    for (int i = 0; i < N; i++) {
                        mas[i] = new_base;
                        index[i] = &mas[i];
                        new_base = new_base->next;
                    }
                    cout << "Enter search year(93,94,95,96,97)" << endl;
                    char data[3];
                    cin >> data;
                    int search = BSearch(mas, data);
                    int search_start = 0;
                    int fam_pos = 0;
                    char buffer[10];
                    if (search == -1) {
                        cout << "Not found" << endl;
                    }
                    else {
                        do {
                            if (search == 0) {
                                break;
                            }
                            else {
                                search--;
                            }
                            fam_pos = strchr(mas[search]->data1->data, '-') - mas[search]->data1->data;
                            strcpy(buffer, mas[search]->data1->data);
                            buffer[fam_pos] = 'a';
                            fam_pos = strchr(buffer, '-') - buffer;
                            buffer[0] = mas[search]->data1->data[fam_pos + 1];
                            buffer[1] = mas[search]->data1->data[fam_pos + 2];
                            if (strncmp(buffer, data, 2) != 0) {
                                search++;
                                break;
                            }
                        } while (1);

                        search_start = search;

                        do {
                            cout << search + 1 << " " << mas[search]->data1->name << "  " << mas[search]->data1->street << "  " << mas[search]->data1->number << " \t" << mas[search]->data1->number1 << "\t" << mas[search]->data1->data << endl;
                            search++;
                            if (search == N) {
                                break;
                            }
                            fam_pos = strchr(mas[search]->data1->data, '-') - mas[search]->data1->data;
                            strcpy(buffer, mas[search]->data1->data);
                            buffer[fam_pos] = 'a';
                            fam_pos = strchr(buffer, '-') - buffer;
                            buffer[0] = mas[search]->data1->data[fam_pos + 1];
                            buffer[1] = mas[search]->data1->data[fam_pos + 2];
                            if (strncmp(buffer, data, 2) != 0) {
                                break;
                            }
                        } while (true);
                        cout << "Create tree ?" << endl;
                        cout << "1-Yes 2-No" << endl;
                        int t;
                        cin >> t;
                        if (t == 1 or t == 2) {
                            if (t == 1) {
                                vertex* root = NULL;
                                massiv = new Base*[N];              
                                int j=0;
                                cout << search_start<<endl;
                                cout << search <<endl;
                                for (int i = search_start; i < search; i++) {
                                    massiv[i] = mas[i]->data1;
                                    cout << massiv[i]->number<< " ";
                                }
                                cout << " //  N K" << endl;
                                
								W = new int[N];
                                for (int i = search_start; i < search; i++) {
                                    W[i] = rand() % 99 + 1;
                                    cout << setw(3) << W[i] << " ";
                                }
                                cout << " // N V" << endl
                                     << endl;
                                BubbleSort(search_start, search);
                                /*for (int i = search_start; i < search; i++) {
                                    cout << setw(3) << massiv[i]->number << " ";
                                }
                                cout << " // O K" << endl;*/
                                
                                for (int i = search_start ; i < search; i++) {
                                    cout << setw(3) << W[i] << " ";
                                }
                                cout << " // O V " << endl
                                     << endl;

                                for (int i = search_start; i < search ; i++) {
                                    Add_Tree(root, massiv[i], W[i]);
                                }
                                root->h = 1;
                                seth(root);
                                cout << endl;
                                LRprint(root);
								cout << "A1" << endl;
                                cout << "|Algoritm|" << "Size Tree |" << "\tSumm Tree  |" << endl; 
                                cout << "|   A1   |" << setw(10) << Size_Tree(root) << "|" << setw(14) << Sum_Tree(root) << "|" << endl;
                                int s = 0;
                                cout << "what to search" << endl;
								cin >> s;
                                TreeSearch(root, s);
                            }
                        }
                        if (t == 2) {
                            menu();
                        }
                    }
                }
                system("PAUSE");
                menu();
            }
            if (choise == 2) {
                menu();
            }
        }
    }
    if (v == 4) {
    	setlocale(LC_ALL, "rus");
        Coding();
        system("PAUSE");
        menu();
    }
    if(v == 5) {
    	exit(0);
	}
}

int main()
{
	SetConsoleCP(1251);
	//setlocale(LC_ALL, "Russian");
    FILE* fp;
    fp = fopen("testBase4.dat", "rb");
    base = new list;
    list_map(fp, base);
    menu();
    return 0;
}
