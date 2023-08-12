#include "fuc.h"


		Queue::Queue(char *n):Set(n){	}
		Queue::Queue():Set(){	}
		Queue::~Queue(){
			cout << " Производный Queue destroyed" <<endl;
		}
		
		template < class VG, class data_type >	
		void Queue::Queue_Init(VG *&p, data_type){
			VG *tail;
			tail=NULL;
			data_type A[N];
			mas_init(A);
			for (i=0; i<N-1; i++) {
				p=new VG;
				p->data=A[i];
				p->prev=tail;
				if(tail!=NULL){
					p->prev->next=p;
				}
				tail=p;
				p=p->next;
			}
			p=new VG;
			p->prev=tail;
			p->prev->next=p;
			p->data=A[i];
			tail=p;
			p->next=NULL;
			while(p->prev!=NULL){
				p=p->prev;
			}
		}
		
		template < typename VG >	
		void Queue::PrintSpis(VG *p){
			VG *buf;
			buf=p;
			cout << "Печать очереди класса Queue" << endl;
			while(buf!=NULL){
				cout << " " <<buf->data;
				buf=buf->next;
			}
			cout << endl;
		}
