//
// Created by Tuowen Zha on 5/17/17.
//

#include "example.h"
#include "brick_cpp.h"
#include "cns_const.h"

// The stencil is a 3x 1D stencil with the above coefficient

int naive_stencil(brickd &inBox, brickd &outBox, brick_list &blist) {
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < inBox.info->dim_z; ++k)
      for (long j = 0; j < inBox.info->dim_y; ++j)
        for (long i = 0; i < inBox.info->dim_x; ++i) {
          float c = 0;
          c -=
              (inBox.elem(b, k + 1, j, i) - inBox.elem(b, k - 1, j, i)) * ALP +
              (inBox.elem(b, k + 2, j, i) - inBox.elem(b, k - 2, j, i)) * BET +
              (inBox.elem(b, k + 3, j, i) - inBox.elem(b, k - 3, j, i)) * GAM +
              (inBox.elem(b, k + 4, j, i) - inBox.elem(b, k - 4, j, i)) * DEL;
          c -=
              (inBox.elem(b, k, j + 1, i) - inBox.elem(b, k, j - 1, i)) * ALP +
              (inBox.elem(b, k, j + 2, i) - inBox.elem(b, k, j - 2, i)) * BET +
              (inBox.elem(b, k, j + 3, i) - inBox.elem(b, k, j - 3, i)) * GAM +
              (inBox.elem(b, k, j + 4, i) - inBox.elem(b, k, j - 4, i)) * DEL;
          c -=
              (inBox.elem(b, k, j, i + 1) - inBox.elem(b, k, j, i - 1)) * ALP +
              (inBox.elem(b, k, j, i + 2) - inBox.elem(b, k, j, i - 2)) * BET +
              (inBox.elem(b, k, j, i + 3) - inBox.elem(b, k, j, i - 3)) * GAM +
              (inBox.elem(b, k, j, i + 4) - inBox.elem(b, k, j, i - 4)) * DEL;
          outBox.elem(b, k, j, i) = c;
        }
  }
  return 35; // write + read
}

int cppaccess_stencil(brickd &inBox, brickd &outBox, brick_list &blist) {
  brick_info *binfo = inBox.info;
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> inB(binfo, inBox.step, inBox.dat);
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> outB(binfo, outBox.step, outBox.dat);
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i) {
          float c;
          c = -(
              (inB(b, k + 1, j, i) - inB(b, k - 1, j, i)) * ALP +
              (inB(b, k + 2, j, i) - inB(b, k - 2, j, i)) * BET +
              (inB(b, k + 3, j, i) - inB(b, k - 3, j, i)) * GAM +
              (inB(b, k + 4, j, i) - inB(b, k - 4, j, i)) * DEL);
          c -=
              (inB(b, k, j + 1, i) - inB(b, k, j - 1, i)) * ALP +
              (inB(b, k, j + 2, i) - inB(b, k, j - 2, i)) * BET +
              (inB(b, k, j + 3, i) - inB(b, k, j - 3, i)) * GAM +
              (inB(b, k, j + 4, i) - inB(b, k, j - 4, i)) * DEL;
          c -=
              (inB(b, k, j, i + 1) - inB(b, k, j, i - 1)) * ALP +
              (inB(b, k, j, i + 2) - inB(b, k, j, i - 2)) * BET +
              (inB(b, k, j, i + 3) - inB(b, k, j, i - 3)) * GAM +
              (inB(b, k, j, i + 4) - inB(b, k, j, i - 4)) * DEL;
          outB(b, k, j, i) = c;
        }
  }
  return 35; // write + read
}

int cppaccess_split1_stencil(brickd &inBox, brickd &outBox, brick_list &blist) {
  brick_info *binfo = inBox.info;
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> inB(binfo, inBox.step, inBox.dat);
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> outB(binfo, outBox.step, outBox.dat);
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) = -(
              (inB(b, k + 1, j, i) - inB(b, k - 1, j, i)) * ALP +
              (inB(b, k + 2, j, i) - inB(b, k - 2, j, i)) * BET +
              (inB(b, k + 3, j, i) - inB(b, k - 3, j, i)) * GAM +
              (inB(b, k + 4, j, i) - inB(b, k - 4, j, i)) * DEL);

    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) -=
              (inB(b, k, j + 1, i) - inB(b, k, j - 1, i)) * ALP +
              (inB(b, k, j + 2, i) - inB(b, k, j - 2, i)) * BET +
              (inB(b, k, j + 3, i) - inB(b, k, j - 3, i)) * GAM +
              (inB(b, k, j + 4, i) - inB(b, k, j - 4, i)) * DEL;

    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) -=
              (inB(b, k, j, i + 1) - inB(b, k, j, i - 1)) * ALP +
              (inB(b, k, j, i + 2) - inB(b, k, j, i - 2)) * BET +
              (inB(b, k, j, i + 3) - inB(b, k, j, i - 3)) * GAM +
              (inB(b, k, j, i + 4) - inB(b, k, j, i - 4)) * DEL;
  }
  return 35; // write + read
}

int cppaccess_split1_buf_stencil(brickd &inBox, brickd &outBox, brick_list &blist) {
  brick_info *binfo = inBox.info;
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> inB(binfo, inBox.step, inBox.dat);
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    float __attribute__((aligned(64))) buf[4][4][4];
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          buf[k][j][i] = -(
              (inB(b, k + 1, j, i) - inB(b, k - 1, j, i)) * ALP +
              (inB(b, k + 2, j, i) - inB(b, k - 2, j, i)) * BET +
              (inB(b, k + 3, j, i) - inB(b, k - 3, j, i)) * GAM +
              (inB(b, k + 4, j, i) - inB(b, k - 4, j, i)) * DEL);

    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          buf[k][j][i] -=
              (inB(b, k, j + 1, i) - inB(b, k, j - 1, i)) * ALP +
              (inB(b, k, j + 2, i) - inB(b, k, j - 2, i)) * BET +
              (inB(b, k, j + 3, i) - inB(b, k, j - 3, i)) * GAM +
              (inB(b, k, j + 4, i) - inB(b, k, j - 4, i)) * DEL;

    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          buf[k][j][i] -=
              (inB(b, k, j, i + 1) - inB(b, k, j, i - 1)) * ALP +
              (inB(b, k, j, i + 2) - inB(b, k, j, i - 2)) * BET +
              (inB(b, k, j, i + 3) - inB(b, k, j, i - 3)) * GAM +
              (inB(b, k, j, i + 4) - inB(b, k, j, i - 4)) * DEL;
    b = b * outBox.step;
    float *bp = &buf[0][0][0];
    for (long i = 0; i < 64; ++i)
      outBox.dat[b + i] = bp[i];
  }
  return 35; // write + read
}

int cppaccess_split2_stencil(brickd &inBox, brickd &outBox, brick_list &blist) {
  brick_info *binfo = inBox.info;
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> inB(binfo, inBox.step, inBox.dat);
  cppaccess<BDIM_Z, BDIM_Y, BDIM_X, float> outB(binfo, outBox.step, outBox.dat);
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) -=
              (inB(b, k + 1, j, i) - inB(b, k - 1, j, i)) * ALP +
              (inB(b, k + 2, j, i) - inB(b, k - 2, j, i)) * BET +
              (inB(b, k + 3, j, i) - inB(b, k - 3, j, i)) * GAM +
              (inB(b, k + 4, j, i) - inB(b, k - 4, j, i)) * DEL;
  }
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) -=
              (inB(b, k, j + 1, i) - inB(b, k, j - 1, i)) * ALP +
              (inB(b, k, j + 2, i) - inB(b, k, j - 2, i)) * BET +
              (inB(b, k, j + 3, i) - inB(b, k, j - 3, i)) * GAM +
              (inB(b, k, j + 4, i) - inB(b, k, j - 4, i)) * DEL;

  }
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < BDIM_Z; ++k)
      for (long j = 0; j < BDIM_Y; ++j)
        for (long i = 0; i < BDIM_X; ++i)
          outB(b, k, j, i) -=
              (inB(b, k, j, i + 1) - inB(b, k, j, i - 1)) * ALP +
              (inB(b, k, j, i + 2) - inB(b, k, j, i - 2)) * BET +
              (inB(b, k, j, i + 3) - inB(b, k, j, i - 3)) * GAM +
              (inB(b, k, j, i + 4) - inB(b, k, j, i - 4)) * DEL;
  }
  return 35; // write + read
}
