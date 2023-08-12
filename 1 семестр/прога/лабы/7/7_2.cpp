# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <conio.h>
const int N=15;
main()
{
	system("CLS"); 	
  int i,j,f, A[N], a =0, b =50;
for(i=0;i<N;i++){
A[i] = rand()%20;
printf("%d\n",A[i]);
}
printf("\nVuvod bez povtorov\n");
 for (i=0; i<N; i++) {
        f = 1;
        for (j=0; j<N; j++) 
            if (A[i] == A[j] && i != j) {
                f = 0;
                break;
            }
        if (f == 1) printf("%d\n", A[i]);
    }

system("PAUSE");
return 0;
}
