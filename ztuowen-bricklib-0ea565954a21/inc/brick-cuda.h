//
// Created by Tuowen Zhao on 1/9/18.
//

#ifndef BRICKLIB_BRICK_CUDA_H
#define BRICKLIB_BRICK_CUDA_H

#include <cuda_runtime.h>
#include <cstdlib>
#include "brick.h"

#ifndef NDEBUG
#define cudaCheck(x) x
#else
#define cudaCheck(x) _cudaCheck(x, #x ,__FILE__, __LINE__)
#endif

template<typename T>
void _cudaCheck(T e, const char* func, const char* call, const int line){
  if(e != cudaSuccess){
    printf("\"%s\" at %d in %s\n\treturned %d\n-> %s\n", func, line, call, (int)e, cudaGetErrorString(e));
    exit(EXIT_FAILURE);
  }
}

#define cu_shl(res, l, r, kn, cw, cid) do { \
    auto l_tmp = __shfl_down_sync(0xffffffff, l, cw - (kn)); \
    auto r_tmp = __shfl_up_sync(0xffffffff, r, kn); \
    res = (cid) < kn? l_tmp : r_tmp; \
  } while(false)

brick_list cuda_copy(brick_list &host);

brick_info *cuda_copy(brick_info *host);

brickd cuda_copy(brickd &host);

brick cuda_copy(brick &host);

void cuda_send(brick &dev, brick &host);

void cuda_recv(brick &host, brick &dev);

void cuda_send(brickd &dev, brickd &host);

void cuda_recv(brickd &host, brickd &dev);

void cuda_free(brick_list &dev);

#endif //BRICKLIB_BRICK_CUDA_H
