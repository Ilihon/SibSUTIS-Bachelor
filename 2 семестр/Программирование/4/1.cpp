#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int n=5; // количество элементов в строке
typedef int rown[n];//rown - новый тип: массив (строка) из n целых чисел
typedef int trob[n-1];

main()
{
 int i,j,m;
 rown *b; // указатель на строку
 trob *c;   // указатель на целое
 printf ( "Число строк?  ");
 scanf ( "%d", &m );
 b = new rown[m]; // выделяем память под матрицу по адресу b, m строк
                                // по n элементов в строке 
if ( b == NULL ) 
{   printf("Не удалось выделить память");
    return 1; // выход по ошибке, код ошибки 1
}
c=new trob[m-1]; // выделяем память под массив сумм строк (m строк)
if ( c == NULL ) 
{   printf("Не удалось выделить память");
    return 1; // выход по ошибке, код ошибки 1
}
// заполняем матрицу случайными числами
for (i=0; i<m; i++)
 {  for (j=0; j<n; j++)
    { b[i][j]=(rand()%10)+1;
      printf("%4d",b[i][j]);
    }
    puts("\n");
 }
 int max=0;
 int ip,jp;
 for (i=0; i<m; i++)
 {   
  for (j=0;j<n;j++)
  {
   if (b[i][j]>max)
   {
    max=b[i][j];
    ip=i;
    jp=j;
   }                    
  }        
 }
  puts("\n");
  printf("%4d %4d",ip,jp);
  puts("\n");
  puts("\n");



for (i=0; i<m; i++)
 {  for (j=0; j<n; j++)
    { 
      if (i==ip)
      b[i][j]=0;
      if (j==jp)
      b[i][j]=0;
      printf("%4d",b[i][j]);
    }
    puts("\n");
 }
puts("\n");

for (i=0,ip=0; i<m; i++)
 {  
    for (j=0,jp=0; j<n; j++)
    { 
      if (b[i][j]!=0)
      {
       c[ip][jp]=b[i][j];       
       printf("%4d",c[ip][jp]);
       jp++;
      }
    }
   		if (jp==n-1)
   		ip++;
    puts("\n");
 }
 
 
 delete b; // освобождаем память, занятую под матрицу b
 delete c; // освобождаем память, занятую под массив c 
 puts("\n");
 system("PAUSE");
 return 0;
}
