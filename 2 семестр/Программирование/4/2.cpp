#include <stdio.h>
#include <stdlib.h>
using namespace std;


main()
{
 int i,j,m,n,v,h,max;
  printf ( "����� �����?  ");
 scanf ( "%d", &m );
  printf ( "����� ��������?  ");
 scanf ( "%d", &n );
 
int  **A; // ��������� A - ��������� �� ������ ����������                        
system("CLS");         
A=new int *[m]; // �������� ������ ��� ������ ����������
if (A==NULL)
{
	puts("�� ������ ������������ ������!");
	return 1;
} 
for (i=0; i<m; i++)
  {  A[i]=new int[n]; // �������� ������ ��� i-� ������ 
     if (A[i]==NULL)
     { 
	 	puts("�� ������ ������������ ������ ");
        return 1;
     }
     for (j=0; j<n; j++)   
        A[i][j]=rand()%10;// ��������� ������
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
int  **D; // ��������� D - ��������� �� ������ ����������                              
D=new int *[m+1]; // �������� ������ ��� ������ ����������
if (D==NULL)
{
	puts("�� ������ ������������ ������!");
	return 1;
} 
for (i=0; i<m; i++)
  {  D[i]=new int[n+1]; // �������� ������ ��� i-� ������ 
     if (D[i]==NULL)
     { 
	 	puts("�� ������ ������������ ������ ");
        return 1;
     }
     for (j=0; j<n; j++)
	 {   
        D[i][j]=A[i][j];// ��������� ������
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






delete  A; // ����������� ������ ������� ����������
A=NULL; 
puts("\n");
system("PAUSE");
return 0;
}
