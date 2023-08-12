#include <stdio.h>
#include <stdlib.h>
#include <iostream>
main()
{
	setlocale(LC_ALL,"Russian"); 
	int i,j,m,n,str=0,sto=0,x,y,all=0;
	int **a,**d;
	printf ( "\nЧисло строк:  ");
	scanf("%d",&m);
	printf ( "\nЧисло столбцов:  ");
	scanf("%d",&n);
	a=new int*[m];
	d=new int*[m+1];
	for (i=0; i<m; i++)
		{
			a[i]=new int[n];
		}
	for (i=0; i<m+1; i++)
		{
			d[i]=new int[n+1];
		}	
	for (i=0; i<m; i++)
	 {  
	 	for (j=0; j<n; j++)
	    { a[i][j]=rand()%5;
	      printf("%4d",a[i][j]);			
	    }
	    puts("\n");
	 }
	 	puts("\n");
		x=0;y=0;
		 for (i=0; i<m+1; i++)
	 {  
	 	for (j=0; j<n+1; j++)
	    { 
			if (j<n&&i<m)
			{
				d[i][j]=a[x][y];
				str+=a[x][y];
				all+=a[x][y];
				y++;
			}	   	
			else d[i][j]=str;				
	    }
	    if (i<m) x++;
	    str=0;
		y=0;
	 }

		 for (j=0; j<n; j++)
	 {
	 	for (i=0; i<m+1; i++)
	 	{
	 		if (j<n&&i<m)
	 		{
			 	sto+=d[i][j];
				all+=d[i][j];			
			}
			else d[i][j]=sto;			
	 	}
	 	sto=0;
	 }	 
	 
	 	d[m][n]=all/2;				
		 		 		 	
   	 		 		 		 		 		 		 	 
		 for (i=0; i<m+1; i++)
	 {  
	 	for (j=0; j<n+1; j++)
	    { 
	      printf("%4d",d[i][j]);		//Выводим массив//
	    }
	    puts("\n");

	 }
	  delete a;
	  delete d; 
	 puts("\n");
	 system("PAUSE");
	 return 0;
	}
