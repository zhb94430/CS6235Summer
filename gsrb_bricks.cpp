#include"brick.h"

#define alpha 0
#define beta_i  1
#define beta_j 2
#define beta_k 3
#define lambda 4
#define rhs  5

#define H2INV  0.8f

int naive_cns(brickd *phi, brickd *inbox, brickd *phi_new, brick_list &blist, 
              float *dx, int color) 
{
  for (long o = 0; o < blist.len; ++o) 
  {
    long b = blist.dat[o];
    long k, j, i;
    for (k = 0; k < phi_new[0].info->dim_z; ++k)
    {
      for (j = 0; j < phi_new[0].info->dim_y; ++j)
      {
        for (i = 0; i < phi_new[0].info->dim_x; ++i) 
        {
          // X dimension
          {
            float helmholtz = inbox[alpha].elem(b,k,j,i) * phi[0].elem(b,k,j,i) - H2INV 
                         * (  
                              inbox[beta_i].elem(b,k,  j,  i+1) * (phi[0].elem(b,k,  j,  i+1) - phi[0].elem(b,k,  j,  i  ))
                            - inbox[beta_i].elem(b,k,  j,  i  ) * (phi[0].elem(b,k,  j,  i  ) - phi[0].elem(b,k,  j,  i-1)) 
                            + inbox[beta_j].elem(b,k,  j+1,i  ) * (phi[0].elem(b,k,  j+1,i  ) - phi[0].elem(b,k,  j,  i  ))
                            - inbox[beta_j].elem(b,k,  j,  i  ) * (phi[0].elem(b,k,  j,  i  ) - phi[0].elem(b,k,  j-1,i  ))
                            + inbox[beta_k].elem(b,k+1,j,  i  ) * (phi[0].elem(b,k+1,j,  i  ) - phi[0].elem(b,k,  j,  i  ))
                            - inbox[beta_k].elem(b,k,  j,  i  ) * (phi[0].elem(b,k,  j,  i  ) - phi[0].elem(b,k-1,j,  i  ))
                           );

            phi_new[0].elem(b,k,j,i) = phi[0].elem(b,k,j,i) - inbox[lambda].elem(b,k,j,i) * (helmholtz-inbox[rhs].elem(b,k,j,i));
          }
        }
      }
    }
  }


  return 1;
}