#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     float x, y,z,t;
     scanf("%f%f",&z,&t);
     y=tan (t)+z; 
     x=((8*z*z)+1)/(y*exp(t)+t*t);
     printf("\n Output: x=%7.2f " ,x);
     system("PAUSE");
    return 0;
}
