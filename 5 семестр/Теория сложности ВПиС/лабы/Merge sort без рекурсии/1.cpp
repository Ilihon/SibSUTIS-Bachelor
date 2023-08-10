#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int random (int N) { return rand()%N; }
int Mprak=0, Cprak=0, rec=0;

void FillMas(int n, int *A, struct stack **head);
void PrintMas(int n, int *A); 
int CheckSum(int n, int *A);
int RunNumber(int n, int *A);
void CopyArray(int n, int *A, int *B);

void DeleteStack (struct stack **head);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);
void print(struct stack *head_a, struct stack *head_b, int p,int n);

void StackToQueue (struct stack **head, struct stack **tail);;

void SelectSort (int n, int *A); 
void BubbleSort (int n, int *A);

void Split (stack **head, stack **head_a, stack **head_b);
void MergeS (stack **head_a, stack **head_b, stack **tail, int q, int r);
void MergeSort (stack **head, stack **tail, int n);

struct stack {
	struct stack *next;
	int data;
};

struct Queue {
	stack *head;
	stack *tail;
};

main() {
	setlocale(LC_ALL, "rus");
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	
	int n;
	printf ("Enter array size: ");
	scanf("%d", &n);
    int A[n], B[n];
    printf ("Enter elements: \n");
    FillMas(n,A, &head);
    printf ("---------------\n");
    
	printf ("\nOriginal array:\n");
    PrintMas(n,A);
	CheckSum(n,A);
	RunNumber(n,A);
    printf ("\n---------------\n");
    
	printf ("\nSelectSort:\n");
    CopyArray(n,A,B);
    SelectSort(n,B);
	printf ("\nOriginal array:\n");
    PrintMas(n,A);
	printf ("\nОтсортированный:\n");
    PrintMas(n,B);
	CheckSum(n,B);
	RunNumber(n,B);
	printf ("\nТрудоёмкость алгоритма = %f", -1+(pow(n,2)+n)/2);
	printf ("\nCprak=%d, Mprak=%d \n", Cprak, Mprak);
    printf ("\n---------------\n");
    
	printf ("\nBubbleSort:\n");
    CopyArray(n,A,B);
    BubbleSort(n,B);
	printf ("\nOriginal array:\n");
    PrintMas(n,A);
	printf ("\nОтсортированный:\n");
    PrintMas(n,B);
	CheckSum(n,B);
	RunNumber(n,B);
	printf ("\nТрудоёмкость алгоритма = %f", pow(n,2));
	printf ("\nCprak=%d, Mprak=%d \n", Cprak, Mprak);
    printf ("\n---------------\n");
    
	printf ("\nMergeSort:\n");
    printf ("\nОригинальная очередь: \n");
	PrintStack (head);
    printf ("\nПроцесс сортировки: \n");
	MergeSort (&head, &tail, n);
    printf ("\nОтсортированная очередь: \n");
	PrintStack (head);
	CheckSumStack (head);
	RunNumberStack (head);
	printf ("\nМинимальная трудоёмкость алгоритма = %f", n*log2(n));
	printf ("\nCprak=%d, Mprak=%d \n", Cprak, Mprak);
    printf ("\n---------------\n");
    
	system("PAUSE");
	return 0;
}

void CopyArray(int n, int *A, int *B){
	for (int i=0;i<n;i++){
		B[i]=A[i];
	}
}

void FillMas(int n, int *A, struct stack **head){    
	for (int i=0;i<n;i++){
		scanf("%d", &A[i]);
    }
	struct stack *p;
	for (int i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=A[i-1];
		p->next=*head;
		*head=p;
	}
}

void PrintMas(int n, int *A){
    printf ("\nPrintMas: \n");
	for(int i=0;i<n;i++){
  		printf("%d \t",A[i]);
  	} 
}

int CheckSum(int n, int *A){
	int sum=0;
    for(int i=0;i<n;i++)
  	{
  		sum=sum+A[i];
  	} 
  	printf ("\nCheckSum = %d", sum); 
  	return sum;
} 

int RunNumber(int n, int *A){
	int i=1;
	int v;
    for (v=1;v<n;v++ )
    {
		if(A[v-1]>A[v]) {
    		i++;
        }    
	}
    printf ("\nRunNumber = %d\n", i); 
    return i;      
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
	printf ("\nCheckSumStack = %d", s);
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

void print(struct stack *head_a, struct stack *head_b, int p, int n){
	struct stack *r=head_a;
	struct stack *q=head_b;
	while (r!=NULL){
		for(int i=0;i<p;i++){
			printf ("%3d ", r->data);
			r=r->next;
		}
		if(p<n){
			for(int i=0;i<p;i++){
				printf ("%3d ", q->data);
				q=q->next;
			}
		}
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
		if ((*head_a)->data<(*head_b)->data) {
			StackToQueue (head_a, tail);
			Mprak++;
			q--;
		}
		else {
			if((*head_a)->data>(*head_b)->data){
				Mprak++;
			}
			StackToQueue (head_b, tail);
			r--;
		}
	}
	while (q>0) {
		StackToQueue (head_a, tail);
		//Mprak++;
		q--;
	}
	while (r>0) {
		StackToQueue (head_b, tail);
		//Mprak++;
		r--;
	}
}

void Split (stack **head, stack **head_a, stack **head_b) {
	stack *k, *p;
	*head_a=*head;
	*head_b=(*head)->next;
	k=*head_a;
	p=*head_b;
	while (p!=NULL) {
		k->next=p->next;
		k=p;
		p=p->next;
	}
}

void MergeSort (stack **head, stack **tail, int n) {
	Mprak = 0, Cprak = 0;
	int i, m, q, p=1, r, iter=0;
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
		iter++;
    	printf ("\nИтерация номер %d \n",iter);
		//print(a,b,p,n);
		
		PrintStack(a);
		if(p<n){
			PrintStack(b);
		}
	}
	c[0].tail->next=NULL;
	*head=c[0].head;
}

void SelectSort (int n, int *A) 
{
	Mprak = 0, Cprak = 0;
	int i,j,k,t;
	for (i = 0; i < n-1; i++ ) { 
		k = i;
		for( j=i+1; j<n; j++){ 
			Cprak++;
	   		if (A[j]<A[k]){
	   			k=j;
			}
		}
		if(k!=i){
			t=A[i];
			A[i]=A[k];
			A[k]=t; 
			Mprak+=3;
		}
	}
}

void BubbleSort (int n, int *A) {
	Mprak=0, Cprak=0;
	int i,j,t;
	for (i = 0; i < n-1; i++) 
	{ 
		for (j=n-1; j>i; j--) 
		{ 
			Cprak++; 
			if (A[j]<A[j-1]) 
			{
				t=A[j];
				A[j]=A[j-1];
				A[j-1]=t;
				Mprak+=3; 
			}
		}
	}
}	
