#include "multiarray.h"
#include "head.h"

int main() {
    // allocations
    bElem *c = randomArray({3});

    auto x_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto alpha_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto beta_i_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto beta_j_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto beta_k_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto out_arr_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    #define x(i, j, k) x_arr[k][j][i]
    #define alpha(i, j, k) alpha_arr[k][j][i]
    #define beta_i(i, j, k) beta_i_arr[k][j][i]
    #define beta_j(i, j, k) beta_j_arr[k][j][i]
    #define beta_k(i, j, k) beta_k_arr[k][j][i]

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
        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 6);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> x_bri(&bInfo, &bStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> alpha_bri(&bInfo, &bStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> beta_i_bri(&bInfo, &bStorage, bSize * 2);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> beta_j_bri(&bInfo, &bStorage, bSize * 3);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> beta_k_bri(&bInfo, &bStorage, bSize * 4);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> out_bri(&bInfo, &bStorage, bSize * 5);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)x_arr, grid_ptr, x_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)alpha_arr, grid_ptr, alpha_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)beta_i_arr, grid_ptr, beta_i_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)beta_j_arr, grid_ptr, beta_j_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)beta_k_arr, grid_ptr, beta_k_bri);
        #undef x
        #undef alpha
        #undef beta_i
        #undef beta_j
        #undef beta_k

        #define x x_bri
        #define alpha alpha_bri
        #define beta_i beta_i_bri
        #define beta_j beta_j_bri
        #define beta_k beta_k_bri
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
