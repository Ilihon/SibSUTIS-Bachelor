#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <iostream>
int main()
{   setlocale(LC_ALL,"Russian"); 
	int *b,*c,*d; 
	int i,n,m,k; 
	printf("\n Введите количество элементов: ");
	scanf("%d",&n);
	b=(int *) malloc(n*sizeof(int));
	c=(int *) malloc(n*sizeof(int));
	d=(int *) malloc(n*sizeof(int));
  	if (b==NULL || c==NULL || d==NULL) 
 	{   printf("Error");
    	return 1; 
 	}
	srand(time(NULL));
	for (i=m=k=0;i<n;i++)
  	{  
		 b[i]=rand()%101-50;
	     printf("\n b[%d]=%d\n",i,b[i]);
	     if (b[i]>=0) {
	     	c[m]=b[i];
	     	m++;
		 }
		 else {
		 	d[k]=b[i];
	     	k++;
	}
  } 
  printf("Положительные:");
  for (i=0;i<m;i++)  
  	printf("\n c[%d]=%d\n",i,c[i]);
  printf("Отрицательные:");
  for (i=0;i<k;i++)  
  	printf("\n d[%d]=%d\n",i,d[i]);
  	
  free(b);//освобождает выделенную по адресу b память
  free(c);
  free(d);
  
  b=NULL;
  c=NULL;
  d=NULL;
  
  system("PAUSE");
  return 0;
}

