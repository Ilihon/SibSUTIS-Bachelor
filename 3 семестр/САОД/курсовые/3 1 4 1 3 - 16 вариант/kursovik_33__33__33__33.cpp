#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iomanip>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define YES true
#define NO false

using namespace std;

const int P = 4000;
bool up = NO;

struct record2
{
	char a[30];
	unsigned short int b;
	char c[10];
	char d[22];
	
};

struct vertex
{
	record2 pole;
	int bal;
	vertex *left;
	vertex *right;
	vertex *ser;
};

vertex *tree = new vertex;

struct spis {
	spis *next;
	spis *prev;
	union{
		record2 pole;
		unsigned char digit [sizeof(pole)];
	};
};

struct queue {
	spis *head;
	spis *tail;
};

void digitalSort(spis *(&S)) {
  int KDI[32];
  for (int i = 0; i < 30; i++)
    KDI[i] = i;
  KDI[30] = 31;
  KDI[31] = 30;
  int L = 32;

  queue q[256];
  spis *p;
  unsigned char d;
  int k;

  for (int j = L - 1; j >= 0; j--) {
    for (int i = 0; i <= 255; i++) {
      q[i].tail = (spis *)&(q[i].head);
    }
    p = S;
    k = KDI[j];
    while (p != NULL) {
      d = p->digit[k];
      q[d].tail->next = p;
      q[d].tail = p;
      p = p->next;
    }

    p = (spis *)&S;

    int i = 0;
    while (i < 256) {
      if (q[i].tail != (spis *)&(q[i].head)) {
        p->next = q[i].head;
        p = q[i].tail;
      }
      i ++;
    }

    p->next = NULL;
  }
  return;
}

void search(spis **mas, int left, int right);

spis* spisok(record2* mas, int size) {
    spis* head = new spis;
    spis* p = head;
    int i;
    for (i = 0; i < size-1; i++) {
        p->pole = mas[i];
        p->next = new spis;
        p = p->next;
    }
    p->pole = mas[i];
    p->next = NULL;
    return head;
}


void print_spis (spis *p) {
		system("cls");
	int i=0, z = 0, b = 0, a, y, n = 20;
	cout << "Choose Select mode:" << endl << "1)4000 (for stop press Enter) " << endl << "2)20" << endl;
	cin >> b;
switch(b) {
    case 1:
    	for(int i=0;i<P;++i) {
			cout<<i+1<<" "<< p->pole.a << "   " << p->pole.b << "   " << p->pole.c << "   " << p->pole.d << endl;		    	
				if (kbhit()) {
        		cout << "Continue? If yes, press number 1";
        		cin >> y;
        		if (y != 1)
        		break;
		}
			p = p -> next;
	}
	break;
    case 2:
		for(int i=0;i<P;++i){
			while((i++)<n){
				cout<<i<<" "<< p->pole.a << "   " << p->pole.b << "   " << p->pole.c << "   " << p->pole.d << endl;
				p = p->next;
			}
		i-=1;
		n+=20;
		cout<<"Continue? If yes, press 1"<<endl;
		cin>>a;  
		if (a == 1){ 
			while((i++)<n){
			cout<<i<<" "<< p->pole.a << "   " << p->pole.b << "   "  << p->pole.c << "   "  << p->pole.d << endl;
			p = p->next;
			}
			i-=2;
    	}
    	else break;
		}
		break;
	}
return;
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
		point->pole = p->pole;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		point->ser = NULL;
		up = YES;
	}
	else 
			if (strncmp(point->pole.d, p->pole.d, 3) > 0) {
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
							up = NO;
						}
			}	
			}
		else {
		if (strncmp(point->pole.d, p->pole.d, 3) < 0) { 
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
								up = NO;
							}
						}
					}
				}
		}
			else {
				if (strncmp(point->pole.d, p->pole.d, 3) == 0){
					addAVL(p, point->ser);
				}
			}
		}
}


void Obhod(vertex *v) {
	if(v==NULL)
		return ;
		else {
			Obhod(v->left);
			cout << v->pole.a << " " << v->pole.b << " " << v->pole.c << " " << v->pole.d << " " << endl;
			Obhod(v->ser);
			Obhod(v->right);
			}
	}

void massive(spis *p){
	spis **mas;
	mas = new spis*[P];
	for (int i = 0; i < P; i ++){
		mas[i]= (p);
		p = p->next;
	}
	search(mas, 0, P-1);
}

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
	
void search(spis **arr, int left, int right) {
	int v = 0, midd = 0, find = 0;
	cin >> v;
	spis *key = arr[v];
	cout << key->pole.a << endl;	
	for (v = 0; v < P; v++) {
		while ( left < right ) {
			midd = (left + right) / 2;
			if (strncmp(key->pole.a, arr[v]->pole.a, 3) < 0) left = midd + 1;
			else right = midd;
		}
	if (strncmp(key->pole.a, arr[v]->pole.a, 3) == 0) {
		find += 1;
		push_queue(arr[v], &tail);
		}
		}
		tree = NULL;
		for (int m = 0; m < find; m ++) {
			if (head != NULL) {
				addAVL(head, tree);
				head = head->next;
				}
    	}
	
}

void find (vertex *root, char data[22]) {
	if (root == NULL) {
		return;
	}
	else if (strncmp (data, root->pole.d, 3) < 0){
		find(root->left, data);
	}
	else if (strncmp(data, root->pole.d, 3) > 0){
		find(root->right, data);
	}
	else if (strncmp(data, root->pole.d, 3) == 0){
		cout << root->pole.a << " " << root->pole.b << " " << root->pole.c << " " << root->pole.d << " " << endl;
		find(root->ser, data);
	}
}

typedef std::pair<char,double> data_t;

bool second_less(const data_t& d1, const data_t& d2) {
 	return d1.second < d2.second;
	}

void ReadBase(vector<data_t> &P_Vect){
	FILE *Base;
	map<char,double> DigitP;
	map<char,double>::iterator Found;
	char str;
	Base=fopen("testBase3.dat","rb");
	if(Base==NULL) {
		cout<<endl<<"Error open base"<<endl;
		exit(1); 
	}
	else {
	 	cout<<endl<<"File base is OPEN "<<endl;
		}
	int count=0;
	int count_struct=-1;
	while (!feof(Base)) {
		count_struct++;
		for(count = 0; count < 30; count++){
			fread(&str, sizeof(char), 1, Base);
				Found = DigitP.find(str);			
				if(Found == DigitP.end()){
					DigitP.insert(pair<char,int>(str,1));
					}
					else {
					(*Found).second++;
					}
			}
	}
	double sum=0;
	for(map<char,double>::iterator it = DigitP.begin(); it != DigitP.end(); it++){
		sum+=(*it).second;
	}
	double P_multipl = 1/(double)sum;
	double control = 0;
	int i = 0;
	for(map<char,double>::iterator it = DigitP.begin(); it != DigitP.end(); it++, i++){
		P_Vect.push_back((*it));
		P_Vect[i].second *= P_multipl;
		}
	
	for(int i = 0; i < P_Vect.size(); i++){
		control += P_Vect[i].second;
	}
}

double Entropy(vector<data_t> &P){
	double sum=0;
	for(int i=0;i<P.size();i++){
		sum+=(P[i].second*log(P[i].second)/log(2));
	}	
	sum*=-1;
	return sum; 
}

double SrDlin(vector<data_t> &P,int *L){
	double sum=0;
	for(int i=0;i<P.size();i++){
		sum+=P[i].second*L[i];
	}
	return sum;
}

int Mediana(int L,int R,vector<data_t> &P){
	double Sl=0;
	for(int i=L;i<R;i++){
		Sl+=P[i].second;
	}
	double Sr = 0; 
	int m = R;
	while(Sl >= Sr){
		m--;
		Sl-=P[m].second;
		Sr+=P[m].second;
	}
	return m;
}


void Fano(int L, int R, int k, vector<data_t> &P, char **C, int *lenght) {
	if(L < R) {
		k++;
		int m = Mediana(L, R, P);
		for(int i = L; i <= R; i++) {
			 	if(i <= m) {
				C[i][k] = 0 + '0'; 
				lenght[i]++;
				}
				else {
					C[i][k] = 1 + '0'; 
					lenght[i]++;
					}
		}
		Fano(L, m, k, P, C, lenght);
		Fano(m+1, R, k, P, C, lenght);
	}
}

void CoddingBase() {
	vector<data_t> P, P_2;
	ReadBase(P);
	P_2 = P;
	sort(P.begin(), P.end(), second_less);
	reverse(P.begin(),P.end());
	int size = P.size();
	
	char **C_Fano = new char*[size];
	int *L_Fano = new int[size];
	for(int i = 0; i < size; i++){
		C_Fano[i] = new char[30];
		L_Fano[i] = 0;
		for(int j = 0; j < 30; j++){
			C_Fano[i][j] = '\0';
		}
	}
	Fano(0, size-1, 1, P, C_Fano, L_Fano);
	for(int i = 0; i < size; i++) {
	    cout << i + 1 << "\t";
		cout << P[i].first << "\t";
		cout << P[i].second << "\t";
		for(int j = 0; j < 30; j++){
			cout<<C_Fano[i][j];
			}
			cout<<"\t"<<L_Fano[i]<<endl;
		}
	cout << endl << "Entropy:  " << Entropy(P) << endl;
	cout << endl << "Average length:  " << SrDlin(P, L_Fano) << endl << endl;
	delete []L_Fano;
}

int main() {
	FILE *fp;
	fp=fopen("testBase3.dat", "rb");
	int b = 0, v;
	record2* mas2 = new record2[P];
    fread(mas2, sizeof(record2), P, fp);
    spis* head = spisok(mas2, P);
	char word[22];
	system("cls");
	cout << "1.No sorting" << endl;
	cout << "2.Sorting" << endl;
	cout << "3.Coding base?" << endl;
	cout << "4.Exit" << endl;
	cin >> v;
	int ans = 0;
	switch(v){
		case 1:
			system("cls");
			print_spis(head);
			break;
		case 2:
			digitalSort(head);
			cout << endl << "Print base? (1 - yes)" << endl;
			cin >> ans;
			if (ans==1){
				print_spis(head);
			}
			massive(head);
			cout << endl << "TREE:" << endl << endl;
			Obhod(tree);
			cin >> word;
			cout << word;
			find (tree, word);
			break;
		case 3:
			CoddingBase();
			break;
		case 4:
			exit(0);
			break;
		}
	system ("pause");
	return 0;
}


