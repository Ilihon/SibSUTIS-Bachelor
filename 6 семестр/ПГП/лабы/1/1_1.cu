#include <cuda.h>
#include <stdio.h>
__global__ void gTest(float* a){

 a[threadIdx.x+blockDim.x*blockIdx.x]=
(float)(threadIdx.x+blockDim.x*blockIdx.x);

}

int main(){
	float *da, *ha;
	int num_of_blocks=10, threads_per_block=32;
	int N=num_of_blocks*threads_per_block;
	ha=(float*)calloc(N, sizeof(float));
	cudaMalloc((void**)&da, N*sizeof(float));
	gTest<<<dim3(num_of_blocks),
	dim3(threads_per_block)>>>(da);
	cudaDeviceSynchronize();
	cudaMemcpy(ha,da,N*sizeof(float),
	cudaMemcpyDeviceToHost);
	for(int i=0;i<N;i++)
	printf("%g\n", ha[i]);
	free(ha);
	cudaFree(da);
	return 0;
}

