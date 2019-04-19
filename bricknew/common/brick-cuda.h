//
// Created by Tuowen Zhao on 12/5/18.
//

#ifndef BRICK_BRICK_CUDA_H
#define BRICK_BRICK_CUDA_H

#include <brick.h>
#include <cuda_runtime.h>

#ifndef NDEBUG
#define cudaCheck(x) x
#else
#define cudaCheck(x) _cudaCheck(x, #x ,__FILE__, __LINE__)
#endif

template<typename T>
void _cudaCheck(T e, const char *func, const char *call, const int line) {
  if (e != cudaSuccess) {
    printf("\"%s\" at %d in %s\n\treturned %d\n-> %s\n", func, line, call, (int) e, cudaGetErrorString(e));
    exit(EXIT_FAILURE);
  }
}

#define cu_shl(res, l, r, kn, cw, cid) do { \
    auto l_tmp = __shfl_down_sync(0xffffffff, l, cw - (kn)); \
    auto r_tmp = __shfl_up_sync(0xffffffff, r, kn); \
    res = (cid) < kn? l_tmp : r_tmp; \
  } while(false)

template<unsigned dims>
BrickInfo<dims> movBrickInfo(BrickInfo<dims> &bInfo, cudaMemcpyKind k) {
  // Make a copy
  BrickInfo<dims> ret = bInfo;
  unsigned size = bInfo.nbricks * static_power<3, dims>::value * sizeof(unsigned);
  cudaMalloc(&ret.adj, size);
  cudaMemcpy(ret.adj, bInfo.adj, size, k);
  return ret;
}

inline BrickStorage movBrickStorage(BrickStorage &bStorage, cudaMemcpyKind k) {
  // Make a copy
  BrickStorage ret = bStorage;
  unsigned size = bStorage.step * bStorage.chunks * sizeof(bElem);
  cudaMalloc(&ret.dat, size);
  cudaMemcpy(ret.dat, bStorage.dat, size, k);
  return ret;
}

#endif //BRICK_BRICK_CUDA_H
