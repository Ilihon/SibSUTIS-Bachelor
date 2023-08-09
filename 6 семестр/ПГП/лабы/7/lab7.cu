#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <cmath>

#include <thrust/device_vector.h>
#include <thrust/fill.h>
#include <thrust/host_vector.h>
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <stdio.h>

using namespace thrust;
using namespace std;

#define A 0.2
#define B 0.01


//обычное 
__global__ void kernel(float koef, float *f, float *res)
{
    int cur = threadIdx.x + blockDim.x * blockIdx.x;
    int prev = cur - 1;
    if(prev == -1)
    {
        res[cur] = f[cur];
    }else
    {
        res[cur] = f[cur] + (koef) * (f[prev] - f[cur]);
    }
}

struct functor
{
    const float koef;
    functor(float _koef) : koef(_koef){}
    __host__ __device__ float operator()(float x, float y)
    {
        return x + koef * (y - x);
    }
};



void iteration(float _koef, thrust::device_vector<float>::iterator  
x,thrust::device_vector<float>::iterator xs, thrust::device_vector<float>::iterator 
y)
{
    functor func(_koef);
    thrust::transform(x+1, xs, x, y+1, func);
}

float x_func(float x){
        return x*x * exp(-(x-A)*(x-A)/B);
}

float t_func(float t){
        return 0;
}

int main()
{
    int Nx = 1024;//максимум на осях
    int Nt = 1024;//максимум по времени
    float tlmt = 0.2;

    float dx = 1.0f/Nx;
    float dt = tlmt/Nt;

    cudaEvent_t start, stop;
    float time;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float *x;
    float *t;
    thrust::host_vector<float> thr(Nx*Nt);//создаём вектор матрицу
    float *cda;
	//выделение памяти
    cudaHostAlloc((void**)&x, Nx*sizeof(float), cudaHostAllocDefault);
    cudaHostAlloc((void**)&t, Nt*sizeof(float), cudaHostAllocDefault);
    cudaHostAlloc((void**)&cda, Nt*Nx*sizeof(float), cudaHostAllocDefault);
	//заполняем матрицу нулями
    for(int i=0;i<Nx;i++){
        for(int j=0;j<Nt;j++){
                thr[i+j*Nt]=0;
                cda[i+j*Nt]=0;
        }
    }


    float value = 0;
    for(int i=0;i<Nx;i++,value+=dx){
        x[i]=value;
        thr[i+0*Nt]=x_func(x[i]);
        cda[i+0*Nt]=x_func(x[i]);
    }

    value = 0;

    for(int i=0;i<Nt;i++,value+=dt){
        t[i]=value;
        thr[0+i*Nt]=t_func(t[i]);
        cda[0+i*Nt]=t_func(t[i]);
    }

    thrust::device_vector<float> dev(Nx*Nt);

    thrust::copy(thr.begin(), thr.end(),dev.begin());

    functor func(dt/dx);

    cudaEventRecord(start,0);
    for(int j=0;j<Nt-1;j++){
        thrust::transform(dev.begin()+(j*Nx)+1, dev.begin()+((j+1)*Nx), dev.begin()+(j*Nx), dev.begin() +((j+1)*Nx)+1, func);
    }
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    thrust::copy(dev.begin(),dev.end(),thr.begin());
    cudaEventElapsedTime(&time, start, stop);
    printf("Thrust time: %f ms\n", time);
	/*for (int i = 0; i < (1 << 8); i++) {
		printf("%d\t%g\n", i, thr[i]);
	}*/
//...................................................................
    
    float *dev_cda;


    cudaMalloc((void **)&dev_cda, Nx * Nt * sizeof(float));
    cudaMemcpy(dev_cda, cda, Nx*Nt * sizeof(float), cudaMemcpyHostToDevice);

    cudaEventRecord(start, 0);

    for(int i=0;i<Nt-1;i++){
        kernel <<< 1, Nx >>> (dt/dx, dev_cda + (i*Nx), dev_cda + ((i+1)*Nx) );
        cudaDeviceSynchronize();
    }
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaMemcpy(cda, dev_cda, Nx*Nt * sizeof(float), cudaMemcpyDeviceToHost);
    cudaEventElapsedTime(&time, start, stop);
    printf("\nCUDA time: %f ms\n\n", time);

    cudaFree(dev_cda);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    return 0;
}
