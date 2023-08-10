#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

int C = 0;
int M = 0;

struct spis {spis *next; int data;};
struct quaue {spis *head; spis *tail;};;

spis *SpisInc(spis *head, int n)
{
 spis *q;
 for (int i=0;i<n;i++)
  {
   q=new spis;
   q->data=n-i;
   q->next=head;
   head=q;
  }
 return head;
}

void list (spis *head)
{
   spis *p;
   p=head;
   while (p!=NULL)
   {
    printf(" %d ",p->data);
    p=p->next;
   }
}

void CheckSum (spis *head) {                                //������� ����������� �����
	int s=0;
	spis *p=head;
	while (p!=NULL) {
		s+=p->data;
		p=p->next;
	}
	printf ("\n����������� �����: %d", s);
}

void RunNumber (spis *head) {                              //������� ���������� �����
	int c=1;
	if (head!=NULL) {
		spis *p=head, *q=p->next;
		while (q!=NULL) {
			if (p->data>q->data) c++;
			p=p->next;
			q=p->next;
		}
		printf ("\n���������� �����: %d\n\n", c);
	}
	else printf ("\n���������� �����: %d\n\n", 0);
}
void Null() {   // ��������� M � C
    M = 0;
    C = 0;
}

void Trud(int q, int r) {    // ����� ������������� ��������
    printf ("C(����) = %d", C);
    if (q >= r) {
        printf ("\n%d <= C(����) <= %d", r, r + q - 1);
    } else
        printf ("\n%d <= C(����) <= %d", q, r + q - 1);
    printf ("\nM(����) = %d\n", M);
    printf ("M(����) = %d\n\n", q + r);
}

void Merge(spis **a, spis **b, int q, int r) {     // ������� �����
    quaue *c=new quaue();
    int i=0;
    c->tail=(spis *)&c->head;
    while (q != 0 && r != 0) {
        ++C;
        if ((*a)->data <= (*b)->data)
            {
             //����������� �������� �� ������ a � ������� c
             M++;
             c->tail->next=*a;
             c->tail=*a;
             *a=(*a)->next;
             q--;
            }
          else
            {
             //����������� �������� �� ������ b � ������� c
             M++;
             c->tail->next=*b;
             c->tail=*b;
             *b=(*b)->next;
             r--;
            }
          }
       while (q > 0)
         {
          //����������� �������� �� ������ a � ������� c
          M++;
          c->tail->next=*a;
          c->tail=*a;
          *a=(*a)->next;
          q--;
         }
       while (r > 0)
         {
          //����������� �������� �� ������ b � ������� c
          M++;
          c->tail->next=*b;
          c->tail=*b;
          *b=(*b)->next;
          r--;
         }
         list(c->head);
        CheckSum(c->head);
        RunNumber(c->head);
}

int main()
{
	setlocale(LC_ALL, "Russian");
    srand(time(0));
    int q;
    int r;
    spis* a=0;
    spis* b=0;
    spis *list1;    // ������������� ������� ������
    spis *list2;    // ������������� ������� ������

    list1 = 0;    // �������� ������
    list2 = 0;
    printf ("������� ���-�� ��������� ��� ������� ������: ");
    scanf ("%d", &q);
    list1=SpisInc(a, q);
    printf ("������� ���-�� ��������� ��� ������� ������: ");
    scanf ("%d", &r);
    list2=SpisInc(b, r);
    printf ("\n������ ������: ");
    list(list1);
    printf ("\n������ ������: ");
    list(list2);
    printf ("\n�������, ���������� �������� ���� �������: ");
    Merge(&list1, &list2, q, r);
    Trud(q, r);
}


