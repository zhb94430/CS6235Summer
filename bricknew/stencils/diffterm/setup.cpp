#include "multiarray.h"
#include "head.h"

int main() {
    // allocations
    bElem *c = randomArray({3});

    auto q_1_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto q_2_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});
    auto q_3_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});

    auto q_5_arr = (bElem (*)[STRIDE][STRIDE]) randomArray({STRIDE, STRIDE, STRIDE});

    auto ux_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto vx_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto wx_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    auto uy_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto vy_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto wy_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    auto uz_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto vz_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto wz_arr = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    auto diffflux1_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto diffflux2_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto diffflux3_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
    auto diffflux4_ref = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

    bElem dxinv0 = c[0];
    bElem dxinv1 = c[1];
    bElem dxinv2 = c[2];

    #define ux(i, j, k) ux_arr[k][j][i]
    #define vx(i, j, k) vx_arr[k][j][i]
    #define wx(i, j, k) wx_arr[k][j][i]

    #define uy(i, j, k) ux_arr[k][j][i]
    #define vy(i, j, k) vx_arr[k][j][i]
    #define wy(i, j, k) wx_arr[k][j][i]

    #define uz(i, j, k) ux_arr[k][j][i]
    #define vz(i, j, k) vx_arr[k][j][i]
    #define wz(i, j, k) wx_arr[k][j][i]

    #define q_1(i, j, k) q_1_arr[k][j][i]
    #define q_2(i, j, k) q_2_arr[k][j][i]
    #define q_3(i, j, k) q_3_arr[k][j][i]

    #define q_5(i, j, k) q_5_arr[k][j][i]


    #define diffflux1(i, j, k) diffflux1_ref[k][j][i]
    #define diffflux2(i, j, k) diffflux2_ref[k][j][i]
    #define diffflux3(i, j, k) diffflux3_ref[k][j][i]
    #define diffflux4(i, j, k) diffflux4_ref[k][j][i]
    {
        auto compute = [&]() -> void {
            #include "arrsched.h"
            {
                #include "kernel1.h"
            }

            #include "arrsched.h"
            {
                #include "kernel2.h"
            }

            #include "arrsched.h"
            {
                #include "kernel3.h"
            }

            #include "arrsched.h"
            {
                #include "kernel4.h"
            }

            #include "arrsched.h"
            {
                #include "kernel5.h"
            }
        };
        
#ifndef TYPE
        #include "timing.h"
#else
        compute();
#endif
    }
    #undef diffflux1
    #undef diffflux2
    #undef diffflux3
    #undef diffflux4

#if TYPE == 1
    {
        auto diffflux1_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto diffflux2_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto diffflux3_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});
        auto diffflux4_gen = (bElem (*)[STRIDE][STRIDE]) zeroArray({STRIDE, STRIDE, STRIDE});

        #define diffflux1(i, j, k) diffflux1_gen[k][j][i]
        #define diffflux2(i, j, k) diffflux2_gen[k][j][i]
        #define diffflux3(i, j, k) diffflux3_gen[k][j][i]
        #define diffflux4(i, j, k) diffflux4_gen[k][j][i]
        auto compute = [&]() -> void {
            #include "vssched.h"

            tile("kernel1.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));

            #include "vssched.h"

            tile("kernel2.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));

            #include "vssched.h"

            tile("kernel3.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));

            #include "vssched.h"

            tile("kernel4.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));

            #include "vssched.h"

            tile("kernel5.py", TVEC, (TILEK, TILEJ, TILEI), ("k", "j", "i"));
        };
    
        #undef diffflux1
        #undef diffflux2
        #undef diffflux3
        #undef diffflux4

        #include "timing.h"
        if (!compareArray({STRIDE, STRIDE, STRIDE}, (bElem *)diffflux4_ref, (bElem *)diffflux4_gen))
            return 1;
    }
#elif TYPE == 2
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        auto xStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 3);
        auto yStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 3);
        auto zStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 3);

        auto qStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 4);

        auto difffluxStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 4);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> ux_bri(&bInfo, &xStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> vx_bri(&bInfo, &xStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> wx_bri(&bInfo, &xStorage, bSize * 2);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> uy_bri(&bInfo, &yStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> vy_bri(&bInfo, &yStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> wy_bri(&bInfo, &yStorage, bSize * 2);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> uz_bri(&bInfo, &zStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> vz_bri(&bInfo, &zStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> wz_bri(&bInfo, &zStorage, bSize * 2);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> q1_bri(&bInfo, &qStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> q2_bri(&bInfo, &qStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> q3_bri(&bInfo, &qStorage, bSize * 2);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> q5_bri(&bInfo, &qStorage, bSize * 3);

        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> diffflux1_bri(&bInfo, &difffluxStorage, 0);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> diffflux2_bri(&bInfo, &difffluxStorage, bSize);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> diffflux3_bri(&bInfo, &difffluxStorage, bSize * 2);
        Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> diffflux4_bri(&bInfo, &difffluxStorage, bSize * 3);

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)q_1_arr, grid_ptr, q1_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)q_2_arr, grid_ptr, q2_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)q_3_arr, grid_ptr, q3_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)q_5_arr, grid_ptr, q5_bri);

        #undef ux
        #undef vx
        #undef wx

        #undef uy
        #undef vy
        #undef wy

        #undef uz
        #undef vz
        #undef wz

        #undef q_1
        #undef q_2
        #undef q_3

        #undef q_5

        #undef diffflux1
        #undef diffflux2
        #undef diffflux3
        #undef diffflux4

        #define ux ux_bri
        #define vx vx_bri
        #define wx wx_bri

        #define uy ux_bri
        #define vy vx_bri
        #define wy wx_bri

        #define uz ux_bri
        #define vz vx_bri
        #define wz wx_bri

        #define q_1 q1_bri
        #define q_2 q2_bri
        #define q_3 q3_bri

        #define q_5 q5_bri

        #define diffflux1 diffflux1_bri
        #define diffflux2 diffflux2_bri
        #define diffflux3 diffflux3_bri
        #define diffflux4 diffflux4_bri
        auto compute = [&]() -> void {
            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_ptr;
            
            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel1.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }

            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel2.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }
            
            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel3.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }
            
            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel4.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }
            
            #include "brisched.h"
            {
                unsigned b = grid[k][j][i];
                brick("kernel5.py", BVEC, (TILEK, TILEJ, TILEI), (BFOLD), b);
            }
        };
        #undef diffflux1
        #undef diffflux2
        #undef diffflux3
        #undef diffflux4
        
        #include "timing.h"

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, (bElem *)diffflux4_ref, grid_ptr, diffflux4_bri))
            return 1;
    }
#endif
    return 0;
}
