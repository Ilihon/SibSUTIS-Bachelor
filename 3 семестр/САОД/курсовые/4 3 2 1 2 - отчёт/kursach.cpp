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
#define YES true
#define NO false


using namespace std;

const int M=256;
const int N=4000;
int sum=0;
int code[M][M];
double entropy = 0, length = 0;
int v=0;


bool up = NO;

struct basa {
    char a[32];
    char b[18];
    short int c;
    short int d;
    char e[10];
};

struct SHANON {
	float p;
	float q;
	int l;
	char a;
};
SHANON A[M];

struct vertex
{
	basa* pole;
	int bal;
	vertex *left;
	vertex *right;
	vertex *next;
};

vertex *tree = new vertex;


struct spis {
	spis *next;
	spis *prev;
	basa *data;
};

struct queue {
	spis *head;
	spis *tail;
};

spis *head = NULL, *tail = NULL;

void push_queue(spis *c, spis **b);
int compare(basa *a, basa *b);

void ll(vertex* &point);
void rr(vertex* &point);
void lr(vertex* &point);
void rl(vertex* &point);
void addAVL(spis *p, vertex *&point);

void Obhod(vertex *v);
int compare_street(char* a,char* b);
void searchAVL (vertex *root, char *data);

void print(basa* mas[]);
void qs(basa* mas[], int left, int right);
void search(basa *mas[], int left, int right);

void shanon();
void FPrint();
void FStart();

int main()
{	
	setlocale(LC_ALL, "Russian");
	const int num = 4000;
    FILE* fp;
	fp = fopen("testbase4.dat", "rb");
    basa* mas[num];
    basa* mas_orig[num];
    basa mas2[num];
    fread(mas2, sizeof(basa), 4000, fp);
	fclose(fp);
    for (int i=0;i<num;i++){
    	mas[i] = &mas2[i];
    	mas_orig[i] = &mas2[i];
	}
	qs(mas,0,num-1);
    
	while(true){
		int v;
		system("cls");
		SetConsoleCP(866);
		cout << "1.Оригинальная база" << endl;
		cout << "2.Отсортированная" << endl;
		cout << "3.Бинарный поиск" << endl;
		cout << "4.Кодирование" << endl;
		cout << "5.Выход" << endl;
		cin >> v;
		if (v == 1 || v == 2 || v == 3 || v==4 || v==5) {
			if (v == 1) {
				print(mas_orig);
			}
			if (v == 2){
		    	print(mas);
			}
			if (v == 3){
		    	char key[18];
				SetConsoleCP(1251);
		    	search(mas,0,num-1);
				system("pause");
		    	cout << endl << "TREE:" << endl << endl;
			    Obhod(tree);
			    cout << endl << "Type key for search:" << endl;
				SetConsoleCP(866);
			    cin >> key;
				SetConsoleCP(1251);
				char *spc = " ";
				strcat(key, spc);
				if(strcmp(key,"0")!=0){
			    	searchAVL(tree,key);
				}
				
			}
		 	if(v==4){
				FStart();
				FPrint();
		 	}
			if(v==5){
				return 0;
			}	
		}
		system("pause");
	}
    return 0;
}

void push_queue(spis *c, spis **b)
{
    if((*b) != NULL)
    {
        spis *temp = new spis;
        temp = c;
        temp->next = NULL;
        (*b)->next = temp;
        (*b) = temp;
    }
    else
    {
        (*b) = new spis;
        (*b) = c;
        (*b)->next = NULL;
        head = (*b);
    }
}

int compare(basa *a, basa *b) 
{ 
	if(strcmp(&a->e[6], &b->e[6]) != 0){
		return strcmp(&a->e[6], &b->e[6]);
	}
	else if (a->e[3] - b->e[3] != 0) {
		return a->e[3] - b->e[3];
	}
	else if (a->e[4] - b->e[4] != 0) {
		return a->e[4] - b->e[4];
	}
	else if (a->e[0] - b->e[0] != 0) {
		return a->e[0] - b->e[0];
	}
	else if (a->e[1] - b->e[1] != 0) {
		return a->e[1] - b->e[1];
	}
	else if (strcmp(a->b, b->b) != 0) {
		return strcmp(a->b, b->b);
	}
	return 0;
}

void ll(vertex* &point)
{
	vertex *current = point->left;
	point->bal = 0;
	current->bal = 0;
	point->left = current->right;
	current->right = point;
	point = current;
}

void rr(vertex* &point)
{
	vertex *current = point->right;

	point->bal = 0;
	current->bal = 0;
	point->right = current->left;
	current->left = point;
	point = current;
}

void lr(vertex* &point)
{
	vertex *current = point->left;
	vertex *reva = current->right;

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

void rl(vertex* &point)
{
	vertex *current = point->right;
	vertex *reva = current->left;

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

void addAVL(spis *p, vertex *&point)
{
	if (point == NULL) {
		point = new vertex;
		point->pole = p->data;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		point->next = NULL;
		up = YES;
	}
	else{
		if (compare_street(point->pole->b, p->data->b) > 0) {
			addAVL(p, point->left);
			if (up == YES) {
				if (point->bal > 0) {
					point->bal = 0;
					up = NO;
				}
				else
					if (point->bal == 0) {
						point->bal = -1;
						up = YES;
					}
					else
						if (point->left->bal < 0) {
							ll(point);
							up = NO;
						}
						else {
							lr(point);
							up = NO;
						}
			}	
		}
		else {
			if (compare_street(point->pole->b, p->data->b) < 0) { 
				addAVL(p, point->right);
					if (up == YES) {
						if (point->bal < 0) {
							point->bal = 0;
							up = NO;
						}
						else {
							if (point->bal == 0) {
								point->bal = 1;
								up = YES;
							}
							else {
								if (point->right->bal > 0) {
									rr(point);
									up = NO;
								}
								else {
									rl(point);
									up = NO;
								}
							}
						}
					}
			}
			if (compare_street(point->pole->b, p->data->b) == 0){
				addAVL(p, point->next);
				up = NO;
			}
		}
	}
}

void Obhod(vertex *v) {
	if(v==NULL){
		return;
	}
	else {
		Obhod(v->left);
		cout << " " << v->pole->a << "\t"  << v->pole->b << "\t"  << v->pole->c << "\t" << v->pole->d << "\t"  << v->pole->e << endl;
		Obhod(v->next);
		Obhod(v->right);
	}
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

void searchAVL (vertex *root, char *data) {
	if (root == NULL) {
		return;
	}
	else if (compare_street(root->pole->b, data) > 0){
		searchAVL(root->left, data);
	}
	else if (compare_street(root->pole->b, data) < 0){
		searchAVL(root->right, data);
	}
	else{
		cout << root->pole->a << "\t"  << root->pole->b << "\t"  << root->pole->c << "\t"  << root->pole->d << "\t"  << root->pole->e << endl;
		searchAVL(root->next, data);
	}
}

void print(basa* mas[])
{
    int v;
    system("cls");
	SetConsoleCP(1251);
    cout << "1.Printout by 20" << endl;
    cout << "2.4000 for 1 click" << endl;
    cout << "3.No print" << endl;
    cin >> v;
    if (v == 1 or v == 2 or v == 3) {
        if (v == 1) {
        	cout << "no 20" << endl;
            int temp = 0;
            int answer;
            for (int i = 0; i < 4000; i++) {
                cout << i << "\t" << mas[i]->a << "\t" << mas[i]->b << "\t" << mas[i]->c << "\t" << mas[i]->d << "\t" << mas[i]->e << endl;
                temp++;
                if (temp % 20 == 0) {
                    cout << "Dalshe?" << endl << "1=da, 0=net" << endl;
                    cin >> answer;
                    if (answer == 1) {
                        continue;
                    }
                    if (answer == 0) {
                        cout << "Closing prog" << endl;
                        system("PAUSE");
                        break;
                    }
                    if ((answer != 1) && (answer != 0)) {				
                    	int s;
                     	cout << "Missclick or u really wanna exit? " << "1 fo yes, 0 fo no" << endl;
                     	cin >> s;
                     	if (s == 1){						 						 
                        	break;
                    	}
                    	if (s == 0){						
                    		cout << "kk, np, moving next" << endl;
                    		continue;
                    	}
                    	if ((s != 1 ) & (s != 0)){
                    		cout << "u missed again. Closing." << endl;
                    		break;
						}
                	}
                }
            }
        }
        if (v == 2) {
            for (int i = 0; i < 4000; i++) {
                cout << i << "\t" << mas[i]->a << "\t" << mas[i]->b << "\t\t" << mas[i]->c << "\t" << mas[i]->d << "\t" << mas[i]->e << endl;
                if (kbhit())
                    if (getch() == 13) {
                        cout << "Stopped " << endl << "Moving next? (Double enter for yes)" << endl;
                        cout << "To exit press esc" << endl;
                        if (getch() == 27) {
                            break;
                        }
						  if (getch() == 13) {
                            continue;
                        }
                        if ((getch() != 13) && (getch() != 27)) {
						int s;
                     	cout << "Missclick or u really wanna exit? " << "1 fo yes, 0 fo no" << endl;
                     	cin >> s;
	                     	if (s == 1){						 						 
	                        break;
	                    	}
	                    	if (s == 0){						
	                    	cout << "kk, np, moving next" << endl;
	                    	continue;
	                    	}	
	                    	 if ((s != 1) && (s != 0)){
	                    	 	break;
							 }
						}
					}
                if (i == 3999) {
                    cout << "End of file" << endl;
                    
                }
            }
        }
    }
	SetConsoleCP(866);
}

void qs(basa* mas[], int left, int right)
{

  register int i, j;
  basa *x;
  basa *temp;

  i = left; j = right;
  x = mas[(left+right)/2];

  do {
    while((compare(mas[i],x) < 0) && (i < right)) i++;
    while((compare(mas[j],x) > 0) && (j > left)) j--;
    if(i <= j) {
      temp = mas[i];
      mas[i] = mas[j];
      mas[j] = temp;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs(mas, left, j);
  if(i < right) qs(mas, i, right);
}

void shanon()
{
	for (int i = 0; i < v; i++)
	{
		A[i].q = A[i - 1].q + A[i].p;
		A[i].l = ceil(-log(A[i].p) / log(2));
	}
	for (int i = 1; i < v; i++)
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

void FPrint(){
	SetConsoleCP(866);
	printf("\n\nКод Фано: \n");

	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");

	SetConsoleCP(1251);
	for (int i = 0; i < v; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].q);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |  %7d      |\n", A[i].l);
		length += A[i].p * A[i].l;
	}
	SetConsoleCP(866);
	printf("\n|    Энтропия   |  Средняя длина  |\n");
	printf("|  %12f |   %10.5f    |\n", entropy, length);

	SetConsoleCP(1251);
}

void FStart(){
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
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 1; i < M; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				SHANON Buf = A[i-1];
				A[i-1]=A[i];
				A[i]=Buf;
				flag = true;
			}
		}
	}
	//system("pause");
	for (i = 0; i < M, A[i].p != 0; i++){
		A[i].p /=sum;
        v++;
        entropy += A[i].p * abs(log(A[i].p) / log(2));
	//	printf("%3d  -  %c   -  %2.6f\n",i, (char)(i-128), A[i].p);
	}
	//system("pause");
	shanon();
}


void search(basa *mas[], int left, int right){
	//SetConsoleCP(866);
	basa *Que[4000]; 
	spis *qu = new spis;
	//spis *que = qu;
	int v = 0, mid = 0, find = 0;
	cout << "Biinary search (year): ";
	char b[2];
	cin >> b;

	//cout << b << endl;	
	for (v = 0; v < 4000; v++) {
		while ( left < right ) {
			mid = (left + right) / 2;
			if (strncmp(b, &mas[v]->e[6],2) < 0) left = mid + 1;
				else right = mid;
			}
			if (strncmp(b, &mas[v]->e[6],2) == 0) {			
				Que[find] = mas[v];
				find +=1;
				qu->data = mas[v];
				push_queue(qu, &tail);
			

				qu->next = new spis;
				qu = qu->next;
			}
	}
	tree = NULL;
	//que->next = NULL;
	//cout <<  find << endl;
 	for(int i = 0; i < find; i++){
 		if (head != NULL){
			addAVL(head, tree);
			head = head->next;
		}
		else cout << "kkk" << endl;
	}
	cout << "Founded " << find << " positions" << endl;
}

