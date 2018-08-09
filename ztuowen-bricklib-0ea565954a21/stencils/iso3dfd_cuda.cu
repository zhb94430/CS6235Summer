// this source is derived from CHILL AST originally from file 'iso3dfd.cpp' as parsed by frontend compiler clang
#include "brick.h"
#include <cuda_runtime.h>
#include "brick-cuda.h"
#include "iso3dfd_cuda.h"

namespace {
  __constant__ float coeff[5];
}

__global__ void
__launch_bounds__(BLOCKDIM, NBLOCK)
_cuda_iso3dfd(struct brickd ptr_next, struct brickd ptr_prev, struct brickd ptr_vel, struct brick_list blist) {
  int lid = threadIdx.x & 31;
  int wid = (threadIdx.x >> 5);
  brick_info *binfo = ptr_next.info;
  if (wid < WARP)
    for (int r = blockIdx.x; r < blist.rlen; r += GRIDDIM)
#ifdef CYCL
      for (int o = blist.bdat[blist.rdat[r]] + wid; o < blist.bdat[blist.rdat[r + 1]]; o+=WARP) {
#else
        for (int l = blist.rdat[r] + wid; l < blist.rdat[r + 1]; l += WARP)
          for (int o = blist.bdat[l]; o < blist.bdat[l + 1]; ++o) {
#endif
      __syncthreads();
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
      float buf1[16];
      float buf0[16];
      {
        for (long iit = 0; iit < 16; ++iit)
          buf0[iit] = 0;
        float ptr_prev_0_0_0_l;
        float ptr_prev_0_0_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                long irel1 = rel;
                for (long yit = 0; yit < 4; yit += 1) {
                  long rel = irel1;
                  // Alignment 28, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      {
                        ptr_prev_0_0_0_l = ptr_prev.dat[b12 * ptr_prev.step + 0 + rel * 32 + lid];
                      }
                      {
                        ptr_prev_0_0_0_r = ptr_prev.dat[b13 * ptr_prev.step + 0 + rel * 32 + lid];
                      }
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 4, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[4];
                    }
                  }
                  // Alignment 29, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 3, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[3];
                    }
                  }
                  // Alignment 30, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 2, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[2];
                    }
                  }
                  // Alignment 31, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 1, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[1];
                    }
                  }
                  // Alignment 32, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      ptr_prev_0_0_0_l = ptr_prev_0_0_0_r;
                      ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[0];
                    }
                  }
                  // Alignment 33, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      {
                        ptr_prev_0_0_0_r = ptr_prev.dat[b14 * ptr_prev.step + 0 + rel * 32 + lid];
                      }
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 31, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[1];
                    }
                  }
                  // Alignment 34, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 30, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[2];
                    }
                  }
                  // Alignment 35, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 29, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[3];
                    }
                  }
                  // Alignment 36, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      cu_shl(ptr_prev_0_0_0, ptr_prev_0_0_0_l, ptr_prev_0_0_0_r, 28, 32, lid);
                    }
                    {
                      buf0[rel + 0] += ptr_prev_0_0_0 * coeff[4];
                    }
                  }
                  irel1 += 1;
                }
              }
              irel2 += 4;
            }
          }
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                // Alignment 32, 0, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b10 * ptr_prev.step + 0 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 1, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b10 * ptr_prev.step + 32 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 2, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b10 * ptr_prev.step + 64 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 3, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b10 * ptr_prev.step + 96 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 0 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[3];
                  }
                }
                // Alignment 32, 5, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 32 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[2];
                  }
                }
                // Alignment 32, 6, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 64 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[2];
                  }
                }
                // Alignment 32, 7, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 96 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[3];
                  }
                }
                // Alignment 32, 8, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b16 * ptr_prev.step + 0 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 9, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b16 * ptr_prev.step + 32 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 1] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 10, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b16 * ptr_prev.step + 64 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 2] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 11, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b16 * ptr_prev.step + 96 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 3] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
              }
              irel2 += 4;
            }
          }
          {
            long irel1 = 0;
            for (long yit = 0; yit < 4; yit += 1) {
              long rel = irel1;
              {
                // Alignment 32, 4, 0
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b4 * ptr_prev.step + 0 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 1
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b4 * ptr_prev.step + 128 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 2
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b4 * ptr_prev.step + 256 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 3
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b4 * ptr_prev.step + 384 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 4
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 0 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[3];
                  }
                }
                // Alignment 32, 4, 5
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 128 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[2];
                  }
                }
                // Alignment 32, 4, 6
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 256 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[2];
                  }
                }
                // Alignment 32, 4, 7
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 384 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[3];
                  }
                }
                // Alignment 32, 4, 8
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b22 * ptr_prev.step + 0 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[1];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 0] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 9
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b22 * ptr_prev.step + 128 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[2];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 4] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 10
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b22 * ptr_prev.step + 256 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[3];
                    buf0[rel + 8] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
                // Alignment 32, 4, 11
                {
                  float ptr_prev_0_0_0;
                  {
                    {
                      ptr_prev_0_0_0_l = ptr_prev.dat[b22 * ptr_prev.step + 384 + rel * 32 + lid];
                    }
                    ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                  }
                  {
                    buf0[rel + 12] += ptr_prev_0_0_0 * coeff[4];
                  }
                }
              }
              irel1 += 1;
            }
          }
        }
      }
      {
        for (long iit = 0; iit < 16; ++iit)
          buf1[iit] = 0;
        float ptr_next_0_0_0_l;
        float ptr_next_0_0_0_r;
        float ptr_prev_0_0_0_l;
        float ptr_prev_0_0_0_r;
        float ptr_vel_0_0_0_l;
        float ptr_vel_0_0_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 1) {
              long rel = irel2;
              {
                long irel1 = rel;
                for (long yit = 0; yit < 4; yit += 1) {
                  long rel = irel1;
                  // Alignment 32, 4, 4
                  {
                    float ptr_prev_0_0_0;
                    {
                      {
                        ptr_prev_0_0_0_l = ptr_prev.dat[b13 * ptr_prev.step + 0 + rel * 32 + lid];
                      }
                      ptr_prev_0_0_0 = ptr_prev_0_0_0_l;
                    }
                    float ptr_vel_0_0_0;
                    {
                      {
                        ptr_vel_0_0_0_l = ptr_vel.dat[b13 * ptr_vel.step + 0 + rel * 32 + lid];
                      }
                      ptr_vel_0_0_0 = ptr_vel_0_0_0_l;
                    }
                    float ptr_next_0_0_0;
                    {
                      {
                        ptr_next_0_0_0_l = ptr_next.dat[b13 * ptr_next.step + 0 + rel * 32 + lid];
                      }
                      ptr_next_0_0_0 = ptr_next_0_0_0_l;
                    }
                    {
                      buf1[rel + 0] += 2.0f * ptr_prev_0_0_0;
                      buf1[rel + 0] += buf0[0 + rel] * ptr_vel_0_0_0;
                      buf1[rel + 0] += (-ptr_next_0_0_0);
                    }
                  }
                  irel1 += 1;
                }
              }
              irel2 += 4;
            }
          }
        }
      }
      {
        float *stp = &ptr_next.dat[ptr_next.step * b];
        for (long sti = 0; sti < 16; ++sti)
          stp[sti * 32 + lid] = buf1[sti];
      }
    }
  }
}

int cuda_iso3dfd(struct brickd &ptr_next, struct brickd &ptr_prev, struct brickd &ptr_vel, struct brick_list &blist) {
  dim3 grid(GRIDDIM), block(BLOCKDIM);
  _cuda_iso3dfd<<<grid,block>>>(ptr_next, ptr_prev, ptr_vel, blist);
  cudaCheck(cudaGetLastError());
  return 1;
}

void cuda_iso3dfd_setup(float *coeff_host) {
  cudaMemcpyToSymbol(coeff, coeff_host, sizeof(float)*5);
}
