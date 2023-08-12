#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int random (int N) { return rand()%N; }
int mp=0, cp=0, rec=0;

void FillIncStack (int n,struct stack **head);
void FillDecStack (int n,struct stack **head);
void FillRandStack (int n,struct stack **head);
void DeleteStack (struct stack **head);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);
void StackToQueue (struct stack **head, struct stack **tail);

void FillIncQueue (int n, struct stack **head, struct stack **tail);
void FillDecQueue (int n, struct stack **head, struct stack **tail);
void FillRandQueue (int n, struct stack **head, struct stack **tail);
void Swap (int &x, int &y);


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

void Hash (int m, stack **head, stack **tail, Queue q[]);
void HashSearch (int m, Queue q[]);

main() {
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	int i, n, m;
	printf (" Vvedite razmer ocheredi: ");
	scanf("%d", &n);
	printf (" Vvedite razmer hesh-tabl: ");
	scanf("%d", &m);
	FillRandQueue (n, &head, &tail);
	printf("\n FillRand: ");
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
		printf (" %d ", i);
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
	printf (" Vvedite kluch poiska: ");
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
	if (i) printf (" Chislo %d naydeno v %d ocheredi!", n, j);
	else printf (" Chisla %d net v ocheredyah!", n, j);
}

