#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct st         
    { char ch;
      struct st *next;   
    } stack;
  main()
  {   stack *p,*q;
      char a;
      p=NULL;
      system ("CLS");     
//  заполнение стека 
      do           
      { a=getchar();
        q=(stack *)malloc(sizeof(stack));
         q->next=p; 
         p=q;
         q->ch=a;
      }  while(a!='.');
//  печать стека c освобождением памяти
      do        
      { p=q->next;
        free(q);
        q=p;
        printf("%c",p->ch);
      } while(p->next!=NULL);
      getch();
      return 0;
  }

