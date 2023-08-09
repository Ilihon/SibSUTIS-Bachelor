#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>

#include <thrust/fill.h>
#include <thrust/sequence.h>

using namespace thrust;

struct saxpy_functor
{
	const float a;
	saxpy_functor(float _a) : a(_a) {}
	__host__ __device__ float operator()(float x, float y){
		return a * x + y;
	}
};

void saxpy(float a, thrust::device_vector<float>& x, thrust::device_vector<float>& y){
	saxpy_functor func(a);
	
	transform(x.begin(), x.end(), y.begin(), y.begin(), func);
}

__global__ void cuda_saxpy(float *a, float *b, float alpha){
	int j = threadIdx.x + blockIdx.x * blockDim.x;
	
	a[j] = j;
	b[j] = 0.87; 
	a[j] = alpha * a[j] + b[j];
}

int main(){
	float elapsedTime;
	cudaEvent_t start, stop;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	thrust::host_vector<float> h1(1 << 24);
	thrust::host_vector<float> h2(1 << 24);
	thrust::sequence(h1.begin(), h1.end());
	thrust::fill(h2.begin(), h2.end(), 0.87);

	thrust::device_vector<float> d1 = h1;
	thrust::device_vector<float> d2 = h2;
	
	cudaEventRecord(start, 0);	
	saxpy(3.0, d1, d2);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);

	printf("Thrust time: %g\n", elapsedTime);

	h2 = d2;
	h1 = d1;

	for(int i = 0; i < (1 << 8); i++){
		printf("%d\t%g\t%g\n", i, h1[i], h2[i]);
	}
	
	float *da, *db, *h, alpha = 3.0;
	int threads_per_block = 512, N = 1 << 24;
	int num_of_blocks = N / threads_per_block;

	h = (float*)calloc(N, sizeof(float));

	cudaMalloc((void**)&da, N * sizeof(float));
	cudaMalloc((void**)&db, N * sizeof(float));
	
	cudaEventRecord(start, 0);
	cuda_saxpy<<<dim3(num_of_blocks), dim3(threads_per_block)>>>(da, db, alpha);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);	
	cudaEventElapsedTime(&elapsedTime, start, stop);

	printf("Cuda time: %g\n", elapsedTime);

	cudaMemcpy(h, da, N * sizeof(float), cudaMemcpyDeviceToHost);

	//for(int i = 0; i < (1 << 8); i++){
	//	printf("%g\n", h[i]);
	//}
	
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	free(h);
	cudaFree(da);
	cudaFree(db);
	return 0;
}

