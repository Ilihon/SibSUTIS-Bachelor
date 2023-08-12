#include<stdio.h>
#include<stdlib.h>
#include <math.h>  
main()
{float s,i,h=0.5,a=2.14,b=-4.21,c=3.25,x1=-4.5,x2=-13.5, xm,xmax;
   system("CLS"); // очистка экрана
   //printf ("Введите  k  ");   
   //scanf ("%d", &k);				
   i= -1;
   xm=x1;
   xmax=x1;			
   while (x1>=x2) 
   { 
         s=(a*(x1*x1)+b*x1 +c) *sin(x1);
         if (s<xm) xm=s;
         if (s>xmax) xmax=s;
         x1-=h;
   }	   							
   printf ("min = %.3f max = %.3f  \n", xm,xmax);   
   system("PAUSE"); 
   return 0;  
}
