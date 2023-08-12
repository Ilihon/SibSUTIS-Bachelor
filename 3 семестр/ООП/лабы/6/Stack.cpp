#include "fuc.h"


		Stack::Stack(char *n) : Set(n){ }
		Stack::Stack():Set(){ }
		Stack::~Stack(){
			cout <<" Производный Stack destroyed" <<endl;
		}
		
		void Stack::Stack_Init(str *&p){
			str *tail;
			tail=NULL;
			int A[N];
			mas_init(A);
			for (i=0; i<N; i++) {
				p=new str;
				p->data=A[i];
				p->next=tail;
				tail=p;
			}
		}
		
		void Stack::PrintSpis(str *p){
			str *buf;
			buf=p;
			cout << "Печать стэка класса Stack" << endl;
			while(buf!=NULL){
				cout << " " <<buf->data;
				buf=buf->next;
			}
			cout << endl;
			
		}
