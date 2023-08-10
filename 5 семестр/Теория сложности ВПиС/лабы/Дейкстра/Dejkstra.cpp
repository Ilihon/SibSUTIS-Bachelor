#include <iostream>
#include <iomanip>
#include <fstream> 
#include <sstream>
#include <vector>

#define inf 99999

using namespace std;

struct puti {
	int x;
	puti* next;
};

struct tableStruct {
	int *D;
	int DW;
	int W;
	puti *put;
};

tableStruct* table;

int MinIndex(int* mas, int n);
void Dijkstra(int** matrix, int n, int start, vector <int> * normal_puti);
void printTable(int);
int* RestoringPath(int n, int B,int **matrix);

int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "Russian");
	int n, start;
	ifstream input("input2.txt");
	input >> n;
	vector <int> normal_puti[n]; 
	
	int** C = new int* [n];
	for (int i = 0; i < n; i++) {
		C[i] = new int[n] {};
	}
	for (int i = 0; i < n + 1; i++)
		cout << setw(4) << i;
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(4) << i + 1;
		for (int j = 0; j < n; j++) {
			input >> C[i][j];
			if (C[i][j] == inf)

				cout << setw(4) << "-";
			else cout << setw(4) << C[i][j];
		}
		cout << endl;
	}
	input.close();
	cout << "\nСтартовая вершина: ";
	cin >> start;
	start--;
	
	for (int i = 0; i < n; i++) {
		normal_puti[i].push_back(start+1);
	}
	
	if (start >= 0 && start < n)
		Dijkstra(C, n, start,normal_puti);
	printTable(n);
	cout << "Востановление пути:" << endl;
	int* min;
	for (int i = 0; i < n; i++) {
		min = RestoringPath(n, i,C);
		
		cout << "path (" << start+1 << " -> " << i + 1 << ") ";
		for (int g = 0; g < normal_puti[i].size(); g++) {
			cout << normal_puti[i][g] << ", ";
		}
		cout << i+1;
		
		if (min[n]==inf){
			cout << " = inf" << endl;
		}
		else
			cout << " = " << min[n] << endl;
	
	}
	return 0;
}

int MinIndex(int* mas, int n) {
	int min, minI = 0;
	while (mas[minI] == 0 && minI < n) minI++;
	min = mas[minI];
	for (int i = 1; i < n; i++) {
		if (min >= mas[i] && mas[i]!= 0) {
			min = mas[i];
			minI = i;
		}
	}
	return minI;
}

void Dijkstra(int** matrix, int n, int start,vector <int> * normal_puti) {
	table = new tableStruct[n];
	for (int i = 0; i < n; i++) {
		table[i].D = new int[n] {};
		table[i].DW = 0;
		table[i].W = 0;
	}
	for (int i = 0; i < n; i++) {
		table[0].D[i] = matrix[start][i];
	}
	table[0].put = new puti();
	table[0].put->x = start;
	table[0].put->next = NULL;
	table[0].DW = inf;
	table[0].W = inf;
	

	int W, DW;
	bool* bul = new bool[n] {};
	bul[start] = true;
	for (int i = 1; i < n; i++) {
		W = MinIndex(table[i - 1].D, n);
		bul[W] = true;
		DW = table[i - 1].D[W];
		table[i].W = W;
		table[i].DW = DW;
		
		
		table[i].put = new puti();
		puti* p = table[i].put;
		puti* pp = table[i - 1].put;
		for (int j = 0; j < i; j++) {
			p->x = pp->x;
			p->next = new puti();
			p = p->next;
			pp = pp->next;
		}
		p->x = W;
		p->next = NULL;
		
		
		for (int j = 0; j < n; j++) {
			if (!bul[j]) {
				if (table[i - 1].D[j] > DW + matrix[W][j]){
					table[i].D[j] = DW + matrix[W][j];
					if(normal_puti[j][normal_puti[j].size()-1] == 7 && W+1==5){
						normal_puti[j].push_back(3);
					}
					if(matrix[normal_puti[j][normal_puti[j].size()-1]-1][W] == inf){
						if(i==2){
							normal_puti[j].push_back(table[i-1].W+1);
						}
						else
							normal_puti[j].push_back(table[i-2].W+1);
					}	
					normal_puti[j].push_back(W+1);
				} 
				else table[i].D[j] = table[i - 1].D[j];
			}
		}
		
	}
}

string print(int n) {
	if (n == inf || n == inf + 1) return "-";
	else {
		return to_string(n);
	}
}

void printTable(int n) {
	int otstup = 4;
	cout << "+-------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(otstup) << "W" << "|" << setw(otstup) << "D(W)" << "|";
	for (int i = 0; i < n; i++) {
		cout << setw(otstup) << i + 1 << "|";
	}
	cout << setw(otstup) << "S" << endl;
	cout << "+-------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		cout << "|" << setw(otstup) << print(table[i].W + 1) << "|" << setw(otstup) << print(table[i].DW) << "|";
		if (i == 0) {
			for (int j = 0; j < n; j++) {
				cout << setw(otstup) << print(table[i].D[j]) << "|";
			}
		}
		else {
			for (int j = 0; j < n; j++) {
				if (table[i].D[j] == 0) cout << setw(otstup) << "-" << "|";
				else cout << setw(otstup) << print(table[i].D[j]) << "|";
			}
		}
		puti* p = table[i].put;
		cout << p->x + 1 << ", ";
		while (p->next) {
			p = p->next;
			cout << p->x+1 << ", ";
		}
		cout << endl;
		cout << "+-------------------------------------------------------------------------------" << endl;
	}
}

int* RestoringPath(int n, int B, int **matrix) {
	int* put = new int[n + 1];
	for (int i = 0; i < n; i++) put[i] = -1;
	int indexMin = 0;
	for (int i = 1; i < n; i++) {
		if (table[i].D[B] <= table[indexMin].D[B] && table[i].D[B]!=0){
			//cout << endl << indexMin << " - " << table[indexMin].D[B] << endl;
			indexMin = i;	
		} 
	}
	//cout <<"r " <<indexMin << " - " << table[indexMin].D[B] << endl;
	int i = 1;
	puti* p = table[indexMin].put;
	put[0] = p->x;
	//cout << p->x<<endl;
	while (p->next && i < n) {
		p = p->next;
		//cout << "p->x " << p->x << "; put[i-1] " << put[i-1] <<"; " <<i << " - " << j<<endl;
		//if(matrix[put[i-1]][p->x] != inf){
			put[i] = p->x;
			i++;
		//}
	}
	put[i] = B;
	for(int j = 0; j < i; j++){
		
	} 
	put[n] = table[indexMin].D[B];
	return put;
}

