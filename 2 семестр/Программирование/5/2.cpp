#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


main()
{
 int i,j,m,k,v;
  printf ( "����� �����?  ");
 scanf ( "%d", &m );

int  **B; // ��������� D - ��������� �� ������ ����������                              
B=new int *[m]; // �������� ������ ��� ������ ����������
if (B==NULL)
{
	puts("�� ������ ������������ ������!");
	return 1;
} 
for (i=0,k=1; i<m; i++,k++)
  {  B[i]=new int[k]; // �������� ������ ��� i-� ������ 
     if (B[i]==NULL)
     { 
	 	puts("�� ������ ������������ ������ ");
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
delete  B; // ����������� ������ ������� ����������
B=NULL; 
puts("\n");
system("PAUSE");
return 0;
}
