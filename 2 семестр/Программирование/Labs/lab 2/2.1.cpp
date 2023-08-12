#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <clocale>

using namespace std;
void fun();



int main ()
{

 int k;
 printf("¬ведите последовательность: ");
 fun();
 system ("PAUSE");
 return 0;
}


void fun()
{   
int n;
scanf("%d",&n);
if(n == 0) return;
if (n<0) {fun();}
else {fun(); printf(" %i ",n);}  
}

