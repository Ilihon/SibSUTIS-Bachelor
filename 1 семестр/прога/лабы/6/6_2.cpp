# include<stdlib.h>
# include<stdio.h>
#include <math.h> 
//int const N=20;
main() 
{
       int N,i; 
float C[N],f=1,p=1,z=1,x,c=1,j; 
printf("Put N \n"); 
scanf("%d",&N);

while (c!=(N+1)){ 
f*=c; 
c+=1;} 
printf("%.0f\n",f); 
for (i=1;i<=N;i++){ 
p*=i; 
x=N-i; 
for (j=1;j<=x;j++){ 
z*=j; 
} 
C[i]=f/(p*z); 
z=1; 
printf("C[%d]=%.0f\n",i,C[i]);} 
system("PAUSE"); 
return 0; 
}
