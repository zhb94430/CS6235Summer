#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define ALP  0.8
#define BET (-0.2)
#define GAM  0.038095238095238 //  4.0/105.0
#define DEL (-0.003571428571429) // -1.0/280.0

#define qu(i, j, k) qu_arr[k][j][i]
#define qv(i, j, k) qv_arr[k][j][i]
#define qw(i, j, k) qw_arr[k][j][i]
#define qpres(i, j, k) qpres_arr[k][j][i]

#define cons_imx(i, j, k) cons_imx_arr[k][j][i]
#define cons_imy(i, j, k) cons_imy_arr[k][j][i]
#define cons_imz(i, j, k) cons_imz_arr[k][j][i]
#define cons_iene(i, j, k) cons_iene_arr[k][j][i]

#define flux_irho(i, j, k) flux_irho_arr[k][j][i]
#define flux_imx(i, j, k) flux_imx_arr[k][j][i]
#define flux_imy(i, j, k) flux_imy_arr[k][j][i]
#define flux_imz(i, j, k) flux_imz_arr[k][j][i]
#define flux_iene(i, j, k) flux_iene_arr[k][j][i]

#define dxinv0 c[0]
#define dxinv1 c[1]
#define dxinv2 c[2]

__global__ void
arr_kernel(
        bElem *qu_ptr, bElem *qv_ptr, bElem *qw_ptr, bElem *qpres_ptr, 
        bElem *cons_imx_ptr, bElem *cons_imy_ptr, bElem *cons_imz_ptr, bElem *cons_iene_ptr, 
        bElem *flux_irho_ptr, bElem *flux_imx_ptr, bElem *flux_imy_ptr, bElem *flux_imz_ptr, bElem *flux_iene_ptr,
        bElem *c) {

    auto qu_arr = (bElem (*)[STRIDE][STRIDE]) qu_ptr;
    auto qv_arr = (bElem (*)[STRIDE][STRIDE]) qv_ptr;
    auto qw_arr = (bElem (*)[STRIDE][STRIDE]) qw_ptr;
    auto qpres_arr = (bElem (*)[STRIDE][STRIDE]) qpres_ptr;

    auto cons_imx_arr = (bElem (*)[STRIDE][STRIDE]) cons_imx_ptr;
    auto cons_imy_arr = (bElem (*)[STRIDE][STRIDE]) cons_imy_ptr;
    auto cons_imz_arr = (bElem (*)[STRIDE][STRIDE]) cons_imz_ptr;
    auto cons_iene_arr = (bElem (*)[STRIDE][STRIDE]) cons_iene_ptr;

    auto flux_irho_arr = (bElem (*)[STRIDE][STRIDE]) flux_irho_ptr;
    auto flux_imx_arr = (bElem (*)[STRIDE][STRIDE]) flux_imx_ptr;
    auto flux_imy_arr = (bElem (*)[STRIDE][STRIDE]) flux_imy_ptr;
    auto flux_imz_arr = (bElem (*)[STRIDE][STRIDE]) flux_imz_ptr;
    auto flux_iene_arr = (bElem (*)[STRIDE][STRIDE]) flux_iene_ptr;

    #include "arrcusched.h"
    {
        #include "kernel.h"
    }
}

#undef qu
#undef qv
#undef qw
#undef qpres

#undef cons_imx
#undef cons_imy
#undef cons_imz
#undef cons_iene

#undef flux_irho
#undef flux_imx
#undef flux_imy
#undef flux_imz
#undef flux_iene

__global__ void
brick_kernel(
        unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI],
        Brick3D qu, Brick3D qv, Brick3D qw, Brick3D qpres, 
        Brick3D cons_imx, Brick3D cons_imy, Brick3D cons_imz, Brick3D cons_iene, 
        Brick3D flux_irho, Brick3D flux_imx, Brick3D flux_imy, Brick3D flux_imz, Brick3D flux_iene,
        bElem *c) {
    #include "bricusched.h"
    brick("kernel.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
}

int main() {
    // allocations
    bElem *c = randomArray({3});
    bElem *c_dev;
    copyToDevice({3}, c_dev, c);

    auto qu_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *qu_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, qu_dev, qu_arr);

    auto qv_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *qv_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, qv_dev, qv_arr);

    auto qw_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *qw_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, qw_dev, qw_arr);

    auto qpres_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *qpres_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, qpres_dev, qpres_arr);

    auto cons_imx_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *cons_imx_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, cons_imx_dev, cons_imx_arr);

    auto cons_imy_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *cons_imy_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, cons_imy_dev, cons_imy_arr);

    auto cons_imz_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *cons_imz_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, cons_imz_dev, cons_imz_arr);

    auto cons_iene_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *cons_iene_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, cons_iene_dev, cons_iene_arr);

    auto flux_irho_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *flux_irho_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, flux_irho_dev, flux_irho_arr);

    auto flux_imx_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *flux_imx_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, flux_imx_dev, flux_imx_arr);

    auto flux_imy_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *flux_imy_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, flux_imy_dev, flux_imy_arr);

    auto flux_imz_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *flux_imz_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, flux_imz_dev, flux_imz_arr);

    auto flux_iene_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *flux_iene_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, flux_iene_dev, flux_iene_arr);

    {
        cudaFuncSetCacheConfig(arr_kernel, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(_TILEI, _TILEJ, _TILEK);
            
            arr_kernel<<< block, thread >>>(qu_dev, qv_dev, qw_dev, qpres_dev, 
                    cons_imx_dev, cons_imy_dev, cons_imz_dev, cons_iene_dev, 
                    flux_irho_dev, flux_imx_dev, flux_imy_dev, flux_imz_dev, flux_iene_dev,
                    c_dev);
        };
        
#ifndef TYPE
        #include "cutiming.h"
#else
        compute();
        copyFromDevice({STRIDE, STRIDE, STRIDE}, flux_iene_arr, flux_iene_dev);
#endif
    }

    cudaDeviceSynchronize();

    cudaFree(qu_dev);
    cudaFree(qv_dev);
    cudaFree(qw_dev);
    cudaFree(qpres_dev);

    cudaFree(cons_imx_dev);
    cudaFree(cons_imy_dev);
    cudaFree(cons_imz_dev);
    cudaFree(cons_iene_dev);

    cudaFree(flux_irho_dev);
    cudaFree(flux_imx_dev);
    cudaFree(flux_imy_dev);
    cudaFree(flux_imz_dev);
    cudaFree(flux_iene_dev);

#if TYPE == 1
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 13);
        Brick3D qu_bri(&bInfo, &bStorage, 0);
        Brick3D qv_bri(&bInfo, &bStorage, bSize);
        Brick3D qw_bri(&bInfo, &bStorage, bSize * 2);
        Brick3D qpres_bri(&bInfo, &bStorage, bSize * 3);

        Brick3D cons_imx_bri(&bInfo, &bStorage, bSize * 4);
        Brick3D cons_imy_bri(&bInfo, &bStorage, bSize * 5);
        Brick3D cons_imz_bri(&bInfo, &bStorage, bSize * 6);
        Brick3D cons_iene_bri(&bInfo, &bStorage, bSize * 7);

        Brick3D flux_irho_bri(&bInfo, &bStorage, bSize * 8);
        Brick3D flux_imx_bri(&bInfo, &bStorage, bSize * 9);
        Brick3D flux_imy_bri(&bInfo, &bStorage, bSize * 10);
        Brick3D flux_imz_bri(&bInfo, &bStorage, bSize * 11);
        Brick3D flux_iene_bri(&bInfo, &bStorage, bSize * 12);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qu_arr, grid_ptr, qu_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qv_arr, grid_ptr, qv_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qw_arr, grid_ptr, qw_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qpres_arr, grid_ptr, qpres_bri);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_imx_arr, grid_ptr, cons_imx_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_imy_arr, grid_ptr, cons_imy_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_imz_arr, grid_ptr, cons_imz_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_iene_arr, grid_ptr, cons_iene_bri);

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        BrickInfo<3> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<3>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        BrickStorage *bStorage_dev;
        BrickStorage _bStorage_dev = movBrickStorage(bStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&bStorage_dev, size);
            cudaMemcpy(bStorage_dev, &_bStorage_dev, size, cudaMemcpyHostToDevice);
        }

        cudaFuncSetCacheConfig(brick_kernel, cudaFuncCachePreferL1);

        auto compute = [&]() -> void {
            Brick3D qu(bInfo_dev, &_bStorage_dev, 0);
            Brick3D qv(bInfo_dev, &_bStorage_dev, bSize);
            Brick3D qw(bInfo_dev, &_bStorage_dev, bSize * 2);
            Brick3D qpres(bInfo_dev, &_bStorage_dev, bSize * 3);

            Brick3D cons_imx(bInfo_dev, &_bStorage_dev, bSize * 4);
            Brick3D cons_imy(bInfo_dev, &_bStorage_dev, bSize * 5);
            Brick3D cons_imz(bInfo_dev, &_bStorage_dev, bSize * 6);
            Brick3D cons_iene(bInfo_dev, &_bStorage_dev, bSize * 7);

            Brick3D flux_irho(bInfo_dev, &_bStorage_dev, bSize * 8);
            Brick3D flux_imx(bInfo_dev, &_bStorage_dev, bSize * 9);
            Brick3D flux_imy(bInfo_dev, &_bStorage_dev, bSize * 10);
            Brick3D flux_imz(bInfo_dev, &_bStorage_dev, bSize * 11);
            Brick3D flux_iene(bInfo_dev, &_bStorage_dev, bSize * 12);

            qu.bStorage = bStorage_dev;
            qv.bStorage = bStorage_dev;
            qw.bStorage = bStorage_dev;
            qpres.bStorage = bStorage_dev;

            cons_imx.bStorage = bStorage_dev;
            cons_imy.bStorage = bStorage_dev;
            cons_imz.bStorage = bStorage_dev;
            cons_iene.bStorage = bStorage_dev;

            flux_irho.bStorage = bStorage_dev;
            flux_imx.bStorage = bStorage_dev;
            flux_imy.bStorage = bStorage_dev;
            flux_imz.bStorage = bStorage_dev;
            flux_iene.bStorage = bStorage_dev;

            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(32);
            
            brick_kernel<<< block, thread >>>(grid, qu, qv, qw, qpres, 
                    cons_imx, cons_imy, cons_imz, cons_iene, 
                    flux_irho, flux_imx, flux_imy, flux_imz, flux_iene, c_dev);
        };

        #include "cutiming.h"

        cudaDeviceSynchronize();

        cudaMemcpy(bStorage.dat, _bStorage_dev.dat, bStorage.chunks * bStorage.step * sizeof(bElem), cudaMemcpyDeviceToHost);

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, flux_iene_arr, grid_ptr, flux_iene_bri))
            return 1;
    }
#endif
    return 0;
}
