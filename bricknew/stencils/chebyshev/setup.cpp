#include "multiarray.h"
#include "head.h"

int main() {
    // allocations
    bElem *c = randomArray({3});
    auto Ac_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto Ap_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto Dinv_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto RHS_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto out_arr_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    #define Ac(i, j, k) Ac_arr[k][j][i]
    #define Ap(i, j, k) Ap_arr[k][j][i]
    #define Dinv(i, j, k) Dinv_arr[k][j][i]
    #define RHS(i, j, k) RHS_arr[k][j][i]

    #define out(i, j, k) out_arr_ref[k][j][i]
    {
        auto compute = [&]() -> void {
            bElem c1 = c[0];
            bElem c2 = c[1];
            bElem h2inv = c[2];
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
    #undef out

#if TYPE == 1
    {
        auto out_arr_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        #define out(i, j, k) out_arr_gen[k][j][i]
        auto compute = [&]() -> void {
            bElem c1 = c[0];
            bElem c2 = c[1];
            bElem h2inv = c[2];

            #include "vssched.h"

            tile("kernel.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));
        };
        #undef out
    
        #include "timing.h"

        if (!compareArray({STRIDE, STRIDE, STRIDE}, (bElem *)out_arr_ref, (bElem *)out_arr_gen))
            return 1;
    }
#elif TYPE == 2
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;
        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});
        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 5);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> Ac_bri(&bInfo, &bStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> Ap_bri(&bInfo, &bStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> Dinv_bri(&bInfo, &bStorage, bSize * 2);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> RHS_bri(&bInfo, &bStorage, bSize * 3);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> out_bri(&bInfo, &bStorage, bSize * 4);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)Ac_arr, grid_ptr, Ac_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)Ap_arr, grid_ptr, Ap_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)Dinv_arr, grid_ptr, Dinv_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)RHS_arr, grid_ptr, RHS_bri);
        #undef Ac
        #undef Ap
        #undef Dinv
        #undef RHS

        #define Ac Ac_bri
        #define Ap Ap_bri
        #define Dinv Dinv_bri
        #define RHS RHS_bri
        #define out out_bri

        auto compute = [&]() -> void {
            bElem c1 = c[0];
            bElem c2 = c[1];
            bElem h2inv = c[2];
            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_ptr;
            
            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }
        };
        #undef out
        
        #include "timing.h"

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)out_arr_ref, grid_ptr, out_bri))
            return 1;
    }
#endif
    return 0;
}
