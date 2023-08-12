#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int random (int N) { return rand()%N; }
int Mprak=0, Cprak=0, rec=0;

void DeleteStack (struct stack **head);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);

void FillIncQueue (int n, struct stack **head, struct stack **tail);
void FillDecQueue (int n, struct stack **head, struct stack **tail);
void FillRandQueue (int n, struct stack **head, struct stack **tail);
void Swap (int &x, int &y);

void ResultTabl (int n);

void DeleteQueue (struct stack **head, struct stack **tail);
void DigitalSort (stack **head);
void DigitalDecSort (stack **head);


void FunkDec (int n, int i);
void FunkInc (int n, int i);
void FunkRand (int n, int i);

struct stack {
	struct stack *next;
	union {
		int data;
		unsigned char digit [sizeof(int)];
	};
};

unsigned char KDI [ sizeof (int) ];

struct Queue {
	stack *head;
	stack *tail;
};

main() {
	for(int i=0; i<sizeof (int); i++){
		KDI[i] = i;
	}
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	int n;
	printf ("Vvedite razmer steka: ");
	scanf("%d", &n);
	FillRandQueue (n, &head, &tail);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	printf ("\n");
	printf ("\nFillInc\t");	
	DigitalSort (&head);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	////////////////////////
	printf ("\nFillDec\t");	
	DigitalDecSort (&head);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	//////////////////////////
	printf ("\n");
	
	ResultTabl (n);
	printf ("\n");
	system("PAUSE");
	return 0;
}
void ResultTabl (int n) {
	int i;
	printf ("|  n   |        Mprak+cprak 	  |");
	printf ("\n|      |   Inc  |   Dec  |  Rand  |");
	for (n=100; n<=500; n+=100) {
		printf ("\n| %4d |", n);
		FunkInc(n, 0);
		printf (" %6.d |", Cprak+Mprak);
		FunkDec(n, 0);
		printf (" %6.d |", Cprak+Mprak);
		FunkRand(n, 0);
		printf(" %6.d |", Cprak+Mprak);
	}
}

void FillIncQueue (int n, struct stack **head, struct stack **tail) {
	int i;
	struct stack *p;
	for (i=1; i<=n; i++) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		(*tail)->next=p;
		*tail=p;
	}
	(*tail)->next=NULL;
}

void FillDecQueue (int n, struct stack **head, struct stack **tail) {
	int i;
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		(*tail)->next=p;
		*tail=p;
	}
	(*tail)->next=NULL;
}

void FillRandQueue (int n, struct stack **head, struct stack **tail) {
	int i, a=0, b=2*n;
	srand(time(NULL));
	struct stack *p;
	for (i=n; i>0; i--) 
    {
		p=(stack *)malloc(sizeof(struct stack));
		//////////////////////////////
		p->data=random(256);
		////////////////////////////
		(*tail)->next=p;
		*tail=p;
	}
	(*tail)->next=NULL;
}

void DeleteStack (struct stack **head) {
	int i;
	struct stack *p=*head;
	while (p!=NULL) {
		*head=p->next;
		free (p);
		p=*head;
	}
}

void DeleteQueue (struct stack **head, struct stack **tail) {
	DeleteStack (head);
	*tail=NULL;
	*tail=(stack*)&(*head);
}

void CheckSumStack (struct stack *head) {
	int s=0;
	struct stack *p=head;
	while (p!=NULL) {
		s+=p->data;
		p=p->next;
	}
	printf ("\nCheckSumStack=%d", s);
}

void RunNumberStack (struct stack *head) {
	int c=1;
	if (head!=NULL) {
		struct stack *p=head, *q=p->next;	
		while (q!=NULL) {
			if (p->data>q->data) c++;
			p=p->next;
			q=p->next;
		}
		printf ("\n RunNumberStack=%d\n\n", c);
	}
	else printf ("\n RunNumberStack=%d\n\n", 0);
}

void PrintStack (struct stack *head) {
	struct stack *p=head;
	while (p!=NULL) {
		printf ("%3d ", p->data);
		p=p->next;
	}
}

void DigitalSort (stack **head) {
	int d, i, j, k, l=sizeof(int);
	stack *p;
	Queue q[256];
	for (j=l; j>0; j--) 
    {
		for (i=0; i<256; i++) 
			q[i].tail=(stack*)&q[i].head;
		p=*head;
//		k=sizeof(int)-1-j;
		k=KDI[j];
		while (p!=NULL) 
        {
			Cprak++;
			d=p->digit[k];
			q[d].tail->next=p;
			q[d].tail=p;
			p=p->next;
			Mprak++;
		}
		p=(stack*)&(*head);
		for (i=0; i<256; i++) 
        {
			if (q[i].tail!=(stack*)&q[i].head) 
            {
				Cprak++;
				p->next=q[i].head;
				p=q[i].tail;
				Mprak++;
			}
		}
		p->next=NULL;
	}
}
///////////////////
void DigitalDecSort (stack **head) {
	int d, i, j, k, l=sizeof(int);
	stack *p;
	Queue q[256];
	for (j=l; j>0; j--) 
    {
		for (i=0; i<256; i++) 
			q[i].tail=(stack*)&q[i].head;
		p=*head;
		//k=sizeof(int)-1-j;
		k=KDI[j];
		while (p!=NULL) 
        {
			Cprak++;
			d=p->digit[k];
			q[d].tail->next=p;
			q[d].tail=p;
			p=p->next;
			Mprak++;
		}
		p=(stack*)&(*head);
		for (i=255; i>=0; i--) 
        {
			if (q[i].tail!=(stack*)&q[i].head) 
            {
				Cprak++;
				p->next=q[i].head;
				p=q[i].tail;
				Mprak++;
			}
		}
		p->next=NULL;
	}
}
///////////////////////

void FunkDec (int n, int i) {
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	Mprak=0; Cprak=0;
	FillDecQueue (n, &head, &tail);
	switch (i) {
		case 0: DigitalSort (&head);
			break;
	}
}

void FunkInc (int n, int i) {
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	Mprak=0; Cprak=0;
	FillIncQueue (n, &head, &tail);
	switch (i) {
		case 0: DigitalSort (&head);
			break;
	}
}

void FunkRand (int n, int i) {
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	Mprak=0; Cprak=0;
	FillRandQueue (n, &head, &tail);
	switch (i) {
		case 0: DigitalSort (&head);
			break;
	}
}
