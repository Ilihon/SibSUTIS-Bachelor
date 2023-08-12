#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
const int N = 100;
int random (int N) { return rand()%N; }
int main()
{   setlocale(LC_ALL,"Russian"); 
	const int n=5,n1=4;
	typedef int rown[n];
	int i,j,x=0,y=0,m,k,max=0;
	rown *b; rown *c;
	srand(time(NULL));
	printf ( "\nЧисло строк:  ");
	scanf ( "%d", &m );
	b = new rown[m]; 
	if ( b == NULL ) 
	{   printf("Не удалось выделить память");
    return 1;
	}
	for (i=0; i<m; i++){ 
		for (j=0; j<n; j++)
    		{ b[i][j]=random(41);
      		printf( "%d    ",b[i][j] );}
			printf("\n");}
    for (i=0; i<m; i++){ 
		for (j=0; j<n; j++){
			if(max<=b[i][j]) {
			x=i;
			y=j;
			max=b[i][j];
			}
		}}
	printf ( "max=%d x=%d   y=%d",max,x,y);
	printf ( "\nИзменённый массив:\n");
	if ((x!=m-1) and (y!=n-1)){
		for (i=0; i<m; i++){ 
			for (j=0; j<n; j++){
				if (i==x) i++;
				if (j==y) j++;
				printf("%d   ",b[i][j]);}printf("\n");}}
	else {if(x==m-1) for (i=0; i<m-1; i++){ 
			for (j=0; j<n; j++){
				if (j==y) j++;
				printf("%d   ",b[i][j]);}printf("\n");}
		if (y==n-1) for (i=0; i<m; i++){ 
			for (j=0; j<n-1; j++){
				if (i==x) i++;
				printf("%d   ",b[i][j]);}printf("\n");}
		}
system("pause");
return 0;
}
