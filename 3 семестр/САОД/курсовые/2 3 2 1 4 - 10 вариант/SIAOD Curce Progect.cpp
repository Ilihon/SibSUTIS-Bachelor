
#define YES true
#define NO false

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


const int M=256;
int sum=0;
const int number=81;
int code[number][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;

struct Base
{
	char FIO[30];
	short int Department;
	char Position[22];
	char Date[10];
};

struct list {
	list* next;
	Base* copydata;
};

struct List {
	List* next;
	List* pred;
	Base* Data;
};

struct queue {
	List* head;
	List* tail;
};

struct vertex
{
	Base *data;
	vertex *next;
	int bal;
	vertex *left;
	vertex *right;
};

struct GM_code {
	char a;
	float p;
	float q;
	int l;
};
GM_code A[M];
GM_code B[number];

vertex *root = NULL;
bool up = NO;

void LRprint(vertex* x);
void addAVL(Base* data, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);
void TreeSearch (vertex* p, char data[30]);

void BaseCoding();
void CodePrint();
void CodeBase();

int compare(Base* A, Base* B) {
	if (strcmp(A->Date, B->Date) == 0) {
		return strcmp(A->Date, B->Date);
	}
	else if (strcmp(&A->Date[6], &B->Date[6]) != 0) {
		return strcmp(&A->Date[6], &B->Date[6]);
	}
	else if (A->Date[3] - B->Date[3] != 0) {
		return A->Date[3] - B->Date[3];
	}
	else if (A->Date[4] - B->Date[4] != 0) {
		return A->Date[4] - B->Date[4];
	}
	else if (A->Date[0] - B->Date[0] != 0) {
		return A->Date[0] - B->Date[0];
	}
	else if (A->Date[1] - B->Date[1] != 0) {
		return A->Date[1] - B->Date[1];
	}
	return 0;
}

void QuickSort(Base* IndexArray[], int left, int right)
{

	register int i, j;
	Base* x;
	Base* temp;

	i = left; j = right;
	x = IndexArray[(left + right) / 2];

	do {
		while ((compare(IndexArray[i], x) < 0) && (i < right))
			i++;
		while ((compare(IndexArray[j], x) > 0) && (j > left))
			j--;
		if (i <= j) {
			temp = IndexArray[i];
			IndexArray[i] = IndexArray[j];
			IndexArray[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (left < j)
		QuickSort(IndexArray, left, j);
	if (i < right)
		QuickSort(IndexArray, i, right);
}

void addQueue(list*& head, Base* data) {//Ð”Ð¾Ð±Ð°Ð²Ð»ÐµÐ½Ð¸Ðµ Ð² Ð¾Ñ‡ÐµÑ€ÐµÐ´ÑŒ
	if (head == NULL) {
		head = new list;
		head->copydata = data;
		head->next = NULL;
		return;
	}
	list* now = head;
	while (now->next != NULL) {
		now = now->next;
	}

	now->next = new list;
	now->next->copydata = data;
	now->next->next = NULL;
}

int Binary_Search(Base* IndexArray[], char *key)   // Ð‘Ð¸Ð½Ð°Ñ€Ð½Ð¸Ðº Ð² ÐºÐ¾Ñ‚Ð¾Ñ€Ð¾Ð¼ Ñ‚Ñ€Ð°Ð±Ð»Ð°
{
	int Left = 0, Right = 4000, Middle = 0;
	list* queue = NULL;
	char buffer[10];
	int year_pos=0;
	while (Left < Right)
	{
		Middle = (Left + Right) / 2;
		
		
		year_pos=strchr(IndexArray[Middle]->Date, '-')-IndexArray[Middle]->Date; //ÊËÞ× ÏÎÈÑÊÀ ÃÎÄ Â ÄÀÒÅ	
   		strcpy(buffer,IndexArray[Middle]->Date);
    	buffer[year_pos]='a';
    	year_pos=strchr(buffer, '-')-buffer;
    	buffer[0]=IndexArray[Middle]->Date[year_pos+1];
    	buffer[1]=IndexArray[Middle]->Date[year_pos+2];
    	
		if ( strncmp(buffer,key,2)<0) 
			Left = Middle+1;
		else Right = Middle-1;
	}
	if(Right==-1)
		Right++;
	if(Right==4000){
		cout << "Can't find that year'" << endl;
		return -1;
	}
	year_pos=strchr(IndexArray[Right]->Date, '-')-IndexArray[Right]->Date;
	strcpy(buffer,IndexArray[Right]->Date);
	buffer[year_pos]='a';
	year_pos=strchr(buffer, '-')-buffer;
	buffer[0]=IndexArray[Right]->Date[year_pos+1];
	buffer[1]=IndexArray[Right]->Date[year_pos+2];
    
	int i = 0;
	if(strncmp(buffer,key,2)!=0){
		cout << "Can't find that year'" << endl;
		return -1;
	}
	else
	return Right;
}
void Print(Base* IndexArray[])
{
	int P = 0;
	system("cls");
	cout << "1.Conclusion to 20" << endl;
	cout << "2.Scrolling" << endl;
	cout << "3.Search" << endl;
	cout << "4.Exit" << endl;
	int bsearch_start=0;
	int bsearch_end=0;
	cin >> P;
	switch (P)
	{
	case 1:
	{
		int temp = 0;
		int answer;
		for (int i = 0; i < 4000; i++) {
			cout << i + 1 << "\t" << IndexArray[i]->FIO << "\t" << IndexArray[i]->Department << "\t" << IndexArray[i]->Position << "\t" << IndexArray[i]->Date << endl;
			//cout << i + 1 << "\t" << arr[i].FIO << "\t" << arr[i].Department << "\t\t" << arr[i].Position << "\t" << arr[i].Date << endl;
			temp++;
			if (temp % 20 == 0) {
				cout << "Continue?" << endl << "1=Yes, 0=No" << endl;
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
					cout << "Misklik or do you really want to exit the program? " << "1 fo yes, 0 fo no" << endl;
					cin >> s;
					if (s == 1) {
						break;
					}
					if (s == 0) {
						cout << "Moving next" << endl;
						continue;
					}
					if ((s != 1) & (s != 0)) {
						cout << "You missed again. Closing." << endl;
						break;
					}
				}
			}
		}
		break;
	}
	case 2:
	{

		for (int i = 0; i < 4000; i++) {
			cout << i + 1 << "\t" << IndexArray[i]->FIO << "\t" << IndexArray[i]->Department << "\t\t" << IndexArray[i]->Position << "\t" << IndexArray[i]->Date << endl;
			//cout << i + 1 << "\t" << arr[i].FIO << "\t" << arr[i].Department << "\t\t" << arr[i].Position << "\t" << arr[i].Date << endl;
			if (_kbhit())
				if (_getch() == 13) {
					cout << "Stopped " << endl << "Continue? (Double enter for yes)" << endl;
					cout << "To exit press Esc" << endl;
					if (_getch() == 27) {
						break;
					}
					if (_getch() == 13) {
						continue;
					}
					if ((_getch() != 13) && (_getch() != 27)) {
						int s;
						cout << "Misklik or do you really want to exit the program? " << "1 fo yes, 0 fo no" << endl;
						cin >> s;
						if (s == 1) {
							break;
						}
						if (s == 0) {
							cout << "Moving next" << endl;
							continue;
						}
					}
				}
			if (i == 3999) {
				cout << "End of file" << endl;

			}
		}
		break;
	}
	case 3:
	{
		char key[10];
		cout << "Enter Sort Key: ";
		cin >> key;
	 	bsearch_start = bsearch_end = Binary_Search(IndexArray, key);
		
		char buffer[10];
		int year_pos=0;
		if(bsearch_start != -1){
			
			do{
				bsearch_end++;
				if(bsearch_end==4000){
					break;
				}
				year_pos=strchr(IndexArray[bsearch_end]->Date, '-')-IndexArray[bsearch_end]->Date; //ÊËÞ× ÏÎÈÑÊÀ ÃÎÄ Â ÄÀÒÅ	
		   		strcpy(buffer,IndexArray[bsearch_end]->Date);
		    	buffer[year_pos]='a';
		    	year_pos=strchr(buffer, '-')-buffer;
		    	buffer[0]=IndexArray[bsearch_end]->Date[year_pos+1];
		    	buffer[1]=IndexArray[bsearch_end]->Date[year_pos+2];
			   	if(strncmp(buffer,key,2)!=0){
			  		break;
				}
			}
			while(YES);
			
			cout <<endl <<endl<<"Founded "<<bsearch_end-bsearch_start <<" pozitions ("<< bsearch_start<< " - "<< bsearch_end-1<<")"<<endl;
			for(int i=bsearch_start;i<bsearch_end;i++){
				cout << "Sirname has been founded: "<<i<<" "<<IndexArray[i]->FIO<<"  "<<IndexArray[i]->Department<<"  "<<IndexArray[i]->Position<<"  "<<IndexArray[i]->Date<<endl;
				addAVL(IndexArray[i], root); //ÊËÞ× ÄÎÁÀÂËÅÍÈß - ÏÅÐÂÛÅ 3 ÁÓÊÂÛ ÈÌÅÍÈ	
			}
			system("PAUSE");
			
			LRprint(root);
			
			cout <<"What name should we find?" <<endl;
			char AVL_key[30];
			cin >> AVL_key;
			TreeSearch(root,AVL_key);
			
			
		}

		system("PAUSE");
		break;
	}
	case 4:
	{
		system("PAUSE");
		break;
	}
	default:
	{
		system("cls");
		cout << "Invalid number entered" << endl;
		system("PAUSE");
		system("cls");
		break;
	}
	}
}

int Menu()
{
	const int Size = 4000;
	FILE* fp;
	fp = fopen("testBase2.dat", "rb");
	Base* IndexArray[Size];
	Base OriginArray[Size];
	fread(OriginArray, sizeof(Base), 4000, fp);
	for (int i = 0; i < Size; i++) {
		IndexArray[i] = &OriginArray[i];
	}
	//fopen_s(&fp, "../testBase2.dat", "rb");
	//Base* arr;
	//arr = new Base[Size];
	//fread(arr, sizeof(Base), 4000, fp);
	int SoD;
	cout << "1.Standard list\n2.Sorted list\n3.Code\n4.Exit" << endl;
	cin >> SoD;
	switch (SoD)
	{
	case 1:
	{
		Print(IndexArray);
		//Print(arr);
		break;
	}
	case 2:
	{
		QuickSort(IndexArray, 0, Size - 1);
		//QuickSort(arr, 0, Size - 1);
		Print(IndexArray);
		//Print(arr);
		break;
	}
	case 3:
		{
		BaseCoding();
		CodeBase();
		CodePrint();
		system("PAUSE");
		break;
	}
	case 4:
	{
		system("PAUSE");
		return 0;
	}
	default:
	{
		system("cls");
		cout << "Invalid number entered\nPlease enter numder again" << endl;
		system("PAUSE");
		system("cls");
		Menu();
		break;
	}
	}
	return 0;
}

int main()
{
	Menu();
	return 0;
}


void CodeBase() {
	FILE *fp, *fcoded;
    fp = fopen("testBase2.dat", "rb");
    fcoded = fopen("BaseCoded.dat", "wb");
	char buffer;
	while (!feof(fp)) {
		fscanf(fp, "%c", &buffer);
		fcompression++;
		for (int i = 0; i < number; i++) {
			if (buffer == B[i].a) {
				for (int j = 0; j < B[i].l; j++) {
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
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nÊîä Ãèëáåðòà-Ìóðà: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| Íîìåð Ñèìâîëà | Ñèìâîë | Âåðîÿòíîñòü |     Êîäîâîå ñëîâî    | Äëèíà êîäîâîãî|\n");
	printf("|               |        |             |                      |     ñëîâà     |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	for (int i = 0; i < number; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, B[i].a, B[i].q);
		for (int j = 0; j <= B[i].l; j++)
			printf("%d", code[i][j]);
		for (int j = B[i].l + 1; j < 18; j++)
			printf(" ");
		printf("    |  %7d      |\n", B[i].l);
		printf("|-----------------------------------------------------------------------------|\n");
		lgm += B[i].p * B[i].l;
	}	
	
	printf("________________________________________________\n");
	printf("|  Ýíòðîïèÿ  |  Ñðåäíÿÿ äëèíà  |  Êîýô ñæàòèÿ  |\n");
	printf("|____________|_________________|_______________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression/cfcompression);
	printf("|____________|_________________|_______________|\n");
	
	cout << endl << endl << entropy+2 <<" > "<< lgm <<endl <<endl;
	
}


void BaseCoding(){
	
	int i,j;
	FILE *fp;	
	fp=fopen("testBase2.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].a = 0;
		A[i].p = 0;
		A[i].q = 0;
		A[i].l = 0;
	}
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		//printf("%c",c);
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].a = c;
		A[c+128].p +=1;
		sum++;
	}
	fclose(fp);	
	
	for (i = 0, j=0; i < M; i++){
		if(A[i].p!=0){
			A[i].p /=sum;
			B[j]=A[i];
			entropy += A[i].p * abs(log(A[i].p) / log(2));
			//cout <<j <<" "<< B[j].a<< " "<< B[j].p <<endl;
			j++;
		}
	}
	
	for (i = 0; i < number; i++){
		B[i].q = B[i-1].q + B[i].p/2;
		B[i].l = ceil(-log(B[i].p) / log(2)) + 1;
	}
	
	for (i = 0; i < number; i++)
	{
		for (j = 0; j <= B[i].l; j++)
		{
			B[i].q *= float(2);
			code[i][j] = floor(B[i].q);
			while (B[i].q >= 1)
				B[i].q -= 1;
		}
	}
	
}


void TreeSearch (vertex* p, char data[30]){
		if(p!=NULL) {                ///Ïîèñê ýëåìåíòà
        	if(strncmp(data,p->data->FIO,3)<0){
                    TreeSearch(p->left,data);
            }else{
                    if(strncmp(data,p->data->FIO,3)>0){
                    	TreeSearch(p->right,data);
                }else{
					cout << "Sirname has been founded: "<<" "<<p->data->FIO<<"  "<<p->data->Position<<"  "<<p->data->Department<<"  "<<p->data->Date<<endl;
                    TreeSearch(p->next,data);
				}
            }
        }
}

void LRprint(vertex* x){
	if (x) {
		LRprint(x->left);  
    		cout<<"  "<<x->data->FIO<<"  "<<x->data->Position<<"  "<<x->data->Department<<"  "<<x->data->Date<<endl;
		LRprint(x->next);
		LRprint(x->right); 
	}
}

void addAVL(Base* data, vertex *&point){
	if (point == NULL) {
		point = new vertex;
		point->data = data;
		point->bal = 0;
		point->left = NULL;
		point->right = NULL;
		point->next = NULL;
		up = YES;
	}
	else{
		if(strncmp(point->data->FIO, data->FIO,3)==0){
			addAVL(data, point->next);
		}
		else{
			if(strncmp(point->data->FIO, data->FIO,3)>0){
				addAVL(data, point->left);
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
			else{ 
				if(strncmp(point->data->FIO, data->FIO,3)<0){
					addAVL(data, point->right);
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
			}
		}
	}
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
