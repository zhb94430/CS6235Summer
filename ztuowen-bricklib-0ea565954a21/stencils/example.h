//
// Created by Tuowen Zhao on 5/17/17.
//

#ifndef BRICKLIB_EXAMPLE_H
#define BRICKLIB_EXAMPLE_H

#include "brick.h"

#define BDIM_Z 4
#define BDIM_Y 4
#define BDIM_X 4
#define BSIZE (BDIM_X*BDIM_Y*BDIM_Z)

// Stencil
int naive_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int naive_def_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int cppaccess_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int cppaccess_split1_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int cppaccess_split1_buf_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int cppaccess_split2_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int unrolled_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int ropt_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int ropt_avx_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

int generated_stencil(brickd &inBox, brickd &outBox, brick_list &blist);

// Stream
int naive_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta);

int naive_def_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta);

int cppaccess_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta);

int noresolve_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta);

int noresolve_specialized_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta);

int unroll_stream(brickd &inBox, brickd &outBox, brick_list &blist, float beta);

// cns
//int generated_cns(brickd *cons, brickd *q, brickd *flux, brick_list &blist);

int mixed_cns(brickd *cons, brickd *q, brickd *flux, brick_list &blist);

int naive_iso3dfd(struct brickd & ptr_next, struct brickd & ptr_prev, struct brickd & ptr_vel, struct brick_list & blist, float *coeff);

int generated_iso3dfd(struct brickd & ptr_next, struct brickd & ptr_prev, struct brickd & ptr_vel, struct brick_list & blist, float *coeff);

int cuda_iso3dfd(struct brickd & ptr_next, struct brickd & ptr_prev, struct brickd & ptr_vel, struct brick_list & blist);

void cuda_iso3dfd_setup(float *coeff_host);

int naive_cns(struct brickd *cons, struct brickd *q, struct brickd *flux, struct brick_list & blist, float *dx);

int generated_cns(struct brickd *cons, struct brickd *q, struct brickd *flux, struct brick_list & blist, float *dx);

int cuda_cns(struct brickd *cons, struct brickd *q, struct brickd *flux, struct brick_list & blist);

void cuda_cns_setup(float *dx);

#endif //BRICKLIB_EXAMPLE_H
