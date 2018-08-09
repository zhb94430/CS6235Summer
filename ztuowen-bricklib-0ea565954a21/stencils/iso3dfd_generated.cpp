// this source is derived from CHILL AST originally from file 'iso3dfd.cpp' as parsed by frontend compiler clang
#include"brick.h"
#include"immintrin.h"
#include"cns_const.h"
#include"omp.h"

int generated_iso3dfd(struct brickd & ptr_next, struct brickd & ptr_prev, struct brickd & ptr_vel, struct brick_list & blist, float *coeff) {
    omp_set_num_threads(blist.lv1);
#pragma omp parallel for schedule(dynamic, 1) proc_bind(spread)
  for (long r = 0; r < blist.rlen; ++r) {
    omp_set_num_threads(blist.lv2);
#pragma omp parallel for schedule(static, 1) proc_bind(close)
    for (long l = blist.rdat[r]; l < blist.rdat[r + 1]; ++l)
      for (long o = blist.bdat[l]; o < blist.bdat[l + 1]; ++o) {
        long b = blist.dat[o];
        {
          brick_info *binfo = ptr_next.info;
          long b0 = binfo->adj[b][0];
          long b1 = binfo->adj[b][1];
          long b2 = binfo->adj[b][2];
          long b3 = binfo->adj[b][3];
          long b4 = binfo->adj[b][4];
          long b5 = binfo->adj[b][5];
          long b6 = binfo->adj[b][6];
          long b7 = binfo->adj[b][7];
          long b8 = binfo->adj[b][8];
          long b9 = binfo->adj[b][9];
          long b10 = binfo->adj[b][10];
          long b11 = binfo->adj[b][11];
          long b12 = binfo->adj[b][12];
          long b13 = b;
          long b14 = binfo->adj[b][13];
          long b15 = binfo->adj[b][14];
          long b16 = binfo->adj[b][15];
          long b17 = binfo->adj[b][16];
          long b18 = binfo->adj[b][17];
          long b19 = binfo->adj[b][18];
          long b20 = binfo->adj[b][19];
          long b21 = binfo->adj[b][20];
          long b22 = binfo->adj[b][21];
          long b23 = binfo->adj[b][22];
          long b24 = binfo->adj[b][23];
          long b25 = binfo->adj[b][24];
          long b26 = binfo->adj[b][25];
          vfloat64 buf1;
          vfloat64 buf0;
          {
#pragma omp simd
            for (long iit = 0; iit < 64; ++iit)
              buf0[iit] = 0;
            __m256i ptr_prev_0_0_0_l;
            __m256i ptr_prev_0_0_0_r;
            {
              // Alignment 4, 4, 0
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 6, 0
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 4, 1
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 6, 1
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 4, 2
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 6, 2
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 4, 3
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 6, 3
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b4 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 0, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 1, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 0]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 8]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 2, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 3, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 8]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 0]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 0, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 5, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 0]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 8]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                }
              }
              // Alignment 0, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 7, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 8]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 0]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 4, 8, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 9, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 0]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 8]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 10, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 0, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 1, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 16]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 24]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 2, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 3, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 24]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 16]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 0, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 5, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 16]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 24]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                }
              }
              // Alignment 0, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 7, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 24]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 16]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 4, 8, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 9, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 16]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 24]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 10, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 0, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 1, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 32]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 40]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 2, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 3, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 40]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 32]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 0, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 5, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 32]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 40]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                }
              }
              // Alignment 0, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 7, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 40]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 32]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 4, 8, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 9, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 32]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 40]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 10, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 0, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 1, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 48]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 56]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 2, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 3, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b10 * ptr_prev.step + 56]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 48]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 0, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 5, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 48]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 56]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                }
              }
              // Alignment 0, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b12 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 1, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 2, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 3, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 4, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[0];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                }
              }
              // Alignment 5, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_r = _mm256_load_si256((__m256i *) &ptr_prev.dat[b14 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 4);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
              }
              // Alignment 6, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 8);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
              }
              // Alignment 7, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 12);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 8, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 7, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 56]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 48]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                }
              }
              // Alignment 4, 8, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 9, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  {
                    __m256i tbelow = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 48]);
                    __m256i tabove = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 56]);
                    ptr_prev_0_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                  }
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
              }
              // Alignment 4, 10, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b16 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 4, 8
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[0 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 6, 8
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[1];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[8 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 4, 9
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[16 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 6, 9
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[2];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[24 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 4, 10
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[32 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 6, 10
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[3];
                  buf0[40 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
                }
              }
              // Alignment 4, 4, 11
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[48 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
              // Alignment 4, 6, 11
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b22 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit)
                  buf0[56 + vit] += ptr_prev_0_0_0[vit] * coeff[4];
              }
            }
          }
          {
#pragma omp simd
            for (long iit = 0; iit < 64; ++iit)
              buf1[iit] = 0;
            __m256i ptr_next_0_0_0_l;
            __m256i ptr_next_0_0_0_r;
            __m256i ptr_prev_0_0_0_l;
            __m256i ptr_prev_0_0_0_r;
            __m256i ptr_vel_0_0_0_l;
            __m256i ptr_vel_0_0_0_r;
            {
              // Alignment 4, 4, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 0]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 0]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 0]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[0 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[0 + vit] += buf0[0 + vit] * ptr_vel_0_0_0[vit];
                  buf1[0 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 6, 4
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 8]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 8]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 8]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[8 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[8 + vit] += buf0[8 + vit] * ptr_vel_0_0_0[vit];
                  buf1[8 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 4, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 16]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 16]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 16]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[16 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[16 + vit] += buf0[16 + vit] * ptr_vel_0_0_0[vit];
                  buf1[16 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 6, 5
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 24]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 24]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 24]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[24 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[24 + vit] += buf0[24 + vit] * ptr_vel_0_0_0[vit];
                  buf1[24 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 4, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 32]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 32]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 32]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[32 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[32 + vit] += buf0[32 + vit] * ptr_vel_0_0_0[vit];
                  buf1[32 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 6, 6
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 40]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 40]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 40]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[40 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[40 + vit] += buf0[40 + vit] * ptr_vel_0_0_0[vit];
                  buf1[40 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 4, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 48]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 48]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 48]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[48 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[48 + vit] += buf0[48 + vit] * ptr_vel_0_0_0[vit];
                  buf1[48 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
              // Alignment 4, 6, 7
              {
                vfloat8 ptr_prev_0_0_0;
                {
                  __m256i ptr_prev_0_0_0reg;
                  ptr_prev_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_prev.dat[b13 * ptr_prev.step + 56]);
                  ptr_prev_0_0_0reg = _mm256_alignr_epi8(ptr_prev_0_0_0_r, ptr_prev_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_prev_0_0_0[0], ptr_prev_0_0_0reg);
                }
                vfloat8 ptr_vel_0_0_0;
                {
                  __m256i ptr_vel_0_0_0reg;
                  ptr_vel_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_vel.dat[b13 * ptr_vel.step + 56]);
                  ptr_vel_0_0_0reg = _mm256_alignr_epi8(ptr_vel_0_0_0_r, ptr_vel_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_vel_0_0_0[0], ptr_vel_0_0_0reg);
                }
                vfloat8 ptr_next_0_0_0;
                {
                  __m256i ptr_next_0_0_0reg;
                  ptr_next_0_0_0_l = _mm256_load_si256((__m256i *) &ptr_next.dat[b13 * ptr_next.step + 56]);
                  ptr_next_0_0_0reg = _mm256_alignr_epi8(ptr_next_0_0_0_r, ptr_next_0_0_0_l, 0);
                  _mm256_store_si256((__m256i *) &ptr_next_0_0_0[0], ptr_next_0_0_0reg);
                }
#pragma omp simd
                for (long vit = 0; vit < 8; ++vit) {
                  buf1[56 + vit] += 2.0f * ptr_prev_0_0_0[vit];
                  buf1[56 + vit] += buf0[56 + vit] * ptr_vel_0_0_0[vit];
                  buf1[56 + vit] += (-ptr_next_0_0_0[vit]);
                }
              }
            }
          }
          {
            float *stp = &ptr_next.dat[ptr_next.step * b];
            __builtin_assume_aligned(stp, 64);
#pragma omp simd
            for (long sti = 0; sti < 64; ++sti)
              stp[sti] = buf1[sti];
          }
        }
      }
  }
  return 1;
}
