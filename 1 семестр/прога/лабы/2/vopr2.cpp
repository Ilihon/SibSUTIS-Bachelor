#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{   float x1,x2,x3,x4,x5,y ;
    printf("Input 5 chisel ");   scanf("%f%f%f%f%f",&x1,&x2,&x3,&x4,&x5);
    y=0;
    if (x1>0)    y+=x1;
    if (x2>0)    y+=x2;
    if (x3>0)    y+=x3;
    if (x4>0)    y+=x4;
    if (x5>0)    y+=x5;
  printf("chislo=%8.2f \n",y); 
   system("PAUSE");
   return EXIT_SUCCESS;
}
