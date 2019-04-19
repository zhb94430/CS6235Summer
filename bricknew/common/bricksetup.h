#ifndef BRICK_SETUP_H
#define BRICK_SETUP_H

#include "brick.h"
#include "cmpconst.h"
#include <vector>
#include <typeinfo>
#include <initializer_list>
#include <cmath>

struct RunningTag {};
struct StopTag {};

template<unsigned select>
struct TagSelect {
    static constexpr RunningTag value = RunningTag();
};

template<>
struct TagSelect<0> {
    static constexpr StopTag value = StopTag();
};

template<unsigned dims, unsigned d>
inline void init_fill(const std::vector<long> &stride, unsigned *adjlist, unsigned *grid_ptr, unsigned *low, unsigned *high, RunningTag t) {
    unsigned str = static_power<3, d - 1>::value;
    init_fill<dims, d - 1>(stride, adjlist, grid_ptr - stride[dims - d], low, high, TagSelect<d - 1>::value);
    init_fill<dims, d - 1>(stride, adjlist + str, grid_ptr, low, high, TagSelect<d - 1>::value);
    init_fill<dims, d - 1>(stride, adjlist + str * 2, grid_ptr + stride[dims - d], low, high, TagSelect<d - 1>::value);
}

template<unsigned dims, unsigned d>
inline void init_fill(const std::vector<long> &stride, unsigned *adjlist, unsigned *grid_ptr, unsigned *low, unsigned *high, StopTag t) {
    if (grid_ptr >= low && grid_ptr < high)
        *adjlist = *grid_ptr;
    else
        *adjlist = 0;
}

template<unsigned dims, unsigned d>
inline void init_iter(const std::vector<long> &dimlist, const std::vector<long> &stride, BrickInfo<dims> &bInfo, unsigned *grid_ptr, unsigned *low, unsigned *high, RunningTag t) {
    if (dims == d) {
        #pragma omp parallel for
        for (long s = 0; s < dimlist[dims - d]; ++s)
            init_iter<dims, d - 1>(dimlist, stride, bInfo, grid_ptr + s * stride[dims - d], low, high, TagSelect<d - 1>::value);
    } else {
        for (long s = 0; s < dimlist[dims - d]; ++s)
            init_iter<dims, d - 1>(dimlist, stride, bInfo, grid_ptr + s * stride[dims - d], low, high, TagSelect<d - 1>::value);
    }
}

template<unsigned dims, unsigned d>
inline void init_iter(const std::vector<long> &dimlist, const std::vector<long> &stride, BrickInfo<dims> &bInfo, unsigned *grid_ptr, unsigned *low, unsigned *high, StopTag t) {
    init_fill<dims, dims>(stride, bInfo.adj[*grid_ptr], grid_ptr, low, high, RunningTag());
}

template<unsigned dims>
BrickInfo<dims> init_grid(unsigned *&grid_ptr, const std::vector<long> &dimlist) {
    long size = 1;
    for (const auto a: dimlist)
        size *= a;
    grid_ptr = (unsigned*) malloc(size * sizeof(unsigned));
    for (unsigned pos = 0; pos < size; ++pos)
        grid_ptr[pos] = pos;

    BrickInfo<dims> bInfo(size);
    
    long tsize = size;
    std::vector<long> stride;
    for (const auto a: dimlist) {
        size = size / a;
        stride.push_back(size);
    }
    
    init_iter<dims, dims>(dimlist, stride, bInfo, grid_ptr, grid_ptr, grid_ptr + tsize, RunningTag());

    return bInfo;
}

template<unsigned dims, unsigned d, typename F, typename A>
inline void fill(const std::vector<long> &tile, const std::vector<long> &stride, bElem *arr, A a, F f, RunningTag t) {
    for (long s = 0; s < tile[dims - d]; ++s)
        fill<dims, d - 1>(tile, stride, arr + s * stride[dims - d], a[s], f, TagSelect<d - 1>::value);
}

template<unsigned dims, unsigned d, typename F, typename A>
inline void fill(const std::vector<long> &tile, const std::vector<long> &stride, bElem *arr, A &a, F f, StopTag t) {
    f(a, arr);
}

template<unsigned dims, unsigned d, typename T, typename F>
inline void iter(const std::vector<long> &dimlist, const std::vector<long> &tile, const std::vector<long> &strideA, const std::vector<long> &strideB, T &brick, bElem *arr, unsigned *grid_ptr, F f, RunningTag t) {
    if (dims == d) {
        #pragma omp parallel for
        for (long s = 0; s < dimlist[dims - d] / tile[dims - d]; ++s)
            iter<dims, d - 1>(dimlist, tile, strideA, strideB, brick, arr + s * tile[dims - d] * strideA[dims - d], grid_ptr + s * strideB[dims - d], f, TagSelect<d - 1>::value);
    } else {
        for (long s = 0; s < dimlist[dims - d] / tile[dims - d]; ++s)
            iter<dims, d - 1>(dimlist, tile, strideA, strideB, brick, arr + s * tile[dims - d] * strideA[dims - d], grid_ptr + s * strideB[dims - d], f, TagSelect<d - 1>::value);
    }
}

template<unsigned dims, unsigned d, typename T, typename F>
inline void iter(const std::vector<long> &dimlist, const std::vector<long> &tile, const std::vector<long> &strideA, const std::vector<long> &strideB, T &brick, bElem *arr, unsigned *grid_ptr, F f, StopTag t) {
    fill<dims, dims>(tile, strideA, arr, brick[*grid_ptr], f, RunningTag());
}

template<unsigned dims, typename F, typename T, unsigned ... BDims>
inline void iter_grid(const std::vector<long> &dimlist, bElem *arr, unsigned *grid_ptr, Brick<Dim<BDims...>, T> &brick, F f) {
    std::vector<long> strideA;
    std::vector<long> strideB;
    std::vector<long> tile = {BDims...};
    
    long sizeA = 1;
    long sizeB = 1;
    for (long a = 0; a < dimlist.size(); ++a) {
        sizeA *= dimlist[a];
        sizeB *= (dimlist[a] / tile[a]);
    }
    for (long a = 0; a < dimlist.size(); ++a) {
        sizeA /= dimlist[a];
        sizeB /= (dimlist[a] / tile[a]);
        strideA.push_back(sizeA);
        strideB.push_back(sizeB);
    }
    
    iter<dims, dims>(dimlist, tile, strideA, strideB, brick, arr, grid_ptr, f, RunningTag());
}

template<unsigned dims, typename T>
inline void copyBrick(const std::vector<long> &dimlist, bElem *arr, unsigned *grid_ptr, T &brick) {
    auto f = [](bElem &brick, bElem *arr) -> void {
        brick = *arr;
    };

    iter_grid<dims>(dimlist, arr, grid_ptr, brick, f);
}

extern bool compareBrick_b;

#pragma omp threadprivate(compareBrick_b)

template<unsigned dims, typename T>
inline bool compareBrick(const std::vector<long> &dimlist, bElem *arr, unsigned *grid_ptr, T &brick) {
    bool ret = true;
    auto f = [&ret](bElem &brick, bElem *arr) -> void {
        bElem diff = std::abs(brick - *arr);
        bool r = (diff < CMP_ERR) || (diff < (std::abs(brick) + std::abs(*arr)) * CMP_ERR);
        compareBrick_b = (compareBrick_b && r);
    };

    #pragma omp parallel
    {
        compareBrick_b = true;
    }

    iter_grid<dims>(dimlist, arr, grid_ptr, brick, f);

    #pragma omp parallel
    {
        #pragma omp critical
        {
            ret = ret && compareBrick_b;
        }
    }

    return ret;
}

#endif
