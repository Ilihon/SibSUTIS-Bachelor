#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct str
{
	struct str *next;
	struct str *prev;
	int data;
};


int const N = 10;

class Set
{
	protected:
		int i,j, A[N];
	
	public:
		Set(char *n){
			cout  << " Иницивализация "<< n<<"-конструктора "<< endl;
			i=j=0;
		}
		Set(){
			cout << " Инициализация конструктора без передачи параметров в него"<< endl;
			i=j=0;
		}
		~Set()
		{
			cout <<" Производный Set destroyed" <<endl <<endl;
			delete A;
		}
		
		void mas_init(){
			cout <<endl << "Массив для списка "<< endl;
			for (i=0; i<N; i++) {
				A[i]=rand()%10+1;
				cout << " "<< A[i];
			}
			cout << endl;
		}
		
		virtual	void PrintSpis(){
			
		}
		
};

class Stack : public Set
{
	
	public:
		Stack(char *n):Set(n){	}
		Stack():Set(){ }
		~Stack(){
			cout <<" Производный Stack destroyed" <<endl;
		}
		void Stack_Init(str *&p){
			str *tail;
			tail=NULL;
			mas_init();
			for (i=0; i<N; i++) {
				p=new str;
				p->data=A[i];
				p->next=tail;
				tail=p;
			}
		}
		
		void PrintSpis(str *p){
			str *buf;
			buf=p;
			cout << "Печать стэка класса Stack" << endl;
			while(buf!=NULL){
				cout << " " <<buf->data;
				buf=buf->next;
			}
			cout << endl;
			
		}
	
};

class Queue : public Set
{
	
	public:
		Queue(char *n):Set(n){	}
		Queue():Set(){	}
		~Queue(){
			cout << " Производный Queue destroyed" <<endl;
		}
		
		void Queue_Init(str *&p){
			str *tail;
			tail=NULL;
			mas_init();
			for (i=0; i<N-1; i++) {
				p=new str;
				p->data=A[i];
				p->prev=tail;
				if(tail!=NULL){
					p->prev->next=p;
				}
				tail=p;
				p=p->next;
			}
			p=new str;
			p->prev=tail;
			p->prev->next=p;
			p->data=A[i];
			tail=p;
			p->next=NULL;
			while(p->prev!=NULL){
				p=p->prev;
			}
		}
		void PrintSpis(str *p){
			str *buf;
			buf=p;
			cout << "Печать очереди класса Queue" << endl;
			while(buf!=NULL){
				cout << " " <<buf->data;
				buf=buf->next;
			}
			cout << endl;
		}
};

main()
{
	//srand(NULL);
	setlocale(LC_ALL, "RUS"); 
	Set a("Set");
	Stack b("Stack");
	Queue c("Queue");
	Stack *v=new Stack();
	Queue *g=new Queue();
		
	system ("Pause");
    system("cls");

	str *p = new str;
	str *q = new str;
	v->Stack_Init(p);
	v->PrintSpis(p);
	g->Queue_Init(q);
	g->PrintSpis(q);
	system ("Pause");
    system("cls");
    
    delete p;
    delete q;
    delete v;
    delete g;
	return 0;	
}
