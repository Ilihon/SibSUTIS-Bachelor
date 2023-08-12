
#include "fuc.h"



main()
{
	//srand(NULL);
	setlocale(LC_ALL, "RUS"); 
	Queue *in=new Queue("Queue(int)");
	Queue *ch=new Queue("Queue(char)");
	Queue *db=new Queue("Queue(doble)");
		
	system ("Pause");
    system("cls");

	str *q = new str;
	in->Queue_Init(q,q->data);
	in->PrintSpis(q);
	
	
	strchar *p = new strchar;
	ch->Queue_Init(p,p->data);
	ch->PrintSpis(p);
	
	strdouble *b = new strdouble;
	db->Queue_Init(b,b->data);
	db->PrintSpis(b);
	
	
	system ("Pause");
    system("cls");
    
	return 0;	
}
