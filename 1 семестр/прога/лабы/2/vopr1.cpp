#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{   float x1,x2,x3,x4,x5,x6,y1,y2,y ;
    printf("Input 6 chisel ");   scanf("%f%f%f%f%f%f",&x1,&x2,&x3,&x4,&x5,&x6);
    y1=x1+x2+x3+x4+x5+x6; y2=x1*x2*x3*x4*x5*x6;
    y=0;
    if (y1>y2)     y=y1-y2;
    if (y1<y2)   y=y2-y1;
  printf("chislo=%8.2f \n",y); 
   system("PAUSE");
   return EXIT_SUCCESS;
}
