#include <stdio.h>

#define N (1024 * 1024)
#define FULL_DATA_SIZE (N * 20)

__global__ void kernel(int *a, int *b, int *c){
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < N){
		int idx1 = (idx + 1) % 256;
		int idx2 = (idx + 2) % 256;
		float as = (a[idx] + a[idx1] + a[idx2]) / 3.0f;
		float bs = (b[idx] + b[idx1] + b[idx2]) / 3.0f;
		c[idx] = (as + bs) / 2;
	}
}

int main(){
	cudaDeviceProp prop;
	int whichDevice;
	
	float elapsedTime;

	int *dev_a, *host_a, *dev_b, *host_b, *dev_c, *host_c;
	//int *host_a_page, *host_b_page, *host_c_page;
	
	cudaMalloc((void**)&dev_a, N * sizeof(int));
	cudaMalloc((void**)&dev_b, N * sizeof(int));
	cudaMalloc((void**)&dev_c, N * sizeof(int));
	/*
	host_a_page = (int*)calloc(N, sizeof(int));
	host_b_page = (int*)calloc(N, sizeof(int));
	host_c_page = (int*)calloc(N, sizeof(int));
	memset(host_a_page, 0, N * sizeof(float));
	memset(host_b_page, 0, N * sizeof(float));
	memset(host_c_page , 0, N * sizeof(float));
	memset(dev_a, 0, N * sizeof(float));
	memset(dev_b, 0, N * sizeof(float));
	memset(dev_c , 0, N * sizeof(float));
	*/
	cudaHostAlloc((void**)&host_a, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void**)&host_b, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void**)&host_c, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);

	cudaGetDevice(&whichDevice);
	cudaGetDeviceProperties(&prop, whichDevice);
	if (!prop.deviceOverlap){
		printf("Device does not support overlapping\n");
		return 0;
	}
	
	cudaEvent_t start, stop;
	
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaStream_t stream;
	cudaStreamCreate(&stream);

	cudaEventRecord(start, 0);
	for (int i = 0; i < FULL_DATA_SIZE; i += N){
		cudaMemcpy(host_a + i, dev_a, N * sizeof(int), cudaMemcpyDeviceToHost);
		cudaMemcpy(host_b + i, dev_b, N * sizeof(int), cudaMemcpyDeviceToHost);

		kernel <<< N / 2048, 32, 0, stream >>> (dev_a, dev_b, dev_c);
		cudaMemcpy(dev_c, host_c + i, N * sizeof(int), cudaMemcpyHostToDevice);
	}
	cudaStreamSynchronize(stream);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Time0: %g\n", elapsedTime);
	
	cudaEventRecord(start, 0);
	for (int i = 0; i < FULL_DATA_SIZE; i += N){
		cudaMemcpyAsync(host_a + i, dev_a, N * sizeof(int), cudaMemcpyDeviceToHost, stream);
		cudaMemcpyAsync(host_b + i, dev_b, N * sizeof(int), cudaMemcpyDeviceToHost, stream);
	
		kernel <<< N / 2048, 32, 0, stream >>> (dev_a, dev_b, dev_c);
		cudaMemcpyAsync(dev_c, host_c + i, N * sizeof(int), cudaMemcpyHostToDevice, stream);
	}
	
	cudaStreamSynchronize(stream);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Time1: %g\n", elapsedTime);
	
////// I
	
	int *dev_a0, *dev_b0, *dev_c0;
	int *dev_a1, *dev_b1, *dev_c1; 
	cudaStream_t stream0, stream1;
	cudaStreamCreate(&stream0);
	cudaStreamCreate(&stream1);

	cudaMalloc((void**)&dev_a0, N * sizeof(int));
	cudaMalloc((void**)&dev_a1, N * sizeof(int));
	cudaMalloc((void**)&dev_b0, N * sizeof(int));
	cudaMalloc((void**)&dev_b1, N * sizeof(int));
	cudaMalloc((void**)&dev_c0, N * sizeof(int));
	cudaMalloc((void**)&dev_c1, N * sizeof(int));
	
	cudaEventRecord(start, 0);
	for (int i = 0; i < FULL_DATA_SIZE; i += N * 2){
	///////// Первый поток //////////
		cudaMemcpyAsync(host_a + i, dev_a0, N * sizeof(int), cudaMemcpyDeviceToHost, stream0);
		cudaMemcpyAsync(host_b + i, dev_b0, N * sizeof(int), cudaMemcpyDeviceToHost, stream0);
	
		kernel <<< N / 2048, 32, 0, stream0 >>> (dev_a0, dev_b0, dev_c0);
		cudaMemcpyAsync(dev_c0, host_c + i, N * sizeof(int), cudaMemcpyHostToDevice, stream0);

	//////// Второй поток //////////
		cudaMemcpyAsync(host_a + i + N, dev_a1, N * sizeof(int), cudaMemcpyDeviceToHost, stream1);
		cudaMemcpyAsync(host_b + i + N, dev_b1, N * sizeof(int), cudaMemcpyDeviceToHost, stream1);
	
		kernel <<< N / 2048, 32, 0, stream1 >>> (dev_a1, dev_b1, dev_c1);
		cudaMemcpyAsync(dev_c1, host_c + i + N, N * sizeof(int), cudaMemcpyHostToDevice, stream1);
	}
	
	cudaStreamSynchronize(stream0);
	cudaStreamSynchronize(stream1);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Time2: %g\n", elapsedTime);

	
////// II
	cudaEventRecord(start, 0);
	for (int i = 0; i < FULL_DATA_SIZE; i += N *2){
	//////// Перемежаемые потоки ///////
		cudaMemcpyAsync(dev_a0, host_a + i, N * sizeof(int), cudaMemcpyHostToDevice, stream0);
		cudaMemcpyAsync(dev_a1, host_a + i + N, N * sizeof(int), cudaMemcpyHostToDevice, stream1);
	
		cudaMemcpyAsync(dev_b0, host_b + i, N * sizeof(int), cudaMemcpyHostToDevice, stream0);
		cudaMemcpyAsync(dev_b1, host_b + i + N, N * sizeof(int), cudaMemcpyHostToDevice, stream1);

	kernel <<< N / 2048, 32, 0, stream0 >>> (dev_a0, dev_b0, dev_c0);
	kernel <<< N / 2048, 32, 0, stream1 >>> (dev_a1, dev_b1, dev_c1);

	cudaMemcpyAsync(host_c + i, dev_c0, N * sizeof(int), cudaMemcpyDeviceToHost, stream0);
	cudaMemcpyAsync(host_c + i + N, dev_c1, N * sizeof(int), cudaMemcpyDeviceToHost, stream1);
	}

	cudaStreamSynchronize(stream0);
	cudaStreamSynchronize(stream1);
	
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Time3: %g\n", elapsedTime);

/////// destroy
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	cudaFreeHost(host_a);
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
	cudaFree(dev_a0);
	cudaFree(dev_b0);
	cudaFree(dev_c0);
	cudaFree(dev_a1);
	cudaFree(dev_b1);
	cudaFree(dev_c1);

	return 0;
}
		 
