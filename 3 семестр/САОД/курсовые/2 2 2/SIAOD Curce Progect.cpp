
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



int compare_date(Base* A, Base* B) {
	if (strcmp(A->Date, B->Date) == 0) {
		return strcmp(A->Date, B->Date);
	}
	else if (strcmp(&A->Date[0], &B->Date[0]) != 0) {
		return strcmp(&A->Date[0], &B->Date[0]);
	}
	else if (A->Date[1] - B->Date[1] != 0) {
		return A->Date[1] - B->Date[1];
	}
	else if (A->Date[3] - B->Date[3] != 0) {
		return A->Date[3] - B->Date[3];
	}
	else if (A->Date[4] - B->Date[4] != 0) {
		return A->Date[4] - B->Date[4];
	}
	else if (A->Date[6] - B->Date[6] != 0) {
		return A->Date[6] - B->Date[6];
	}
	return 0;
}

int compare_name(Base* A, Base* B) {
	char bufferA[30];
	char bufferB[30];
	strncpy(bufferA, A->FIO,3);
	strncpy(bufferB, B->FIO,3);
	return strcmp(bufferB, bufferA);
}


void QuickSort(Base* IndexArray[], int left, int right, int sort)
{
	int i, j;
	Base* x;
	Base* temp;

	i = left; j = right;
	x = IndexArray[(left + right) / 2];

	do {
		if(sort==0){
			while ((compare_name(IndexArray[i], x) < 0) && (i < right))
				i++;
			while ((compare_name(IndexArray[j], x) > 0) && (j > left))
				j--;
		}else{
			while ((compare_date(IndexArray[i], x) < 0) && (i < right))
				i++;
			while ((compare_date(IndexArray[j], x) > 0) && (j > left))
				j--;
		}
		
		if (i <= j) {
			temp = IndexArray[i];
			IndexArray[i] = IndexArray[j];
			IndexArray[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (left < j)
		QuickSort(IndexArray, left, j,sort);
	if (i < right)
		QuickSort(IndexArray, i, right,sort);
}

int Binary_Search(Base* IndexArray[], char *key)   
{
	int Left = 0, Right = 4000, Middle = 0;
	char buffer[10];
	while (Left < Right)
	{
		Middle = (Left + Right) / 2;
		
    	buffer[0]=IndexArray[Middle]->Date[0];
    	buffer[1]=IndexArray[Middle]->Date[1];
    	if (strncmp(buffer,key,2)==0)
    		return Middle;
    	
		if ( strncmp(buffer,key,2)<0) 
			Left = Middle+1;
		else Right = Middle-1;
	}
	return -1;
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
		if(bsearch_start != -1){
			do{
				if(bsearch_start==0){
					break;
				}
				else{
					bsearch_start--;
				}
			   	if(strncmp(IndexArray[bsearch_start]->Date,key,2)!=0){
			   		bsearch_start++;
			   		break;
				}
			}
			while(YES);
			
			do{
				bsearch_end++;
				if(bsearch_end==4000){
					break;
				}
		    	buffer[0]=IndexArray[bsearch_end]->Date[0];
		    	buffer[1]=IndexArray[bsearch_end]->Date[1];
			   	if(strncmp(buffer,key,2)!=0){
			  		break;
				}
			}
			while(YES);
			
			cout <<endl <<endl<<"Founded "<<bsearch_end-bsearch_start <<" pozitions ("<< bsearch_start<< " - "<< bsearch_end-1<<")"<<endl;
			for(int i=bsearch_start;i<bsearch_end;i++){
				cout << "Date has been founded: "<<i<<" "<<IndexArray[i]->FIO<<"  "<<IndexArray[i]->Department<<"  "<<IndexArray[i]->Position<<"  "<<IndexArray[i]->Date<<endl;
				
			}
			system("PAUSE");
		}
		else{
			cout << "Can't find that date" << endl;
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
	int SoD;
	cout << "1.Standard list\n2.Sorted list\n3.Exit" << endl;
	cin >> SoD;
	switch (SoD)
	{
	case 1:
	{
		Print(IndexArray);
		break;
	}
	case 2:
	{
		for(int v=0;v<2;v++)
			QuickSort(IndexArray, 0, Size - 1,v);
		Print(IndexArray);
		break;
	}
	case 3:
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
