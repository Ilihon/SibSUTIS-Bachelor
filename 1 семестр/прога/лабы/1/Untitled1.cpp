#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     int z,t,y ;  
     double x;
     y=2;
     z=4;
     t=5/(1+y*y);
     x=2*y+3*sinh(t)-z;
     printf("\n Output: x=%7.2f " ,x);
     system("PAUSE");
    return 0;
}
