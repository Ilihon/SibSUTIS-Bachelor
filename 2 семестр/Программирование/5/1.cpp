#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


main()
{
 int i,j,m,k,v;
  printf ( "Число строк?  ");
 scanf ( "%d", &m );

 
int  *A; // Объявляем A - указатель на массив указателей                        
A = new  int[m]; // Выделяем память под массив указателей
  if (A==NULL)
   {  
   	  puts("Не создан динамический массив!");
      return 1;
   } 

     for (j=0; j<m; j++) 
	 {  
        A[j]=rand() % 10;
     }
  for (i=0; i<m; i++)
  { 
     printf(" %d",A[i]);
  }
puts("\n");

  printf ( "Число столбцов?  ");
 scanf ( "%d", &k );
 if (k>m)
 {
 	printf("%d > %d", k,m);
 	return 1;
 }


v=0;
int g=0;
int  **B; // Объявляем D - указатель на массив указателей                              
B=new int *[k]; // Выделяем память под массив указателей
if (B==NULL)
{
	puts("Не создан динамический массив!");
	return 1;
} 
for (i=0; i<m; i++,g++)
  {  B[i]=new int[k]; // Выделяем память под i-ю строку 
     if (B[i]==NULL)
     { 
	 	puts("Не создан динамический массив ");
        return 1;
     }
     for (j=0; j<k; j++,v++)
	 {  
	 	if (v>=m)
	 	{
		B[g][j]=0;
		i=m;
		}
		else 
        {
		B[g][j]=A[v];
		}
        printf(" %d",B[g][j]);
	 }  
	 puts("\n");
  }
delete  A; // Освобождаем память массива указателей
A=NULL; 
puts("\n");
system("PAUSE");
return 0;
}
