#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int N = 5;

struct vertex
{
	vertex *left;
	vertex *right;
	string data; // слова
	int repeat; // частота
};

vertex *root = NULL;

void SDP(char* data, vertex*&p); // построение СДП + запись частоты
void PrintLR(vertex* x); // обход слева на право

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "\t\t\t Словарь частот встречаемости ключевых" << endl;
	cout << "\t\t\t    слов в тексте программы на Си" << endl;
	cout << "\t\t\t             на базе СДП" << endl;
	cout << "\n\n";


	char buff[100];
	ifstream file("cr.txt");

	if (!file.is_open()) {
		cout << "Файл не может быть открыт!\n";
		return 1;
	}

	while (!file.eof()) {
		file >> buff; // считали слово
		SDP(buff, root);
		//cout << buff << ' '; // напечатали слово
	}
	file.close();
	
	
 	PrintLR(root);
 	system("PAUSE");
	return 0;
}
void SDP(char *data, vertex* &p) //рекурсвивная СДП
{
	if (!p) {
		p = new vertex;
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		p->repeat = 1;

	} 
	else if (data == p->data) {
			p->repeat++; // увеличиваем частоту
		}
		else if (data < p->data) {
				SDP(data, p->left);
		     }
			 else if (data > p->data) {
					  SDP(data, p->right);
			      }
				  else {
					  return;
				  }
}
void PrintLR(vertex *x) // Выводит содержимое дерева обходом слева направо
{ 
	if (x == NULL) return;
	PrintLR(x->left);
	cout << x->data.c_str() << '-' << x->repeat << endl; 
	PrintLR(x->right);
}
