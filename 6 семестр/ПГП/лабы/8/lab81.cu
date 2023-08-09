#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>

#include <thrust/fill.h>
#include <thrust/sequence.h>

#pragma comment (lib, "cublas.lib")
#include <cublas_v2.h>

struct saxpy_functor{
	const float a;
	saxpy_functor(float _a) : a(_a) {}
	__host__ __device__ float operator()(float x, float y){
		return a * x + y;
	}
};

void saxpy(float a, thrust::device_vector<float>& x, thrust::device_vector<float>& y){
	saxpy_functor func(a);
	thrust::transform(x.begin(), x.end(), y.begin(), y.begin(), func);
}

__host__ void print_array(float *data1, float *data2, int num_elem, const char *prefix){
	printf("\n%s", prefix);
	for(int i = 0; i < num_elem; i++)
		printf("\n%2d: %2.4f %2.4f", i + 1, data1[i], data2[i]);
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

	printf("Saxpy time: %g\n", elapsedTime);
		
	const int num_elem = 8;
	const size_t size_in_bytes = (num_elem * sizeof(float));
	float *da, *db, *ha, *hb;

	cudaMalloc((void**) &da, size_in_bytes);
	cudaMalloc((void**) &db, size_in_bytes);

	cudaMallocHost((void**) &ha, size_in_bytes);
	cudaMallocHost((void**) &hb, size_in_bytes);

	memset(ha, 0, size_in_bytes);
	memset(hb, 0, size_in_bytes);

	cublasHandle_t cublas_handle;
	cublasCreate(&cublas_handle);

	for (int i = 0; i < num_elem; i++) {
		ha[i] = (float)i;
		hb[i] = 0.87;
	}

	print_array(ha, hb, num_elem, "Before set");
	printf("\n");

	const int num_rows = num_elem;
	const int num_cols = 1;
	const size_t elem_size = sizeof(float);

	cublasSetMatrix(num_rows, num_cols, elem_size, ha, num_rows, da, num_rows);
	cublasSetMatrix(num_rows, num_cols, elem_size, hb, num_rows, db, num_rows);

	const int stride = 1;
	float alpha = 3.0F;
	
	cudaEventRecord(start, 0);
	cublasSaxpy(cublas_handle, num_elem, &alpha, da, stride, db, stride);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);

	cublasGetMatrix(num_rows, num_cols, elem_size, da, num_rows, ha, num_rows);
	cublasGetMatrix(num_rows, num_cols, elem_size, db, num_rows, hb, num_rows);

	const int default_stream = 0;
	cudaStreamSynchronize(default_stream);

	print_array(ha, hb, num_elem, "After set");
	printf("\n");
	
/*
	cudaEventRecord(start, 0);
	cuda_saxpy<<<dim3(num_of_blocks), dim3(threads_per_block)>>>(da, db, alpha);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);	

	printf("Cuda Saxpy time: %g\n", elapsedTime);
*/
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Cublas time: %g\n", elapsedTime);

	//for(int i = 0; i < (1 << 8); i++){
	//	printf("%g\t%g\n", ha[i], hb[i]);
	//}
	
	cublasDestroy(cublas_handle);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	cudaFreeHost(ha);
	cudaFreeHost(hb);
	cudaFree(da);
	cudaFree(db);
	return 0;
}

