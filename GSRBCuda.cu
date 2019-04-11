#include "GSRBCuda.h"
#include "GSRBConstants.h"


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
    i = currentOffset+1;

    for (k=1; k<pencil-1; k++)
    {
        for(j=1; j<pencil-1; j++)
        {

            int ijk = i + j*pencil + k*plane;

            if ((i+j+k+color) % 2 == 0)
            {
                double helmholtz = alpha[ijk]*phi[ijk]
                                 - H2INV*(
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

    double* tmp;

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
    long numOfThreads = 64;
    long numOfBlocks = ceil(grid/numOfThreads);

    dim3 dimBlock(numOfThreads);
    dim3 dimGrid(numOfBlocks);

    printf("Config: #ofThreads %d, #ofBlocks %d\n", numOfThreads, numOfBlocks);

    cudaEvent_t start, stop;
    float et;
    cudaCheck(cudaEventCreate(&start));
    cudaCheck(cudaEventCreate(&stop));
    cudaCheck(cudaEventRecord(start));

    printf("GSRBCuda Starting..\n");
    auto t1 = std::chrono::high_resolution_clock::now();

    for (int timestep = 0; timestep < 4; timestep++)
    {
      // Cuda Kernel Call
      GSRBKernel<<<dimGrid, dimBlock>>> (phi_device, phi_new_device, rhs_device, alpha_device, beta_i_device, 
                                         beta_j_device , beta_k_device , lambda_device, 0);

      cudaCheck(cudaGetLastError());
      cudaDeviceSynchronize();
      cudaCheck(cudaGetLastError());

      GSRBKernel<<<dimGrid, dimBlock>>> (phi_device, phi_new_device, rhs_device, alpha_device, beta_i_device, 
                                         beta_j_device , beta_k_device , lambda_device, 1);

      cudaCheck(cudaGetLastError());
      cudaDeviceSynchronize();
      cudaCheck(cudaGetLastError());

      tmp = phi_new_device;
      phi_new_device = phi_device;
      phi_device = tmp;
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

    std::cout << "CUDA Time is "
              << fp_ms.count()
              << " milliseconds\n";

    // Time event end
    cudaCheck(cudaEventRecord(stop));
    cudaCheck(cudaEventSynchronize(stop));
    cudaCheck(cudaEventElapsedTime(&et, start, stop));
    cudaCheck(cudaEventDestroy(start));
    cudaCheck(cudaEventDestroy(stop));

    printf("Cuda Time is %f\n", et);

    // More Memory Management
    cudaCheck(cudaMemcpy(phi    , phi_device,     grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(phi_new, phi_new_device, grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(rhs    , rhs_device,     grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(alpha  , alpha_device,   grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(beta_i , beta_i_device,  grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(beta_j , beta_j_device,  grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(beta_k , beta_k_device,  grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaMemcpy(lambda , lambda_device,  grid * sizeof(double), cudaMemcpyDeviceToHost));
    cudaCheck(cudaGetLastError());

    cudaFree(phi_device    );
    cudaFree(phi_new_device);
    cudaFree(rhs_device    );
    cudaFree(alpha_device  );
    cudaFree(beta_i_device );
    cudaFree(beta_j_device );
    cudaFree(beta_k_device );
    cudaFree(lambda_device );
}
