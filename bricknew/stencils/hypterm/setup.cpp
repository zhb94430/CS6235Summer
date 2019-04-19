#include "multiarray.h"
#include "head.h"

#define ALP  0.8
#define BET (-0.2)
#define GAM  0.038095238095238 //  4.0/105.0
#define DEL (-0.003571428571429) // -1.0/280.0

int main() {
    // allocations
    auto qu_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto qv_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto qw_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto qpres_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});

    auto cons_imx_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto cons_imy_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto cons_imz_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto cons_iene_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});

    #define qu(i, j, k) qu_arr[k][j][i]
    #define qv(i, j, k) qv_arr[k][j][i]
    #define qw(i, j, k) qw_arr[k][j][i]
    #define qpres(i, j, k) qpres_arr[k][j][i]

    #define cons_imx(i, j, k) cons_imx_arr[k][j][i]
    #define cons_imy(i, j, k) cons_imy_arr[k][j][i]
    #define cons_imz(i, j, k) cons_imz_arr[k][j][i]
    #define cons_iene(i, j, k) cons_iene_arr[k][j][i]

    auto flux_irho_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto flux_imx_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto flux_imy_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto flux_imz_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto flux_iene_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    #define flux_irho(i, j, k) flux_irho_ref[k][j][i]
    #define flux_imx(i, j, k) flux_imx_ref[k][j][i]
    #define flux_imy(i, j, k) flux_imy_ref[k][j][i]
    #define flux_imz(i, j, k) flux_imz_ref[k][j][i]
    #define flux_iene(i, j, k) flux_iene_ref[k][j][i]

    bElem *c = randomArray({3});

    bElem dxinv0 = c[0];
    bElem dxinv1 = c[1];
    bElem dxinv2 = c[2];
    {
        auto compute = [&]() -> void {
            #include "arrsched.h"
            {
                #include "kernel.h"
            }
        };
        
#ifndef TYPE
        #include "timing.h"
#else
        compute();
#endif
    }
    #undef flux_irho
    #undef flux_imx
    #undef flux_imy
    #undef flux_imz
    #undef flux_iene

#if TYPE == 1
    {
        auto flux_irho_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto flux_imx_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto flux_imy_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto flux_imz_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto flux_iene_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

        #define flux_irho(i, j, k) flux_irho_gen[k][j][i]
        #define flux_imx(i, j, k) flux_imx_gen[k][j][i]
        #define flux_imy(i, j, k) flux_imy_gen[k][j][i]
        #define flux_imz(i, j, k) flux_imz_gen[k][j][i]
        #define flux_iene(i, j, k) flux_iene_gen[k][j][i]
        auto compute = [&]() -> void {
            #include "vssched.h"

            tile("kernel.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));
        };
        #undef flux_irho
        #undef flux_imx
        #undef flux_imy
        #undef flux_imz
        #undef flux_iene
    
        #include "timing.h"

        if (!compareArray({STRIDE, STRIDE, STRIDE}, (bElem *)flux_iene_ref, (bElem *)flux_iene_gen))
            return 1;
    }
#elif TYPE == 2
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;
        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});
        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 13);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> qu_bri(&bInfo, &bStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> qv_bri(&bInfo, &bStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> qw_bri(&bInfo, &bStorage, bSize * 2);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> qpres_bri(&bInfo, &bStorage, bSize * 3);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> cons_imx_bri(&bInfo, &bStorage, bSize * 4);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> cons_imy_bri(&bInfo, &bStorage, bSize * 5);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> cons_imz_bri(&bInfo, &bStorage, bSize * 6);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> cons_iene_bri(&bInfo, &bStorage, bSize * 7);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> flux_irho_bri(&bInfo, &bStorage, bSize * 8);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> flux_imx_bri(&bInfo, &bStorage, bSize * 9);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> flux_imy_bri(&bInfo, &bStorage, bSize * 10);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> flux_imz_bri(&bInfo, &bStorage, bSize * 11);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> flux_iene_bri(&bInfo, &bStorage, bSize * 12);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qu_arr, grid_ptr, qu_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qv_arr, grid_ptr, qv_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qw_arr, grid_ptr, qw_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)qpres_arr, grid_ptr, qpres_bri);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_imx_arr, grid_ptr, cons_imx_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_imy_arr, grid_ptr, cons_imy_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_imz_arr, grid_ptr, cons_imz_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)cons_iene_arr, grid_ptr, cons_iene_bri);

        #undef qu
        #undef qv
        #undef qw
        #undef qpres

        #undef cons_imx
        #undef cons_imy
        #undef cons_imz
        #undef cons_iene

        #define qu qu_bri
        #define qv qv_bri
        #define qw qw_bri
        #define qpres qpres_bri

        #define cons_imx cons_imx_bri
        #define cons_imy cons_imy_bri
        #define cons_imz cons_imz_bri
        #define cons_iene cons_iene_bri

        #define flux_irho flux_irho_bri
        #define flux_imx flux_imx_bri
        #define flux_imy flux_imy_bri
        #define flux_imz flux_imz_bri
        #define flux_iene flux_iene_bri
        auto compute = [&]() -> void {
            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_ptr;
            
            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }
        };
        #undef out
        
        #include "timing.h"

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)flux_iene_ref, grid_ptr, flux_iene_bri))
            return 1;
    }
#endif
    return 0;
}
