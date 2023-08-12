#include <stdlib.h> 
#include <stdio.h> 
#include <conio.h> 
#include <time.h> 

const int N = 20; 
int random (int N) {return rand() % N; } 

int main() 
{ 
int a= 0, b= 20, i, j, c, k, C[N], D[N]; 
 
srand(time(NULL));                           //генерирует массивы С и Д
for(i= 0; i<N; i++) C[i] = random(b-a+1) + a; 
for(i= 0; i<N; i++) D[i] = random(b-a+1) + a; 
 
 
 //вовод их на экран
printf("\n Array C: \n"); for(i=0; i<N; i++) printf(" %d", C[i]); 
printf("\n Array D: \n"); for(i=0; i<N; i++) printf(" %d", D[i]); 

for(i= N-1; i>=1; i=i-1) //Сортировка С по возростанию
for(j=0; j<i; j++) 
if(C[j]>C[j+1]) {c= C[j]; C[j] = C[j+1]; C[j+1] = c; } 

for(i= N-1; i>=1; i=i-1) //Сортировка С по возростанию
for(j=0; j<i; j++) 
if(D[j]>D[j+1]) {c= D[j]; D[j] = D[j+1]; D[j+1] = c; } 



printf("\n Array D: \n"); for(i=0; i<N; i++) printf(" %d", D[i]); 
printf("\n Array C: \n"); for(i=0; i<N; i++) printf(" %d", C[i]); 




int E[N*2] = {}; i= j= k= 0; 
 
for(i=0,k=0;i<=N-1; i++,k+=2)
{
E[k]=C[i]; E[k+1]=D[i];
         
for(a= k+1; a>=1; a--)
for(j=0; j<a; j++) 
if(E[j]>E[j+1]) {c= E[j]; E[j] = E[j+1]; E[j+1] = c; }       
         
         
}
              


printf("\n Array E: \n"); for(i=0; i<N*2; i++) printf(" %d \n", E[i]); 
getch(); 
return 0; 
}

