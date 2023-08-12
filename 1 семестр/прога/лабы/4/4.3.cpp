#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>  

int main()
{ system("CLS");
     float S,i,n;
     printf("¬ведите n ");    scanf("%f",&n);
     for (S=0,i=2; i<=n*2; i+=2) 
            S+= tan(i);     
     printf ("S=%.2f",S);
    system("PAUSE");
    return 0;
}
