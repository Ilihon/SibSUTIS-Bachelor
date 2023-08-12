#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     int y,z ;  
     float x, t;
     scanf("%d%d",&z,&y); 
     t=sin(2+z); 
     x=(6*t*t)-((1/tan(z))+1)/(y*y);             
     printf("\n Output: x=%7.4f " ,x);
     system("PAUSE");
    return 0;
}
