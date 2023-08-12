#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     int z,t ;  
     float x, y;
     scanf("%d%d",&z,&t);
     y=sin(t); 
     x=(4*(y*y))/(4*y*exp(z) - 2*t*t*t);
     printf("\n Output: x=%7.2f " ,x);
     system("PAUSE");
    return 0;
}
