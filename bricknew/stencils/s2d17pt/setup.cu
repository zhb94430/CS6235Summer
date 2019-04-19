#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define out(i, j) out_arr[j][i]
#define in(i, j) in_arr[j][i]

__global__ void
arr_kernel(bElem *in_ptr, bElem *out_ptr, bElem *c) {
    auto in_arr = (bElem (*)[STRIDE]) in_ptr;
    auto out_arr = (bElem (*)[STRIDE]) out_ptr;
    #include "arrcusched.h"
    {
        #include "kernel.h"
    }
}

#undef out
#undef in

__global__ void
brick_kernel(unsigned (*grid)[STRIDE/TILEI], Brick2D in, Brick2D out, bElem *c) {
    #include "bricusched.h"
    brick("kernel.py", BVEC, (TILEJ, TILEI), (BFOLD), b);
}

int main() {
    // allocations
    bElem *c = randomArray({17});
    bElem *c_dev;
    copyToDevice({17}, c_dev, c);

    auto in_arr = randomArray({STRIDE, STRIDE});
    bElem *in_dev;
    copyToDevice({STRIDE, STRIDE}, in_dev, in_arr);

    auto out_arr = zeroArray({STRIDE, STRIDE});
    bElem *out_dev;
    copyToDevice({STRIDE, STRIDE}, out_dev, out_arr);

    {
        auto compute = [&]() -> void {
            dim3 block(N/TILEI, N/TILEJ), thread(_TILEI, _TILEJ);
            
            arr_kernel<<< block, thread >>>(in_dev, out_dev, c_dev);
        };
        
#ifndef TYPE
        #include "cutiming.h"
#else
        compute();
#endif
        copyFromDevice({STRIDE, STRIDE}, out_arr, out_dev);
    }

#if TYPE == 1
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEJ * TILEI;

        auto bInfo = init_grid<2>(grid_ptr, {STRIDE/TILEJ, STRIDE/TILEI});

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 2);
        Brick<Dim<TILEJ, TILEI>, Dim<BFOLD>> in_bri(&bInfo, &bStorage, 0);
        Brick<Dim<TILEJ, TILEI>, Dim<BFOLD>> out_bri(&bInfo, &bStorage, bSize);

        BrickInfo<2> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<2>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        copyBrick<2>({STRIDE, STRIDE}, in_arr, grid_ptr, in_bri);

        BrickStorage *bStorage_dev;
        BrickStorage _bStorage_dev = movBrickStorage(bStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&bStorage_dev, size);
            cudaMemcpy(bStorage_dev, &_bStorage_dev, size, cudaMemcpyHostToDevice);
        }

        auto compute = [&]() -> void {
            Brick2D bIn(bInfo_dev, &_bStorage_dev, 0);
            Brick2D bOut(bInfo_dev, &_bStorage_dev, bSize);
            bIn.bStorage = bStorage_dev;
            bOut.bStorage = bStorage_dev;
            auto grid = (unsigned (*)[STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ), thread(32);
            
            brick_kernel<<< block, thread >>>(grid, bIn, bOut, c_dev);
        };

        #include "cutiming.h"

        cudaDeviceSynchronize();

        cudaMemcpy(bStorage.dat, _bStorage_dev.dat, bStorage.chunks * bStorage.step * sizeof(bElem), cudaMemcpyDeviceToHost);

        if (!compareBrick<2>({STRIDE, STRIDE}, out_arr, grid_ptr, out_bri))
            return 1;
    }
#endif
    return 0;
}
