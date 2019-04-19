#include "multiarray.h"
#include "head.h"

int main() {
    // allocations
    bElem *c = randomArray({17});
    auto in_arr = (bElem (*)[STRIDE]) randomArray({STRIDE, STRIDE});
    auto out_arr_ref = (bElem (*)[STRIDE]) zeroArray({STRIDE, STRIDE});

    #define out(i, j) out_arr_ref[j][i]
    #define in(i, j) in_arr[j][i]
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
        auto out_arr_gen = (bElem (*)[STRIDE]) zeroArray({STRIDE, STRIDE});
        #define out(i, j) out_arr_gen[j][i]
        auto compute = [&in_arr, &out_arr_gen, &c]() -> void {
            #include "vssched.h"

            tile("kernel.py", TVEC, (TILEJ, TILEI), ("k", "j", "i"));
        };
        #undef out
    
        #include "timing.h"

        if (!compareArray({STRIDE, STRIDE}, (bElem *)out_arr_ref, (bElem *)out_arr_gen))
            return 1;
    }
#elif TYPE == 2
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEJ * TILEI;
        auto bInfo = init_grid<2>(grid_ptr, {STRIDE/TILEJ, STRIDE/TILEI});
        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 2);
        Brick<Dim<TILEJ, TILEI>, Dim<BFOLD>> in_bri(&bInfo, &bStorage, 0);
        Brick<Dim<TILEJ, TILEI>, Dim<BFOLD>> out_bri(&bInfo, &bStorage, bSize);

        copyBrick<2>({STRIDE, STRIDE}, (bElem *)in_arr, grid_ptr, in_bri);
        #undef in

        #define in in_bri
        #define out out_bri

        auto compute = [&]() -> void {
            auto grid = (unsigned (*)[STRIDE/TILEI]) grid_ptr;
            
            #include "brisched.h"
            {
                unsigned b = grid[j][i];
                brick("kernel.py", BVEC, (TILEJ, TILEI), (BFOLD), b);
            }
        };
        #undef out
        
        #include "timing.h"

        if (!compareBrick<2>({STRIDE, STRIDE}, (bElem *)out_arr_ref, grid_ptr, out_bri))
            return 1;
    }
#endif
    return 0;
}
