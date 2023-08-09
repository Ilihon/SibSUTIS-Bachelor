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

// вывод матрицы
void output(float *a, int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++)
			printf("%g  ", a[j + i * N]);
		printf("\n");
	}
	printf("\n\n");
} 

// инициализация матрицы
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

// простое транспонирование
__global__ void transpos(float *a, float *b){
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int I = gridDim.x * blockDim.x;
	b[j + i * I] = a[i + j * I];
}

// наивное использование разделяемой памяти (динамически)
__global__ void transpos21(float *a, float *b){
	extern __shared__ float buffer[];
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int N = blockDim.x * gridDim.x;

	buffer[threadIdx.y + threadIdx.x * blockDim.y] = a[i + j * N];
	__syncthreads();
	
	i = threadIdx.x + blockIdx.y * blockDim.x;
	j = threadIdx.y + blockIdx.x * blockDim.y;
	
	b[i + j * N] = buffer[threadIdx.x + threadIdx.y * blockDim.x];
}

#define SH_DIM 32

//алгоритм использования разделяемой памяти (статически)
__global__ void transpos22(float *a, float *b){
	__shared__ float buffer[SH_DIM][SH_DIM];
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int N = blockDim.x * gridDim.x;

	buffer[threadIdx.y][threadIdx.x] = a[i + j * N];
	__syncthreads();

	i = threadIdx.x + blockIdx.y * blockDim.x;
	j = threadIdx.y + blockIdx.x * blockDim.y;
	b[i + j * N] = buffer[threadIdx.x][threadIdx.y];
}

// алгоритм разрешения конфликта банков
__global__ void transpos3(float *a, float *b){
	__shared__ float buffer[SH_DIM][SH_DIM + 1];
	
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int N = blockDim.x * gridDim.x;

	buffer[threadIdx.y][threadIdx.x] = a[i + j * N];
	__syncthreads();
	
	i = threadIdx.x + blockIdx.y * blockDim.x;
	j = threadIdx.y + blockIdx.x * blockDim.y;
	b[i + j * N] = buffer[threadIdx.x][threadIdx.y];
}
 
int main(int argc, char* argv[]){
	if(argc < 3){
		printf("USAGE: matrix <dimension of matrix> <dimension_of_threads\n");
		return -1;
	}
	int N = atoi(argv[1]);
	int dim_of_threads = atoi(argv[2]);
	if(N % dim_of_threads){
		printf("change dimensions\n");
		return -1;
	}
	int dim_of_blocks = N / dim_of_threads;
	const int max_size = 1<<8;
	if(dim_of_blocks > max_size){
		printf("too many blocks\n");
		return -1;
	} 
 	float *da, *h, *db;
 	h = (float*)calloc(N * N, sizeof(float));
	//hb = (float*)calloc(N * N, sizeof(float));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&da, N * N * sizeof(float)));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&db, N * N * sizeof(float)));
	gTest1<<<dim3(dim_of_blocks, dim_of_blocks), dim3(dim_of_threads, dim_of_threads)>>>(da);
	CUDA_CHECK_RETURN(cudaDeviceSynchronize());
	memset(h, 0.0, N * N * sizeof(float));
	cudaMemcpy(h, da, N * N * sizeof(float), cudaMemcpyDeviceToHost);
	//output(h, N);
	
	// простое транспонирование
	transpos<<<dim3(dim_of_blocks, dim_of_blocks), dim3(dim_of_threads, dim_of_threads)>>>(da, db);
	CUDA_CHECK_RETURN(cudaDeviceSynchronize());
	memset(h, 0.0, N * N * sizeof(float));
 	CUDA_CHECK_RETURN(cudaMemcpy(h, db, N * N * sizeof(float), cudaMemcpyDeviceToHost));
	//output(h, N);

	// наивное разделение памяти (динамически)
	transpos21<<<dim3(dim_of_blocks, dim_of_blocks), dim3(dim_of_threads, dim_of_threads),dim_of_threads * dim_of_threads * sizeof(float)>>>(da, db);
	CUDA_CHECK_RETURN(cudaDeviceSynchronize());
	memset(h, 0.0, N * N * sizeof(float));
	CUDA_CHECK_RETURN(cudaMemcpy(h, db, N * N * sizeof(float), cudaMemcpyDeviceToHost));
	//output(h, N);

	// наиваное разделение памяти (статически)
	transpos22<<<dim3(dim_of_blocks, dim_of_blocks), dim3(dim_of_threads, dim_of_threads)>>>(da,db);
	cudaDeviceSynchronize();
	memset(h, 0.0, N * N * sizeof(float));
	cudaMemcpy(h, db, N * N * sizeof(float), cudaMemcpyDeviceToHost);
	//output(h, N);

	// разрешение конфликтов банков
	transpos3<<<dim3(dim_of_blocks, dim_of_blocks), dim3(dim_of_threads, dim_of_threads)>>>(da, db);
	cudaDeviceSynchronize();
	memset(h, 0.0, N * N * sizeof(float));
	cudaMemcpy(h, db, N * N * sizeof(float), cudaMemcpyDeviceToHost);
	//output(h, N);
	
 	free(h);
 	cudaFree(da);
	cudaFree(db);
 	return 0;
}

