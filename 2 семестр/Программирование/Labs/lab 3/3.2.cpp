#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
main()
{
	setlocale(LC_ALL,"Russian"); 
  	int i,n,j; 
  	float  *a,*b; 
  	printf ("Используя оператор new, выделить память под одномерный динамический массив a[n] (n вводить с клавиатуры) и массив указателей b[n].    Заполнить его вещественными случайными числами. Отсортировать массив по возрастанию, используя  массив указателей . Вывести исходный  и отсортированный массив. Освободить память.");
 	printf("\n Ввести количество элементов: "); 
 	scanf ("%d", &n);
 	a = new float [n]; 
 	b = new float [n]; 
  
 	if (a==NULL || b==NULL)  
	{  
    	printf(" Error ");
    	return 1; 
	}
	printf("\n Массив: "); 
 	for (i = 0; i<n; i ++ ) 
 	{ 
   		a[i]=(float)rand()*20/RAND_MAX;
   		printf ("\n a[%d] = %f", i, a[i]);
 	}
	  
  	printf("\n");
  	
  	for (i=1; i<n; i++) {
        for (j=1; j<n-i; j++) 
            if (a[j]>a[j+1]) 
			{
                *(b+j)=a[j];
                a[j]=a[j+1];
                a[j+1]=*(b+j);
            }
    }
     printf("\n Отсортированный массив: ");
	for (i=0; i<n; i++) 
     	printf ("\n a[%d] = %f", i, a[i]); 
     	printf("\n");  	
    
   

	   
 	delete a; 
 	a=NULL;
 	
 	delete b; 
 	b=NULL;
 	
 	system("pause");
 	return 0;
}

  
