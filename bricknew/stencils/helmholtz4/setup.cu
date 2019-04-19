#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define x(i, j, k) x_arr[k][j][i]
#define alpha(i, j, k) alpha_arr[k][j][i]
#define beta_i(i, j, k) beta_i_arr[k][j][i]
#define beta_j(i, j, k) beta_j_arr[k][j][i]
#define beta_k(i, j, k) beta_k_arr[k][j][i]
#define out(i, j, k) out_arr[k][j][i]
#define c1 c[0]
#define c2 c[1]
#define h2inv c[2]

__global__ void
arr_kernel(bElem *x_ptr, bElem *alpha_ptr, bElem *beta_i_ptr, bElem *beta_j_ptr, bElem *beta_k_ptr, bElem *out_ptr,
        bElem *c) {
    auto x_arr = (bElem (*)[STRIDE][STRIDE]) x_ptr;
    auto alpha_arr = (bElem (*)[STRIDE][STRIDE]) alpha_ptr;
    auto beta_i_arr = (bElem (*)[STRIDE][STRIDE]) beta_i_ptr;
    auto beta_j_arr = (bElem (*)[STRIDE][STRIDE]) beta_j_ptr;
    auto beta_k_arr = (bElem (*)[STRIDE][STRIDE]) beta_k_ptr;

    auto out_arr = (bElem (*)[STRIDE][STRIDE]) out_ptr;

    #include "arrcusched.h"
    {
        #include "kernel.h"
    }
}

#undef x
#undef alpha
#undef beta_i
#undef beta_j
#undef beta_k
#undef out

__global__ void
brick_kernel(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], Brick3D x, Brick3D alpha, Brick3D beta_i, Brick3D beta_j,
        Brick3D beta_k, Brick3D out, bElem *c) {
    #include "bricusched.h"
    brick("kernel.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

int main() {
    // allocations
    bElem *c = randomArray({3});
    bElem *c_dev;
    copyToDevice({3}, c_dev, c);

    auto x_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *x_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, x_dev, x_arr);

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

    auto out_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *out_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, out_dev, out_arr);

    {
        cudaFuncSetCacheConfig(arr_kernel, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(_TILEI, _TILEJ, _TILEK);
            
            arr_kernel<<< block, thread >>>(x_dev, alpha_dev, beta_i_dev, beta_j_dev, beta_k_dev, out_dev, c_dev);
        };
        
#ifndef TYPE
        #include "cutiming.h"
#else
        compute();
        copyFromDevice({STRIDE, STRIDE, STRIDE}, out_arr, out_dev);
#endif
    }

    cudaDeviceSynchronize();

    cudaFree(x_dev);
    cudaFree(alpha_dev);
    cudaFree(beta_i_dev);
    cudaFree(beta_j_dev);
    cudaFree(beta_k_dev);
    cudaFree(out_dev);

#if TYPE == 1
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 6);

        Brick3D x_bri(&bInfo, &bStorage, 0);
        Brick3D alpha_bri(&bInfo, &bStorage, bSize);
        Brick3D beta_i_bri(&bInfo, &bStorage, bSize * 2);
        Brick3D beta_j_bri(&bInfo, &bStorage, bSize * 3);
        Brick3D beta_k_bri(&bInfo, &bStorage, bSize * 4);
        Brick3D out_bri(&bInfo, &bStorage, bSize * 5);

        BrickInfo<3> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<3>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, x_arr, grid_ptr, x_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, alpha_arr, grid_ptr, alpha_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_i_arr, grid_ptr, beta_i_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_j_arr, grid_ptr, beta_j_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_k_arr, grid_ptr, beta_k_bri);

        BrickStorage *bStorage_dev;
        BrickStorage _bStorage_dev = movBrickStorage(bStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&bStorage_dev, size);
            cudaMemcpy(bStorage_dev, &_bStorage_dev, size, cudaMemcpyHostToDevice);
        }

        cudaFuncSetCacheConfig(brick_kernel, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            Brick3D x(bInfo_dev, &_bStorage_dev, 0);
            Brick3D alpha(bInfo_dev, &_bStorage_dev, bSize);
            Brick3D beta_i(bInfo_dev, &_bStorage_dev, bSize * 2);
            Brick3D beta_j(bInfo_dev, &_bStorage_dev, bSize * 3);
            Brick3D beta_k(bInfo_dev, &_bStorage_dev, bSize * 4);
            Brick3D out(bInfo_dev, &_bStorage_dev, bSize * 5);
           
            x.bStorage = bStorage_dev;
            alpha.bStorage = bStorage_dev;
            beta_i.bStorage = bStorage_dev;
            beta_j.bStorage = bStorage_dev;
            beta_k.bStorage = bStorage_dev;
            out.bStorage = bStorage_dev;

            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(32);
            
            brick_kernel<<< block, thread >>>(grid, x, alpha, beta_i, beta_j, beta_k, out, c_dev);
        };

        #include "cutiming.h"

        cudaDeviceSynchronize();

        cudaMemcpy(bStorage.dat, _bStorage_dev.dat, bStorage.chunks * bStorage.step * sizeof(bElem), cudaMemcpyDeviceToHost);

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, out_arr, grid_ptr, out_bri))
            return 1;
    }
#endif
    return 0;
}
