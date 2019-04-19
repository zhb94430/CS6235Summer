#include "multiarray.h"
#include "head.h"

int main() {
    // allocations
    bElem *c = randomArray({19});
    auto in_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto out_arr_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    #define in(i, j, k) in_arr[k][j][i]
    #define out(i, j, k) out_arr_ref[k][j][i]
    {
        auto compute = [&in_arr, &out_arr_ref, &c]() -> void {
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
        auto compute = [&in_arr, &out_arr_gen, &c]() -> void {
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
        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 2);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> in_bri(&bInfo, &bStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> out_bri(&bInfo, &bStorage, bSize);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)in_arr, grid_ptr, in_bri);
        #undef in

        #define in in_bri
        #define out out_bri

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

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)out_arr_ref, grid_ptr, out_bri))
            return 1;
    }
#endif
    return 0;
}
