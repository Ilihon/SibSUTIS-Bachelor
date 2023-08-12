#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

int main(int argc, char *argv[])
{
     int z,t ;  
     float x, y;
     scanf("%d%d",&z,&t);
     y=cos(t+z); 
     x=(4*(log(y*y*y))-z/t );
     printf("\n Output: x=%7.2f " ,x);
     system("PAUSE");
    return 0;
}
