#include <stdio.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "./bricklib/inc/brick.h"
#include "GSRBCuda.h"
#include "GSRBBricks.h"
#include "GSRBConstants.h"

// Buffers
double* phi    ;
double* phi_new;
double* rhs    ;
double* alpha  ;
double* beta_i ;
double* beta_j ;
double* beta_k ;
double* lambda ;

double* cpu_phi    ;
double* cpu_phi_new;
double* cpu_rhs    ;
double* cpu_alpha  ;
double* cpu_beta_i ;
double* cpu_beta_j ;
double* cpu_beta_k ;
double* cpu_lambda ;

double* cuda_phi    ;
double* cuda_phi_new;
double* cuda_rhs    ;
double* cuda_alpha  ;
double* cuda_beta_i ;
double* cuda_beta_j ;
double* cuda_beta_k ;
double* cuda_lambda ;

double* bricks_phi    ;
double* bricks_phi_new;
double* bricks_rhs    ;
double* bricks_alpha  ;
double* bricks_beta_i ;
double* bricks_beta_j ;
double* bricks_beta_k ;
double* bricks_lambda ;

// Prototypes
void GSRB(double *phi, double *phi_new, double *rhs, double *alpha,
         double *beta_i, double *beta_j, double *beta_k, double *lambda);

// Helper Functions
void InitBufferWithSize(int size);
void CompareResults();

int main(int argc, char** argv)
{
    InitBufferWithSize(grid);

    // ------------   CPU Benchmark  ---------------
    GSRB(cpu_phi, cpu_phi_new, cpu_rhs, cpu_alpha, cpu_beta_i, cpu_beta_j, cpu_beta_k, cpu_lambda);

    // ------------   CUDA Benchmark  ---------------
    GSRBCuda(cuda_phi, cuda_phi_new, cuda_rhs, cuda_alpha, cuda_beta_i, cuda_beta_j, cuda_beta_k, cuda_lambda);

    // ------------   BRICKS Benchmark  ---------------
    // // Start Timer
    // // TODO: How to time bricks?
    GSRBBricks(bricks_phi, bricks_phi_new, bricks_rhs, bricks_alpha, bricks_beta_i, bricks_beta_j, bricks_beta_k, bricks_lambda);
    // // End Timer

    // Compare
    CompareResults();
}

void GSRB(double *phi, double *phi_new, double *rhs, double *alpha,
          double *beta_i, double *beta_j, double *beta_k, double *lambda) 
{
    int i, j, k, color;
    double h2inv = 1.0/64;
    double* tmp;

    printf("GSRB Starting..\n");
    auto t1 = std::chrono::high_resolution_clock::now();

    for (int timestep = 0; timestep < 4; timestep++)
    {
      color = 0;

      for(k=1;k<pencil-1;k++){
        for(j=1;j<pencil-1;j++){
          for(i=1;i<pencil-1;i++){
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

      for(k=1;k<pencil-1;k++){
        for(j=1;j<pencil-1;j++){
          for(i=1;i<pencil-1;i++){
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

      tmp = phi_new;
      phi_new = phi;
      phi = tmp;
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "CPU Time is "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";
}

// Helper functions
void CompareResults()
{
    double diff_phi    ;
    double diff_phi_new;
    double diff_rhs    ;
    double diff_alpha  ;
    double diff_beta_i ;
    double diff_beta_j ;
    double diff_beta_k ;
    double diff_lambda ;

    double threshold = 0.000001;

    for (int i = 0; i < grid; i++)
    {
        diff_phi     = std::abs(cpu_phi[i]     - cuda_phi[i]);
        diff_phi_new = std::abs(cpu_phi_new[i] - cuda_phi_new[i]);
        diff_rhs     = std::abs(cpu_rhs[i]     - cuda_rhs[i]);
        diff_alpha   = std::abs(cpu_alpha[i]   - cuda_alpha[i]);
        diff_beta_i  = std::abs(cpu_beta_i[i]  - cuda_beta_i[i]);
        diff_beta_j  = std::abs(cpu_beta_j[i]  - cuda_beta_j[i]);
        diff_beta_k  = std::abs(cpu_beta_k[i]  - cuda_beta_k[i]);
        diff_lambda  = std::abs(cpu_lambda[i]  - cuda_lambda[i]);

        if ( diff_phi     > threshold ||
             diff_phi_new > threshold ||
             diff_rhs     > threshold ||
             diff_alpha   > threshold ||
             diff_beta_i  > threshold ||
             diff_beta_j  > threshold ||
             diff_beta_k  > threshold ||
             diff_lambda  > threshold )
        {
           printf("Results does not match at i = %d\n", i);
        }
    }
}

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

    cpu_phi     = (double*)malloc(actualSize);
    cpu_phi_new = (double*)malloc(actualSize);
    cpu_rhs     = (double*)malloc(actualSize);
    cpu_alpha   = (double*)malloc(actualSize);
    cpu_beta_i  = (double*)malloc(actualSize);
    cpu_beta_j  = (double*)malloc(actualSize);
    cpu_beta_k  = (double*)malloc(actualSize);
    cpu_lambda  = (double*)malloc(actualSize);

    cuda_phi     = (double*)malloc(actualSize);
    cuda_phi_new = (double*)malloc(actualSize);
    cuda_rhs     = (double*)malloc(actualSize);
    cuda_alpha   = (double*)malloc(actualSize);
    cuda_beta_i  = (double*)malloc(actualSize);
    cuda_beta_j  = (double*)malloc(actualSize);
    cuda_beta_k  = (double*)malloc(actualSize);
    cuda_lambda  = (double*)malloc(actualSize);

    bricks_phi     = (double*)malloc(actualSize);
    bricks_phi_new = (double*)malloc(actualSize);
    bricks_rhs     = (double*)malloc(actualSize);
    bricks_alpha   = (double*)malloc(actualSize);
    bricks_beta_i  = (double*)malloc(actualSize);
    bricks_beta_j  = (double*)malloc(actualSize);
    bricks_beta_k  = (double*)malloc(actualSize);
    bricks_lambda  = (double*)malloc(actualSize);

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

    std::memcpy(cpu_phi,     phi,     actualSize);
    std::memcpy(cpu_phi_new, phi_new, actualSize);
    std::memcpy(cpu_rhs,     rhs,     actualSize);
    std::memcpy(cpu_alpha,   alpha,   actualSize);
    std::memcpy(cpu_beta_i,  beta_i,  actualSize);
    std::memcpy(cpu_beta_j,  beta_j,  actualSize);
    std::memcpy(cpu_beta_k,  beta_k,  actualSize);
    std::memcpy(cpu_lambda,  lambda,  actualSize);

    std::memcpy(cuda_phi,     phi,     actualSize);
    std::memcpy(cuda_phi_new, phi_new, actualSize);
    std::memcpy(cuda_rhs,     rhs,     actualSize);
    std::memcpy(cuda_alpha,   alpha,   actualSize);
    std::memcpy(cuda_beta_i,  beta_i,  actualSize);
    std::memcpy(cuda_beta_j,  beta_j,  actualSize);
    std::memcpy(cuda_beta_k,  beta_k,  actualSize);
    std::memcpy(cuda_lambda,  lambda,  actualSize);

    std::memcpy(bricks_phi,     phi,     actualSize);
    std::memcpy(bricks_phi_new, phi_new, actualSize);
    std::memcpy(bricks_rhs,     rhs,     actualSize);
    std::memcpy(bricks_alpha,   alpha,   actualSize);
    std::memcpy(bricks_beta_i,  beta_i,  actualSize);
    std::memcpy(bricks_beta_j,  beta_j,  actualSize);
    std::memcpy(bricks_beta_k,  beta_k,  actualSize);
    std::memcpy(bricks_lambda,  lambda,  actualSize);
}




