#include <iostream>
#include "brick.h"
#include "brick-mpi.h"
#include "omp.h"
#include "stencils/example.h"

#define ARGS ptr_next, ptr_prev, ptr_vel, blist, &coeff[0]
#define _EXAMPLE iso3dfd

typedef int (*casefunc)(brickd &, brickd &, brickd &, brick_list &, float *);

#define TOT 1e11
#define UNIT "GGPs"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define _COMPOSE(x, y) x ## _ ## y
#define _PASTE(x, y) _COMPOSE(x,y)
#define CASE(x) _PASTE(x, _EXAMPLE)
#define _NEXAMPLE(x, y) {#x, y}
#define EXAMPLE(x) _NEXAMPLE(x, CASE(x))

int main(int argc, char **argv) {
  // Usage: <this program> n
  //  n - elements on each dimension
  MPI_Init(&argc, &argv);
  long n = std::stoi(argv[1]);
  long RZ, RY, RX;
  long BZ, BY, BX;
  sscanf(argv[2], "%ld,%ld,%ld", &RZ, &RY, &RX);
  sscanf(argv[3], "%ld,%ld,%ld", &BZ, &BY, &BX);
  int mpi_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  if (mpi_rank == 0) {
    if (n % BDIM_X != 0 || n % BDIM_Y != 0 || n & BDIM_Z != 0)
      std::cerr << "The size of the input dimension is not divisible by the size of the block" << std::endl;
    std::cout << "Benchmark running with " << n << " elements at each dimension for " TOSTRING(_EXAMPLE) << std::endl;
    std::cout << "RZ " << RZ << ";RY " << RY << ";RX " << RX << std::endl;
    std::cout << "BZ " << BZ << ";BY " << BY << ";BX " << BX << std::endl;
    std::cout << "Running with " << omp_get_num_procs() << " procs" << std::endl;
  }
  //  ---- Initialize data ----
  int mpi_size;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  int cb = 0;
  while (mpi_size > 1) {
    cb += 1;
    if (mpi_size & 1)
      throw std::runtime_error("Not a 2 cube");
    mpi_size >>= 1;
  }
  if (cb % 3 != 0)
    throw std::runtime_error("Not a 2 cube");
  cb = 1 << (cb / 3);
  brick_decomp bd({n * cb, n * cb, n * cb}, {RZ, RY, RX}, {BZ, BY, BX}, {BDIM_Z, BDIM_Y, BDIM_X}, MPI_COMM_WORLD, 4);
  // Create bricks according to the mapping
  brick_list blist = bd.get_list();
  brick_info *binfo = bd.get_info();
  brick bprev = bd.allocate(1);
  brick bnext = bd.allocate(1);
  brick bvel = bd.allocate(1);
  brickd ptr_next(bnext, 0);
  brickd ptr_prev(bprev, 0);
  brickd ptr_vel(bvel, 0);
  ptr_next.zero();
  ptr_prev.zero();
  ptr_vel.random();
  float coeff[] = {0.1, 0.2, 0.3, 0.4, 0.5};
  int comm;
  double tm;
  long totn = blist.len * binfo->bri_sz;
  long iter = (long) 50;
  omp_set_nested(1);
  // ---- Benchmarking ----
  comm = 1;
  tm = omp_get_wtime();
  for (long t = 0; t < iter; ++t) {
    generated_iso3dfd(ptr_next, ptr_prev, ptr_vel, blist, &coeff[0]);
    bd.exchange(bprev);
    bd.exchange(bnext);
    generated_iso3dfd(ptr_prev, ptr_next, ptr_vel, blist, &coeff[0]);
    bd.exchange(bprev);
    bd.exchange(bnext);
  }
  tm = (omp_get_wtime() - tm) / iter;
  if (mpi_rank == 0) {
    std::cout << tm << "s" << std::endl;
    std::cout << (blist.len * binfo->bri_sz) * comm * 1e-9 / tm << "\t" UNIT << std::endl;
  }
  MPI_Finalize();
  return 0;
}
