#ifndef GSRBBRICKS_H
#define GSRBBRICKS_H

#include <stdio.h>

#include "./bricklib/inc/brick.h"
#include "GSRBConstants.h"

#define BDIM_Z  4
#define BDIM_Y  4
#define BDIM_X  4

#define RZ 4
#define RY 4
#define RX 4

#define BZ 4
#define BY 4
#define BX 4

#define n pencil

int GSRBBricks(double* phi, double* phi_new, double* rhs, double* alpha,
               double* beta_i, double* beta_j, double* beta_k, double* lambda);

#endif