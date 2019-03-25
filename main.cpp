#include <stdio.h>
#include <iostream>
#include <random>
#include <ctime>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "./bricklib/inc/brick.h"
#include "GSRBCuda.h"

#define pencil 32
#define plane  1024
#define grid   32768

// Buffers
double* phi    ;
double* phi_new;
double* rhs    ;
double* alpha  ;
double* beta_i ;
double* beta_j ;
double* beta_k ;
double* lambda ;

// Prototypes
void GSRB(double *phi, double *phi_new, double *rhs, double *alpha,
         double *beta_i, double *beta_j, double *beta_k, double *lambda);
int GSRBBricks(brickd *phi, brickd *inbox, brickd *phi_new, brick_list &blist, 
          float *dx, int color);
int GSRBGenerated(brickd *phi, brickd *inbox, brickd *phi_new, brick_list &blist, 
                  float *dx, int color);
void InitBufferWithSize(int size);

int main(int argc, char** argv)
{
    InitBufferWithSize(grid);

    // ------------   CPU Benchmark  ---------------
    GSRB(phi, phi_new, rhs, alpha, beta_i, beta_j, beta_k, lambda);

    // ------------   Store Result to compare later -------------
    

    // ------------   CUDA Benchmark  ---------------
    GSRBCuda(phi, phi_new, rhs, alpha, beta_i, beta_j, beta_k, lambda);


    // ------------   BRICKS Benchmark  ---------------
    // InitBufferWithSize(grid * sizeof(double));
    // // Start Timer
    // // TODO: How to time bricks?
    // GSRBBricks(phi, phi_new, rhs, alpha, beta_i, beta_j, beta_k, lambda, color);
    // // End Timer
}

void GSRB(double *phi, double *phi_new, double *rhs, double *alpha,
          double *beta_i, double *beta_j, double *beta_k, double *lambda) 
{
    int i, j, k, color;
    double h2inv = 1.0/64;

    printf("GSRB Bench Starting..\n");
    clock_t start = clock();

    color = 0;

    for(k=0;k<pencil;k++){
      for(j=0;j<pencil;j++){
        for(i=0;i<pencil;i++){
          int ijk = i + j*pencil + k*plane;
          if(i+j+k+color % 2 == 0){ // color signifies red or black case
            double helmholtz = alpha[ijk]*phi[ijk]
                             - h2inv*(
                                 beta_i[ijk+1     ]*( phi[ijk+1     ]-phi[ijk       ] )
                               - beta_i[ijk       ]*( phi[ijk       ]-phi[ijk-1     ] )
                               + beta_j[ijk+pencil]*( phi[ijk+pencil]-phi[ijk       ] )
                               - beta_j[ijk       ]*( phi[ijk       ]-phi[ijk-pencil] )
                               + beta_k[ijk+plane ]*( phi[ijk+plane ]-phi[ijk       ] )
                               - beta_k[ijk       ]*( phi[ijk       ]-phi[ijk-plane ] )
                                  );

            phi_new[ijk] = phi[ijk] - lambda[ijk]*(helmholtz-rhs[ijk]);
          }
        }
      }
    }

    color = 1;

    for(k=0;k<pencil;k++){
      for(j=0;j<pencil;j++){
        for(i=0;i<pencil;i++){
          int ijk = i + j*pencil + k*plane;
          if(i+j+k+color % 2 == 0){ // color signifies red or black case
            double helmholtz = alpha[ijk]*phi[ijk]
                             - h2inv*(
                                 beta_i[ijk+1     ]*( phi[ijk+1     ]-phi[ijk       ] )
                               - beta_i[ijk       ]*( phi[ijk       ]-phi[ijk-1     ] )
                               + beta_j[ijk+pencil]*( phi[ijk+pencil]-phi[ijk       ] )
                               - beta_j[ijk       ]*( phi[ijk       ]-phi[ijk-pencil] )
                               + beta_k[ijk+plane ]*( phi[ijk+plane ]-phi[ijk       ] )
                               - beta_k[ijk       ]*( phi[ijk       ]-phi[ijk-plane ] )
                                  );

            phi_new[ijk] = phi[ijk] - lambda[ijk]*(helmholtz-rhs[ijk]);
          }
        }
      }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU Time is %f\n", time_spent);
}

// Helper functions
void InitBufferWithSize(int size)
{
    int actualSize = size*sizeof(double);

    phi     = (double*)malloc(actualSize);
    phi_new = (double*)malloc(actualSize);
    rhs     = (double*)malloc(actualSize);
    alpha   = (double*)malloc(actualSize);
    beta_i  = (double*)malloc(actualSize);
    beta_j  = (double*)malloc(actualSize);
    beta_k  = (double*)malloc(actualSize);
    lambda  = (double*)malloc(actualSize);

    double range_from = 0.0;
    double range_to = 1.0;
    std::default_random_engine generator((unsigned) clock());
    std::uniform_real_distribution<double> distr(range_from, range_to); 

    for (int i = 0; i < size; ++i)
    {
        phi    [i] = distr(generator);
        phi_new[i] = distr(generator);
        rhs    [i] = distr(generator);
        alpha  [i] = distr(generator);
        beta_i [i] = distr(generator);
        beta_j [i] = distr(generator);
        beta_k [i] = distr(generator);
        lambda [i] = distr(generator);
    }
}




