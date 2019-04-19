#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define H2INV  0.8f

__global__ void GSRBKernel(double* phi, double* phi_new, double* rhs, double* alpha, double* beta_i,
                           double* beta_j, double* beta_k, double* lambda, int color)
{
    int i, j, k;
    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i >= STRIDE-GZ || i < GZ)
    {
       return;
    }

    for (k=GZ; k<STRIDE-GZ; k++)
    {
        for(j=GZ; j<STRIDE-GZ; j++)
        {

            int ijk = i + j*STRIDE + k*(STRIDE*STRIDE);

            // if ((i+j+k+color) % 2 == 0)
            {
                double helmholtz = alpha[ijk]*phi[ijk]
                                 - H2INV*(
                                       beta_i[ijk+1     ]*( phi[ijk+1     ]-phi[ijk       ] )
                                     - beta_i[ijk       ]*( phi[ijk       ]-phi[ijk-1     ] )
                                     + beta_j[ijk+STRIDE]*( phi[ijk+STRIDE]-phi[ijk       ] )
                                     - beta_j[ijk       ]*( phi[ijk       ]-phi[ijk-STRIDE] )
                                     + beta_k[ijk+(STRIDE*STRIDE) ]*( phi[ijk+(STRIDE*STRIDE) ]-phi[ijk       ] )
                                     - beta_k[ijk       ]*( phi[ijk       ]-phi[ijk-(STRIDE*STRIDE) ] )
                                      );

                phi_new[ijk] = phi[ijk] - lambda[ijk]*(helmholtz-rhs[ijk]);
            }
        }
    }
}

__global__ void
brick_kernel(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], Brick3D phi, Brick3D alpha, Brick3D beta_i, Brick3D beta_j,
        Brick3D beta_k, Brick3D phi_new, Brick3D lambda, Brick3D rhs) {
    unsigned k = GZ / TILEK + blockIdx.z;
    unsigned j = GZ / TILEJ + blockIdx.y;
    unsigned i = GZ / TILEI + blockIdx.x;

    unsigned b = grid[k][j][i];

    brick("kernel.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

int main() {
    // allocations
    bElem *c = randomArray({3});
    bElem *c_dev;
    copyToDevice({3}, c_dev, c);

    auto phi_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *phi_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, phi_dev, phi_arr);

    auto phi_new_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *phi_new_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, phi_new_dev, phi_new_arr);

    auto alpha_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *alpha_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, alpha_dev, alpha_arr);

    auto beta_i_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *beta_i_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, beta_i_dev, beta_i_arr);

    auto beta_j_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *beta_j_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, beta_j_dev, beta_j_arr);

    auto beta_k_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *beta_k_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, beta_k_dev, beta_k_arr);

    auto rhs_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *rhs_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, rhs_dev, rhs_arr);

    auto lambda_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *lambda_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, lambda_dev, lambda_arr);

    // CPU
    {

        for(int k=GZ;k<STRIDE-GZ;k++){
            for(int j=GZ;j<STRIDE-GZ;j++){
                for(int i=GZ;i<STRIDE-GZ;i++){
                    int ijk = i + j*STRIDE + k*STRIDE*STRIDE;

                    { // color signifies red or black case
                      double helmholtz = alpha_arr[ijk]*phi_arr[ijk]
                                       - H2INV*(
                                           beta_i_arr[ijk+1     ]*( phi_arr[ijk+1     ]-phi_arr[ijk       ] )
                                         - beta_i_arr[ijk       ]*( phi_arr[ijk       ]-phi_arr[ijk-1     ] )
                                         + beta_j_arr[ijk+STRIDE]*( phi_arr[ijk+STRIDE]-phi_arr[ijk       ] )
                                         - beta_j_arr[ijk       ]*( phi_arr[ijk       ]-phi_arr[ijk-STRIDE] )
                                         + beta_k_arr[ijk+(STRIDE*STRIDE) ]*( phi_arr[ijk+(STRIDE*STRIDE) ]-phi_arr[ijk       ] )
                                         - beta_k_arr[ijk       ]*( phi_arr[ijk       ]-phi_arr[ijk-(STRIDE*STRIDE) ] )
                                            );

                      phi_new_arr[ijk] = phi_arr[ijk] - lambda_arr[ijk]*(helmholtz-rhs_arr[ijk]);
                    }
                }
            }
        }
    }

    // CUDA
    {
        auto compute = [&]() -> void {
            long numOfThreads = STRIDE;
            // long numOfBlocks = ceil(STRIDE/numOfThreads);
            long numOfBlocks = ceil(STRIDE*STRIDE*STRIDE/(numOfThreads*STRIDE*STRIDE)); // Unroll on i

            dim3 dimBlock(numOfThreads);
            dim3 dimGrid(numOfBlocks);
            
            GSRBKernel<<<dimGrid, dimBlock>>> (phi_dev, phi_new_dev, rhs_dev, alpha_dev, beta_i_dev, 
                                         beta_j_dev , beta_k_dev , lambda_dev, 0);
        };
        
        compute();
        auto phi_new_cuda = zeroArray({STRIDE, STRIDE, STRIDE});
        copyFromDevice({STRIDE, STRIDE, STRIDE}, phi_new_cuda, phi_new_dev);

        if (!compareArray({STRIDE, STRIDE, STRIDE}, (bElem *)phi_new_arr, (bElem *)phi_new_cuda))
            std::cout << "arr don't match" << std::endl;
    }

    cudaDeviceSynchronize();

    cudaFree(phi_dev);
    cudaFree(phi_new_dev);
    cudaFree(alpha_dev);
    cudaFree(beta_i_dev);
    cudaFree(beta_j_dev);
    cudaFree(beta_k_dev);
    cudaFree(rhs_dev);
    cudaFree(lambda_dev);
    
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 8);

        Brick3D phi_bri(&bInfo, &bStorage, 0);
        Brick3D alpha_bri(&bInfo, &bStorage, bSize);
        Brick3D beta_i_bri(&bInfo, &bStorage, bSize * 2);
        Brick3D beta_j_bri(&bInfo, &bStorage, bSize * 3);
        Brick3D beta_k_bri(&bInfo, &bStorage, bSize * 4);
        Brick3D phi_new_bri(&bInfo, &bStorage, bSize * 5);
        Brick3D lambda_bri(&bInfo, &bStorage, bSize * 6);
        Brick3D rhs_bri(&bInfo, &bStorage, bSize * 7);

        BrickInfo<3> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<3>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, phi_arr, grid_ptr, phi_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, alpha_arr, grid_ptr, alpha_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_i_arr, grid_ptr, beta_i_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_j_arr, grid_ptr, beta_j_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_k_arr, grid_ptr, beta_k_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, phi_new_arr, grid_ptr, phi_new_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, lambda_arr, grid_ptr, lambda_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, rhs_arr, grid_ptr, rhs_bri);

        BrickStorage *bStorage_dev;
        BrickStorage _bStorage_dev = movBrickStorage(bStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&bStorage_dev, size);
            cudaMemcpy(bStorage_dev, &_bStorage_dev, size, cudaMemcpyHostToDevice);
        }

        auto compute = [&]() -> void {
            Brick3D phi(bInfo_dev, &_bStorage_dev, 0);
            Brick3D alpha(bInfo_dev, &_bStorage_dev, bSize);
            Brick3D beta_i(bInfo_dev, &_bStorage_dev, bSize * 2);
            Brick3D beta_j(bInfo_dev, &_bStorage_dev, bSize * 3);
            Brick3D beta_k(bInfo_dev, &_bStorage_dev, bSize * 4);
            Brick3D phi_new(bInfo_dev, &_bStorage_dev, bSize * 5);
            Brick3D lambda(bInfo_dev, &bStorage, bSize * 6);
            Brick3D rhs(bInfo_dev, &bStorage, bSize * 7);
           
            phi.bStorage = bStorage_dev;
            alpha.bStorage = bStorage_dev;
            beta_i.bStorage = bStorage_dev;
            beta_j.bStorage = bStorage_dev;
            beta_k.bStorage = bStorage_dev;
            phi_new.bStorage = bStorage_dev;
            lambda.bStorage = bStorage_dev;
            rhs.bStorage = bStorage_dev;

            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(32);
            
            brick_kernel<<< block, thread >>>(grid, phi, alpha, beta_i, beta_j, beta_k, phi_new, lambda, rhs);
        };

        compute();

        cudaDeviceSynchronize();

        cudaMemcpy(bStorage.dat, _bStorage_dev.dat, bStorage.chunks * bStorage.step * sizeof(bElem), cudaMemcpyDeviceToHost);

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, phi_new_arr, grid_ptr, phi_new_bri))
            std::cout << "brick don't match" << std::endl;
    }
    return 0;
}

