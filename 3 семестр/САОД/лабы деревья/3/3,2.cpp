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
	string data; // �����
	int repeat; // �������
};

vertex *root = NULL;

void SDP(char* data, vertex*&p); // ���������� ��� + ������ �������
void PrintLR(vertex* x); // ����� ����� �� �����

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "\t\t\t ������� ������ ������������� ��������" << endl;
	cout << "\t\t\t    ���� � ������ ��������� �� ��" << endl;
	cout << "\t\t\t             �� ���� ���" << endl;
	cout << "\n\n";


	char buff[100];
	ifstream file("cr.txt");

	if (!file.is_open()) {
		cout << "���� �� ����� ���� ������!\n";
		return 1;
	}

	while (!file.eof()) {
		file >> buff; // ������� �����
		SDP(buff, root);
		//cout << buff << ' '; // ���������� �����
	}
	file.close();
	
	
 	PrintLR(root);
 	system("PAUSE");
	return 0;
}
void SDP(char *data, vertex* &p) //������������ ���
{
	if (!p) {
		p = new vertex;
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		p->repeat = 1;

	} 
	else if (data == p->data) {
			p->repeat++; // ����������� �������
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
void PrintLR(vertex *x) // ������� ���������� ������ ������� ����� �������
{ 
	if (x == NULL) return;
	PrintLR(x->left);
	cout << x->data.c_str() << '-' << x->repeat << endl; 
	PrintLR(x->right);
}
