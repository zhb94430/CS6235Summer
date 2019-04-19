#include <omp.h>
#include <iostream>
#include <typeinfo>
#include "vecscatter.h"
#include "bricksetup.h"
#include "multiarray.h"
#include "immintrin.h"

#define GZ 32
#define STRIDE (GZ * 2 + N)

#define VEC_ALIGN 64
typedef bElem vfloat1024[1024] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat512[512] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat256[256] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat128[128] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat64[64] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat32[32] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat16[16] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat8[8] __attribute__((aligned(VEC_ALIGN)));
typedef bElem vfloat4[4] __attribute__((aligned(32)));
typedef bElem vfloat2[2] __attribute__((aligned(16)));
