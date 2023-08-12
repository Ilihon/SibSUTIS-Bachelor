#include <stdlib.h>
 #include <stdio.h> 
const int N = 20; 
int random (int N) { return rand()%N; } 
main() 
{ 
int i, a = 0, b = 10; 
float X[N];
for ( i = 0; i < N; i ++ ){ 
X[i] = (float) rand()*(b-a)/RAND_MAX + a; 
printf("X[%d]=%f\n",i,X[i]);} 
printf("Bolshie:\n"); 
for ( i = 1; i < N-1; i ++ ){ 
if (X[i]>X[i-1] && X[i]>X[i+1]) 
printf("X[%d]=%f\n",i,X[i]); 
} 
system("PAUSE"); 
return 0; 
}
