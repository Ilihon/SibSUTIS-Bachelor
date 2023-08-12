#include <stdlib.h>
#include <stdio.h>
const int N = 20;
int random (int N) { return rand()%N; }
main()
{ system("CLS"); 
  int i=0, A[N], a = -10, b = 10;
  for ( i = 0; i < N; i ++ )
     A[i] = random(b-a+1) + a;
      printf("\nMassiv\n"); 
  for ( i = 0; i < N; i ++ )
  printf("%4d\n",A[i]);
  for ( i = 0; i < N; i ++ ){
  
  if(A[i]>0)
  printf("pol=%d\n",A[i]);
  else
  printf("otr=%d\n",A[i]);
}
  system("PAUSE");
  return 0;
}
