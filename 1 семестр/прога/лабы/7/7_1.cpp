#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 

int main() 
{ 

float a=2.14, b=-4.21, c=3.25, x=-4.5, x1=-33.5, h=0.5, y; 
int n=(x-x1)/h, i=0, j, k; 
printf ("%d\n", n); 
float A[n]; 
for (x;x>=x1;x+=-h) 
{
y=a*x*x*sin(x)+b*x+c; 
A[i]=y; 
printf(" A[i]={%4.3f} \n", A[i]);
i++;
} 
for(i=0;i<n-1;i++) 
for(j=n-2;j>=i;j--)
if(A[j]>A[j-1])
{ 
k=A[j]; 
A[j]=A[j-1];
A[j-1]=k; 
} 
printf ("\n Ot bol'shego' k men'shemu: \n"); 
for(i=0;i<=n-1;i++) 
printf(" A[i]={%4.3f} \n", A[i]); 
system("PAUSE"); 
return 0; 
}
