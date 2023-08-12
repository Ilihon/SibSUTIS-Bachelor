#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL,"RUS");
	srand(time(NULL));
	int *A,i,j,m,k,l,s; l=0;
	printf("Введите число элементов в массиве: ");
	scanf("%d",&m);
	A=new int [m];
	for (i=0;i<m;i++)
	{
		A[i]=rand()%9+1;
		printf("%d ",A[i]);
	}
	printf("\n");
	printf("Введите число элементов в каждой строке: ");
	scanf("%d",&k);
	if(m%k==0)
		s=m/k;
	else
		s=m/k+1;
	int **B;
	B=new int*[s];
	for (i=0;i<s;i++)
		B[i]=new int[k];
	for(i=0;i<s;i++)
		for(j=0;j<k;j++)
		{
			if(l<m)
			{
				B[i][j]=A[l];
				l++;
			}
			else
				B[i][j]=0;
		}
	for(i=0;i<s;i++)
	{
		for(j=0;j<k;j++)
			printf("%d ",B[i][j]);
		printf("\n");
	}
	return 0;
	delete A;
	for (i=0;i<s;i++)
		delete B[i];
}
