#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


main()
{
 int i,j,m,k,v;
  printf ( "����� �����?  ");
 scanf ( "%d", &m );

 
int  *A; // ��������� A - ��������� �� ������ ����������                        
A = new  int[m]; // �������� ������ ��� ������ ����������
  if (A==NULL)
   {  
   	  puts("�� ������ ������������ ������!");
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

  printf ( "����� ��������?  ");
 scanf ( "%d", &k );
 if (k>m)
 {
 	printf("%d > %d", k,m);
 	return 1;
 }


v=0;
int g=0;
int  **B; // ��������� D - ��������� �� ������ ����������                              
B=new int *[k]; // �������� ������ ��� ������ ����������
if (B==NULL)
{
	puts("�� ������ ������������ ������!");
	return 1;
} 
for (i=0; i<m; i++,g++)
  {  B[i]=new int[k]; // �������� ������ ��� i-� ������ 
     if (B[i]==NULL)
     { 
	 	puts("�� ������ ������������ ������ ");
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
delete  A; // ����������� ������ ������� ����������
A=NULL; 
puts("\n");
system("PAUSE");
return 0;
}
