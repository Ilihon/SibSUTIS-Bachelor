#include <stdio.h>
#include <stdlib.h>
using namespace std;


main()
{
 int i,j,m,n,v,h,max;
  printf ( "Число строк?  ");
 scanf ( "%d", &m );
  printf ( "Число столбцов?  ");
 scanf ( "%d", &n );
 
int  **A; // Объявляем A - указатель на массив указателей                        
system("CLS");         
A=new int *[m]; // Выделяем память под массив указателей
if (A==NULL)
{
	puts("Не создан динамический массив!");
	return 1;
} 
for (i=0; i<m; i++)
  {  A[i]=new int[n]; // Выделяем память под i-ю строку 
     if (A[i]==NULL)
     { 
	 	puts("Не создан динамический массив ");
        return 1;
     }
     for (j=0; j<n; j++)   
        A[i][j]=rand()%10;// Заполняем строку
  }
  for (i=0; i<m; i++)
  {  for (j=0; j<n; j++)
         printf(" %d",A[i][j]);
     printf("\n");
  }
puts("\n");


max=0;
v=0;
h=0;
int  **D; // Объявляем D - указатель на массив указателей                              
D=new int *[m+1]; // Выделяем память под массив указателей
if (D==NULL)
{
	puts("Не создан динамический массив!");
	return 1;
} 
for (i=0; i<m; i++)
  {  D[i]=new int[n+1]; // Выделяем память под i-ю строку 
     if (D[i]==NULL)
     { 
	 	puts("Не создан динамический массив ");
        return 1;
     }
     for (j=0; j<n; j++)
	 {   
        D[i][j]=A[i][j];// Заполняем строку
     	v=v+D[i][j];
	 }  
	 D[i][n]=v;
	 max=max+v;
	 v=0;
  }
  D[m]=new int[n+1]; 
  D[m][n]=max;
  
 for (i=0; i<n; i++)
  { 
  for (j=0; j<m; j++)
	 {   
     	h=h+D[j][i];
	 }  
	 D[m][i]=h;
	 h=0;
  } 
  
  
  for (i=0; i<=m; i++)
  {  
  for (j=0; j<=n; j++)
         printf(" %d",D[i][j]);
     printf("\n");
  }
puts("\n");






delete  A; // Освобождаем память массива указателей
A=NULL; 
puts("\n");
system("PAUSE");
return 0;
}
