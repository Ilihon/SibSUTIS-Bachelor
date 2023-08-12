#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "function.h"

int random (int N) { return rand()%N; }
int mp=0, cp=0, rec=0;

main() {
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	int i, n, m;
	printf ("Vvedite razmer ocheredi: ");
	scanf("%d", &n);
	printf ("Vvedite razmer hesh-tabl: ");
	scanf("%d", &m);
	FillRandQueue (&head, &tail, n);
	PrintStack (head);
	printf ("\n");
	Queue q[m];
	for (i=0; i<m; i++) {
		q[i].head=NULL;
		q[i].tail=(stack*)&q[i].head;
	}
	printf ("\n");
	Hash (m, &head, &tail, q);
	printf ("\n");
	HashSearch (m, q);
	printf ("\n");
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

void FillIncQueue (struct stack **head, struct stack **tail, int n) {
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

void FillDecQueue (struct stack **head, struct stack **tail, int n) {
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

void FillRandQueue (struct stack **head, struct stack **tail, int n) {
	int i, a=0, b=2*n;
	srand(time(NULL));
	struct stack *p;
	for (i=n; i>0; i--) {
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


void CheckSumStack (struct stack *head) {
	int s=0;
	struct stack *p=head;
	while (p!=NULL) {
		s+=p->data;
		p=p->next;
	}
	printf ("\n%d", s);
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
		printf ("\n%d\n", c);
	}
	else printf ("\n%d\n", 0);
}

void PrintMas (int A[], int n) {
	int i;
	for (i=0; i<n; i++) {
		if(i%20==0 && i!=0) printf ("\n");
		printf ("%3d ", A[i]);
	}
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

void StackToQueue (struct stack **head, struct stack **tail) {
	(*tail)->next=*head;
	*tail=*head;
	*head=(*head)->next;
	(*tail)->next=NULL;
}

void Hash (int m, stack **head, stack **tail, Queue q[]) {
	int i, j;
	stack *p=*head, *z;
	while (p!=NULL) {
		j=p->data%m;
		z=q[j].head;
		i=0;
		while (z!=NULL) {
			if (z->data==p->data) i++;
			z=z->next;
		}
		if (i==0) {
			StackToQueue (&p, &(q[j].tail));
			(q[j].tail)->next=NULL;
		}
		else p=p->next;
	}
	for (i=0; i<m; i++) {
		printf ("%d ", i);
		p=q[i].head;
		while (p!=NULL) {
			printf ("-> %d ", p->data);
			p=p->next;
		}
		printf ("\n");
	}
}

void HashSearch (int m, Queue q[]) {
	int i=0, j, n;
	stack *p;
	printf ("Vvedite kluch poiska: ");
	scanf("%d", &n);
	j=n%m;
	p=q[j].head;
	while (p!=NULL) {
		if (n==p->data) {
			i++;
			break;
		}
		p=p->next;
	}
	if (i) printf ("Chislo %d naydeno v %d ocheredi!", n, j);
	else printf ("Chisla %d net v ocheredyah!", n, j);
}

