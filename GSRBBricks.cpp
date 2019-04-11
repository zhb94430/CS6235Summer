#include "GSRBBricks.h"

int GSRBBricksCode(brickd& phi, brickd& phi_new, brickd& rhs, brickd& alpha,
                   brickd& beta_i, brickd& beta_j, brickd& beta_k, brickd& lambda,
                   brick_list& blist, int* color)
{
    for (long o = 0; o < blist.len; ++o) 
    {
      long b = blist.dat[o];
      long i, j, k;
      for (k = 1; k < phi.info->dim_z-1; ++k)
      {
        for (j = 1; j < phi.info->dim_y-1; ++j)
        {
          for (i = 1; i < phi.info->dim_x-1; ++i) 
          {
            
            int ijk = i + j*pencil + k*plane;

            if ((i+j+k+color[0]) % 2 == 0)
            {
              float helmholtz = alpha.elem(b,k,j,i) * phi.elem(b,k,j,i) - H2INV 
                           * (  
                                beta_i.elem(b,k,  j,  i+1) * (phi.elem(b,k,  j,  i+1) - phi.elem(b,k,  j,  i  ))
                              - beta_i.elem(b,k,  j,  i  ) * (phi.elem(b,k,  j,  i  ) - phi.elem(b,k,  j,  i-1)) 
                              + beta_j.elem(b,k,  j+1,i  ) * (phi.elem(b,k,  j+1,i  ) - phi.elem(b,k,  j,  i  ))
                              - beta_j.elem(b,k,  j,  i  ) * (phi.elem(b,k,  j,  i  ) - phi.elem(b,k,  j-1,i  ))
                              + beta_k.elem(b,k+1,j,  i  ) * (phi.elem(b,k+1,j,  i  ) - phi.elem(b,k,  j,  i  ))
                              - beta_k.elem(b,k,  j,  i  ) * (phi.elem(b,k,  j,  i  ) - phi.elem(b,k-1,j,  i  ))
                             );

              phi_new.elem(b,k,j,i) = phi.elem(b,k,j,i) - lambda.elem(b,k,j,i) * (helmholtz-rhs.elem(b,k,j,i));
            }
          }
        }
      }
    }
    return 1;
}

int GSRBGenerated(struct ::brickd &phi, struct ::brickd &phi_new, struct ::brickd &rhs, struct ::brickd &alpha, struct ::brickd &beta_i, struct ::brickd &beta_j, struct ::brickd &beta_k, struct ::brickd &lambda, struct ::brick_list &blist, int *color) {
  for (long o = 0; o < blist.len; ++o) {
    long b = blist.dat[o];
    long i;
    long j;
    long k;
    {
      brick_info *binfo = phi_new.info;
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
      bElem buf0[2];
      bElem buf1[2];
      bElem buf2[2];
      bElem buf3[2];
      bElem buf4[2];
      bElem buf5[2];
      bElem buf6[2];
      bElem buf7[2];
      bElem buf8[2];
      bElem buf9[2];
      {
        for (long iit = 0; iit < 2; ++iit) 
          buf0[iit] = 0;
        for (long iit = 0; iit < 2; ++iit) 
          buf1[iit] = 0;
        for (long iit = 0; iit < 2; ++iit) 
          buf3[iit] = 0;
        for (long iit = 0; iit < 2; ++iit) 
          buf4[iit] = 0;
        float phi_1_0_0_l;
        float phi_1_0_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 2) {
              long rel = irel2;
              {
                // Alignment 2, 4, 4
                {
                  float phi_1_0_0;
                  {
                    {
                      phi_1_0_0_l = phi.dat[b12 * phi.step + 0 + rel * 32 + lid];
                    }
                    {
                      phi_1_0_0_r = phi.dat[b13 * phi.step + 0 + rel * 32 + lid];
                    }
                    cu_shl(phi_1_0_0, phi_1_0_0_l, phi_1_0_0_r, 1, 4, lid & 3);
                  }
                  {
                    buf1[rel + 0] -= phi_1_0_0;
                  }
                }
                // Alignment 3, 4, 4
                {
                  float phi_1_0_0;
                  {
                    phi_1_0_0_l = phi_1_0_0_r;
                    phi_1_0_0 = phi_1_0_0_l;
                  }
                  {
                    buf0[rel + 0] -= phi_1_0_0;
                    buf1[rel + 0] -= phi_1_0_0;
                  }
                }
                // Alignment 4, 4, 4
                {
                  float phi_1_0_0;
                  {
                    {
                      phi_1_0_0_r = phi.dat[b14 * phi.step + 0 + rel * 32 + lid];
                    }
                    cu_shl(phi_1_0_0, phi_1_0_0_l, phi_1_0_0_r, 3, 4, lid & 3);
                  }
                  {
                    buf0[rel + 0] -= phi_1_0_0;
                  }
                }
              }
              irel2 += 1;
            }
          }
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 2) {
              long rel = irel2;
              {
                // Alignment 3, 3, 4
                {
                  float phi_1_0_0;
                  {
                    {
                      float tbelow;
                      tbelow = phi.dat[b10 * phi.step + 0 + rel * 32 + lid];
                      float tabove;
                      tabove = phi.dat[b13 * phi.step + 0 + rel * 32 + lid];
                      cu_shl(phi_1_0_0_l, tbelow, tabove, 4, 16, lid & 15);
                    }
                    phi_1_0_0 = phi_1_0_0_l;
                  }
                  {
                    buf4[rel + 0] -= phi_1_0_0;
                  }
                }
                // Alignment 3, 4, 4
                {
                  float phi_1_0_0;
                  {
                    {
                      phi_1_0_0_l = phi.dat[b13 * phi.step + 0 + rel * 32 + lid];
                    }
                    phi_1_0_0 = phi_1_0_0_l;
                  }
                  {
                    buf3[rel + 0] -= phi_1_0_0;
                    buf4[rel + 0] -= phi_1_0_0;
                  }
                }
                // Alignment 3, 5, 4
                {
                  float phi_1_0_0;
                  {
                    {
                      float tbelow;
                      tbelow = phi.dat[b13 * phi.step + 0 + rel * 32 + lid];
                      float tabove;
                      tabove = phi.dat[b16 * phi.step + 0 + rel * 32 + lid];
                      cu_shl(phi_1_0_0_l, tbelow, tabove, 12, 16, lid & 15);
                    }
                    phi_1_0_0 = phi_1_0_0_l;
                  }
                  {
                    buf3[rel + 0] -= phi_1_0_0;
                  }
                }
              }
              irel2 += 1;
            }
          }
        }
      }
      {
        for (long iit = 0; iit < 2; ++iit) 
          buf2[iit] = 0;
        for (long iit = 0; iit < 2; ++iit) 
          buf6[iit] = 0;
        for (long iit = 0; iit < 2; ++iit) 
          buf7[iit] = 0;
        float beta_i_1_0_0_l;
        float beta_i_1_0_0_r;
        float phi_0_0_1_l;
        float phi_0_0_1_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 2) {
              long rel = irel2;
              {
                // Alignment 3, 4, 4
                {
                  float beta_i_1_0_0;
                  {
                    {
                      beta_i_1_0_0_l = beta_i.dat[b13 * beta_i.step + 0 + rel * 32 + lid];
                    }
                    beta_i_1_0_0 = beta_i_1_0_0_l;
                  }
                  {
                    buf2[rel + 0] -= beta_i_1_0_0 * buf1[0 + rel];
                  }
                }
                // Alignment 4, 4, 4
                {
                  float beta_i_1_0_0;
                  {
                    {
                      beta_i_1_0_0_r = beta_i.dat[b14 * beta_i.step + 0 + rel * 32 + lid];
                    }
                    cu_shl(beta_i_1_0_0, beta_i_1_0_0_l, beta_i_1_0_0_r, 3, 4, lid & 3);
                  }
                  {
                    buf2[rel + 0] -= beta_i_1_0_0 * buf0[0 + rel];
                  }
                }
              }
              irel2 += 1;
            }
          }
          {
            {
              // Alignment 4, 4, 2
              {
                float phi_0_0_1;
                {
                  {
                    {
                      float tfront;
                      tfront = phi.dat[b4 * phi.step + 32 + lid];
                      float tback;
                      tback = phi.dat[b13 * phi.step + 0 + lid];
                      cu_shl(phi_0_0_1_l, tfront, tback, 16, 32, lid);
                    }
                  }
                  phi_0_0_1 = phi_0_0_1_l;
                }
                {
                  buf7[0] -= phi_0_0_1;
                }
              }
              // Alignment 4, 4, 3
              {
                float phi_0_0_1;
                {
                  {
                    phi_0_0_1_l = phi.dat[b13 * phi.step + 0 + lid];
                  }
                  phi_0_0_1 = phi_0_0_1_l;
                }
                {
                  buf6[0] -= phi_0_0_1;
                  buf7[0] -= phi_0_0_1;
                }
              }
              // Alignment 4, 4, 4
              {
                float phi_0_0_1;
                {
                  {
                    {
                      float tfront;
                      tfront = phi.dat[b13 * phi.step + 0 + lid];
                      float tback;
                      tback = phi.dat[b13 * phi.step + 32 + lid];
                      cu_shl(phi_0_0_1_l, tfront, tback, 16, 32, lid);
                    }
                  }
                  phi_0_0_1 = phi_0_0_1_l;
                }
                {
                  buf6[0] -= phi_0_0_1;
                  buf7[1] -= phi_0_0_1;
                }
              }
              // Alignment 4, 4, 5
              {
                float phi_0_0_1;
                {
                  {
                    phi_0_0_1_l = phi.dat[b13 * phi.step + 32 + lid];
                  }
                  phi_0_0_1 = phi_0_0_1_l;
                }
                {
                  buf6[1] -= phi_0_0_1;
                  buf7[1] -= phi_0_0_1;
                }
              }
              // Alignment 4, 4, 6
              {
                float phi_0_0_1;
                {
                  {
                    {
                      float tfront;
                      tfront = phi.dat[b13 * phi.step + 32 + lid];
                      float tback;
                      tback = phi.dat[b22 * phi.step + 0 + lid];
                      cu_shl(phi_0_0_1_l, tfront, tback, 16, 32, lid);
                    }
                  }
                  phi_0_0_1 = phi_0_0_1_l;
                }
                {
                  buf6[1] -= phi_0_0_1;
                }
              }
            }
          }
        }
      }
      {
        for (long iit = 0; iit < 2; ++iit) 
          buf5[iit] = 0;
        float beta_j_0_1_0_l;
        float beta_j_0_1_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 2) {
              long rel = irel2;
              {
                // Alignment 4, 3, 4
                {
                  float beta_j_0_1_0;
                  {
                    {
                      beta_j_0_1_0_l = beta_j.dat[b13 * beta_j.step + 0 + rel * 32 + lid];
                    }
                    beta_j_0_1_0 = beta_j_0_1_0_l;
                  }
                  {
                    buf5[rel + 0] -= beta_j_0_1_0 * buf4[0 + rel];
                  }
                }
                // Alignment 4, 4, 4
                {
                  float beta_j_0_1_0;
                  {
                    {
                      float tbelow;
                      tbelow = beta_j.dat[b13 * beta_j.step + 0 + rel * 32 + lid];
                      float tabove;
                      tabove = beta_j.dat[b16 * beta_j.step + 0 + rel * 32 + lid];
                      cu_shl(beta_j_0_1_0_l, tbelow, tabove, 12, 16, lid & 15);
                    }
                    beta_j_0_1_0 = beta_j_0_1_0_l;
                  }
                  {
                    buf5[rel + 0] -= buf2[0 + rel] + beta_j_0_1_0 * buf3[0 + rel];
                  }
                }
              }
              irel2 += 1;
            }
          }
        }
      }
      {
        for (long iit = 0; iit < 2; ++iit) 
          buf8[iit] = 0;
        float beta_k_0_0_1_l;
        float beta_k_0_0_1_r;
        {
          {
            {
              // Alignment 4, 4, 3
              {
                float beta_k_0_0_1;
                {
                  {
                    beta_k_0_0_1_l = beta_k.dat[b13 * beta_k.step + 0 + lid];
                  }
                  beta_k_0_0_1 = beta_k_0_0_1_l;
                }
                {
                  buf8[0] -= beta_k_0_0_1 * buf7[0];
                }
              }
              // Alignment 4, 4, 4
              {
                float beta_k_0_0_1;
                {
                  {
                    {
                      float tfront;
                      tfront = beta_k.dat[b13 * beta_k.step + 0 + lid];
                      float tback;
                      tback = beta_k.dat[b13 * beta_k.step + 32 + lid];
                      cu_shl(beta_k_0_0_1_l, tfront, tback, 16, 32, lid);
                    }
                  }
                  beta_k_0_0_1 = beta_k_0_0_1_l;
                }
                {
                  buf8[0] -= buf5[0] + beta_k_0_0_1 * buf6[0];
                }
              }
              // Alignment 4, 4, 5
              {
                float beta_k_0_0_1;
                {
                  {
                    beta_k_0_0_1_l = beta_k.dat[b13 * beta_k.step + 32 + lid];
                  }
                  beta_k_0_0_1 = beta_k_0_0_1_l;
                }
                {
                  buf8[1] -= beta_k_0_0_1 * buf7[1];
                }
              }
              // Alignment 4, 4, 6
              {
                float beta_k_0_0_1;
                {
                  {
                    {
                      float tfront;
                      tfront = beta_k.dat[b13 * beta_k.step + 32 + lid];
                      float tback;
                      tback = beta_k.dat[b22 * beta_k.step + 0 + lid];
                      cu_shl(beta_k_0_0_1_l, tfront, tback, 16, 32, lid);
                    }
                  }
                  beta_k_0_0_1 = beta_k_0_0_1_l;
                }
                {
                  buf8[1] -= buf5[1] + beta_k_0_0_1 * buf6[1];
                }
              }
            }
          }
        }
      }
      {
        for (long iit = 0; iit < 2; ++iit) 
          buf9[iit] = 0;
        float alpha_0_0_0_l;
        float alpha_0_0_0_r;
        float lambda_0_0_0_l;
        float lambda_0_0_0_r;
        float phi_0_0_0_l;
        float phi_0_0_0_r;
        float rhs_0_0_0_l;
        float rhs_0_0_0_r;
        {
          {
            long irel2 = 0;
            for (long zit = 0; zit < 4; zit += 2) {
              long rel = irel2;
              {
                // Alignment 4, 4, 4
                {
                  float phi_0_0_0;
                  {
                    {
                      phi_0_0_0_l = phi.dat[b13 * phi.step + 0 + rel * 32 + lid];
                    }
                    phi_0_0_0 = phi_0_0_0_l;
                  }
                  float lambda_0_0_0;
                  {
                    {
                      lambda_0_0_0_l = lambda.dat[b13 * lambda.step + 0 + rel * 32 + lid];
                    }
                    lambda_0_0_0 = lambda_0_0_0_l;
                  }
                  float alpha_0_0_0;
                  {
                    {
                      alpha_0_0_0_l = alpha.dat[b13 * alpha.step + 0 + rel * 32 + lid];
                    }
                    alpha_0_0_0 = alpha_0_0_0_l;
                  }
                  float rhs_0_0_0;
                  {
                    {
                      rhs_0_0_0_l = rhs.dat[b13 * rhs.step + 0 + rel * 32 + lid];
                    }
                    rhs_0_0_0 = rhs_0_0_0_l;
                  }
                  {
                    buf9[rel + 0] -= phi_0_0_0;
                    buf9[rel + 0] -= lambda_0_0_0 * (alpha_0_0_0 * phi_0_0_0 - 0.800000012f * buf8[0 + rel] - rhs_0_0_0);
                  }
                }
              }
              irel2 += 1;
            }
          }
        }
      }
      {
        bElem *stp = &phi_new.dat[phi_new.step * b];
        for (long sti = 0; sti < 2; ++sti) 
          stp[sti * 32 + lid] = buf9[sti];
      }
    }
  }
  return 1;
}

int GSRBBricks(double* phi, double* phi_new, double* rhs, double* alpha,
               double* beta_i, double* beta_j, double* beta_k, double* lambda);
{
    brick_info binfo(BDIM_Z, BDIM_Y, BDIM_X);
  // Create bricks according to the mapping
    brick_list blist = binfo.genList(n / BDIM_Z + 2, n / BDIM_Y + 2, n / BDIM_X + 2, RZ, RY, RX, BZ, BY, BX);

    // Need to convert double* to brickd*
    brickd bricks_phi    (&binfo);
    brickd bricks_phi_new(&binfo);
    brickd bricks_rhs    (&binfo);
    brickd bricks_alpha  (&binfo);
    brickd bricks_beta_i (&binfo);
    brickd bricks_beta_j (&binfo);
    brickd bricks_beta_k (&binfo);
    brickd bricks_lambda (&binfo);

    bricks_phi.dat = phi;
    bricks_phi_new.dat = phi_new;
    bricks_rhs.dat = rhs;
    bricks_alpha.dat = alpha;
    bricks_beta_i.dat = beta_i;
    bricks_beta_j.dat = beta_j;
    bricks_beta_k.dat = beta_k;
    bricks_lambda.dat = lambda;

    printf("GSRBBricks Starting..\n");
    auto t1 = std::chrono::high_resolution_clock::now();

    for (int timestep = 0; timestep < 4; timestep++)
    {
      GSRBGenerated(bricks_phi, bricks_phi_new, bricks_rhs, bricks_alpha, bricks_beta_i, bricks_beta_j, bricks_beta_k, bricks_lambda, blist, 0);
      GSRBGenerated(bricks_phi, bricks_phi_new, bricks_rhs, bricks_alpha, bricks_beta_i, bricks_beta_j, bricks_beta_k, bricks_lambda, blist, 1);  

      // Swap Phi and Phi_new 
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

    std::cout << "Brick Time is "
              << fp_ms.count()
              << " milliseconds\n";

    phi = bricks_phi.dat;
    phi_new = bricks_phi_new.dat;
    rhs = bricks_rhs.dat;
    alpha = bricks_alpha.dat;
    beta_i = bricks_beta_i.dat;
    beta_j = bricks_beta_j.dat;
    beta_k = bricks_beta_k.dat;
    lambda = bricks_lambda.dat;

    return 1;
}