#include "brick-cuda.h"
#include "head.h"
#include "headcu.h"

#define H2INV  0.8f

__global__ void GSRBKernel(double* phi, double* phi_new, double* rhs, double* alpha, double* beta_i,
                           double* beta_j, double* beta_k, double* lambda, int color)
{
    int i, j, k;
    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i >= STRIDE-GZ || i < GZ)
    {
       return;
    }

    for (k=GZ; k<STRIDE-GZ; k++)
    {
        for(j=GZ; j<STRIDE-GZ; j++)
        {

            int ijk = i + j*STRIDE + k*(STRIDE*STRIDE);

            // if ((i+j+k+color) % 2 == 0)
            {
                double helmholtz = alpha[ijk]*phi[ijk]
                                 - H2INV*(
                                       beta_i[ijk+1     ]*( phi[ijk+1     ]-phi[ijk       ] )
                                     - beta_i[ijk       ]*( phi[ijk       ]-phi[ijk-1     ] )
                                     + beta_j[ijk+STRIDE]*( phi[ijk+STRIDE]-phi[ijk       ] )
                                     - beta_j[ijk       ]*( phi[ijk       ]-phi[ijk-STRIDE] )
                                     + beta_k[ijk+(STRIDE*STRIDE) ]*( phi[ijk+(STRIDE*STRIDE) ]-phi[ijk       ] )
                                     - beta_k[ijk       ]*( phi[ijk       ]-phi[ijk-(STRIDE*STRIDE) ] )
                                      );

                phi_new[ijk] = phi[ijk] - lambda[ijk]*(helmholtz-rhs[ijk]);
            }
        }
    }
}

__global__ void
brick_kernel(unsigned (*grid)[STRIDE/TILEJ][STRIDE/TILEI], Brick3D phi, Brick3D alpha, Brick3D beta_i, Brick3D beta_j,
        Brick3D beta_k, Brick3D phi_new, Brick3D lambda, Brick3D rhs) {
    unsigned k = GZ / TILEK + blockIdx.z;
    unsigned j = GZ / TILEJ + blockIdx.y;
    unsigned i = GZ / TILEI + blockIdx.x;

    unsigned b = grid[k][j][i];

{
  auto *binfo = phi_new.bInfo;
  long neighbor0 = binfo->adj[b][0];
  long neighbor1 = binfo->adj[b][1];
  long neighbor2 = binfo->adj[b][2];
  long neighbor3 = binfo->adj[b][3];
  long neighbor4 = binfo->adj[b][4];
  long neighbor5 = binfo->adj[b][5];
  long neighbor6 = binfo->adj[b][6];
  long neighbor7 = binfo->adj[b][7];
  long neighbor8 = binfo->adj[b][8];
  long neighbor9 = binfo->adj[b][9];
  long neighbor10 = binfo->adj[b][10];
  long neighbor11 = binfo->adj[b][11];
  long neighbor12 = binfo->adj[b][12];
  long neighbor13 = b;
  long neighbor14 = binfo->adj[b][14];
  long neighbor15 = binfo->adj[b][15];
  long neighbor16 = binfo->adj[b][16];
  long neighbor17 = binfo->adj[b][17];
  long neighbor18 = binfo->adj[b][18];
  long neighbor19 = binfo->adj[b][19];
  long neighbor20 = binfo->adj[b][20];
  long neighbor21 = binfo->adj[b][21];
  long neighbor22 = binfo->adj[b][22];
  long neighbor23 = binfo->adj[b][23];
  long neighbor24 = binfo->adj[b][24];
  long neighbor25 = binfo->adj[b][25];
  long neighbor26 = binfo->adj[b][26];
  bElem buf0[16];
  {
    {
      {
        long _cg_rel2 = 0;
        for (long _cg_idx2 = 0; _cg_idx2 < 8; _cg_idx2 += 1)
        {
          long rel = _cg_rel2;
          {
            // New offset [0, 0, 0]
            buf0[0 + rel] = 0;
          }
          {
            // New offset [0, 4, 0]
            buf0[1 + rel] = 0;
          }
          _cg_rel2 += 2;
        }
      }
    }
    {
      bElem _cg_beta_i000_vecbuf;
      bElem _cg_beta_i100_vecbuf;
      bElem _cg_phi000_vecbuf;
      bElem _cg_phi100_vecbuf;
      bElem _cg_phi_100_vecbuf;
      bElem _cg_beta_j010_vecbuf;
      bElem _cg_beta_j000_vecbuf;
      bElem _cg_beta_k001_vecbuf;
      bElem _cg_beta_k000_vecbuf;
      {
        long _cg_rel2 = 0;
        for (long _cg_idx2 = 0; _cg_idx2 < 7; _cg_idx2 += 1)
        {
          long rel = _cg_rel2;
          {
            // New offset [-1, 0, 0]
            bElem _cg_beta_i100_reg;
            bElem _cg_phi100_reg;
            bElem _cg_phi000_reg;
            bElem _cg_beta_j100_reg;
            bElem _cg_beta_k101_reg;
            bElem _cg_beta_k100_reg;
            {
              _cg_beta_i000_vecbuf = beta_i.dat[neighbor13 * beta_i.step + (threadIdx.x + rel * 32)];
              _cg_phi_100_vecbuf = phi.dat[neighbor12 * phi.step + (threadIdx.x + rel * 32)];
              _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + (threadIdx.x + rel * 32)];
              _cg_beta_j000_vecbuf = beta_j.dat[neighbor13 * beta_j.step + (threadIdx.x + rel * 32)];
              _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + (threadIdx.x + rel * 32)];
              _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 64 + (threadIdx.x + rel * 32)];
              _cg_beta_i100_reg = _cg_beta_i000_vecbuf;
              _cg_phi100_reg = _cg_phi000_vecbuf;
              bElem _cg_vectmp0;
              // merge0 _cg_phi_100_vecbuf ,_cg_phi000_vecbuf, 7 -> _cg_vectmp0
              cu_shl(_cg_vectmp0, _cg_phi_100_vecbuf, _cg_phi000_vecbuf, 1, 8, threadIdx.x & 7);
              _cg_phi000_reg = _cg_vectmp0;
              _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
              _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
              _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
            }
            buf0[0 + rel] -= _cg_beta_i100_reg * _cg_phi100_reg;
            buf0[0 + rel] += _cg_beta_i100_reg * _cg_phi000_reg;
            buf0[0 + rel] -= _cg_beta_j100_reg * _cg_phi100_reg;
            buf0[0 + rel] -= _cg_beta_k101_reg * _cg_phi100_reg;
            buf0[0 + rel] -= _cg_beta_k100_reg * _cg_phi100_reg;
          }
          {
            // New offset [0, 0, 0]
            bElem _cg_beta_i100_reg;
            bElem _cg_phi100_reg;
            bElem _cg_phi000_reg;
            bElem _cg_beta_j010_reg;
            {
              _cg_beta_i100_vecbuf = beta_i.dat[neighbor14 * beta_i.step + (threadIdx.x + rel * 32)];
              _cg_phi100_vecbuf = phi.dat[neighbor14 * phi.step + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp0;
              _cg_vectmp0 = beta_j.dat[neighbor13 * beta_j.step + 32 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp1;
              _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j010_vecbuf
              cu_shl(_cg_beta_j010_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
              bElem _cg_vectmp2;
              // merge0 _cg_beta_i000_vecbuf ,_cg_beta_i100_vecbuf, 1 -> _cg_vectmp2
              cu_shl(_cg_vectmp2, _cg_beta_i000_vecbuf, _cg_beta_i100_vecbuf, 7, 8, threadIdx.x & 7);
              _cg_beta_i100_reg = _cg_vectmp2;
              bElem _cg_vectmp3;
              // merge0 _cg_phi000_vecbuf ,_cg_phi100_vecbuf, 1 -> _cg_vectmp3
              cu_shl(_cg_vectmp3, _cg_phi000_vecbuf, _cg_phi100_vecbuf, 7, 8, threadIdx.x & 7);
              _cg_phi100_reg = _cg_vectmp3;
              _cg_phi000_reg = _cg_phi000_vecbuf;
              _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
            }
            buf0[0 + rel] += _cg_beta_i100_reg * _cg_phi100_reg;
            buf0[0 + rel] -= _cg_beta_i100_reg * _cg_phi000_reg;
            buf0[0 + rel] -= _cg_beta_j010_reg * _cg_phi000_reg;
          }
          {
            // New offset [-1, 4, 0]
            bElem _cg_beta_i100_reg;
            bElem _cg_phi100_reg;
            bElem _cg_phi000_reg;
            bElem _cg_beta_j100_reg;
            bElem _cg_beta_k101_reg;
            bElem _cg_beta_k100_reg;
            {
              _cg_beta_i000_vecbuf = beta_i.dat[neighbor13 * beta_i.step + 32 + (threadIdx.x + rel * 32)];
              _cg_phi_100_vecbuf = phi.dat[neighbor12 * phi.step + 32 + (threadIdx.x + rel * 32)];
              _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 32 + (threadIdx.x + rel * 32)];
              _cg_beta_j000_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 32 + (threadIdx.x + rel * 32)];
              _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 32 + (threadIdx.x + rel * 32)];
              _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 96 + (threadIdx.x + rel * 32)];
              _cg_beta_i100_reg = _cg_beta_i000_vecbuf;
              _cg_phi100_reg = _cg_phi000_vecbuf;
              bElem _cg_vectmp0;
              // merge0 _cg_phi_100_vecbuf ,_cg_phi000_vecbuf, 7 -> _cg_vectmp0
              cu_shl(_cg_vectmp0, _cg_phi_100_vecbuf, _cg_phi000_vecbuf, 1, 8, threadIdx.x & 7);
              _cg_phi000_reg = _cg_vectmp0;
              _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
              _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
              _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
            }
            buf0[1 + rel] -= _cg_beta_i100_reg * _cg_phi100_reg;
            buf0[1 + rel] += _cg_beta_i100_reg * _cg_phi000_reg;
            buf0[1 + rel] -= _cg_beta_j100_reg * _cg_phi100_reg;
            buf0[1 + rel] -= _cg_beta_k101_reg * _cg_phi100_reg;
            buf0[1 + rel] -= _cg_beta_k100_reg * _cg_phi100_reg;
          }
          {
            // New offset [0, 4, 0]
            bElem _cg_beta_i100_reg;
            bElem _cg_phi100_reg;
            bElem _cg_phi000_reg;
            bElem _cg_beta_j010_reg;
            {
              _cg_beta_i100_vecbuf = beta_i.dat[neighbor14 * beta_i.step + 32 + (threadIdx.x + rel * 32)];
              _cg_phi100_vecbuf = phi.dat[neighbor14 * phi.step + 32 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp0;
              _cg_vectmp0 = beta_j.dat[neighbor16 * beta_j.step + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp1;
              _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 32 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j010_vecbuf
              cu_shl(_cg_beta_j010_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
              bElem _cg_vectmp2;
              // merge0 _cg_beta_i000_vecbuf ,_cg_beta_i100_vecbuf, 1 -> _cg_vectmp2
              cu_shl(_cg_vectmp2, _cg_beta_i000_vecbuf, _cg_beta_i100_vecbuf, 7, 8, threadIdx.x & 7);
              _cg_beta_i100_reg = _cg_vectmp2;
              bElem _cg_vectmp3;
              // merge0 _cg_phi000_vecbuf ,_cg_phi100_vecbuf, 1 -> _cg_vectmp3
              cu_shl(_cg_vectmp3, _cg_phi000_vecbuf, _cg_phi100_vecbuf, 7, 8, threadIdx.x & 7);
              _cg_phi100_reg = _cg_vectmp3;
              _cg_phi000_reg = _cg_phi000_vecbuf;
              _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
            }
            buf0[1 + rel] += _cg_beta_i100_reg * _cg_phi100_reg;
            buf0[1 + rel] -= _cg_beta_i100_reg * _cg_phi000_reg;
            buf0[1 + rel] -= _cg_beta_j010_reg * _cg_phi000_reg;
          }
          _cg_rel2 += 2;
        }
      }
      {
        // New offset [-1, 0, 7]
        bElem _cg_beta_i100_reg;
        bElem _cg_phi100_reg;
        bElem _cg_phi000_reg;
        bElem _cg_beta_j100_reg;
        bElem _cg_beta_k101_reg;
        bElem _cg_beta_k100_reg;
        {
          _cg_beta_i000_vecbuf = beta_i.dat[neighbor13 * beta_i.step + 448 + threadIdx.x];
          _cg_phi_100_vecbuf = phi.dat[neighbor12 * phi.step + 448 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 448 + threadIdx.x];
          _cg_beta_j000_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 448 + threadIdx.x];
          _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 448 + threadIdx.x];
          _cg_beta_k001_vecbuf = beta_k.dat[neighbor22 * beta_k.step + threadIdx.x];
          _cg_beta_i100_reg = _cg_beta_i000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
          bElem _cg_vectmp0;
          // merge0 _cg_phi_100_vecbuf ,_cg_phi000_vecbuf, 7 -> _cg_vectmp0
          cu_shl(_cg_vectmp0, _cg_phi_100_vecbuf, _cg_phi000_vecbuf, 1, 8, threadIdx.x & 7);
          _cg_phi000_reg = _cg_vectmp0;
          _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
          _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
          _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
        }
        buf0[14] -= _cg_beta_i100_reg * _cg_phi100_reg;
        buf0[14] += _cg_beta_i100_reg * _cg_phi000_reg;
        buf0[14] -= _cg_beta_j100_reg * _cg_phi100_reg;
        buf0[14] -= _cg_beta_k101_reg * _cg_phi100_reg;
        buf0[14] -= _cg_beta_k100_reg * _cg_phi100_reg;
      }
      {
        // New offset [0, 0, 7]
        bElem _cg_beta_i100_reg;
        bElem _cg_phi100_reg;
        bElem _cg_phi000_reg;
        bElem _cg_beta_j010_reg;
        {
          _cg_beta_i100_vecbuf = beta_i.dat[neighbor14 * beta_i.step + 448 + threadIdx.x];
          _cg_phi100_vecbuf = phi.dat[neighbor14 * phi.step + 448 + threadIdx.x];
          bElem _cg_vectmp0;
          _cg_vectmp0 = beta_j.dat[neighbor13 * beta_j.step + 480 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 448 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j010_vecbuf
          cu_shl(_cg_beta_j010_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
          bElem _cg_vectmp2;
          // merge0 _cg_beta_i000_vecbuf ,_cg_beta_i100_vecbuf, 1 -> _cg_vectmp2
          cu_shl(_cg_vectmp2, _cg_beta_i000_vecbuf, _cg_beta_i100_vecbuf, 7, 8, threadIdx.x & 7);
          _cg_beta_i100_reg = _cg_vectmp2;
          bElem _cg_vectmp3;
          // merge0 _cg_phi000_vecbuf ,_cg_phi100_vecbuf, 1 -> _cg_vectmp3
          cu_shl(_cg_vectmp3, _cg_phi000_vecbuf, _cg_phi100_vecbuf, 7, 8, threadIdx.x & 7);
          _cg_phi100_reg = _cg_vectmp3;
          _cg_phi000_reg = _cg_phi000_vecbuf;
          _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
        }
        buf0[14] += _cg_beta_i100_reg * _cg_phi100_reg;
        buf0[14] -= _cg_beta_i100_reg * _cg_phi000_reg;
        buf0[14] -= _cg_beta_j010_reg * _cg_phi000_reg;
      }
      {
        // New offset [-1, 4, 7]
        bElem _cg_beta_i100_reg;
        bElem _cg_phi100_reg;
        bElem _cg_phi000_reg;
        bElem _cg_beta_j100_reg;
        bElem _cg_beta_k101_reg;
        bElem _cg_beta_k100_reg;
        {
          _cg_beta_i000_vecbuf = beta_i.dat[neighbor13 * beta_i.step + 480 + threadIdx.x];
          _cg_phi_100_vecbuf = phi.dat[neighbor12 * phi.step + 480 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 480 + threadIdx.x];
          _cg_beta_j000_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 480 + threadIdx.x];
          _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 480 + threadIdx.x];
          _cg_beta_k001_vecbuf = beta_k.dat[neighbor22 * beta_k.step + 32 + threadIdx.x];
          _cg_beta_i100_reg = _cg_beta_i000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
          bElem _cg_vectmp0;
          // merge0 _cg_phi_100_vecbuf ,_cg_phi000_vecbuf, 7 -> _cg_vectmp0
          cu_shl(_cg_vectmp0, _cg_phi_100_vecbuf, _cg_phi000_vecbuf, 1, 8, threadIdx.x & 7);
          _cg_phi000_reg = _cg_vectmp0;
          _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
          _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
          _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
        }
        buf0[15] -= _cg_beta_i100_reg * _cg_phi100_reg;
        buf0[15] += _cg_beta_i100_reg * _cg_phi000_reg;
        buf0[15] -= _cg_beta_j100_reg * _cg_phi100_reg;
        buf0[15] -= _cg_beta_k101_reg * _cg_phi100_reg;
        buf0[15] -= _cg_beta_k100_reg * _cg_phi100_reg;
      }
      {
        // New offset [0, 4, 7]
        bElem _cg_beta_i100_reg;
        bElem _cg_phi100_reg;
        bElem _cg_phi000_reg;
        bElem _cg_beta_j010_reg;
        {
          _cg_beta_i100_vecbuf = beta_i.dat[neighbor14 * beta_i.step + 480 + threadIdx.x];
          _cg_phi100_vecbuf = phi.dat[neighbor14 * phi.step + 480 + threadIdx.x];
          bElem _cg_vectmp0;
          _cg_vectmp0 = beta_j.dat[neighbor16 * beta_j.step + 448 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 480 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j010_vecbuf
          cu_shl(_cg_beta_j010_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
          bElem _cg_vectmp2;
          // merge0 _cg_beta_i000_vecbuf ,_cg_beta_i100_vecbuf, 1 -> _cg_vectmp2
          cu_shl(_cg_vectmp2, _cg_beta_i000_vecbuf, _cg_beta_i100_vecbuf, 7, 8, threadIdx.x & 7);
          _cg_beta_i100_reg = _cg_vectmp2;
          bElem _cg_vectmp3;
          // merge0 _cg_phi000_vecbuf ,_cg_phi100_vecbuf, 1 -> _cg_vectmp3
          cu_shl(_cg_vectmp3, _cg_phi000_vecbuf, _cg_phi100_vecbuf, 7, 8, threadIdx.x & 7);
          _cg_phi100_reg = _cg_vectmp3;
          _cg_phi000_reg = _cg_phi000_vecbuf;
          _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
        }
        buf0[15] += _cg_beta_i100_reg * _cg_phi100_reg;
        buf0[15] -= _cg_beta_i100_reg * _cg_phi000_reg;
        buf0[15] -= _cg_beta_j010_reg * _cg_phi000_reg;
      }
    }
    {
      bElem _cg_beta_j000_vecbuf;
      bElem _cg_beta_j010_vecbuf;
      bElem _cg_phi000_vecbuf;
      bElem _cg_beta_k000_vecbuf;
      bElem _cg_beta_k001_vecbuf;
      {
        // New offset [-1, 0, -1]
        bElem _cg_beta_k101_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor4 * phi.step + 448 + threadIdx.x];
          _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[0] += _cg_beta_k101_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 4, -1]
        bElem _cg_beta_k101_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 32 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor4 * phi.step + 480 + threadIdx.x];
          _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[1] += _cg_beta_k101_reg * _cg_phi100_reg;
      }
      {
        // New offset [0, -1, 0]
        bElem _cg_beta_j010_reg;
        bElem _cg_phi000_reg;
        {
          _cg_beta_j010_vecbuf = beta_j.dat[neighbor13 * beta_j.step + threadIdx.x];
          bElem _cg_vectmp0;
          _cg_vectmp0 = phi.dat[neighbor13 * phi.step + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = phi.dat[neighbor10 * phi.step + 32 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 3 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp1, _cg_vectmp0, 8, 32, threadIdx.x);
          _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
          _cg_phi000_reg = _cg_phi000_vecbuf;
        }
        buf0[0] += _cg_beta_j010_reg * _cg_phi000_reg;
      }
      {
        // New offset [-1, 0, 0]
        bElem _cg_beta_k101_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 64 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + threadIdx.x];
          _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[2] += _cg_beta_k101_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 1, 0]
        bElem _cg_beta_j100_reg;
        bElem _cg_phi100_reg;
        {
          bElem _cg_vectmp0;
          _cg_vectmp0 = beta_j.dat[neighbor13 * beta_j.step + 32 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j000_vecbuf
          cu_shl(_cg_beta_j000_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
          bElem _cg_vectmp2;
          _cg_vectmp2 = phi.dat[neighbor13 * phi.step + 32 + threadIdx.x];
          bElem _cg_vectmp3;
          _cg_vectmp3 = phi.dat[neighbor13 * phi.step + threadIdx.x];
          // merge1 _cg_vectmp3 ,_cg_vectmp2, 1 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp3, _cg_vectmp2, 24, 32, threadIdx.x);
          _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[0] += _cg_beta_j100_reg * _cg_phi100_reg;
      }
      {
        // New offset [0, 3, 0]
        bElem _cg_beta_j010_reg;
        bElem _cg_phi000_reg;
        {
          _cg_beta_j010_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 32 + threadIdx.x];
          bElem _cg_vectmp0;
          _cg_vectmp0 = phi.dat[neighbor13 * phi.step + 32 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = phi.dat[neighbor13 * phi.step + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 3 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp1, _cg_vectmp0, 8, 32, threadIdx.x);
          _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
          _cg_phi000_reg = _cg_phi000_vecbuf;
        }
        buf0[1] += _cg_beta_j010_reg * _cg_phi000_reg;
      }
      {
        // New offset [-1, 4, 0]
        bElem _cg_beta_k101_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 96 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 32 + threadIdx.x];
          _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[3] += _cg_beta_k101_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 5, 0]
        bElem _cg_beta_j100_reg;
        bElem _cg_phi100_reg;
        {
          bElem _cg_vectmp0;
          _cg_vectmp0 = beta_j.dat[neighbor16 * beta_j.step + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 32 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j000_vecbuf
          cu_shl(_cg_beta_j000_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
          bElem _cg_vectmp2;
          _cg_vectmp2 = phi.dat[neighbor16 * phi.step + threadIdx.x];
          bElem _cg_vectmp3;
          _cg_vectmp3 = phi.dat[neighbor13 * phi.step + 32 + threadIdx.x];
          // merge1 _cg_vectmp3 ,_cg_vectmp2, 1 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp3, _cg_vectmp2, 24, 32, threadIdx.x);
          _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[1] += _cg_beta_j100_reg * _cg_phi100_reg;
      }
      {
        long _cg_rel2 = 0;
        for (long _cg_idx2 = 0; _cg_idx2 < 6; _cg_idx2 += 1)
        {
          long rel = _cg_rel2;
          {
            // New offset [0, -1, 1]
            bElem _cg_beta_j010_reg;
            bElem _cg_phi000_reg;
            {
              _cg_beta_j010_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 64 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp0;
              _cg_vectmp0 = phi.dat[neighbor13 * phi.step + 64 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp1;
              _cg_vectmp1 = phi.dat[neighbor10 * phi.step + 96 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp1 ,_cg_vectmp0, 3 -> _cg_phi000_vecbuf
              cu_shl(_cg_phi000_vecbuf, _cg_vectmp1, _cg_vectmp0, 8, 32, threadIdx.x);
              _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
              _cg_phi000_reg = _cg_phi000_vecbuf;
            }
            buf0[2 + rel] += _cg_beta_j010_reg * _cg_phi000_reg;
          }
          {
            // New offset [-1, 0, 1]
            bElem _cg_beta_k100_reg;
            bElem _cg_phi100_reg;
            bElem _cg_beta_k101_reg;
            {
              _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 64 + (threadIdx.x + rel * 32)];
              _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 128 + (threadIdx.x + rel * 32)];
              _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 64 + (threadIdx.x + rel * 32)];
              _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
              _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
              _cg_phi100_reg = _cg_phi000_vecbuf;
            }
            buf0[0 + rel] += _cg_beta_k100_reg * _cg_phi100_reg;
            buf0[4 + rel] += _cg_beta_k101_reg * _cg_phi100_reg;
          }
          {
            // New offset [-1, 1, 1]
            bElem _cg_beta_j100_reg;
            bElem _cg_phi100_reg;
            {
              bElem _cg_vectmp0;
              _cg_vectmp0 = beta_j.dat[neighbor13 * beta_j.step + 96 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp1;
              _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 64 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j000_vecbuf
              cu_shl(_cg_beta_j000_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
              bElem _cg_vectmp2;
              _cg_vectmp2 = phi.dat[neighbor13 * phi.step + 96 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp3;
              _cg_vectmp3 = phi.dat[neighbor13 * phi.step + 64 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp3 ,_cg_vectmp2, 1 -> _cg_phi000_vecbuf
              cu_shl(_cg_phi000_vecbuf, _cg_vectmp3, _cg_vectmp2, 24, 32, threadIdx.x);
              _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
              _cg_phi100_reg = _cg_phi000_vecbuf;
            }
            buf0[2 + rel] += _cg_beta_j100_reg * _cg_phi100_reg;
          }
          {
            // New offset [0, 3, 1]
            bElem _cg_beta_j010_reg;
            bElem _cg_phi000_reg;
            {
              _cg_beta_j010_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 96 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp0;
              _cg_vectmp0 = phi.dat[neighbor13 * phi.step + 96 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp1;
              _cg_vectmp1 = phi.dat[neighbor13 * phi.step + 64 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp1 ,_cg_vectmp0, 3 -> _cg_phi000_vecbuf
              cu_shl(_cg_phi000_vecbuf, _cg_vectmp1, _cg_vectmp0, 8, 32, threadIdx.x);
              _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
              _cg_phi000_reg = _cg_phi000_vecbuf;
            }
            buf0[3 + rel] += _cg_beta_j010_reg * _cg_phi000_reg;
          }
          {
            // New offset [-1, 4, 1]
            bElem _cg_beta_k100_reg;
            bElem _cg_phi100_reg;
            bElem _cg_beta_k101_reg;
            {
              _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 96 + (threadIdx.x + rel * 32)];
              _cg_beta_k001_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 160 + (threadIdx.x + rel * 32)];
              _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 96 + (threadIdx.x + rel * 32)];
              _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
              _cg_beta_k101_reg = _cg_beta_k001_vecbuf;
              _cg_phi100_reg = _cg_phi000_vecbuf;
            }
            buf0[1 + rel] += _cg_beta_k100_reg * _cg_phi100_reg;
            buf0[5 + rel] += _cg_beta_k101_reg * _cg_phi100_reg;
          }
          {
            // New offset [-1, 5, 1]
            bElem _cg_beta_j100_reg;
            bElem _cg_phi100_reg;
            {
              bElem _cg_vectmp0;
              _cg_vectmp0 = beta_j.dat[neighbor16 * beta_j.step + 64 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp1;
              _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 96 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j000_vecbuf
              cu_shl(_cg_beta_j000_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
              bElem _cg_vectmp2;
              _cg_vectmp2 = phi.dat[neighbor16 * phi.step + 64 + (threadIdx.x + rel * 32)];
              bElem _cg_vectmp3;
              _cg_vectmp3 = phi.dat[neighbor13 * phi.step + 96 + (threadIdx.x + rel * 32)];
              // merge1 _cg_vectmp3 ,_cg_vectmp2, 1 -> _cg_phi000_vecbuf
              cu_shl(_cg_phi000_vecbuf, _cg_vectmp3, _cg_vectmp2, 24, 32, threadIdx.x);
              _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
              _cg_phi100_reg = _cg_phi000_vecbuf;
            }
            buf0[3 + rel] += _cg_beta_j100_reg * _cg_phi100_reg;
          }
          _cg_rel2 += 2;
        }
      }
      {
        // New offset [0, -1, 7]
        bElem _cg_beta_j010_reg;
        bElem _cg_phi000_reg;
        {
          _cg_beta_j010_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 448 + threadIdx.x];
          bElem _cg_vectmp0;
          _cg_vectmp0 = phi.dat[neighbor13 * phi.step + 448 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = phi.dat[neighbor10 * phi.step + 480 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 3 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp1, _cg_vectmp0, 8, 32, threadIdx.x);
          _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
          _cg_phi000_reg = _cg_phi000_vecbuf;
        }
        buf0[14] += _cg_beta_j010_reg * _cg_phi000_reg;
      }
      {
        // New offset [-1, 0, 7]
        bElem _cg_beta_k100_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k000_vecbuf = beta_k.dat[neighbor13 * beta_k.step + 448 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 448 + threadIdx.x];
          _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[12] += _cg_beta_k100_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 1, 7]
        bElem _cg_beta_j100_reg;
        bElem _cg_phi100_reg;
        {
          bElem _cg_vectmp0;
          _cg_vectmp0 = beta_j.dat[neighbor13 * beta_j.step + 480 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 448 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j000_vecbuf
          cu_shl(_cg_beta_j000_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
          bElem _cg_vectmp2;
          _cg_vectmp2 = phi.dat[neighbor13 * phi.step + 480 + threadIdx.x];
          bElem _cg_vectmp3;
          _cg_vectmp3 = phi.dat[neighbor13 * phi.step + 448 + threadIdx.x];
          // merge1 _cg_vectmp3 ,_cg_vectmp2, 1 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp3, _cg_vectmp2, 24, 32, threadIdx.x);
          _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[14] += _cg_beta_j100_reg * _cg_phi100_reg;
      }
      {
        // New offset [0, 3, 7]
        bElem _cg_beta_j010_reg;
        bElem _cg_phi000_reg;
        {
          _cg_beta_j010_vecbuf = beta_j.dat[neighbor13 * beta_j.step + 480 + threadIdx.x];
          bElem _cg_vectmp0;
          _cg_vectmp0 = phi.dat[neighbor13 * phi.step + 480 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = phi.dat[neighbor13 * phi.step + 448 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 3 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp1, _cg_vectmp0, 8, 32, threadIdx.x);
          _cg_beta_j010_reg = _cg_beta_j010_vecbuf;
          _cg_phi000_reg = _cg_phi000_vecbuf;
        }
        buf0[15] += _cg_beta_j010_reg * _cg_phi000_reg;
      }
      {
        // New offset [-1, 4, 7]
        bElem _cg_beta_k100_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k000_vecbuf = _cg_beta_k001_vecbuf;
          _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 480 + threadIdx.x];
          _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[13] += _cg_beta_k100_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 5, 7]
        bElem _cg_beta_j100_reg;
        bElem _cg_phi100_reg;
        {
          bElem _cg_vectmp0;
          _cg_vectmp0 = beta_j.dat[neighbor16 * beta_j.step + 448 + threadIdx.x];
          bElem _cg_vectmp1;
          _cg_vectmp1 = beta_j.dat[neighbor13 * beta_j.step + 480 + threadIdx.x];
          // merge1 _cg_vectmp1 ,_cg_vectmp0, 1 -> _cg_beta_j000_vecbuf
          cu_shl(_cg_beta_j000_vecbuf, _cg_vectmp1, _cg_vectmp0, 24, 32, threadIdx.x);
          bElem _cg_vectmp2;
          _cg_vectmp2 = phi.dat[neighbor16 * phi.step + 448 + threadIdx.x];
          bElem _cg_vectmp3;
          _cg_vectmp3 = phi.dat[neighbor13 * phi.step + 480 + threadIdx.x];
          // merge1 _cg_vectmp3 ,_cg_vectmp2, 1 -> _cg_phi000_vecbuf
          cu_shl(_cg_phi000_vecbuf, _cg_vectmp3, _cg_vectmp2, 24, 32, threadIdx.x);
          _cg_beta_j100_reg = _cg_beta_j000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[15] += _cg_beta_j100_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 0, 8]
        bElem _cg_beta_k100_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k000_vecbuf = beta_k.dat[neighbor22 * beta_k.step + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor22 * phi.step + threadIdx.x];
          _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[14] += _cg_beta_k100_reg * _cg_phi100_reg;
      }
      {
        // New offset [-1, 4, 8]
        bElem _cg_beta_k100_reg;
        bElem _cg_phi100_reg;
        {
          _cg_beta_k000_vecbuf = beta_k.dat[neighbor22 * beta_k.step + 32 + threadIdx.x];
          _cg_phi000_vecbuf = phi.dat[neighbor22 * phi.step + 32 + threadIdx.x];
          _cg_beta_k100_reg = _cg_beta_k000_vecbuf;
          _cg_phi100_reg = _cg_phi000_vecbuf;
        }
        buf0[15] += _cg_beta_k100_reg * _cg_phi100_reg;
      }
    }
  }
  bElem buf1[16];
  {
    {
      bElem _cg_phi000_vecbuf;
      bElem _cg_lambda000_vecbuf;
      bElem _cg_alpha000_vecbuf;
      bElem _cg_rhs000_vecbuf;
      {
        long _cg_rel2 = 0;
        for (long _cg_idx2 = 0; _cg_idx2 < 8; _cg_idx2 += 1)
        {
          long rel = _cg_rel2;
          {
            // New offset [0, 0, 0]
            bElem _cg_phi000_reg;
            bElem _cg_lambda000_reg;
            bElem _cg_alpha000_reg;
            bElem _cg_rhs000_reg;
            {
              _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + (threadIdx.x + rel * 32)];
              _cg_lambda000_vecbuf = lambda.dat[neighbor13 * lambda.step + (threadIdx.x + rel * 32)];
              _cg_alpha000_vecbuf = alpha.dat[neighbor13 * alpha.step + (threadIdx.x + rel * 32)];
              _cg_rhs000_vecbuf = rhs.dat[neighbor13 * rhs.step + (threadIdx.x + rel * 32)];
              _cg_phi000_reg = _cg_phi000_vecbuf;
              _cg_lambda000_reg = _cg_lambda000_vecbuf;
              _cg_alpha000_reg = _cg_alpha000_vecbuf;
              _cg_rhs000_reg = _cg_rhs000_vecbuf;
            }
            buf1[0 + rel] = _cg_phi000_reg - _cg_lambda000_reg * (_cg_alpha000_reg * _cg_phi000_reg - H2INV * buf0[0 + rel] - _cg_rhs000_reg);
          }
          {
            // New offset [0, 4, 0]
            bElem _cg_phi000_reg;
            bElem _cg_lambda000_reg;
            bElem _cg_alpha000_reg;
            bElem _cg_rhs000_reg;
            {
              _cg_phi000_vecbuf = phi.dat[neighbor13 * phi.step + 32 + (threadIdx.x + rel * 32)];
              _cg_lambda000_vecbuf = lambda.dat[neighbor13 * lambda.step + 32 + (threadIdx.x + rel * 32)];
              _cg_alpha000_vecbuf = alpha.dat[neighbor13 * alpha.step + 32 + (threadIdx.x + rel * 32)];
              _cg_rhs000_vecbuf = rhs.dat[neighbor13 * rhs.step + 32 + (threadIdx.x + rel * 32)];
              _cg_phi000_reg = _cg_phi000_vecbuf;
              _cg_lambda000_reg = _cg_lambda000_vecbuf;
              _cg_alpha000_reg = _cg_alpha000_vecbuf;
              _cg_rhs000_reg = _cg_rhs000_vecbuf;
            }
            buf1[1 + rel] = _cg_phi000_reg - _cg_lambda000_reg * (_cg_alpha000_reg * _cg_phi000_reg - H2INV * buf0[1 + rel] - _cg_rhs000_reg);
          }
          _cg_rel2 += 2;
        }
      }
    }
    bElem *phi_new_ref = &phi_new.dat[neighbor13 * phi_new.step];
    for (long sti = 0; sti < 16; ++sti)
    {
      phi_new_ref[sti * 32 + threadIdx.x] = buf1[sti];
    }
  }
}

}

int main() {
    // allocations
    bElem *c = randomArray({3});
    bElem *c_dev;
    copyToDevice({3}, c_dev, c);

    auto phi_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *phi_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, phi_dev, phi_arr);

    auto phi_new_arr = zeroArray({STRIDE, STRIDE, STRIDE});
    bElem *phi_new_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, phi_new_dev, phi_new_arr);

    auto alpha_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *alpha_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, alpha_dev, alpha_arr);

    auto beta_i_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *beta_i_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, beta_i_dev, beta_i_arr);

    auto beta_j_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *beta_j_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, beta_j_dev, beta_j_arr);

    auto beta_k_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *beta_k_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, beta_k_dev, beta_k_arr);

    auto rhs_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *rhs_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, rhs_dev, rhs_arr);

    auto lambda_arr = randomArray({STRIDE, STRIDE, STRIDE});
    bElem *lambda_dev;
    copyToDevice({STRIDE, STRIDE, STRIDE}, lambda_dev, lambda_arr);

    // CPU
    {

        for(int k=GZ;k<STRIDE-GZ;k++){
            for(int j=GZ;j<STRIDE-GZ;j++){
                for(int i=GZ;i<STRIDE-GZ;i++){
                    int ijk = i + j*STRIDE + k*STRIDE*STRIDE;

                    { // color signifies red or black case
                      double helmholtz = alpha_arr[ijk]*phi_arr[ijk]
                                       - H2INV*(
                                           beta_i_arr[ijk+1     ]*( phi_arr[ijk+1     ]-phi_arr[ijk       ] )
                                         - beta_i_arr[ijk       ]*( phi_arr[ijk       ]-phi_arr[ijk-1     ] )
                                         + beta_j_arr[ijk+STRIDE]*( phi_arr[ijk+STRIDE]-phi_arr[ijk       ] )
                                         - beta_j_arr[ijk       ]*( phi_arr[ijk       ]-phi_arr[ijk-STRIDE] )
                                         + beta_k_arr[ijk+(STRIDE*STRIDE) ]*( phi_arr[ijk+(STRIDE*STRIDE) ]-phi_arr[ijk       ] )
                                         - beta_k_arr[ijk       ]*( phi_arr[ijk       ]-phi_arr[ijk-(STRIDE*STRIDE) ] )
                                            );

                      phi_new_arr[ijk] = phi_arr[ijk] - lambda_arr[ijk]*(helmholtz-rhs_arr[ijk]);
                    }
                }
            }
        }
    }

    // CUDA
    {
        auto compute = [&]() -> void {
            long numOfThreads = STRIDE;
            // long numOfBlocks = ceil(STRIDE/numOfThreads);
            long numOfBlocks = ceil(STRIDE*STRIDE*STRIDE/(numOfThreads*STRIDE*STRIDE)); // Unroll on i

            dim3 dimBlock(numOfThreads);
            dim3 dimGrid(numOfBlocks);
            
            GSRBKernel<<<dimGrid, dimBlock>>> (phi_dev, phi_new_dev, rhs_dev, alpha_dev, beta_i_dev, 
                                         beta_j_dev , beta_k_dev , lambda_dev, 0);
        };
        
        compute();
        auto phi_new_cuda = zeroArray({STRIDE, STRIDE, STRIDE});
        copyFromDevice({STRIDE, STRIDE, STRIDE}, phi_new_cuda, phi_new_dev);

        if (!compareArray({STRIDE, STRIDE, STRIDE}, (bElem *)phi_new_arr, (bElem *)phi_new_cuda))
            std::cout << "arr don't match" << std::endl;
    }

    cudaDeviceSynchronize();

    cudaFree(phi_dev);
    cudaFree(phi_new_dev);
    cudaFree(alpha_dev);
    cudaFree(beta_i_dev);
    cudaFree(beta_j_dev);
    cudaFree(beta_k_dev);
    cudaFree(rhs_dev);
    cudaFree(lambda_dev);
    
    {
        unsigned *grid_ptr;
        unsigned bSize = TILEK * TILEJ * TILEI;

        auto bInfo = init_grid<3>(grid_ptr, {STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI});

        unsigned *grid_dev;
        copyToDevice({STRIDE/TILEK, STRIDE/TILEJ, STRIDE/TILEI}, grid_dev, grid_ptr);

        auto bStorage = BrickStorage::allocate(bInfo.nbricks, bSize * 8);

        Brick3D phi_bri(&bInfo, &bStorage, 0);
        Brick3D alpha_bri(&bInfo, &bStorage, bSize);
        Brick3D beta_i_bri(&bInfo, &bStorage, bSize * 2);
        Brick3D beta_j_bri(&bInfo, &bStorage, bSize * 3);
        Brick3D beta_k_bri(&bInfo, &bStorage, bSize * 4);
        Brick3D phi_new_bri(&bInfo, &bStorage, bSize * 5);
        Brick3D lambda_bri(&bInfo, &bStorage, bSize * 6);
        Brick3D rhs_bri(&bInfo, &bStorage, bSize * 7);

        BrickInfo<3> *bInfo_dev;
        auto _bInfo_dev = movBrickInfo(bInfo, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickInfo<3>);
            cudaMalloc(&bInfo_dev, size);
            cudaMemcpy(bInfo_dev, &_bInfo_dev, size, cudaMemcpyHostToDevice);
        }

        copyBrick<3>({STRIDE, STRIDE, STRIDE}, phi_arr, grid_ptr, phi_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, alpha_arr, grid_ptr, alpha_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_i_arr, grid_ptr, beta_i_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_j_arr, grid_ptr, beta_j_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, beta_k_arr, grid_ptr, beta_k_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, phi_new_arr, grid_ptr, phi_new_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, lambda_arr, grid_ptr, lambda_bri);
        copyBrick<3>({STRIDE, STRIDE, STRIDE}, rhs_arr, grid_ptr, rhs_bri);

        BrickStorage *bStorage_dev;
        BrickStorage _bStorage_dev = movBrickStorage(bStorage, cudaMemcpyHostToDevice);
        {
            unsigned size = sizeof(BrickStorage);
            cudaMalloc(&bStorage_dev, size);
            cudaMemcpy(bStorage_dev, &_bStorage_dev, size, cudaMemcpyHostToDevice);
        }

        auto compute = [&]() -> void {
            Brick3D phi(bInfo_dev, &_bStorage_dev, 0);
            Brick3D alpha(bInfo_dev, &_bStorage_dev, bSize);
            Brick3D beta_i(bInfo_dev, &_bStorage_dev, bSize * 2);
            Brick3D beta_j(bInfo_dev, &_bStorage_dev, bSize * 3);
            Brick3D beta_k(bInfo_dev, &_bStorage_dev, bSize * 4);
            Brick3D phi_new(bInfo_dev, &_bStorage_dev, bSize * 5);
            Brick3D lambda(bInfo_dev, &bStorage, bSize * 6);
            Brick3D rhs(bInfo_dev, &bStorage, bSize * 7);
           
            phi.bStorage = bStorage_dev;
            alpha.bStorage = bStorage_dev;
            beta_i.bStorage = bStorage_dev;
            beta_j.bStorage = bStorage_dev;
            beta_k.bStorage = bStorage_dev;
            phi_new.bStorage = bStorage_dev;
            lambda.bStorage = bStorage_dev;
            rhs.bStorage = bStorage_dev;

            auto grid = (unsigned (*)[STRIDE/TILEJ][STRIDE/TILEI]) grid_dev;
            dim3 block(N/TILEI, N/TILEJ, N/TILEK), thread(32);
            
            brick_kernel<<< block, thread >>>(grid, phi, alpha, beta_i, beta_j, beta_k, phi_new, lambda, rhs);
        };

        compute();

        cudaDeviceSynchronize();

        cudaMemcpy(bStorage.dat, _bStorage_dev.dat, bStorage.chunks * bStorage.step * sizeof(bElem), cudaMemcpyDeviceToHost);

        if (!compareBrick<3>({STRIDE, STRIDE, STRIDE}, phi_new_arr, grid_ptr, phi_new_bri))
            std::cout << "brick don't match" << std::endl;
    }
    return 0;
}

