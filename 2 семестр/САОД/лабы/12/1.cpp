#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <graphics.h>

int random (int N) { return rand()%N; }
int Mprak=0, Cprak=0, rec=0;

void FillIncStack (int n,struct stack **head);
void FillDecStack (int n,struct stack **head);
void FillRandStack (int n,struct stack **head);
void DeleteStack (struct stack **head);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);

void StackToQueue (struct stack **head, struct stack **tail);
void Swap (int &x, int &y);

void Result(int n);
void ResultTabl (int n);

void QuickSort (int *A, int l, int r);

void Split (stack **head, stack **head_a, stack **head_b);
void MergeS (stack **head_a, stack **head_b, stack **tail, int q, int r);
void MergeSort (stack **head, stack **tail, int n);

void QuickSort (int *A, int l, int r) ;

void FillRand (int n, int *A) ;

void FuncDec (int n, int i);
void FuncInc (int n, int i);
void FuncRand (int n, int i);

struct stack {
	struct stack *next;
	int data;
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
	FillRandStack (n,&head);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	printf ("\n");
	MergeSort (&head, &tail, n);
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	Result (n);
	printf ("\n");
	ResultTabl (100);
	printf ("\n");
	
	
	//////////////5+
	
	/*
	initwindow(800,800);
 	moveto(100,700);         
	lineto(100,60);     
			
	lineto(95,65);	
	lineto(100,60);     
 	lineto(105,65);	
 	moveto(100,700);
 	lineto(700,700);
 	lineto(695,695);
 	moveto(700,700);
 	lineto(695,705);
 
 	moveto(100,600);
 	lineto(90,600);
 	outtextxy(65,592,"100");
 	moveto(100,500);
 	lineto(90,500);
 	outtextxy(65,492,"200");
 	moveto(100,400);
 	lineto(90,400);
 	outtextxy(65,392,"300");
 	moveto(100,300);
 	lineto(90,300);
 	outtextxy(65,292,"400");
 	moveto(100,200);
 	lineto(90,200);
 	outtextxy(65,192,"500");
 	outtextxy(95,45,"n");
 
 
 	moveto(200,700);
 	lineto(200,710);
 	outtextxy(180,715,"3000");
 	moveto(300,700);
 	lineto(300,710);
	outtextxy(280,715,"6000");
 	moveto(400,700);
 	lineto(400,710);
 	outtextxy(380,715,"9000");
 	moveto(500,700);
 	lineto(500,710);
 	outtextxy(480,715,"12000");
	moveto(600,700);
 	lineto(600,710);
 	outtextxy(580,715,"15000"); 
 
 	outtextxy(660,715,"C(prak)+M(prak)"); 
  
 	moveto(100,700);
 
 	for(int i=2;i<500;i++)
	{
		FuncRand(i,0);
		lineto(102+((Cprak+Mprak)/30),700-i);      
	}

	moveto(100,700);
	setcolor(GREEN); 
	for(int i=0;i<500;i++){
		FuncRand(i,1);
		lineto(100+((Cprak+Mprak)/30),700-i);      
	}*/
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

void FillDecStack ( int n,struct stack **head) {
	int i;
	struct stack *p;
	for (i=1; i<=n; i++) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
	}
}

void FillRandStack (int n,struct stack **head) {
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


void StackToQueue (struct stack **head, struct stack **tail) {
	(*tail)->next=*head;
	*tail=*head;
	*head=(*head)->next;
	(*tail)->next=NULL;
}

void MergeS (stack **head_a, stack **head_b, stack **tail, int q, int r) {
	while (q!=0 && r!=0) {
		Cprak++;
		if ((*head_a)->data<=(*head_b)->data) {
			StackToQueue (head_a, tail);
			Mprak++;
			q--;
		}
		else {
			StackToQueue (head_b, tail);
			Mprak++;
			r--;
		}
	}
	while (q>0) {
		StackToQueue (head_a, tail);
		Mprak++;
		q--;
	}
	while (r>0) {
		StackToQueue (head_b, tail);
		Mprak++;
		r--;
	}
}

void Split (stack **head, stack **head_a, stack **head_b) {
	stack *k, *p;
	*head_a=*head;
	*head_b=(*head)->next;
	k=*head_a;
	p=*head_b;
	Mprak+=4;
	while (p!=NULL) {
		k->next=p->next;
		k=p;
		p=p->next;
		Mprak+=2;
	}
}
 
void Swap (int &x, int &y) {
	int t=x; x=y; y=t;
}

void Result (int n) {
	printf ("\nCteor=%f, Mteor=%f", n*log2(n), n*log2(n)+n);
	printf ("\nCprak=%d, Mprak=%d \n", Cprak, Mprak);
}


void ResultTabl (int n) {
	int i;
	printf ("|  n   |        Mprak+cprak 	  |");
	printf ("\n|      |   Inc  |   Dec  |  Rand  |");
	for (; n<=500; n+=100) {
		printf ("\n| %4d |", n);
		FuncInc (n, 0);
		printf (" %6.d |", Cprak+Mprak);
		FuncDec (n, 0);
		printf (" %6.d |", Cprak+Mprak);
		FuncRand (n, 0);
		printf (" %6.d |", Cprak+Mprak);
	}
}

void MergeSort (stack **head, stack **tail, int n) {
	int i, m, q, p=1, r;
	stack *a=NULL, *b=NULL;
	Queue c[2];
	Split (head, &a, &b);
	while (p<n) {
		c[0].tail=(stack*)&c[0].head;
		c[1].tail=(stack*)&c[1].head;
		i=0;
		m=n;
		while (m>0) {
			if (m>=p) q=p;
			else q=m;
			m-=q;
			if (m>=p) r=p;
			else r=m;
			m-=r;
			MergeS (&a, &b, &c[i].tail, q, r);
			i=1-i;
		}
		a=c[0].head;
		b=c[1].head;
		p*=2;
	}
	c[0].tail->next=NULL;
	*head=c[0].head;
}

void FillRand (int n, int *A) {
	int i, a=0, b=2*n;
	srand(time(NULL));
	for ( i = 0; i < n; i ++ ) A[i] = random(b-a+1)+a;
}


void QuickSort (int *A, int l, int r) {
	int x=A[l], i=l, j=r;
	while (i<=j) {
		while (Cprak++, A[i]<x) i++;
		while (Cprak++, A[j]>x) j--;
		if (i<=j) {
			Swap (A[i], A[j]);
			Mprak+=3;
			i++;
			j--;
		}
	}
	if (l<j) QuickSort (A, l, j);
	if (i<r) QuickSort (A, i, r);
}

void FuncDec (int n, int i) {
	Mprak=0; Cprak=0;
	int A[n];
	switch (i) {
		case 0: 
			stack *head, *tail;
			head=NULL;
			tail=(stack*)&head;
			FillDecStack (n,&head);
			MergeSort (&head, &tail, n);
			break;
	}
}

void FuncInc (int n, int i) {
	Mprak=0; Cprak=0;
	int A[n];
	switch (i) {
		case 0: 
			stack *head, *tail;
			head=NULL;
			tail=(stack*)&head;
			FillIncStack (n,&head);
			MergeSort (&head, &tail, n);
			break;
	}
}

void FuncRand (int n, int i) {
	Mprak=0; Cprak=0;
	int A[n];
	switch (i) {
		case 0: 
			stack *head, *tail;
			head=NULL;
			tail=(stack*)&head;
			FillRandStack (n,&head);
			MergeSort (&head, &tail, n);
			break;
			
		case 1: 
		FillRand (n, A);
		QuickSort (A, 0, n-1);
			break;
	}
}
