#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <time.h>

using namespace std;
const unsigned short int Page = 20;
int *Weight;

struct record2 {
    char a[30];
    unsigned short int b;
    char c[10];
    char d[22];
};

struct List {
    List* next;
    union {
        record2 data;
        unsigned char Digit[sizeof(data)];
    };
    union {
        unsigned short int data2;
    	unsigned char Deposit[sizeof(data2)];
    };
    List* head;
    List* tail;
};

struct vertex
{
	record2 *data;
	int balance;
	int weight;
	vertex *next;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;

struct coding 
{
    char symbol;
    unsigned int quantity;
    float probability;
    unsigned short int lengthCW = 0;
    char *codeword;
};

void quickSortCoding(coding *A, int R, int L) 
{
    while (L <= R)
    {
        char x = A[L].symbol;
        int i = L;
        int j = R;
        while (i <= j)
        {
            while (A[i].symbol < x)
                i++;
            while (A[j].symbol > x)
                j--;

            if (i <= j)
            {
            	if (A[i].symbol > A[j].symbol){
                char tmp_ch;
                tmp_ch = A[i].symbol;
                A[i].symbol = A[j].symbol;
                A[j].symbol = tmp_ch;

                unsigned int tmp_q;
                tmp_q = A[i].quantity;
                A[i].quantity = A[j].quantity;
                A[j].quantity = tmp_q;

                float tmp_prop;
                tmp_prop = A[i].probability;
                A[i].probability = A[j].probability;
                A[j].probability = tmp_prop;
               
            }
             i++;
                j--;
        }
	}
        if (i < R)
        {
            quickSortCoding(A, R, i);
            R = j;
        }
        else
        {
            quickSortCoding(A, j, L);
            L = i;
        }
    }
}

void Gilbert_Mur(coding *&code, int n){
	float *Q = new float[n];
	
	float pr=0;
	for(int i=0; i<=n; i++){
		Q[i]=pr+(float)code[i].probability/2;
		pr+=code[i].probability;
		code[i].lengthCW=-log2(code[i].probability)+2;
	}
	for(int i=0; i<=n; i++){
		
		code[i].codeword = new char[code[i].lengthCW];
		for(int j=0; j<code[i].lengthCW; j++){
		Q[i]*=2;
		if (Q[i]>1) {
			code[i].codeword[j]='1';
		}
			else if (Q[i]<1){
				code[i].codeword[j]='0';
			}
		code[i].codeword[j+1]='\0';
		if(Q[i]>=1) 
		Q[i]-=1;
		}
	}
}

void tableSymbols(coding *&code, int &numsUnique)
{ 
    int s_byte[256] = {0};
    int totalNums = 0;
    char ch; 

    fstream file("testBase3.dat", ios::in | ios::binary); 

    while (!file.read((char *)&ch, sizeof(ch)).eof())
    {                
        totalNums++;
        if (int(ch) < 0)
            s_byte[int(ch) + 256]++;
        else
            s_byte[int(ch)]++;
    }
    file.close();

    for (int i = 0; i < 256; i++)
        if (s_byte[i] != 0)
            numsUnique++;

    code = new coding[numsUnique];
    unsigned short int temp = 0;
    for (int i = 0; i < 256; i++)
    {
        if (s_byte[i] != 0)
        {
            code[temp].symbol = char(i);
        
            code[temp].quantity = s_byte[i];
            code[temp].probability = (float)s_byte[i] / (float)totalNums;
            temp++;
        }
    }
    quickSortCoding(code, 0, numsUnique - 1);
    Gilbert_Mur(code, numsUnique - 1);
    cout << "Unique Symbols = " << numsUnique << endl;
}

void PrintElems(record2 item) {
    cout << item.a << "   ";
	cout.setf(std::ios::left);
	cout.width(5);
	cout << item.b << "   ";
	cout << item.c << "     ";
	cout << item.d << endl;
}

void ReadList(List** p, unsigned int& size) {
    fstream* file = new fstream;
    file->open("testBase3.dat", ios::in | ios::binary);
    record2* data = new record2;
    List* temp = *p = new List;
    file->read((char*)data, sizeof(*data)).eof();
    temp->data = *data;
    temp->data2 = data->b;
    size++;
    while (!file->read((char*)data, sizeof(*data)).eof()) {
        temp->next = new List;
        temp = temp->next;
        temp->data = *data;
    	temp->data2 = data->b;
        size++;
    }
    temp->next = 0;
    file->close();
}

void PrintList(List* head) {
    if (head == NULL){
		return;
	}
	List *p = head;
	int j = 0;
	int key;
	int i = 20;
	do {
    	system("CLS");
    	for (; (j < i) && (p != NULL); j++, p = p->next) {
    		cout.setf(std::ios::right);
    		cout.width(4);
   			cout << (j + 1) << ")" << "  ";
    		PrintElems(p->data);
    	}
    	do {
    		switch (key = getch()) {
    			case 75: // left
        		if (j != 20) {
        			i = i - 20;
        			j = i - 20;
          			p = head;
          			for (int f = 0; f < j; f++)
            			p = p->next;
        		} else
          			key = 0;
        		break;
      			case 77: // right
        		if (p != NULL) {
          			i = i + 20;
        		} else
         	 		key = 0;
        		break;
      		}
   		} while ((key != 75) && (key != 77) && (key != 27));
	} while (key != 27);
		system("CLS");
}

void PrintMas(record2* mas) {
	cout << "20 / full ? (1/2)" << endl;
	int b = _getch();
	int c = 0;
	if (b == '1') {
		for (int i = 0; i < 4000; i += 20) {
			while (c < 20) {
				cout.setf(std::ios::right);
	    		cout.width(4);
	   			cout << (c + i + 1) << ")" << "  ";
	    		PrintElems(mas[c+i]);
				c++;
			} c = 0;
			cout << "continue?(1/2)";
			char a = _getch();
			cout << endl;
			if (a == '2') {
				break;
			}
		}
	}
	else if (b == '2') {
		for (int i = 0; i < 4000; i++) {
			cout.setf(std::ios::right);
	    	cout.width(4);
	   		cout << (i + 1) << ")" << "  ";
	    	PrintElems(mas[c+i]);
			if (_kbhit()) {
				cout << "continue?(%/0) : ";
				char a = _getch();
				if (!a) {
					break;
				}
			}
		}
	}
	/*	
    if (head == NULL){
		return;
	}
	List *p = head;
	int j = 0;
	int key;
	int i = 20;
	do {
    	system("CLS");
    	for (; (j < i) && (p != NULL); j++, p = p->next) {
    		cout.setf(std::ios::right);
    		cout.width(4);
   			cout << (j + 1) << ")" << "  ";
    		PrintElems(p->data);
    	}
    	do {
    		switch (key = getch()) {
    			case 75: // left
        		if (j != 20) {
        			i = i - 20;
        			j = i - 20;
          			p = head;
          			for (int f = 0; f < j; f++)
            			p = p->next;
        		} else
          			key = 0;
        		break;
      			case 77: // right
        		if (p != NULL) {
          			i = i + 20;
        		} else
         	 		key = 0;
        		break;
      		}
   		} while ((key != 75) && (key != 77) && (key != 27));
	} while (key != 27);
		system("CLS");
		*/
}
void DigitalSort(List** S) {
    List** unSort = S;
    int KDI[8];
    KDI[7] = 30;
    KDI[6] = 31;
    KDI[0]=38;
    KDI[1]=39;
    KDI[2]=35;
    KDI[3]=36;
    KDI[4]=32;
    KDI[5]=33;
    int L = 8;
    List q[256];
    List* p;
    unsigned char d;
    int k;
    for (int j = L - 1; j >= 0; j--) {
        for (int i = 0; i < 256; i++) {
            q[i].tail = (List*)&(q[i].head);
        }
        k = KDI[j];
        while ((*unSort) != 0) {
            d = (*unSort)->Digit[k];
            q[d].tail->next = *S;
            q[d].tail = *S;
            (*unSort) = (*unSort)->next;
        }
        p = (List*)S;
        for (int i = 0; i < 256; i++) {
            if (q[i].tail != (List*)&(q[i].head)) {
                p->next = q[i].head;
                p = q[i].tail;
            }
        }
        p->next = 0;
	}
	int l=sizeof(unsigned short int);
    unsigned char KDI2 [ sizeof (unsigned short int) ];
    for(int i=0; i < sizeof (unsigned short int); i++){
		KDI2[i] = i;
	}
    List** preSort = S;
    List q2[256];
    List* p2;
	for (int j=l-1; j>0; j--) 
    {
		for(int i=0; i<256; i++) 
			q2[i].tail=(List*)&q2[i].head;
		k=KDI2[j];
        while ((*preSort) != 0) {
            d = (*preSort)->Deposit[k];
            q2[d].tail->next = *S;
            q2[d].tail = *S;
            (*preSort) = (*preSort)->next;
        }
        p2 = (List*)S;
        for (int i = 0; i < 256; i++) {
            if (q2[i].tail != (List*)&(q2[i].head)) {
                p2->next = q2[i].head;
                p2 = q2[i].tail;
            }
        }
        p2->next = 0;
	}
	
}

void BubbleSort(int search_start, int result_index)
{
    int i, j,v;
    for (i = search_start; i < result_index - 1; i++) {
        for (j = result_index - 1; j > i; j--) {
            if (Weight[j] > Weight[j - 1]) {
                v = Weight[j];
                Weight[j] = Weight[j - 1];
                Weight[j - 1] = v;
            }
        }
    }
}

int compare_date(record2 *a, record2 *b) {
	if(strcmp(&a->c[6], &b->c[6]) != 0){
		return strcmp(&a->c[6], &b->c[6]);
	}
	return 0;
}

int compare_date_tree(record2 *a, char *b) {
	if(strncmp(&a->c[6], b,2) != 0){
		return strcmp(&a->c[6], b);
	}
	return 0;
}

void PrintTree(vertex *p){
	if(p != NULL){
		PrintTree(p -> left);
		cout << p->data->a << "\t" << p->data->b << "\t\t" << p->data->c << "\t" << p->data->d << endl;
		PrintTree(p -> next);
		PrintTree(p -> right);
	}
}

void SearchTree(vertex* p, char *data){
	if(p!=NULL)           
    {
        if (compare_date_tree(p->data, data) == 0) {
			cout << p->data->a << "\t" << p->data->b << "\t\t" << p->data->c << "\t" << p->data->d << endl;
			SearchTree(p->next, data);
		}
		else if (compare_date_tree(p->data, data) > 0) {
			SearchTree(p->left, data);
		}
		else if (compare_date_tree(p->data, data) < 0) {
			SearchTree(p->right, data);
		}
	}
}

void delete_tree(vertex *&p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->next);
		delete_tree(p->right);
		delete p;
	}
}

void A1(vertex*& p, record2 *data, int w) {
    if (p == NULL) {
        p = new vertex;
        p->data = data;
        p->weight = w;
        p->left = NULL;
        p->right = NULL;
        p->next = NULL;
    }
    else
    if(compare_date(p->data, data) == 0){
		A1(p->next, data, w);
	}
    else if (compare_date(p->data, data) > 0) {
        A1(p->left, data, w);
    }
    else if (compare_date(p->data, data) < 0) {
        A1(p->right, data, w);
    }
}

int Search(record2*& arr, int key) {
    int l = 0, r = 4000, m = 0;
	while (l <= r) {
		m = (int)((l + r) / 2);
		if (arr[m].b == key) {
			return m;
		}
		if (arr[m].b < key) {
			l = m + 1;
		}
		else r = m - 1;
	}
	return -1;
}
/*
void search(List_A1 *p, char* key) //��������� ������ � ����
{ 
	List_A1 *l=p; List_A1 *r=p;
	char k[3];
	k[0]=p->data.d[0];
	k[1]=p->data.d[1];
	k[2]=p->data.d[2]; 
	while (p!=NULL) 
		{ 
			if (strcmp(key, k)<0) //���� ���� ������ ������ �� �������� �����
				{ 
					p=p->left;
					if (p!=NULL) {
		 			k[0]=p->data.d[0];
	 	 			k[1]=p->data.d[1];
	 	 			k[2]=p->data.d[2];
					}
				} //�� �� ���� ����� � ��������� ������ � ����� �����
			else if (strcmp(key, k)>0) //�� ���� ���� ������, �� �� ���� ������� � ��� �� ���������
				{ 
					p=p->right;
	 	 			if (p!=NULL) {
					k[0]=p->data.d[0];
	 	  			k[1]=p->data.d[1];
	 	 			k[2]=p->data.d[2];
					}
				} 
			else if (strcmp(key, k)==0 && p->finded != 1) //�� ���� ����� ��� �����, �� �� ������ ���...
				{
					cout<<p->data.a << "   "; cout << p->data.b << "   " << p->data.c << "     " << p->data.d <<endl; //������� ������ ���� �����
					p->finded = 1;
					if (p->left != NULL) {
				 		l=p->left;
						search(l, key); } //���������� �� ������� ������ ����� ��������� � ����� ������
					if (p->right != NULL) {
						r=p->right;
						search(r, key); //���������� ������ ��������� �� ������� ������, ��� � ���� ����� ����������� ��� �� �� �����
					}	
					if (p->left == NULL && p->right == NULL) break;
				}
				else if (strcmp(key, k)==0 && p->finded == 1) break;	
		}
}
*/
void printTableSymbols(coding *code, int numSymbols)//����� ���������
{

    cout << "                                                                                                                          "
         << "\n";
    cout << "|" << setw(11) << ""
         << "|" << setw(18) << ""
         << "|" << setw(26) << ""
         << "|" << setw(26) << ""
         << "|" << setw(32) << ""
         << "|"
         << "\n";
    cout << "|"
         << "Sym's Code "
         << "|"
         << " Times in text    "
         << "|"
         << "   Probability            "
         << "|"
         << "       Length (L)         "
         << "|"
         << "          Codeword              "
         << "|"
         << "\n";
    cout << "|" << setw(11) << ""
         << "|" << setw(18) << ""
         << "|" << setw(26) << ""
         << "|" << setw(26) << ""
         << "|" << setw(32) << ""
         << "|"
         << "\n";
    cout << "                                                                                           "
         << "\n";

    float entropy = 0;
    double averageLength = 0;
    for (int i = 0; i < numSymbols; i++)
    {
        entropy += code[i].probability * log2(code[i].probability);
        averageLength += (double)code[i].lengthCW * (double)code[i].probability;
        cout << "|"
             << setw(7) << (int)(unsigned char)code[i].symbol << setw(4) << ""
             << "|"
             << setw(15) << code[i].quantity << setw(3) << ""
             << "|"
             << setw(23) << fixed << code[i].probability << setw(3) << ""
             << "|"
             << setw(23) << code[i].lengthCW << setw(3) << ""
             << "|"
             << setw(29) << code[i].codeword << setw(3) << ""
             << "|"
             << "\n";
    }
    cout << "                                                                                                                          "
         << "\n";

    cout << "  Entropy: " << -entropy << "\n";
    cout << "  Sheight: " << averageLength << "\n";
}

void copy_base(List *a, List *b) {
	for (int i = 0; i < 4000; i++) {
		a = a->next;
		b->next = new List;
		b = b->next;
		b->data = a->data;
	}
	b->next = NULL;
}

void indexMas(List *SortList, record2*arr){
	for (int i = 0; SortList != 0; SortList = SortList->next, i++)
		arr[i]= SortList->data;
}

int main() {
    system("chcp 866");
    system("cls");
    srand(time(0));
    int a=0, size2 = 0;
    List* OrigList = new List;
    List* SortList  = new List;
    List* IndexList  = new List;
    unsigned int size = 0;
    int key;
    int search_start = 0;
        
    ReadList(&OrigList, size);
	SortList = OrigList;
    DigitalSort(&SortList);
	
	record2* arr;
    arr = new record2[size];
    indexMas(SortList, arr);
	
    while (a!=6) {
	    system("CLS");
	    cout << "	1 - Print list" << endl << "	2 - Sort list" << endl << "	3 - Find in list" 
		<< endl <<  "	4 - Print tree" << endl << "	5 - Code (Gilbert-Moore)" << endl << "	6 - Exit " << endl;
		cin >> a;
		switch(a)
		{
		    case 1: {
				system("CLS");
		       	PrintList(OrigList);
		       	break;
			}
		    case 2: {
				system("CLS");
		        PrintMas(arr);
		        break;
			} 
		    case 3: {
		    	system("CLS");
		    	cout << "   Enter the deposit: ";
		    	cin >> key;
		    	int result_index = Search(arr, key);
		    	if(result_index == -1) {
					cout << "Nothing found" << endl;
				} else {
					do {
						if(result_index == 0) {
							break;
						} else {
							result_index--;
						}
						if(arr[result_index].b != key) {
							result_index++;
							break;
						}
					} while(true);
					search_start = result_index;
					do {
						result_index++;
						if(result_index == size) {
							break;
						}
						if(arr[result_index].b != key) {
							break;
						}
					} while(true);
					if (root != NULL) {
						delete_tree(root);
						root = NULL;
					}
					Weight = new int[size];
		            for (int i = search_start; i < result_index; i++) {
		                Weight[i] = rand() % 99 + 1;
		            }
		            BubbleSort(search_start, result_index);
					cout << endl << endl<< (result_index - search_start) << " recordings (" << (search_start + 1) << " " << result_index << ")" <<endl;
					for (int i = search_start; i < result_index; i++) {
						PrintElems(arr[i]);
		                A1(root, &arr[i], Weight[i]);
					}
				}
		    	break;
		    }
		    
		    case 4: {
		    	system("CLS");
		        PrintTree(root);
		        cout << endl << "Enter year:" << endl;
				char date[2];
				cin >> date;
				SearchTree(root,date);
		   		break;
		   	}
		    case 5: {
		    	system("CLS");
		        int numSymbols = 0;
		        coding *codeGM = 0;
		        tableSymbols(codeGM, numSymbols);
		        printTableSymbols(codeGM, numSymbols);
				break;
			}
		}
	   	system("PAUSE");
	}
    return 0;
}
