#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>  

int main()
{ system("CLS");
     float S=0,i,n;
    // printf("¬ведите n ");    scanf("%f",&n);
     for (i=0.1; i<2; i+=0.2) 
     {
            S+= log(i);     
              printf ("S=%.3f \n",S);}
     printf ("S=%.3f",S);
    system("PAUSE");
    return 0;
}
