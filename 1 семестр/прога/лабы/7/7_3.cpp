# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
const int N=20;
const int k=0;
main(){
		system("CLS"); 	
  int i,j,f,B[k],A[N], a =-10, b=10;
for(i=0;i<N;i++){
A[i] =float((rand()%10-5));
printf("%d\n",A[i]);
}
int k=0;
for(i=0;i<N;i++)
if(A[i]>0){
	B[k]=A[i];
	printf("  %d\n", B[k]);
	k+=1;
}
system("PAUSE");
return 0;
}
