#include"brick.h"

#define alpha 0

#define beta_i  1

#define beta_j 2

#define beta_k 3

#define lambda 4

#define rhs  5

#define H2INV  0.8f

int naive_cns(brickd *phi, brickd *inbox, brickd *phi_new, brick_list &blist, float *dx, int color) {
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    long k;
    long j;
    long i;
    {
      brick_info *binfo = phi_new[0].info;
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
      vfloat64 buf0;
      vfloat64 buf1;
      vfloat64 buf2;
      vfloat64 buf3;
      vfloat64 buf4;
      vfloat64 buf5;
      vfloat64 buf6;
      vfloat64 buf7;
      vfloat64 buf8;
      vfloat64 buf9;
      {
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf0[iit] = 0;
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf1[iit] = 0;
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf3[iit] = 0;
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf4[iit] = 0;
        __m256i phi_0__1_0_0_l;
        __m256i phi_0__1_0_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                long irel1 = rel;
                for (long yit = 0; yit < 4; yit += 2) {
                  long rel = irel1;
                  // Alignment 2, 4, 4
                  {
                    vfloat8 phi_0__1_0_0;
                    {
                      __m256i phi_0__1_0_0reg;
                      phi_0__1_0_0_l = _mm256_load_si256((__m256i *)&phi[0].dat[b12 * phi[0].step + 0 + rel]);
                      phi_0__1_0_0_r = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 0 + rel]);
                      phi_0__1_0_0reg = _mm256_alignr_epi8(phi_0__1_0_0_r, phi_0__1_0_0_l, 12);
                      _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                    }
                    #pragma vector
                    for (long vit = 0; vit < 8; ++vit) 
                      buf1[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                  }
                  // Alignment 3, 4, 4
                  {
                    vfloat8 phi_0__1_0_0;
                    {
                      __m256i phi_0__1_0_0reg;
                      phi_0__1_0_0_l = phi_0__1_0_0_r;
                      phi_0__1_0_0reg = phi_0__1_0_0_l;
                      _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                    }
                    #pragma vector
                    for (long vit = 0; vit < 8; ++vit) {
                      buf0[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                      buf1[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                    }
                  }
                  // Alignment 4, 4, 4
                  {
                    vfloat8 phi_0__1_0_0;
                    {
                      __m256i phi_0__1_0_0reg;
                      phi_0__1_0_0_r = _mm256_load_si256((__m256i *)&phi[0].dat[b14 * phi[0].step + 0 + rel]);
                      phi_0__1_0_0reg = _mm256_alignr_epi8(phi_0__1_0_0_r, phi_0__1_0_0_l, 4);
                      _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                    }
                    #pragma vector
                    for (long vit = 0; vit < 8; ++vit) 
                      buf0[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                  }
                  irel1 += 8;
                }
              }
              irel2 += 16;
            }
          }
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                // Alignment 3, 3, 4
                {
                  vfloat8 phi_0__1_0_0;
                  {
                    __m256i phi_0__1_0_0reg;
                    {
                      __m256i tbelow = _mm256_load_si256((__m256i *)&phi[0].dat[b10 * phi[0].step + 8 + rel]);
                      __m256i tabove = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 0 + rel]);
                      phi_0__1_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                    }
                    phi_0__1_0_0reg = phi_0__1_0_0_l;
                    _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf4[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                }
                // Alignment 3, 4, 4
                {
                  vfloat8 phi_0__1_0_0;
                  {
                    __m256i phi_0__1_0_0reg;
                    phi_0__1_0_0_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 0 + rel]);
                    phi_0__1_0_0reg = phi_0__1_0_0_l;
                    _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf3[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                    buf4[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                  }
                }
                // Alignment 3, 5, 4
                {
                  vfloat8 phi_0__1_0_0;
                  {
                    __m256i phi_0__1_0_0reg;
                    {
                      __m256i tbelow = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 0 + rel]);
                      __m256i tabove = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 8 + rel]);
                      phi_0__1_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                    }
                    phi_0__1_0_0reg = phi_0__1_0_0_l;
                    _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf3[rel + (0 + vit)] -= phi_0__1_0_0[vit];
                    buf4[rel + (8 + vit)] -= phi_0__1_0_0[vit];
                  }
                }
                // Alignment 3, 6, 4
                {
                  vfloat8 phi_0__1_0_0;
                  {
                    __m256i phi_0__1_0_0reg;
                    phi_0__1_0_0_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 8 + rel]);
                    phi_0__1_0_0reg = phi_0__1_0_0_l;
                    _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf3[rel + (8 + vit)] -= phi_0__1_0_0[vit];
                    buf4[rel + (8 + vit)] -= phi_0__1_0_0[vit];
                  }
                }
                // Alignment 3, 7, 4
                {
                  vfloat8 phi_0__1_0_0;
                  {
                    __m256i phi_0__1_0_0reg;
                    {
                      __m256i tbelow = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 8 + rel]);
                      __m256i tabove = _mm256_load_si256((__m256i *)&phi[0].dat[b16 * phi[0].step + 0 + rel]);
                      phi_0__1_0_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                    }
                    phi_0__1_0_0reg = phi_0__1_0_0_l;
                    _mm256_store_si256((__m256i *)&phi_0__1_0_0[0], phi_0__1_0_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf3[rel + (8 + vit)] -= phi_0__1_0_0[vit];
                }
              }
              irel2 += 16;
            }
          }
        }
      }
      {
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf2[iit] = 0;
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf6[iit] = 0;
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf7[iit] = 0;
        __m256i inbox_1__1_0_0_l;
        __m256i inbox_1__1_0_0_r;
        __m256i phi_0__0_0_1_l;
        __m256i phi_0__0_0_1_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                long irel1 = rel;
                for (long yit = 0; yit < 4; yit += 2) {
                  long rel = irel1;
                  // Alignment 3, 4, 4
                  {
                    vfloat8 inbox_1__1_0_0;
                    {
                      __m256i inbox_1__1_0_0reg;
                      inbox_1__1_0_0_l = _mm256_load_si256((__m256i *)&inbox[1].dat[b13 * inbox[1].step + 0 + rel]);
                      inbox_1__1_0_0reg = inbox_1__1_0_0_l;
                      _mm256_store_si256((__m256i *)&inbox_1__1_0_0[0], inbox_1__1_0_0reg);
                    }
                    #pragma vector
                    for (long vit = 0; vit < 8; ++vit) 
                      buf2[rel + (0 + vit)] -= inbox_1__1_0_0[vit] * buf1[0 + vit + rel];
                  }
                  // Alignment 4, 4, 4
                  {
                    vfloat8 inbox_1__1_0_0;
                    {
                      __m256i inbox_1__1_0_0reg;
                      inbox_1__1_0_0_r = _mm256_load_si256((__m256i *)&inbox[1].dat[b14 * inbox[1].step + 0 + rel]);
                      inbox_1__1_0_0reg = _mm256_alignr_epi8(inbox_1__1_0_0_r, inbox_1__1_0_0_l, 4);
                      _mm256_store_si256((__m256i *)&inbox_1__1_0_0[0], inbox_1__1_0_0reg);
                    }
                    #pragma vector
                    for (long vit = 0; vit < 8; ++vit) 
                      buf2[rel + (0 + vit)] -= inbox_1__1_0_0[vit] * buf0[0 + vit + rel];
                  }
                  irel1 += 8;
                }
              }
              irel2 += 16;
            }
          }
          {
            long irel1 = 0;
            for (long yit = 0; yit < 4; yit += 2) {
              long rel = irel1;
              {
                // Alignment 4, 4, 2
                {
                  vfloat8 phi_0__0_0_1;
                  {
                    __m256i phi_0__0_0_1reg;
                    phi_0__0_0_1_l = _mm256_load_si256((__m256i *)&phi[0].dat[b4 * phi[0].step + 48 + rel]);
                    phi_0__0_0_1reg = phi_0__0_0_1_l;
                    _mm256_store_si256((__m256i *)&phi_0__0_0_1[0], phi_0__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf7[rel + (0 + vit)] -= phi_0__0_0_1[vit];
                }
                // Alignment 4, 4, 3
                {
                  vfloat8 phi_0__0_0_1;
                  {
                    __m256i phi_0__0_0_1reg;
                    phi_0__0_0_1_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 0 + rel]);
                    phi_0__0_0_1reg = phi_0__0_0_1_l;
                    _mm256_store_si256((__m256i *)&phi_0__0_0_1[0], phi_0__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf6[rel + (0 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (0 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (16 + vit)] -= phi_0__0_0_1[vit];
                  }
                }
                // Alignment 4, 4, 4
                {
                  vfloat8 phi_0__0_0_1;
                  {
                    __m256i phi_0__0_0_1reg;
                    phi_0__0_0_1_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 16 + rel]);
                    phi_0__0_0_1reg = phi_0__0_0_1_l;
                    _mm256_store_si256((__m256i *)&phi_0__0_0_1[0], phi_0__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf6[rel + (0 + vit)] -= phi_0__0_0_1[vit];
                    buf6[rel + (16 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (16 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (32 + vit)] -= phi_0__0_0_1[vit];
                  }
                }
                // Alignment 4, 4, 5
                {
                  vfloat8 phi_0__0_0_1;
                  {
                    __m256i phi_0__0_0_1reg;
                    phi_0__0_0_1_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 32 + rel]);
                    phi_0__0_0_1reg = phi_0__0_0_1_l;
                    _mm256_store_si256((__m256i *)&phi_0__0_0_1[0], phi_0__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf6[rel + (16 + vit)] -= phi_0__0_0_1[vit];
                    buf6[rel + (32 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (32 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (48 + vit)] -= phi_0__0_0_1[vit];
                  }
                }
                // Alignment 4, 4, 6
                {
                  vfloat8 phi_0__0_0_1;
                  {
                    __m256i phi_0__0_0_1reg;
                    phi_0__0_0_1_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 48 + rel]);
                    phi_0__0_0_1reg = phi_0__0_0_1_l;
                    _mm256_store_si256((__m256i *)&phi_0__0_0_1[0], phi_0__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf6[rel + (32 + vit)] -= phi_0__0_0_1[vit];
                    buf6[rel + (48 + vit)] -= phi_0__0_0_1[vit];
                    buf7[rel + (48 + vit)] -= phi_0__0_0_1[vit];
                  }
                }
                // Alignment 4, 4, 7
                {
                  vfloat8 phi_0__0_0_1;
                  {
                    __m256i phi_0__0_0_1reg;
                    phi_0__0_0_1_l = _mm256_load_si256((__m256i *)&phi[0].dat[b22 * phi[0].step + 0 + rel]);
                    phi_0__0_0_1reg = phi_0__0_0_1_l;
                    _mm256_store_si256((__m256i *)&phi_0__0_0_1[0], phi_0__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf6[rel + (48 + vit)] -= phi_0__0_0_1[vit];
                }
              }
              irel1 += 8;
            }
          }
        }
      }
      {
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf5[iit] = 0;
        __m256i inbox_2__0_1_0_l;
        __m256i inbox_2__0_1_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                // Alignment 4, 3, 4
                {
                  vfloat8 inbox_2__0_1_0;
                  {
                    __m256i inbox_2__0_1_0reg;
                    inbox_2__0_1_0_l = _mm256_load_si256((__m256i *)&inbox[2].dat[b13 * inbox[2].step + 0 + rel]);
                    inbox_2__0_1_0reg = inbox_2__0_1_0_l;
                    _mm256_store_si256((__m256i *)&inbox_2__0_1_0[0], inbox_2__0_1_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf5[rel + (0 + vit)] -= inbox_2__0_1_0[vit] * buf4[0 + vit + rel];
                }
                // Alignment 4, 4, 4
                {
                  vfloat8 inbox_2__0_1_0;
                  {
                    __m256i inbox_2__0_1_0reg;
                    {
                      __m256i tbelow = _mm256_load_si256((__m256i *)&inbox[2].dat[b13 * inbox[2].step + 0 + rel]);
                      __m256i tabove = _mm256_load_si256((__m256i *)&inbox[2].dat[b13 * inbox[2].step + 8 + rel]);
                      inbox_2__0_1_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                    }
                    inbox_2__0_1_0reg = inbox_2__0_1_0_l;
                    _mm256_store_si256((__m256i *)&inbox_2__0_1_0[0], inbox_2__0_1_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf5[rel + (0 + vit)] -= buf2[0 + vit + rel] + inbox_2__0_1_0[vit] * buf3[0 + vit + rel];
                }
                // Alignment 4, 5, 4
                {
                  vfloat8 inbox_2__0_1_0;
                  {
                    __m256i inbox_2__0_1_0reg;
                    inbox_2__0_1_0_l = _mm256_load_si256((__m256i *)&inbox[2].dat[b13 * inbox[2].step + 8 + rel]);
                    inbox_2__0_1_0reg = inbox_2__0_1_0_l;
                    _mm256_store_si256((__m256i *)&inbox_2__0_1_0[0], inbox_2__0_1_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf5[rel + (8 + vit)] -= inbox_2__0_1_0[vit] * buf4[8 + vit + rel];
                }
                // Alignment 4, 6, 4
                {
                  vfloat8 inbox_2__0_1_0;
                  {
                    __m256i inbox_2__0_1_0reg;
                    {
                      __m256i tbelow = _mm256_load_si256((__m256i *)&inbox[2].dat[b13 * inbox[2].step + 8 + rel]);
                      __m256i tabove = _mm256_load_si256((__m256i *)&inbox[2].dat[b16 * inbox[2].step + 0 + rel]);
                      inbox_2__0_1_0_l = _mm256_permute2x128_si256(tabove, tbelow, 3);
                    }
                    inbox_2__0_1_0reg = inbox_2__0_1_0_l;
                    _mm256_store_si256((__m256i *)&inbox_2__0_1_0[0], inbox_2__0_1_0reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf5[rel + (8 + vit)] -= buf2[8 + vit + rel] + inbox_2__0_1_0[vit] * buf3[8 + vit + rel];
                }
              }
              irel2 += 16;
            }
          }
        }
      }
      {
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf8[iit] = 0;
        __m256i inbox_3__0_0_1_l;
        __m256i inbox_3__0_0_1_r;
        {
          {
            long irel1 = 0;
            for (long yit = 0; yit < 4; yit += 2) {
              long rel = irel1;
              {
                // Alignment 4, 4, 3
                {
                  vfloat8 inbox_3__0_0_1;
                  {
                    __m256i inbox_3__0_0_1reg;
                    inbox_3__0_0_1_l = _mm256_load_si256((__m256i *)&inbox[3].dat[b13 * inbox[3].step + 0 + rel]);
                    inbox_3__0_0_1reg = inbox_3__0_0_1_l;
                    _mm256_store_si256((__m256i *)&inbox_3__0_0_1[0], inbox_3__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf8[rel + (0 + vit)] -= inbox_3__0_0_1[vit] * buf7[0 + vit + rel];
                }
                // Alignment 4, 4, 4
                {
                  vfloat8 inbox_3__0_0_1;
                  {
                    __m256i inbox_3__0_0_1reg;
                    inbox_3__0_0_1_l = _mm256_load_si256((__m256i *)&inbox[3].dat[b13 * inbox[3].step + 16 + rel]);
                    inbox_3__0_0_1reg = inbox_3__0_0_1_l;
                    _mm256_store_si256((__m256i *)&inbox_3__0_0_1[0], inbox_3__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf8[rel + (0 + vit)] -= buf5[0 + vit + rel] + inbox_3__0_0_1[vit] * buf6[0 + vit + rel];
                    buf8[rel + (16 + vit)] -= inbox_3__0_0_1[vit] * buf7[16 + vit + rel];
                  }
                }
                // Alignment 4, 4, 5
                {
                  vfloat8 inbox_3__0_0_1;
                  {
                    __m256i inbox_3__0_0_1reg;
                    inbox_3__0_0_1_l = _mm256_load_si256((__m256i *)&inbox[3].dat[b13 * inbox[3].step + 32 + rel]);
                    inbox_3__0_0_1reg = inbox_3__0_0_1_l;
                    _mm256_store_si256((__m256i *)&inbox_3__0_0_1[0], inbox_3__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf8[rel + (16 + vit)] -= buf5[16 + vit + rel] + inbox_3__0_0_1[vit] * buf6[16 + vit + rel];
                    buf8[rel + (32 + vit)] -= inbox_3__0_0_1[vit] * buf7[32 + vit + rel];
                  }
                }
                // Alignment 4, 4, 6
                {
                  vfloat8 inbox_3__0_0_1;
                  {
                    __m256i inbox_3__0_0_1reg;
                    inbox_3__0_0_1_l = _mm256_load_si256((__m256i *)&inbox[3].dat[b13 * inbox[3].step + 48 + rel]);
                    inbox_3__0_0_1reg = inbox_3__0_0_1_l;
                    _mm256_store_si256((__m256i *)&inbox_3__0_0_1[0], inbox_3__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) {
                    buf8[rel + (32 + vit)] -= buf5[32 + vit + rel] + inbox_3__0_0_1[vit] * buf6[32 + vit + rel];
                    buf8[rel + (48 + vit)] -= inbox_3__0_0_1[vit] * buf7[48 + vit + rel];
                  }
                }
                // Alignment 4, 4, 7
                {
                  vfloat8 inbox_3__0_0_1;
                  {
                    __m256i inbox_3__0_0_1reg;
                    inbox_3__0_0_1_l = _mm256_load_si256((__m256i *)&inbox[3].dat[b22 * inbox[3].step + 0 + rel]);
                    inbox_3__0_0_1reg = inbox_3__0_0_1_l;
                    _mm256_store_si256((__m256i *)&inbox_3__0_0_1[0], inbox_3__0_0_1reg);
                  }
                  #pragma vector
                  for (long vit = 0; vit < 8; ++vit) 
                    buf8[rel + (48 + vit)] -= buf5[48 + vit + rel] + inbox_3__0_0_1[vit] * buf6[48 + vit + rel];
                }
              }
              irel1 += 8;
            }
          }
        }
      }
      {
        #pragma vector
        for (long iit = 0; iit < 64; ++iit) 
          buf9[iit] = 0;
        __m256i inbox_0__0_0_0_l;
        __m256i inbox_0__0_0_0_r;
        __m256i inbox_4__0_0_0_l;
        __m256i inbox_4__0_0_0_r;
        __m256i inbox_5__0_0_0_l;
        __m256i inbox_5__0_0_0_r;
        __m256i phi_0__0_0_0_l;
        __m256i phi_0__0_0_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                long irel1 = rel;
                for (long yit = 0; yit < 4; yit += 2) {
                  long rel = irel1;
                  // Alignment 4, 4, 4
                  {
                    vfloat8 phi_0__0_0_0;
                    {
                      __m256i phi_0__0_0_0reg;
                      phi_0__0_0_0_l = _mm256_load_si256((__m256i *)&phi[0].dat[b13 * phi[0].step + 0 + rel]);
                      phi_0__0_0_0reg = phi_0__0_0_0_l;
                      _mm256_store_si256((__m256i *)&phi_0__0_0_0[0], phi_0__0_0_0reg);
                    }
                    vfloat8 inbox_4__0_0_0;
                    {
                      __m256i inbox_4__0_0_0reg;
                      inbox_4__0_0_0_l = _mm256_load_si256((__m256i *)&inbox[4].dat[b13 * inbox[4].step + 0 + rel]);
                      inbox_4__0_0_0reg = inbox_4__0_0_0_l;
                      _mm256_store_si256((__m256i *)&inbox_4__0_0_0[0], inbox_4__0_0_0reg);
                    }
                    vfloat8 inbox_0__0_0_0;
                    {
                      __m256i inbox_0__0_0_0reg;
                      inbox_0__0_0_0_l = _mm256_load_si256((__m256i *)&inbox[0].dat[b13 * inbox[0].step + 0 + rel]);
                      inbox_0__0_0_0reg = inbox_0__0_0_0_l;
                      _mm256_store_si256((__m256i *)&inbox_0__0_0_0[0], inbox_0__0_0_0reg);
                    }
                    vfloat8 inbox_5__0_0_0;
                    {
                      __m256i inbox_5__0_0_0reg;
                      inbox_5__0_0_0_l = _mm256_load_si256((__m256i *)&inbox[5].dat[b13 * inbox[5].step + 0 + rel]);
                      inbox_5__0_0_0reg = inbox_5__0_0_0_l;
                      _mm256_store_si256((__m256i *)&inbox_5__0_0_0[0], inbox_5__0_0_0reg);
                    }
                    #pragma vector
                    for (long vit = 0; vit < 8; ++vit) {
                      buf9[rel + (0 + vit)] -= phi_0__0_0_0[vit];
                      buf9[rel + (0 + vit)] -= inbox_4__0_0_0[vit] * (inbox_0__0_0_0[vit] * phi_0__0_0_0[vit] - 0.800000012f * buf8[0 + vit + rel] - inbox_5__0_0_0[vit]);
                    }
                  }
                  irel1 += 8;
                }
              }
              irel2 += 16;
            }
          }
        }
      }
      {
        bElem *stp = &phi_new[0].dat[phi_new[0].step * b];
        __builtin_assume_aligned(stp, 64);
        #pragma vector nontemporal
        #pragma omp simd
        for (long sti = 0; sti < 64; ++sti) 
          stp[sti] = buf9[sti];
      }
    }
  }
  return 1;
}

