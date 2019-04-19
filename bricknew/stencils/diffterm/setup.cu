#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define q_1(i, j, k) q_1_arr[k][j][i]
#define q_2(i, j, k) q_2_arr[k][j][i]
#define q_3(i, j, k) q_3_arr[k][j][i]
#define q_5(i, j, k) q_5_arr[k][j][i]

#define ux(i, j, k) ux_arr[k][j][i]
#define vx(i, j, k) vx_arr[k][j][i]
#define wx(i, j, k) wx_arr[k][j][i]

#define uy(i, j, k) uy_arr[k][j][i]
#define vy(i, j, k) vy_arr[k][j][i]
#define wy(i, j, k) wy_arr[k][j][i]

#define uz(i, j, k) uz_arr[k][j][i]
#define vz(i, j, k) vz_arr[k][j][i]
#define wz(i, j, k) wz_arr[k][j][i]

#define diffflux1(i, j, k) diffflux1_arr[k][j][i]
#define diffflux2(i, j, k) diffflux2_arr[k][j][i]
#define diffflux3(i, j, k) diffflux3_arr[k][j][i]
#define diffflux4(i, j, k) diffflux4_arr[k][j][i]

#define dxinv0 c[0]
#define dxinv1 c[1]
#define dxinv2 c[2]

__global__ void
arr_kernel1(bElem *q_1_ptr, bElem *q_2_ptr, bElem *q_3_ptr, 
        bElem *ux_ptr, bElem *vx_ptr, bElem *wx_ptr, 
        bElem *uy_ptr, bElem *vy_ptr, bElem *wy_ptr, 
        bElem *uz_ptr, bElem *vz_ptr, bElem *wz_ptr, 
        bElem *c) {
    auto q_1_arr = (bElem (*)[STRIDE][STRIDE]) q_1_ptr;
    auto q_2_arr = (bElem (*)[STRIDE][STRIDE]) q_2_ptr;
    auto q_3_arr = (bElem (*)[STRIDE][STRIDE]) q_3_ptr;

    auto ux_arr = (bElem (*)[STRIDE][STRIDE]) ux_ptr;
    auto vx_arr = (bElem (*)[STRIDE][STRIDE]) vx_ptr;
    auto wx_arr = (bElem (*)[STRIDE][STRIDE]) wx_ptr;

    auto uy_arr = (bElem (*)[STRIDE][STRIDE]) uy_ptr;
    auto vy_arr = (bElem (*)[STRIDE][STRIDE]) vy_ptr;
    auto wy_arr = (bElem (*)[STRIDE][STRIDE]) wy_ptr;

    auto uz_arr = (bElem (*)[STRIDE][STRIDE]) uz_ptr;
    auto vz_arr = (bElem (*)[STRIDE][STRIDE]) vz_ptr;
    auto wz_arr = (bElem (*)[STRIDE][STRIDE]) wz_ptr;

    #include "arrcusched.h"
    {
        #include "kernel1.h"
    }
}

__global__ void
arr_kernel2(bElem *q_1_ptr, 
        bElem *vy_ptr, 
        bElem *wz_ptr, 
        bElem *diffflux1_ptr,
        bElem *c) {
    auto q_1_arr = (bElem (*)[STRIDE][STRIDE]) q_1_ptr;

    auto vy_arr = (bElem (*)[STRIDE][STRIDE]) vy_ptr;
    auto wz_arr = (bElem (*)[STRIDE][STRIDE]) wz_ptr;

    auto diffflux1_arr = (bElem (*)[STRIDE][STRIDE]) diffflux1_ptr;

    #include "arrcusched.h"
    {
        #include "kernel2.h"
    }
}

__global__ void
arr_kernel3(bElem *q_2_ptr, 
        bElem *ux_ptr, bElem *wz_ptr, 
        bElem *diffflux2_ptr,
        bElem *c) {
    auto q_2_arr = (bElem (*)[STRIDE][STRIDE]) q_2_ptr;

    auto ux_arr = (bElem (*)[STRIDE][STRIDE]) ux_ptr;
    auto wz_arr = (bElem (*)[STRIDE][STRIDE]) wz_ptr;

    auto diffflux2_arr = (bElem (*)[STRIDE][STRIDE]) diffflux2_ptr;

    #include "arrcusched.h"
    {
        #include "kernel3.h"
    }
}

__global__ void
arr_kernel4(bElem *q_3_ptr, 
        bElem *ux_ptr, bElem *vy_ptr, 
        bElem *diffflux3_ptr,
        bElem *c) {
    auto q_3_arr = (bElem (*)[STRIDE][STRIDE]) q_3_ptr;

    auto ux_arr = (bElem (*)[STRIDE][STRIDE]) ux_ptr;
    auto vy_arr = (bElem (*)[STRIDE][STRIDE]) vy_ptr;

    auto diffflux3_arr = (bElem (*)[STRIDE][STRIDE]) diffflux3_ptr;

    #include "arrcusched.h"
    {
        #include "kernel4.h"
    }
}

__global__ void
arr_kernel5(bElem *q_1_ptr, bElem *q_2_ptr, bElem *q_3_ptr, bElem *q_5_ptr,
        bElem *ux_ptr, bElem *vx_ptr, bElem *wx_ptr, 
        bElem *uy_ptr, bElem *vy_ptr, bElem *wy_ptr, 
        bElem *uz_ptr, bElem *vz_ptr, bElem *wz_ptr, 
        bElem *diffflux1_ptr, bElem *diffflux2_ptr, bElem *diffflux3_ptr, bElem *diffflux4_ptr,
        bElem *c) {
    auto q_1_arr = (bElem (*)[STRIDE][STRIDE]) q_1_ptr;
    auto q_2_arr = (bElem (*)[STRIDE][STRIDE]) q_2_ptr;
    auto q_3_arr = (bElem (*)[STRIDE][STRIDE]) q_3_ptr;
    auto q_5_arr = (bElem (*)[STRIDE][STRIDE]) q_5_ptr;

    auto ux_arr = (bElem (*)[STRIDE][STRIDE]) ux_ptr;
    auto vx_arr = (bElem (*)[STRIDE][STRIDE]) vx_ptr;
    auto wx_arr = (bElem (*)[STRIDE][STRIDE]) wx_ptr;

    auto uy_arr = (bElem (*)[STRIDE][STRIDE]) uy_ptr;
    auto vy_arr = (bElem (*)[STRIDE][STRIDE]) vy_ptr;
    auto wy_arr = (bElem (*)[STRIDE][STRIDE]) wy_ptr;

    auto uz_arr = (bElem (*)[STRIDE][STRIDE]) uz_ptr;
    auto vz_arr = (bElem (*)[STRIDE][STRIDE]) vz_ptr;
    auto wz_arr = (bElem (*)[STRIDE][STRIDE]) wz_ptr;

    auto diffflux1_arr = (bElem (*)[STRIDE][STRIDE]) diffflux1_ptr;
    auto diffflux2_arr = (bElem (*)[STRIDE][STRIDE]) diffflux2_ptr;
    auto diffflux3_arr = (bElem (*)[STRIDE][STRIDE]) diffflux3_ptr;
    auto diffflux4_arr = (bElem (*)[STRIDE][STRIDE]) diffflux4_ptr;

    #include "arrcusched.h"
    {
        #include "kernel5.h"
    }
}

#undef q_1
#undef q_2
#undef q_3
#undef q_5

#undef ux
#undef vx
#undef wx

#undef uy
#undef vy
#undef wy

#undef uz
#undef vz
#undef wz

#undef diffflux1
#undef diffflux2
#undef diffflux3
#undef diffflux4

__global__ void
brick_kernel1(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], 
        Brick3D q_1, Brick3D q_2, Brick3D q_3,
        Brick3D ux, Brick3D vx, Brick3D wx, 
        Brick3D uy, Brick3D vy, Brick3D wy, 
        Brick3D uz, Brick3D vz, Brick3D wz, bElem *c) {

    #include "bricusched.h"
    brick("kernel1.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

__global__ void
brick_kernel2(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], 
        Brick3D q_1, Brick3D vy, Brick3D wz, Brick3D diffflux1, bElem *c) {

    #include "bricusched.h"
    brick("kernel2.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

__global__ void
brick_kernel3(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], 
        Brick3D q_2, Brick3D ux, Brick3D wz, Brick3D diffflux2, bElem *c) {

    #include "bricusched.h"
    brick("kernel3.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

__global__ void
brick_kernel4(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], 
        Brick3D q_3, Brick3D ux, Brick3D vy, Brick3D diffflux3, bElem *c) {

    #include "bricusched.h"
    brick("kernel4.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

__global__ void
brick_kernel5(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], 
        Brick3D q_1, Brick3D q_2, Brick3D q_3, Brick3D q_5, 
        Brick3D ux, Brick3D vx, Brick3D wx, 
        Brick3D uy, Brick3D vy, Brick3D wy, 
        Brick3D uz, Brick3D vz, Brick3D wz, 
        Brick3D diffflux1, Brick3D diffflux2, Brick3D diffflux3, Brick3D diffflux4, bElem *c) {

    #include "bricusched.h"
    brick("kernel5.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

int main() {
    // allocations
    bElem *c = randomArray({3});
    bElem *c_dev;
    copyToDevice({3}, c_dev, c);

    auto q_1_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *q_1_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, q_1_dev, q_1_arr);

    auto q_2_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *q_2_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, q_2_dev, q_2_arr);

    auto q_3_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *q_3_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, q_3_dev, q_3_arr);

    auto q_5_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *q_5_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, q_5_dev, q_5_arr);

    auto ux_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *ux_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, ux_dev, ux_arr);

    auto vx_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *vx_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, vx_dev, vx_arr);

    auto wx_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *wx_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, wx_dev, wx_arr);

    auto uy_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *uy_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, uy_dev, uy_arr);

    auto vy_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *vy_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, vy_dev, vy_arr);

    auto wy_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *wy_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, wy_dev, wy_arr);

    auto uz_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *uz_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, uz_dev, uz_arr);

    auto vz_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *vz_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, vz_dev, vz_arr);

    auto wz_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *wz_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, wz_dev, wz_arr);

    auto diffflux1_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *diffflux1_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, diffflux1_dev, diffflux1_arr);

    auto diffflux2_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *diffflux2_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, diffflux2_dev, diffflux2_arr);

    auto diffflux3_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *diffflux3_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, diffflux3_dev, diffflux3_arr);

    auto diffflux4_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *diffflux4_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, diffflux4_dev, diffflux4_arr);

    {
        cudaFuncSetCacheConfig(arr_kernel1, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(arr_kernel2, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(arr_kernel3, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(arr_kernel4, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(arr_kernel5, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(_TILEI, _TILEJ, _TILEK);
            
            arr_kernel1<<< block, thread >>>(q_1_dev, q_2_dev, q_3_dev, ux_dev, vx_dev, wx_dev, uy_dev, vy_dev, wy_dev, uz_dev, vz_dev, wz_dev, c_dev);

            arr_kernel2<<< block, thread >>>(q_1_dev, vy_dev, wz_dev, diffflux1_dev, c_dev);

            arr_kernel3<<< block, thread >>>(q_2_dev, ux_dev, wz_dev, diffflux2_dev, c_dev);

            arr_kernel4<<< block, thread >>>(q_3_dev, ux_dev, vy_dev, diffflux3_dev, c_dev);

            arr_kernel5<<< block, thread >>>(q_1_dev, q_2_dev, q_3_dev, q_5_dev, ux_dev, vx_dev, wx_dev, uy_dev, vy_dev, wy_dev,
                    uz_dev, vz_dev, wz_dev, diffflux1_dev, diffflux2_dev, diffflux3_dev, diffflux4_dev, c_dev);
        };
        
#ifndef TYPE
        #include "cutiming.h"
#else
        compute();
        copyFromDevice({STRIDE, STRIDE, STRIDE}, diffflux4_arr, diffflux4_dev);
#endif
    }

    cudaDeviceSynchronize();

    cudaFree(q_1_dev);
    cudaFree(q_2_dev);
    cudaFree(q_3_dev);
    cudaFree(q_5_dev);

    cudaFree(ux_dev);
    cudaFree(vx_dev);
    cudaFree(wx_dev);

    cudaFree(uy_dev);
    cudaFree(vy_dev);
    cudaFree(wy_dev);

    cudaFree(uz_dev);
    cudaFree(vz_dev);
    cudaFree(wz_dev);

    cudaFree(diffflux1_dev);
    cudaFree(diffflux2_dev);
    cudaFree(diffflux3_dev);
    cudaFree(diffflux4_dev);

#if TYPE == 1
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        BrickInfo<3> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<3>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        auto xStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 3);
        auto yStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 3);
        auto zStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 3);

        auto qStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 4);

        BrickStorage *xStorage_dev;
        BrickStorage _xStorage_dev = movBrickStorage(xStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&xStorage_dev, size);
            cudaMemcpy(xStorage_dev, &_xStorage_dev, size, cudaMemcpyHostToDevice);
        }

        BrickStorage *yStorage_dev;
        BrickStorage _yStorage_dev = movBrickStorage(yStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&yStorage_dev, size);
            cudaMemcpy(yStorage_dev, &_yStorage_dev, size, cudaMemcpyHostToDevice);
        }

        BrickStorage *zStorage_dev;
        BrickStorage _zStorage_dev = movBrickStorage(zStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&zStorage_dev, size);
            cudaMemcpy(zStorage_dev, &_zStorage_dev, size, cudaMemcpyHostToDevice);
        }

        auto difffluxStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 4);

        BrickStorage *difffluxStorage_dev;
        BrickStorage _difffluxStorage_dev = movBrickStorage(difffluxStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&difffluxStorage_dev, size);
            cudaMemcpy(difffluxStorage_dev, &_difffluxStorage_dev, size, cudaMemcpyHostToDevice);
        }

        Brick3D ux_bri(&bInfo, &xStorage, 0);
        Brick3D vx_bri(&bInfo, &xStorage, bSize);
        Brick3D wx_bri(&bInfo, &xStorage, bSize * 2);

        Brick3D uy_bri(&bInfo, &yStorage, 0);
        Brick3D vy_bri(&bInfo, &yStorage, bSize);
        Brick3D wy_bri(&bInfo, &yStorage, bSize * 2);

        Brick3D uz_bri(&bInfo, &zStorage, 0);
        Brick3D vz_bri(&bInfo, &zStorage, bSize);
        Brick3D wz_bri(&bInfo, &zStorage, bSize * 2);

        Brick3D q1_bri(&bInfo, &qStorage, 0);
        Brick3D q2_bri(&bInfo, &qStorage, bSize);
        Brick3D q3_bri(&bInfo, &qStorage, bSize * 2);

        Brick3D q5_bri(&bInfo, &qStorage, bSize * 3);

        Brick3D diffflux1_bri(&bInfo, &difffluxStorage, 0);
        Brick3D diffflux2_bri(&bInfo, &difffluxStorage, bSize);
        Brick3D diffflux3_bri(&bInfo, &difffluxStorage, bSize * 2);
        Brick3D diffflux4_bri(&bInfo, &difffluxStorage, bSize * 3);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, q_1_arr, grid_ptr, q1_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, q_2_arr, grid_ptr, q2_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, q_3_arr, grid_ptr, q3_bri);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, q_5_arr, grid_ptr, q5_bri);

        BrickStorage *qStorage_dev;
        BrickStorage _qStorage_dev = movBrickStorage(qStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&qStorage_dev, size);
            cudaMemcpy(qStorage_dev, &_qStorage_dev, size, cudaMemcpyHostToDevice);
        }

        cudaFuncSetCacheConfig(brick_kernel1, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(brick_kernel2, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(brick_kernel3, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(brick_kernel4, cudaFuncCachePreferL1);

        cudaFuncSetCacheConfig(brick_kernel5, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {

            Brick3D ux(bInfo_dev, &_xStorage_dev, 0);
            Brick3D vx(bInfo_dev, &_xStorage_dev, bSize);
            Brick3D wx(bInfo_dev, &_xStorage_dev, bSize * 2);

            Brick3D uy(bInfo_dev, &_yStorage_dev, 0);
            Brick3D vy(bInfo_dev, &_yStorage_dev, bSize);
            Brick3D wy(bInfo_dev, &_yStorage_dev, bSize * 2);

            Brick3D uz(bInfo_dev, &_zStorage_dev, 0);
            Brick3D vz(bInfo_dev, &_zStorage_dev, bSize);
            Brick3D wz(bInfo_dev, &_zStorage_dev, bSize * 2);

            Brick3D q1(bInfo_dev, &_qStorage_dev, 0);
            Brick3D q2(bInfo_dev, &_qStorage_dev, bSize);
            Brick3D q3(bInfo_dev, &_qStorage_dev, bSize * 2);

            Brick3D q5(bInfo_dev, &_qStorage_dev, bSize * 3);

            Brick3D diffflux1(bInfo_dev, &_difffluxStorage_dev, 0);
            Brick3D diffflux2(bInfo_dev, &_difffluxStorage_dev, bSize);
            Brick3D diffflux3(bInfo_dev, &_difffluxStorage_dev, bSize * 2);
            Brick3D diffflux4(bInfo_dev, &_difffluxStorage_dev, bSize * 3);

            ux.bStorage = xStorage_dev;
            vx.bStorage = xStorage_dev;
            wx.bStorage = xStorage_dev;

            uy.bStorage = yStorage_dev;
            vy.bStorage = yStorage_dev;
            wy.bStorage = yStorage_dev;

            uz.bStorage = zStorage_dev;
            vz.bStorage = zStorage_dev;
            wz.bStorage = zStorage_dev;

            q1.bStorage = qStorage_dev;
            q2.bStorage = qStorage_dev;
            q3.bStorage = qStorage_dev;

            q5.bStorage = qStorage_dev;

            diffflux1.bStorage = difffluxStorage_dev;
            diffflux2.bStorage = difffluxStorage_dev;
            diffflux3.bStorage = difffluxStorage_dev;
            diffflux4.bStorage = difffluxStorage_dev;

            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(32);
            
            brick_kernel1<<< block, thread >>>(grid, q1, q2, q3, ux, vx, wx, uy, vy, wy, uz, vz, wz, c_dev);

            brick_kernel2<<< block, thread >>>(grid, q1, vy, wz, diffflux1, c_dev);

            brick_kernel3<<< block, thread >>>(grid, q2, ux, wz, diffflux2, c_dev);

            brick_kernel4<<< block, thread >>>(grid, q3, ux, vy, diffflux3, c_dev);

            brick_kernel5<<< block, thread >>>(grid, q1, q2, q3, q5, ux, vx, wx, uy, vy, wy,
                    uz, vz, wz, diffflux1, diffflux2, diffflux3, diffflux4, c_dev);
        };

        #include "cutiming.h"

        cudaDeviceSynchronize();

        cudaMemcpy(difffluxStorage.dat, _difffluxStorage_dev.dat, difffluxStorage.chunks * difffluxStorage.step * sizeof(bElem), cudaMemcpyDeviceToHost);

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, diffflux4_arr, grid_ptr, diffflux4_bri))
            return 1;
    }
#endif
    return 0;
}
