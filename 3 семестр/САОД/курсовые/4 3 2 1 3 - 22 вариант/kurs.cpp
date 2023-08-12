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
float entropy = 0, length = 0;
int v=0;


bool up = NO;

struct basa {
    char a[32];
    char b[18];
    short int c;
    short int d;
    char e[10];
};

struct Fano {
	float p;
	int l;
};

Fano A[M];


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

//-------------------------------------------------
int compare(basa *a, basa *b) {
	if (strcmp(a->b, b->b) != 0) {
		return strcmp(a->b, b->b);
	}
	else if(strcmp(&a->e[6], &b->e[6]) != 0){
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
	return 0;
}
//----------------------------------------------------

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
	else 
			if (strncmp(point->pole->a, p->data->a,4) > 0) {
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
						//	lr(point);
							up = NO;
						}
			}	
			}
		else {
		if (strncmp(point->pole->a, p->data->a,4) < 0) { 
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
							//	rl(point);
								up = NO;
							}
						}
					}
				}
		}
		
		if (strncmp(point->pole->a, p->data->a,4) == 0){
			addAVL(p, point->next);
		}
		
			else {
				return;
			}
		}
}

void Obhod(vertex *v) {
	if(v==NULL)
		return ;
		else {
			Obhod(v->left);
			cout << v->pole->a << "\t"  << v->pole->b << "\t"  << v->pole->c << "\t" << v->pole->d << "\t"  << v->pole->e << endl;
			Obhod(v->next);
			Obhod(v->right);
			}
	}


void searchAVL (vertex *root, char data[10]) {
	
	if (root == NULL) {
		return;
	}
	else if (strncmp (data, root->pole->a, 4) < 0){
		searchAVL(root->left, data);
	}
	else if (strncmp(data, root->pole->a, 4) > 0){
		searchAVL(root->right, data);
	}
	else if (strncmp(data, root->pole->a, 4) == 0){
		cout << root->pole->a << "\t"  << root->pole->b << "\t"  << root->pole->c << "\t"  << root->pole->d << "\t"  << root->pole->e << endl;
		searchAVL(root->next, data);
		//cout << root->pole.a << " " << root->pole.b << " " << root->pole.c << " " << root->pole.d << " " << endl;
		//find(root->right, data);
	}
}

void print(basa* mas[])
{
    int v;
    system("cls");
    cout << "1.Printout by 20" << endl;
    cout << "2.4000 for 1 click" << endl;
    cout << "3.Close prog" << endl;
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

void search(basa *mas[], int left, int right);

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

void FPrint(){
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(866);
	printf("\n\nКод Фано: \n");

	printf("| Номер Символа | Символ | Вероятность |     Кодовое слово    | Длина кодового|\n");
	printf("|               |        |             |                      |     слова     |\n");

	for (int i = 0; i < M; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, (char)(i-128), A[i].p);
		for (int j = 1; j <= A[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |  %7d      |\n", A[i].l);

		length += A[i].p * A[i].l;
	}	
	printf("|  Энтропия  |  Средняя длина  |\n");
	printf("| %10f |   %10.5f    |\n", entropy, length);

	
}

void Fstart(){
	
	int i,j;
	FILE *fp;	
	fp=fopen("testBase4.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
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
				Fano B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	system("pause");
	for (i = 0; i < M; i++){
		A[i].p /=sum;
		if(A[i].p!=0){
        	v++;
        	entropy += A[i].p * abs(log(A[i].p) / log(2));
		}
    	cout << i << " - " << (char)(i-128) << " - " << A[i].p <<endl;
	}
	system("pause");
	fano(0, v-1, 0);
}




int main()
{	
	const int num = 4000;
    FILE* fp;
	fp = fopen("testbase4.dat", "rb");
    basa* mas[num];
    basa mas2[num];
    fread(mas2, sizeof(basa), 4000, fp);
    for (int i=0;i<num;i++){
    	mas[i] = &mas2[i];
	}
    /*   
    int chs;
    cout << "Sorted ot default? (1/0)" << endl;
    cin >> chs;
    char key[10];
    if (chs == 1){
    	  qs(mas,0,num-1);
    	  print(mas);
    	  search(mas,0,num-1);
    	  cout << endl << "TREE:" << endl << endl;
	      Obhod(tree);
	      cout << "Type key for search:" << endl;
	      cin >> key;
	      searchAVL(tree,key);
	}
	else if (chs == 0){
		print(mas);
	}*/
	fclose(fp);
 	
 		
	Fstart();
	FPrint();
    return 0;
}

void search(basa *mas[], int left, int right){
	
	basa *Que[4000]; 
	spis *qu = new spis;
	//spis *que = qu;
	int v = 0, mid = 0, find = 0;
	char b[2];
	cin >> b;

	cout << b << endl;	
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
	cout <<  find << endl;
 	for(int i = 1; i < find+1; i++){
 		
 			if (head != NULL){
		
				addAVL(head, tree);
				head = head->next;
			}
			else cout << "kkk" << endl;
	 

		
	}
	cout <<  find << endl;
	
	
}

