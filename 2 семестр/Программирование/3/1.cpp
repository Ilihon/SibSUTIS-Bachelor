#include <iostream>
#include <math.h>
#include <stdio.h>
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
      int a[n],i;
      
      for (i=0;i<n;i++)
      {
	  a[i] = random(101)-50;
      printf("%d    ",a[i]);
  	  }
  	  cout << endl;
      i=0;
chislo(i,n,a); 
cout << k << endl;
cout << m;
int *d;
int *c;
d=(int *) malloc(k*sizeof(int));
if ( d == NULL ) // если не удалось выделить память 
 {  
     printf(" Не удалось выделить память ");
    return 1; // выход по ошибке, код ошибки 1
 }
 
c=(int *) malloc(m*sizeof(int));
if ( c == NULL ) // если не удалось выделить память 
 {  
     printf(" Не удалось выделить память ");
    return 1; // выход по ошибке, код ошибки 1
 }
 cout << endl;
int j=0,v=0;
  	for (i=0,j=0,v=0;i<n;i++)
   	{   
     if (a[i]<0) 
     {
     	d[j]=a[i];
		j++;
	 }
	  if (a[i]>=0) 
     {
     	c[v]=a[i];
		v++;  	
	 }
  	}

for (i=0;i<k;i++)
	printf("%d   ",d[i]);	
free(d);
d=NULL;

cout<< endl;	
for (i=0;i<m;i++)
	printf("%d   ",c[i]);	
free(c);
c=NULL;
	
system ("Pause");
return 0;
}
