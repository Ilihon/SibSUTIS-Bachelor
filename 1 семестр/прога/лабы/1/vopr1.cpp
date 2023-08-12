#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     int z ;  
     float x, y, t;
     scanf("%d%f",&z,&t);
     y=t+2*(cos(z)/sin(z)); 
     x=(3*(y*y))/(4*tan(z)-2*(t*t));
     printf("\n Output: x=%7.2f " ,x);
     system("PAUSE");
    return 0;
}
