#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
main()
{
	setlocale(LC_ALL,"Russian"); 
  	int i,n,j; 
  	float  *a,*b; 
  	printf ("��������� �������� new, �������� ������ ��� ���������� ������������ ������ a[n] (n ������� � ����������) � ������ ���������� b[n].    ��������� ��� ������������� ���������� �������. ������������� ������ �� �����������, ���������  ������ ���������� . ������� ��������  � ��������������� ������. ���������� ������.");
 	printf("\n ������ ���������� ���������: "); 
 	scanf ("%d", &n);
 	a = new float [n]; 
 	b = new float [n]; 
  
 	if (a==NULL || b==NULL)  
	{  
    	printf(" Error ");
    	return 1; 
	}
	printf("\n ������: "); 
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
     printf("\n ��������������� ������: ");
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

  
