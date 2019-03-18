#include "GSRBCuda.h"

#define pencil 32
#define plane  1024
#define grid   32768

#define DEFAULT_THRESHOLD  4000
#define BLOCKSIZE 64
#define TILESIZE 16
#define cudaCheck(x) _cudaCheck(x, #x ,__FILE__, __LINE__)

template<typename T>
void _cudaCheck(T e, const char* func, const char* call, const int line){
  if(e != cudaSuccess){
    printf("\"%s\" at %d in %s\n\treturned %d\n-> %s\n", func, line, call, (int)e, cudaGetErrorString(e));
    exit(EXIT_FAILURE);
  }
}

__global__ void GSRBKernel(double* phi, double* phi_new, double* rhs, double* alpha, double* beta_i,
                           double* beta_j, double* beta_k, double* lambda, int color)
{
    // TODO: Find out what i, j, k maps to in terms of blockIdx, blockDim, threadIdx
    int currentOffset = blockIdx.x + blockDim.x + threadIdx.x;

    int i, j, k;
    double h2inv = 1.0/64;
    k = currentOffset;

    for (j=0; j<pencil; j++)
    {
        for(i=0; i<pencil; i++)
        {

    int ijk = i + j*pencil + k*plane;

    if (i+j+k+color % 2 == 0)
    {
        double helmholtz = alpha[ijk]*phi[ijk]
                         - h2inv*(
                               beta_i[ijk+1     ]*( phi[ijk+1     ]-phi[ijk       ] )
                             - beta_i[ijk       ]*( phi[ijk       ]-phi[ijk-1     ] )
                             + beta_j[ijk+pencil]*( phi[ijk+pencil]-phi[ijk       ] )
                             - beta_j[ijk       ]*( phi[ijk       ]-phi[ijk-pencil] )
                             + beta_k[ijk+plane ]*( phi[ijk+plane ]-phi[ijk       ] )
                             - beta_k[ijk       ]*( phi[ijk       ]-phi[ijk-plane ] )
                              );

        phi_new[ijk] = phi[ijk] - lambda[ijk]*(helmholtz-rhs[ijk]);
    }
        }
    }
}

void GSRBCuda(double* phi, double* phi_new, double* rhs, double* alpha, double* beta_i,
              double* beta_j, double* beta_k, double* lambda)
{
    //CUDA Buffers
    double* phi_device    ;
    double* phi_new_device;
    double* rhs_device    ;
    double* alpha_device  ;
    double* beta_i_device ;
    double* beta_j_device ;
    double* beta_k_device ;
    double* lambda_device ;

    // Init Memory on GPU
    // Cuda Memory Management
    cudaCheck(cudaMalloc((void**) &phi_device    , grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &phi_new_device, grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &rhs_device    , grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &alpha_device  , grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &beta_i_device , grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &beta_j_device , grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &beta_k_device , grid * sizeof(double)));
    cudaCheck(cudaMalloc((void**) &lambda_device , grid * sizeof(double)));
    cudaCheck(cudaGetLastError());

    cudaCheck(cudaMemcpy(phi_device    , phi    , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(phi_new_device, phi_new, grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(rhs_device    , rhs    , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(alpha_device  , alpha  , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(beta_i_device , beta_i , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(beta_j_device , beta_j , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(beta_k_device , beta_k , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaMemcpy(lambda_device , lambda , grid * sizeof(double), cudaMemcpyHostToDevice));
    cudaCheck(cudaGetLastError());

    // Printing out some device data
    struct cudaDeviceProp properties;
    cudaGetDeviceProperties(&properties, 0);
    int maxGridSize = properties.maxGridSize[0];
    int maxBlockSize = properties.maxThreadsDim[0];
    int maxThreadCount = properties.maxThreadsPerBlock;
    size_t sharedMemoryPerBlock = properties.sharedMemPerBlock;
    printf("MaxGridDim1 %d, MaxBlockDim1 %d, MaxThreadPerBlock %d, SharedMemPerBlock %d\n", 
            maxGridSize,    maxBlockSize,    maxThreadCount,       sharedMemoryPerBlock);

    // Dimension
    // TODO, need to figure out how many
    long numOfBlocks = 50;

    dim3 dimGrid(numOfBlocks);
    dim3 dimBlock(numOfBlocks);

    printf("Config: #ofBlocks %d, #ofThreads %d\n", numOfBlocks, numOfBlocks);

    cudaEvent_t start, stop;
    float et;
    cudaCheck(cudaEventCreate(&start));
    cudaCheck(cudaEventCreate(&stop));
    cudaCheck(cudaEventRecord(start));

    // Cuda Kernel Call
    GSRBKernel<<<dimGrid, dimBlock>>> (phi_device, phi_new_device, rhs_device, alpha_device, beta_i_device, 
                                       beta_j_device , beta_k_device , lambda_device, color);

    cudaCheck(cudaGetLastError());
    cudaDeviceSynchronize();
    cudaCheck(cudaGetLastError());

    // Time event end
    cudaCheck(cudaEventRecord(stop));
    cudaCheck(cudaEventSynchronize(stop));
    cudaCheck(cudaEventElapsedTime(&et, start, stop));
    cudaCheck(cudaEventDestroy(start));
    cudaCheck(cudaEventDestroy(stop));

    printf("Cuda Time is %f\n", et);

    // More Memory Management
    // cudaMemcpy(host_output, device_output, inputSize, cudaMemcpyDeviceToHost);
    // cudaFree(device_output);
    // cudaFree(device_input);
}
