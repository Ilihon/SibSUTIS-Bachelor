#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int random (int N) { return rand()%N; }
int mp=0, cp=0, rec=0;

struct stack {
	struct stack *next;
	int data;
};

void FillIncStack (struct stack **head, int n);
void FillDecStack (struct stack **head, int n);
void FillRandStack (struct stack **head, int n);
void DeleteStack (struct stack **head);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);



main() {
	struct stack *head, *tail;
	head=tail=NULL;
	int n;
	printf ("Vvedite razmer steka: ");
	scanf("%d", &n);
	printf ("\nFillIncStack\n", n);
	FillIncStack (&head, n);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	DeleteStack (&head);
	printf ("\nFillRandStack\n", n);
	FillRandStack (&head, n);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	DeleteStack (&head);
	printf ("\nFillDecStack\n", n);
	FillDecStack (&head, n);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	DeleteStack (&head);
	
	system("PAUSE");
	return 0;
}

void FillIncStack (struct stack **head, int n) {
	int i;
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
	}
}

void FillDecStack (struct stack **head, int n) {
	int i;
	struct stack *p;
	for (i=1; i<=n; i++) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
	}
}

void FillRandStack (struct stack **head, int n) {
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


void DeleteStack (struct stack **head) {
	int i;
	struct stack *p=*head;
	while (p!=NULL) {
		*head=p->next;
		free (p);
		p=*head;
	}
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
		printf ("\nRunNumberStack=%d\n", c);
	}
	else printf ("\nRunNumberStack=%d\n", 0);
}


void PrintStack (struct stack *head) {
	struct stack *p=head;
	while (p!=NULL) {
		printf ("%3d ", p->data);
		p=p->next;
	}
}


void Swap (int &x, int &y) {
	int t=x; x=y; y=t;
}












