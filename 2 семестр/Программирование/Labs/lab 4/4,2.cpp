#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
const int N = 100;
int random (int N) { return rand()%N; }
main()
{	
	int i,j,x=0,y=0,m,n,s=0,s1=0,max=0;
    setlocale(LC_ALL,"Russian"); 
	srand(time(NULL));
	printf ( "\nЧисло строк:  ");
	scanf("%d",&m);
	printf ( "\nЧисло столбцов:  ");
	scanf ( "%d", &n );
	int **D= new int *[m+1];
	for (i=0;i<n+1;i++) D[i]=new int (i+1);
	for (i=0; i<m; i++){ 
		for (j=0; j<n; j++)
    		 {D[i][j]=random(10);
		}
	printf("\n");
	}
   for (i=0; i<m; i++){ 
		for (j=0; j<n; j++){
   		printf("%d         ",D[i][j]);
   }
    	printf("\n");
}
printf ( "\nИзменённый массив\n");
    for (i=0;i<m;i++){
    	for (j=0;j<n;j++){
    		s=s+D[i][j];
    		s1=s1+D[j][i];
    		max=max+D[i][j];
		}
		D[m][i]=s1;
		D[i][n]=s;
		printf("%d %d ",s1,s);
		s=0;
		s1=0;
	}
	D[m][n]=max;
	for (i=0; i<=m; i++){ 
		for (j=0; j<=n; j++){
   		printf("%d      ",D[i][j]);
   }
    	printf("\n");
}
system("pause");
return 0;
}
