#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <iostream>
#include <fstream> 

using namespace std;

#define CUDA_CHECK_RETURN(value) {\
	cudaError_t _m_cudaStat=value;\
	if(_m_cudaStat!=cudaSuccess){\
		fprintf(stderr,"Error %s at line %d in file %s\n",cudaGetErrorString(_m_cudaStat),__LINE__,__FILE__);\
		exit(1);\
	}\
}

__global__ void Vector(float* a, float* b, float* c, int N) {
	int i = threadIdx.x + blockDim.x*blockIdx.x;
	if (i < N){
		a[i] = i + 1;
		b[i] = i + 1;
		c[i] = a[i] + b[i];
	}
	else {
		return;
	}
}

int main() {
	int N;
	float *da, *db, *dc, *a, *b, *c;
	float sum = 0, MEGA_sum=0;
	ofstream benchmark_output;
	benchmark_output.open("bench result.csv", ios_base::app);
	benchmark_output << "ThreadsPerBlock;Block;Timer" << endl;

	for (int k = 1 << 1; k <= 1 << 10; k = k << 1) {
		sum = 0;
		fprintf(stderr, "Threads per Blocks(%i):\n", k);
		for (int j = 10; j <= 23; j++)
		{
			N = 1 << j;
			a = (float*)calloc(N, sizeof(float));
			b = (float*)calloc(N, sizeof(float));
			c = (float*)calloc(N, sizeof(float));

			for (int i = 0; i < N; i++) {}

			CUDA_CHECK_RETURN(cudaMalloc((void**)&da, N * sizeof(float)));
			CUDA_CHECK_RETURN(cudaMalloc((void**)&db, N * sizeof(float)));
			CUDA_CHECK_RETURN(cudaMalloc((void**)&dc, N * sizeof(float)));

			float elapsedTime;

			cudaEvent_t start, stop;
			cudaEventCreate(&start);
			cudaEventCreate(&stop);

			cudaEventRecord(start, 0);
			Vector <<< N / k, k >>> (da, db, dc, N);
			cudaEventRecord(stop, 0);
			cudaEventSynchronize(stop);
			cudaEventElapsedTime(&elapsedTime, start, stop);
			fprintf(stderr, "%f\n", elapsedTime);
			sum += elapsedTime;
			CUDA_CHECK_RETURN(cudaGetLastError());
			CUDA_CHECK_RETURN(cudaMemcpy(a, da, N * sizeof(float), cudaMemcpyDeviceToHost));
			CUDA_CHECK_RETURN(cudaMemcpy(b, db, N * sizeof(float), cudaMemcpyDeviceToHost));
			CUDA_CHECK_RETURN(cudaMemcpy(c, dc, N * sizeof(float), cudaMemcpyDeviceToHost));
			cudaEventDestroy(start);
			cudaEventDestroy(stop);
			free(a);
			free(b);
			free(c);
			cudaFree(da);
			cudaFree(db);
			cudaFree(dc);
			benchmark_output << k << ";" << N << ";" << elapsedTime << endl;
		}
		fprintf(stderr, "\nSummary time: %f\n\n", sum);
		MEGA_sum += sum;
	}
	benchmark_output.close();
	fprintf(stderr, "\nMEGA Summary time: %f\n\n", MEGA_sum);
	return 0;
}

