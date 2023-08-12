#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>  

int main()
{ system("CLS");
     float S,i;
     for (S=0,i=1; i<=25; i++) 
            S+= sin (i);     
     printf ("S=%f",S);
    system("PAUSE");
    return 0;
}
