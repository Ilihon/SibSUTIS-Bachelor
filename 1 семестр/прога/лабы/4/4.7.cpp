#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{    system("CLS"); 
     int S,n,i;
      printf("¬ведите n ");    scanf("%d",&n);
     for (S=1,i=1; i<=n; i++) 
            S*=i;     
     printf ("n=%d S=%d",n,S);
    system("PAUSE");
    return 0;
}
