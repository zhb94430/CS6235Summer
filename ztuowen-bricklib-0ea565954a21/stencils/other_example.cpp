//
// Created by Tuowen Zhao on 5/17/17.
//

#include "example.h"
#include "brick_cpp.h"

int naive_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta) {
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < inBox.info->dim_z; ++k)
      for (long j = 0; j < inBox.info->dim_y; ++j)
        for (long i = 0; i < inBox.info->dim_x; ++i)
          outBox.elem(b, k, j, i) = outBox.elem(b, k, j, i) + inBox.elem(b, k, j, i) * beta;
  }
  return 24; // write + read
}

int cppaccess_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta) {
  brick_info *binfo = inBox.info;
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> inB(binfo, inBox.step, inBox.dat);
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> outB(binfo, outBox.step, outBox.dat);
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) = outB(b, k, j, i) + inB(b, k, j, i) * beta;
  }
  return 24; // write + read
}

int noresolve_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta) {
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o] * outBox.info->bri_sz;
    long offset = 0;
    for (long k = 0; k < inBox.info->dim_z; ++k)
      for (long j = 0; j < inBox.info->dim_y; ++j)
#pragma omp simd
          for (long i = 0; i < inBox.info->dim_x; ++i) {
            outBox.dat[b + offset] = outBox.dat[b + offset] + inBox.dat[b + offset] * beta;
            ++offset;
          }
  }
  return 24; // write + read
}

int noresolve_specialized_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta) {
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o] * BSIZE;
    long offset = 0;
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i, ++offset)
          outBox.dat[b + offset] = outBox.dat[b + offset] + inBox.dat[b + offset] * beta;
  }
  return 24; // write + read
}

int unroll_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta) {
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o] * BSIZE;
    for (long i = 0; i < BSIZE; ++i) {
      outBox.dat[b + i] = outBox.dat[b + i] + inBox.dat[b + i] * beta;
    }
  }
  return 24; // write + read
}
