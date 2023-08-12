#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


main()
{
 int i,j,m,k,v;
  printf ( "Число строк?  ");
 scanf ( "%d", &m );

int  **B; // Объявляем D - указатель на массив указателей                              
B=new int *[m]; // Выделяем память под массив указателей
if (B==NULL)
{
	puts("Не создан динамический массив!");
	return 1;
} 
for (i=0,k=1; i<m; i++,k++)
  {  B[i]=new int[k]; // Выделяем память под i-ю строку 
     if (B[i]==NULL)
     { 
	 	puts("Не создан динамический массив ");
        return 1;
     }
     B[i][0]=i+1;
	 printf(" %d",B[i][0]);  
     for (j=1; j<k; j++,v++)
	 {
	 	B[i][j]=(i+1)*(j+1);
		printf(" %d",B[i][j]);
	 }  
	 puts("\n");
  }
delete  B; // Освобождаем память массива указателей
B=NULL; 
puts("\n");
system("PAUSE");
return 0;
}
