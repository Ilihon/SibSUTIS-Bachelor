#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int random (int N) { return rand()%N; }
int Mprak=0, Cprak=0, rec=0;

void FillIncStack (int n,struct stack **head);
void FillDecStack (int n,struct stack **head);
void FillRandStack (int n,struct stack **head);
void DeleteStack (struct stack **head);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);

void FillIncQueue (int n, struct stack **head, struct stack **tail);
void FillDecQueue (int n, struct stack **head, struct stack **tail);
void FillRandQueue (int n, struct stack **head, struct stack **tail);
void Swap (int &x, int &y);

void Result(int n);

void DeleteQueue (struct stack **head, struct stack **tail);
void DigitalSort (stack **head, stack **tail);

struct stack {
	struct stack *next;
	union {
		int data;
		unsigned char digit [sizeof(int)];
	};
};

struct Queue {
	stack *head;
	stack *tail;
};

main() {
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
	DigitalSort (&head, &tail);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	Result(n);
	printf ("\n");
	printf ("\n");
	system("PAUSE");
	return 0;
}


void FillIncStack (int n, struct stack **head) {
	int i;
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
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

void FillDecStack (int n, struct stack **head) {
	int i;
	struct stack *p;
	for (i=1; i<=n; i++) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
	}
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

void FillRandStack (int n, struct stack **head) {
	int i, a=0, b=2*n;
	srand(time(NULL));
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=random(b-a+1)+a;
		p->next=*head;
		*head=p;
	}
}

void FillRandQueue (int n, struct stack **head, struct stack **tail) {
	int i, a=0, b=2*n;
	srand(time(NULL));
	struct stack *p;
	for (i=n; i>0; i--) 
    {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=random(b-a+1)+a;;
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

void CheckSum ( int n,int *A) {
	int i, s;
	for (s=0, i=0; i< n; i++) s+=A[i];
	printf ("\nCheckSum=%d", s);
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


void Result (int n) {
	printf ("\nCteor=%f, Mteor=%f", n*log2(n), n*log2(n));
	printf ("\nCprak=%d, Mprak=%d \n", Cprak, Mprak);
}

void DigitalSort (stack **head, stack **tail) {
	int d, i, j, k, l=sizeof(int);
	stack *p;
	Queue q[256];
	for (j=l; j>0; j--) 
    {
		for (i=0; i<256; i++) q[i].tail=(stack*)&q[i].head;
		p=*head;
		k=sizeof(int)-1-j;
		while (p!=NULL) 
        {
			d=p->digit[k];
			q[d].tail->next=p;
			q[d].tail=p;
			p=p->next;
		}
		p=(stack*)&(*head);
		for (i=0; i<256; i++) 
        {
			if (q[i].tail!=(stack*)&q[i].head) 
            {
				p->next=q[i].head;
				p=q[i].tail;
			}
		}
		p->next=NULL;
	}
}

