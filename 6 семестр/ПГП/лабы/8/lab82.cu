#include <stdio.h>
#include <malloc.h>

#pragma comment (lib, "cufft.lib")
#include <cufft.h>

#define NX 365
#define BATCH 1
#define pi 3.141592

__global__ void gInitData(cufftComplex *data){
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	
	float x = i * 2.0F * pi / NX;
	data[i].x = cosf(x) - 3.0F * sinf(x);
	data[i].y = 0.0F;
}

int main(){
	cufftHandle plan;
	cufftComplex *data;
	cufftComplex *data_h = (cufftComplex*)calloc(NX, sizeof(cufftComplex));
	
	cudaMalloc((void**) &data, sizeof(cufftComplex) * NX * BATCH);

	FILE *f = fopen("file.txt", "r");
	for (int i = 0; i < NX; i++){
		float a, b, c;
		fscanf(f, "%f%f%f%f", &a, &b, &data_h[i].x, &c);
		if (data_h[i].x == 999 && i != 0)
			data_h[i].x = data_h[i-1].x;
		data_h[i].y = 0;
	}		

	cudaMemcpy(data, data_h, NX * sizeof(cufftComplex), cudaMemcpyHostToDevice);
	
	if (cudaGetLastError() != cudaSuccess){
		printf("Cuda error: Failed to allocate\n");
		return -1;
	}

	//gInitData <<< 1, NX >>> (data);
	//cudaDeviceSynchronize();

	if (cufftPlan1d(&plan, NX, CUFFT_C2C, BATCH) != CUFFT_SUCCESS){
		printf("CUFFT error: Plan creation failed\n");
		return -1;
	}

	if (cufftExecC2C(plan, data, data, CUFFT_FORWARD) != CUFFT_SUCCESS){
		printf("CUFFT error: EXECC2C Forward failed\n");
		return -1;
	}

	if (cudaDeviceSynchronize() != cudaSuccess){
		printf("Cuda error: failed to synchronize\n");
		return -1;
	}

	cudaMemcpy(data_h, data, NX * sizeof(cufftComplex), cudaMemcpyDeviceToHost);

	for (int i = 0; i < NX; i++)
		printf("%g    \t%g\n", data_h[i].x, data_h[i].y);
	
	cufftDestroy(plan);
	cudaFree(data);
	free(data_h);

	return 0;
} 
