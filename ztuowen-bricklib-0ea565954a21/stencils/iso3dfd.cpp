//
// Created by Tuowen Zha on 5/17/17.
//

#include "brick.h"
#include "cns_const.h"

// The stencil is a 3x 1D stencil with the above coefficient

int naive_iso3dfd(brickd &ptr_next, brickd &ptr_prev, brickd &ptr_vel, brick_list &blist, float *coeff) {
#pragma omp parallel for
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    for (long k = 0; k < ptr_prev.info->dim_z; ++k)
      for (long j = 0; j < ptr_prev.info->dim_y; ++j)
        for (long i = 0; i < ptr_prev.info->dim_x; ++i) {
          float c = ptr_prev.elem(b, k, j, i) * coeff[0];
          c +=
              ptr_prev.elem(b, k + 1, j, i) * coeff[1] + ptr_prev.elem(b, k - 1, j, i) * coeff[1] +
              ptr_prev.elem(b, k + 2, j, i) * coeff[2] + ptr_prev.elem(b, k - 2, j, i) * coeff[2] +
              ptr_prev.elem(b, k + 3, j, i) * coeff[3] + ptr_prev.elem(b, k - 3, j, i) * coeff[3] +
              ptr_prev.elem(b, k + 4, j, i) * coeff[4] + ptr_prev.elem(b, k - 4, j, i) * coeff[4];
          c +=
              ptr_prev.elem(b, k, j + 1, i) * coeff[1] + ptr_prev.elem(b, k, j - 1, i) * coeff[1] +
              ptr_prev.elem(b, k, j + 2, i) * coeff[2] + ptr_prev.elem(b, k, j - 2, i) * coeff[2] +
              ptr_prev.elem(b, k, j + 3, i) * coeff[3] + ptr_prev.elem(b, k, j - 3, i) * coeff[3] +
              ptr_prev.elem(b, k, j + 4, i) * coeff[4] + ptr_prev.elem(b, k, j - 4, i) * coeff[4];
          c +=
              ptr_prev.elem(b, k, j, i + 1) * coeff[1] + ptr_prev.elem(b, k, j, i - 1) * coeff[1] +
              ptr_prev.elem(b, k, j, i + 2) * coeff[2] + ptr_prev.elem(b, k, j, i - 2) * coeff[2] +
              ptr_prev.elem(b, k, j, i + 3) * coeff[3] + ptr_prev.elem(b, k, j, i - 3) * coeff[3] +
              ptr_prev.elem(b, k, j, i + 4) * coeff[4] + ptr_prev.elem(b, k, j, i - 4) * coeff[4];
          ptr_next.elem(b, k, j, i) =
              2.0f * ptr_prev.elem(b, k, j, i) + c * ptr_vel.elem(b, k, j, i) + (-ptr_next.elem(b, k, j, i));
        }
  }
  return 1; // write + read
}

