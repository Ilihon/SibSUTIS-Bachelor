
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <string.h>

using namespace std;

struct str
{
	struct str *next;
	struct str *prev;
	int data;
};

int const n = 10;


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	
	int i, j,k;
	struct str *p, *v, *head, *tail;
	tail=NULL;
	for (i=n; i>0; i--) {
		p=(str *)malloc(sizeof(struct str));
		p->data=i;
		p->next=tail;
		//tail->prev=p;
		tail=p;
	}
	p=tail;
	while (p!=NULL) {
		cout << " " << p->data; 
		p=p->next;
	}
	
	
	
	
	//���������� �����
	cout << endl << "������� ����� K �������� ��� �����������: ";
	cin >> k;
	p=tail;
	for(i=0;i<k;i++){
		head=p;
		p=p->next;
	}
	v=(str *)malloc(sizeof(struct str));
	v->data=rand()%10+1;
	v->next=p;
	head->next=v;
	cout<<"���������: ";
	p=tail;
	while (p!=NULL) {
		cout << " " << p->data; 
		p=p->next;
	}
	
	
	//�������� �����
	cout << endl << "������� ����� K �������� ��� ��������: ";
	cin >> k;
	p=tail;
	for(i=0;i<k-1;i++){
		head=p;
		//cout << " " << p->data; 
		p=p->next;
	}
	head->next=p->next;
	cout<<"���������: ";
	p=tail;
	while (p!=NULL) {
		cout << " " << p->data; 
		p=p->next;
	}
	
	//������� ����� ������ � ������
	i=0;
	p=tail;
	while (p!=NULL) {
		p=p->next;
		i++;
	}
	cout << endl << "����� ��������� � ������: " << i<<endl;
	
	//����������� p-��� ����� ������ ������ k-���
	cout << endl << "������� ����� K �������� ��� ��������: ";
	cin >> k;
	p=tail;
	for(i=0;i<j-1;i++){
		head=p;
		//cout << " " << p->data; 
		p=p->next;
	}
	
	
	
	
	system("PAUSE");
}
