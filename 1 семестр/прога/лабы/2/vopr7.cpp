#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
float K, M, N;
float h;
printf("input: K,M,N");
scanf("\n %f%f%f", &K,&M,&N);
if(N<K){
if(N<M){
if(K<M){
h = K;
K = N;
N = M;
M = h;
}
else { h = K;
K = N;
N = h;
}
}
else { h = K;
K = M;
M = N;
N = h;
}
} 
else { if(N>M){
if(M<K){
h = K;
K = M;
M = h;
}
} 
else { h = N;
N = M;
M = h;
}
}
printf("K=%f, M=%f, N=%f", K,M,N);
system("PAUSE");
return 0;

}
