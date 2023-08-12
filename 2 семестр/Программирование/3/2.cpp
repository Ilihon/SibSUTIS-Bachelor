#include <iostream>
#include <math.h>
#include <stdio.h>
#include <ctime> 
#include <stdlib.h>
using namespace std;
int random (int N) { return rand()%N; }
int m =0,k=0;

int chislo(int i, int n, int *a)
{
     if (i<n)
     {
        if (a[i]<0) 
        {
        	k++;
        }      
     chislo(i+1,n,a);
     
     	if (a[n-1-i]>0)
    	{
     	m++;
     	}   
     }
}



main()
{
      int n;
      cin >> n;
      cout << endl;
      float *a,*b;
	  int i;
      
  a = new float [n]; // выделение памяти под n целых чисел
  if ( a == NULL ) // если не удалось выделить память 
 {  
     printf(" Не удалось выделить память ");
    return 1; // выход по ошибке, код ошибки 1
 }
  b = new float [n]; // выделение памяти под n целых чисел
  if ( b == NULL ) // если не удалось выделить память 
 {  
     printf(" Не удалось выделить память ");
    return 1; // выход по ошибке, код ошибки 1
 } 
 srand(time(NULL));
for (i=0;i<n;i++)
      {
	  a[i] = (float)rand()*(-100)/RAND_MAX +50;
      printf("%.2f    ",a[i]);
  	  }
  	  cout << endl;
 for (i=0;i<n;i++)
      {
	  b[i] = *(a+i);
      //printf("%.2f    ",a[i]);
  	  } 	  
      i=0;
      
 cout << endl;
 int k, j, t=0;
 for (i=0;i<n;i++)
      {
      k=i;
      for (j=i+1;j<n;j++)
	  	if (b[j]<b[k])  k=j;
		t=b[i];
		b[i]=b[k];
		b[k]=t;
      printf("%.2f    ",b[i]);
  	  } 
delete a;
delete b;
a=NULL;
b=NULL;    
 
system ("Pause");
return 0;
}
