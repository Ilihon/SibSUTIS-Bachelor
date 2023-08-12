#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     float x,y,t,z;
     scanf("%f%f",&z,&t);
     y=cos(t+z); 
     x=4*log(y*y*y)- z/t;
     printf("\n Output: x=%7.2f " ,x);
     system("PAUSE");
    return 0;
}
