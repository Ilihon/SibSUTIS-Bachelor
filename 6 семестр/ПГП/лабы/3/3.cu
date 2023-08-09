#include <cuda.h>
#include <stdio.h>
#include <math.h>

#define CUDA_CHECK_RETURN(value){\
	cudaError_t _m_cudaStat = value;\
	if (_m_cudaStat != cudaSuccess){\
		fprintf(stderr, "Error %s atline %d in file %s\n",\
		 cudaGetErrorString(_m_cudaStat), __LINE__, __FILE__);\
		exit(1);\
	}\
}\

__global__ void gTest1(float* a){
 	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int I = gridDim.x * blockDim.x;
	a[i + j * I] = (float)(i + j * I);
}

__global__ void gTest2(float *a){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int J = gridDim.y * blockDim.y;
	a[j + i * J] = (float)(threadIdx.y + blockIdx.y * blockDim.y);
}

__global__ void transpos(float *a, float *b){
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int I = gridDim.x * blockDim.x;
	b[j + i * I] = a[i + j * I];
}
 
int main(){
 	float elapsedTime;
	cudaEvent_t start, stop;
	float *da, *ha, *db, *hb;

 	int num_of_blocks = 2, threads_per_blocks = 8;
 	int n = num_of_blocks * threads_per_blocks;
	int N = n * n;

	ha = (float*)calloc(N, sizeof(float));
	hb = (float*)calloc(N, sizeof(float));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&da, N * sizeof(float)));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&db, N * sizeof(float)));

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);
	gTest1<<<dim3(num_of_blocks, num_of_blocks), dim3(threads_per_blocks, threads_per_blocks)>>>(da);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	fprintf(stderr, "%f\n", elapsedTime);


	cudaEventRecord(start, 0);
	gTest2<<<dim3(num_of_blocks, num_of_blocks), dim3(threads_per_blocks, threads_per_blocks)>>>(db);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	fprintf(stderr, "%f\n", elapsedTime);

	cudaDeviceSynchronize();
	printf("\nGenerated matrix:\n");
	CUDA_CHECK_RETURN(cudaMemcpy(ha, da, N * sizeof(float), cudaMemcpyDeviceToHost));
	for (int i = 0; i < sqrt(N); i++) {
		for (int j = 0; j < sqrt(N); j++) {
			printf("%g  ", ha[j + i * n]);
		}
		printf("\n");
	}
	printf("\n\n");

	transpos<<<dim3(num_of_blocks, num_of_blocks), dim3(threads_per_blocks, threads_per_blocks)>>>(da, db);
	cudaDeviceSynchronize();
	printf("\nTransposited matrix:\n");
	cudaMemcpy(hb, db, N * sizeof(float), cudaMemcpyDeviceToHost);
 	for(int i = 0; i < sqrt(N); i++){
		for(int j = 0; j < sqrt(N); j++){
			printf("%g  ", hb[j + i * n]);
		}
		printf("\n");
	}

	cudaEventDestroy(start);
	cudaEventDestroy(stop);
 	free(ha);
	free(hb);
 	cudaFree(da);
	cudaFree(db);
 	return 0;
}
