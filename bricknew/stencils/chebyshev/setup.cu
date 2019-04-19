#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define Ac(i, j, k) Ac_arr[k][j][i]
#define Ap(i, j, k) Ap_arr[k][j][i]
#define Dinv(i, j, k) Dinv_arr[k][j][i]
#define RHS(i, j, k) RHS_arr[k][j][i]
#define out(i, j, k) out_arr[k][j][i]
#define out(i, j, k) out_arr[k][j][i]
#define c1 c[0]
#define c2 c[1]
#define h2inv c[2]

__global__ void
arr_kernel(bElem *Ac_ptr, bElem *Ap_ptr, bElem *Dinv_ptr, bElem *RHS_ptr, bElem *out_ptr,
        bElem *c) {
    auto Ac_arr = (bElem (*)[STRIDE][STRIDE]) Ac_ptr;
    auto Ap_arr = (bElem (*)[STRIDE][STRIDE]) Ap_ptr;
    auto Dinv_arr = (bElem (*)[STRIDE][STRIDE]) Dinv_ptr;
    auto RHS_arr = (bElem (*)[STRIDE][STRIDE]) RHS_ptr;

    auto out_arr = (bElem (*)[STRIDE][STRIDE]) out_ptr;

    #include "arrcusched.h"
    {
        #include "kernel.h"
    }
}

#undef Ac
#undef Ap
#undef Dinv
#undef RHS
#undef out

__global__ void
brick_kernel(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], Brick3D Ac, Brick3D Ap, Brick3D Dinv, Brick3D RHS, Brick3D out, bElem *c) {
    #include "bricusched.h"
    brick("kernel.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

int main() {
    // allocations
    bElem *c = randomArray({3});
    bElem *c_dev;
    copyToDevice({3}, c_dev, c);

    auto Ac_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *Ac_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, Ac_dev, Ac_arr);

    auto Ap_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *Ap_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, Ap_dev, Ap_arr);

    auto Dinv_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *Dinv_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, Dinv_dev, Dinv_arr);

    auto RHS_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *RHS_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, RHS_dev, RHS_arr);

    auto out_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *out_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, out_dev, out_arr);

    {
        cudaFuncSetCacheConfig(arr_kernel, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(_TILEI, _TILEJ, _TILEK);
            
            arr_kernel<<< block, thread >>>(Ac_dev, Ap_dev, Dinv_dev, RHS_dev, out_dev, c_dev);
        };
        
#ifndef TYPE
        #include "cutiming.h"
#else
        compute();
        copyFromDevice({STRIDE, STRIDE, STRIDE}, out_arr, out_dev);
#endif
    }

    cudaDeviceSynchronize();

    cudaFree(Ac_dev);
    cudaFree(Ap_dev);
    cudaFree(Dinv_dev);
    cudaFree(RHS_dev);
    cudaFree(out_dev);

#if TYPE == 1
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 5);
        Brick3D Ac_bri(&bInfo, &bStorage, 0);
        Brick3D Ap_bri(&bInfo, &bStorage, bSize);
        Brick3D Dinv_bri(&bInfo, &bStorage, bSize * 2);
        Brick3D RHS_bri(&bInfo, &bStorage, bSize * 3);
        Brick3D out_bri(&bInfo, &bStorage, bSize * 4);

        BrickInfo<3> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<3>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, Ac_arr, grid_ptr, Ac_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, Ap_arr, grid_ptr, Ap_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, Dinv_arr, grid_ptr, Dinv_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, RHS_arr, grid_ptr, RHS_bri);

        BrickStorage *bStorage_dev;
        BrickStorage _bStorage_dev = movBrickStorage(bStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&bStorage_dev, size);
            cudaMemcpy(bStorage_dev, &_bStorage_dev, size, cudaMemcpyHostToDevice);
        }

        cudaFuncSetCacheConfig(brick_kernel, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            Brick3D Ac(bInfo_dev, &_bStorage_dev, 0);
            Brick3D Ap(bInfo_dev, &_bStorage_dev, bSize);
            Brick3D Dinv(bInfo_dev, &_bStorage_dev, bSize * 2);
            Brick3D RHS(bInfo_dev, &_bStorage_dev, bSize * 3);
            Brick3D out(bInfo_dev, &_bStorage_dev, bSize * 4);

            Ac.bStorage = bStorage_dev;
            Ap.bStorage = bStorage_dev;
            Dinv.bStorage = bStorage_dev;
            RHS.bStorage = bStorage_dev;
            out.bStorage = bStorage_dev;

            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(32);
            
            brick_kernel<<< block, thread >>>(grid, Ac, Ap, Dinv, RHS, out, c_dev);
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
