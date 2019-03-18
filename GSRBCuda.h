#ifndef GSRBCuda_h
#define GSRBCuda_h

#include <stdio.h>

void GSRBCuda(double* phi, double* phi_new, double* rhs, double* alpha, double* beta_i,
              double* beta_j, double* beta_k, double* lambda);

#endif /* GSRBCuda_h */
