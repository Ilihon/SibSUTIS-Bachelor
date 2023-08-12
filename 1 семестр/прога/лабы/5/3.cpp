#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main()
{
      int s,i,a,b,n;
 

   printf ("¬ведите  n  ");   
   scanf ("%d", &n);				
   i= 2;
   b=0;
   while (i<=n) 
   { 
         a=0; 
         for (s=1;s<=i;s++)
         {
             if(i%s==0) 
             {
                       a++; 
             }
         }
         if(a==2)
         {
                 printf ("prostoe chislo = %d \n",i);
                 b++;
         }
                 
         i++;
   }			
   printf ("kolichestvo prostih = %d  \n", b);   
   system("PAUSE"); 
   return 0;  
}

