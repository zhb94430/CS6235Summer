#include <stdlib.h>

#define pencil 32
#define plane  1024
#define grid   32768

void GSRB(double *phi, double *phi_new, double *rhs, double *alpha,
	  double *beta_i, double *beta_j, double *beta_k, double *lambda, int color) {
 int i, j, k;
 double h2inv = 1.0/64;
 for(k=0;k<pencil;k++){
  for(j=0;j<pencil;j++){
    for(i=0;i<pencil;i++){
        int ijk = i + j*pencil + k*plane;
          if(i+j+k+color % 2 == 0){ // color signifies red or black case


        double helmholtz =  alpha[ijk]*phi[ijk]
	  -h2inv*(
		    beta_i[ijk+1     ]*( phi[ijk+1     ]-phi[ijk       ] )
		    -beta_i[ijk       ]*( phi[ijk       ]-phi[ijk-1     ] )
		    +beta_j[ijk+pencil]*( phi[ijk+pencil]-phi[ijk       ] )
		    -beta_j[ijk       ]*( phi[ijk       ]-phi[ijk-pencil] )
		    +beta_k[ijk+plane ]*( phi[ijk+plane ]-phi[ijk       ] )
		    -beta_k[ijk       ]*( phi[ijk       ]-phi[ijk-plane ] )
		    );
        phi_new[ijk] = phi[ijk] - lambda[ijk]*(helmholtz-rhs[ijk]);
	  }}}}
}


int main(int argc, char **argv) {
  int t;
  double *phi    = (double *)malloc(grid*sizeof(double));
  double *phi_new= (double *)malloc(grid*sizeof(double));
  double *rhs    = (double *)malloc(grid*sizeof(double));
  double *alpha  = (double *)malloc(grid*sizeof(double));
  double *beta_i = (double *)malloc(grid*sizeof(double));
  double *beta_j = (double *)malloc(grid*sizeof(double));
  double *beta_k = (double *)malloc(grid*sizeof(double));
  double *lambda = (double *)malloc(grid*sizeof(double));
  double *tmp;

  // TODO ADD RANDOM NUMBER INITIALIZATION OF INPUTS

// sequential loop that runs on host
for (t=0; t<4; t++) {
  (void) GSRB(phi,phi_new,rhs,alpha, beta_i,beta_j,beta_k,lambda,0);
  (void) GSRB(phi,phi_new,rhs,alpha, beta_i,beta_j,beta_k,lambda,1);
  tmp = phi_new;
  phi_new = phi;
  phi = tmp;
 }

// TODO: PERFORM VALIDATION ON PHI BETWEEN HOST AND GPU

}


