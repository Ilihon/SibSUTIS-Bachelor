#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL,"RUS");
	int **A,i,j,k,n;
	printf("¬ведите размер таблицы умножени€: ");
	scanf("%d",&n);
	n=n+1;
	A=new int*[n];
	for (i=0;i<n;i++)
	{
		A[i]=new int[i+1];
		for (j=0,k=1;j<=i;j++,k++)
			A[i][j]=i*k;	
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<i;j++)
			printf("%d ",A[i][j]);
		printf("\n");
	}
	for(i=0;i<n;i++)
		delete A[i];
	return 0;
}
