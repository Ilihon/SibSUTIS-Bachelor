#include <stdio.h> 
#include <conio.h> 
const int M = 5; 
const int N = 5; 
main () 

{int i,j; 
float A[M][N], sum; 

sum=0; 
printf("Input elements of massive\n");
for ( i = 0; i < M; i ++ ) 

for ( j = 0; j < N; j ++ ) 

scanf ("%f", &A[i][j]); 

for ( i = 0; i < M; i ++ ) 
{ 
for ( j = 0; j < N; j ++ ) 
{ sum+=A[i][j]; 
} 
for ( j = 0; j < N; j ++ ) {
A[i][j]=A[i][j]/sum;} 
sum=0; 
} 
printf("\n");
for ( i = 0; i < M; i ++ ) 
for ( j = 0; j < N; j ++ ) 
printf("%f\n",A[i][j]); 


return 0; 

}
