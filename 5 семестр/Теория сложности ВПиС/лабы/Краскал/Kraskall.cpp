#include <iostream>
#include <fstream> 
#include <iomanip>
#include <vector>

using namespace std;

int** matrix;
int N;
int* mas;
int sum = 0;
int oper = 0;

struct ostov
{
	int x;
	int y;
	int w;
};

struct list
{
	ostov* ost;
	list* next;
};

bool prov();

int main()
{
	ifstream input("input2.txt");
	input >> N;
	matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N] {};
	}
	for (int i = 0; i < N + 1; i++)
		cout << setw(3) << i;
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << setw(3) << i + 1;
		for (int j = 0; j < N; j++) {
			input >> matrix[i][j];
			if (matrix[i][j] != -1)
				cout << setw(3) << matrix[i][j];
			else cout << setw(3) << "-";
		}
		cout << endl;
	}
	input.close();
	
	system("pause");
	cout << endl;
	
	int j1, j2;
	int min = 1;
	bool flag = true;
	list* mOstov = new list();
	mOstov->next = NULL;
	mOstov->ost = new ostov();
	mOstov->ost = NULL;
	list* l = mOstov;
	mas = new int[N] {};
	for (int i = 0; i < N; i++)
		mas[i] = i + 1;
	/*vector<int> sort_mas;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (matrix[i][j] != -1) {
				sort_mas.push_back(matrix[i][j]);
			}
		}
	}
	for(int i = 0; i < sort_mas.size(); i++){
		cout << sort_mas[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < sort_mas.size()-1; i++){
		int min = sort_mas[i];
		int temp_j = i;
		for (int j = i+1; j < sort_mas.size(); j++){
			if(sort_mas[j]<min){
				min = sort_mas[j];
				temp_j=j;
			}
		}
		int buf = sort_mas[i];
		sort_mas[i] = sort_mas[temp_j];
		sort_mas[temp_j] = buf;
		oper++;
	}
	for(int i = 0; i < sort_mas.size(); i++){
		cout << sort_mas[i] << ' ';
	}
	cout << endl;*/
	while (flag) {
		for (int i = 0; i < N; i++) {
			for (int j = i; j < N; j++) {
				if (matrix[i][j] == min) {
					if (mas[i] != mas[j]) {
						if (mOstov->ost == NULL) {
							mOstov->ost = new ostov();
							mOstov->ost->x = i;
							mOstov->ost->y = j;
							mOstov->ost->w = matrix[i][j];
							l = mOstov;
						}
						else {
							l = l->next;
							l = new list();
							l->ost = new ostov();
							l->next = NULL;
							l->ost->x = i;
							l->ost->y = j;
							l->ost->w = matrix[i][j];
						}
					}
					cout << "(" << i + 1 << "," << j + 1 << ") = " << matrix[i][j];
					if (mas[i] == mas[j]){
						cout << " - no";
					//	oper++;
					}
					else{
						sum+=matrix[i][j];
					//	oper+=N;	
					}
					cout << endl;
					if (mas[i] != mas[j]) {
						int mn;
						int mm;
						//int oper_flag =0;
						if (mas[i] < mas[j]) { 
							mn = mas[i];
							mm = mas[j]; 
						}
						else { 
							mn = mas[j]; 
							mm = mas[i];
						}
						for (int k = 0; k < N; k++) {
							if (mas[k] == mm /*|| mas[k] == mn*/) {
								mas[k] = mn;
								//oper++;
								//oper_flag = 1;
							}
						}
						//oper+=oper_flag;
						flag = prov();
						if (flag == false) {
						cout << "Min sum = " << sum << endl;
						//cout << "oper = " << oper << endl;
						return 0;
						}
					}
				}
			}
		}
		min++;
	}
	system("pause");
	return 0;
}
bool prov() {
	bool flg = false;
	for (int i = 0; i < N - 1; i++)
	{
		if (mas[i] != mas[i + 1]) {
			flg = true;
		}
		cout << mas[i] << " ";
	}
	cout << mas[N-1];
	cout << endl;
	return flg;
}
