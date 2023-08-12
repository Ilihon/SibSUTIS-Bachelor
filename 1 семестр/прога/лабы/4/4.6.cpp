#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>  

int main()
{ system("CLS");
     float S,i,n,x;
     printf("¬ведите n ");    scanf("%f",&n);
     for (S=0,x=1,i=1; i<=n; x*=-1,i++) 
            S+= i*x;     
     printf ("S=%f",S);
    system("PAUSE");
    return 0;
}
