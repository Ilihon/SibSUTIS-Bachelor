#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<time.h>

int n = 5;

struct TStudent{
	char surname[15];
	int marks[4];
};

struct spis{//элемент списка студентов
	TStudent s;
	spis *next;
} *head,*p,*pp;

main(){
	srand(time(0));
	int i = 0;
	TStudent A[5]={{"Just",2 + rand() % 4,2 + rand() % 4,2 + rand() % 4,2 + rand() % 4},
				   {"Enormous",2 + rand() % 4,2 + rand() % 4,2 + rand() % 4,2 + rand() % 4},
				   {"Butovsky",2 + rand() % 4,2 + rand() % 4,2 + rand() % 4,2 + rand() % 4},
				   {"Stoyak",2 + rand() % 4,2 + rand() % 4,2 + rand() % 4,2 + rand() % 4},
				   {"Kolossa",2 + rand() % 4,2 + rand() % 4,2 + rand() % 4,2 + rand() % 4}};
	head=new spis;
	head->next=NULL;
	do{
		p=new spis;
		strcpy(p->s.surname, A[i].surname);
		p->s.marks[0] = A[i].marks[0];
		p->s.marks[1] = A[i].marks[1];
		p->s.marks[2] = A[i].marks[2];
		p->s.marks[3] = A[i].marks[3];
		p->next = head->next;
		head->next = p;
		i++;
	}while (i!=n);
	for (p=head->next; p!=NULL; p=p->next)
	{
		printf("%-16s %2d %2d %2d %2d \n",p->s.surname, p->s.marks[0], p->s.marks[1], p->s.marks[2], p->s.marks[3]);
	}
	for (p=head; p->next!=0;)
	{
		if (p->next->s.marks[0]<=2 || p->next->s.marks[1]<=2 || p->next->s.marks[2]<=2 || p->next->s.marks[3]<=2)
		{
			pp=p->next; 
			p->next=p->next->next; 
			delete(pp);
		}
		else p=p->next;
	}
	 printf("\n");
	for (p=head->next; p!=0; p=p->next)
	{
		printf("%-16s %2d %2d %2d %2d\n",p->s.surname, p->s.marks[0], p->s.marks[1], p->s.marks[2], p->s.marks[3]);

	}
	system("PAUSE");
}
