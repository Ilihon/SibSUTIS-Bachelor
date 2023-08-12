#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>  

int main()
{ system("CLS");
     float S,i,n;
    // printf("¬ведите n ");    scanf("%f",&n);
     for (S=0,n=1,i=0.18; i<=0.36; n++,i+=0.02) 
            S+= pow(i,n);     
     printf ("S=%.3f",S);
    system("PAUSE");
    return 0;
}
