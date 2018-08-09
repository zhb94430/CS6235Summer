#include <iostream>
#include "brick.h"
#include "omp.h"
#include "stencils/example.h"
#include <cuda_runtime.h>
#include "brick-cuda.h"

#ifdef _EX_stencil
#define ARGS inBox, outBox, blist
#define _EXAMPLE stencil

typedef int (*casefunc)(brickd &, brickd &, brick_list &);

#define TOT 1e11
#define UNIT "GFLOPs"
#elif defined _EX_stream
#define ARGS inBox, outBox, blist, 0.1
#define _EXAMPLE stream
typedef int (*casefunc)(brickd&, brickd&, brick_list&, float);
#define TOT 1e10
#define UNIT "GBs"
#elif defined _EX_iso3dfd
#define ARGS ptr_next, ptr_prev, ptr_vel, blist, &coeff[0]
#define ARGS_DEV ptr_next_dev, ptr_prev_dev, ptr_vel_dev, blist_dev
#define _EXAMPLE iso3dfd

typedef int (*casefunc)(brickd &, brickd &, brickd &, brick_list &);

#define TOT 1e10
#define UNIT "GGPs"
#else
#define ARGS &(cons[0]), &(q[0]), &(flux[0]), blist, &coeff[0]
#define ARGS_DEV cons_dev, q_dev, flux_dev, blist_dev
#define _EXAMPLE cns

typedef int (*casefunc)(brickd *, brickd *, brickd *, brick_list &);

#define TOT 1e10
#define UNIT "GFLOPs"
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define _COMPOSE(x, y) x ## _ ## y
#define _PASTE(x, y) _COMPOSE(x,y)
#define CASE(x) _PASTE(x, _EXAMPLE)
#define _NEXAMPLE(x, y) {#x, y}
#define EXAMPLE(x) _NEXAMPLE(x, CASE(x))

struct testcase {
  const char *name;
  casefunc fun;
};

#ifdef _EX_stencil
static testcase testcases[] = {
    EXAMPLE(generated),
    {NULL, NULL}
};
#elif defined _EX_stream
static testcase testcases[] = {
    EXAMPLE(naive),
    EXAMPLE(naive_def),
    EXAMPLE(cppaccess),
    EXAMPLE(noresolve),
    EXAMPLE(noresolve_specialized),
    EXAMPLE(unroll),
    {NULL, NULL}
};
#elif defined _EX_iso3dfd
static testcase testcases[] = {
    EXAMPLE(cuda),
    {NULL, NULL}
};
#else
static testcase testcases[] = {
    EXAMPLE(cuda),
    {NULL, NULL}
};
#endif

int main(int argc, char **argv) {
  // Usage: <this program> n
  //  n - elements on each dimension
  long n = 384;
  long RZ, RY, RX;
  long BZ, BY, BX;
  sscanf(argv[1], "%ld,%ld,%ld", &RZ, &RY, &RX);
  sscanf(argv[2], "%ld,%ld,%ld", &BZ, &BY, &BX);
  /*
  if (n % BDIM_X != 0 || n % BDIM_Y != 0 || n & BDIM_Z != 0)
    std::cerr << "The size of the input dimension is not divisible by the size of the block" << std::endl;
  std::cout << "Benchmark running with " << n << " elements at each dimension for " TOSTRING(_EXAMPLE) << std::endl;
  std::cout << "RZ " << RZ << ";RY " << RY << ";RX " << RX << std::endl;
  std::cout << "BZ " << BZ << ";BY " << BY << ";BX " << BX << std::endl;
  std::cout << "Running with " << omp_get_num_procs() << " procs" << std::endl;*/
  //  ---- Initialize data ----
  // Brick info
  brick_info binfo(BDIM_Z, BDIM_Y, BDIM_X);
  // Create bricks according to the mapping
  brick_list blist = binfo.genList(n / BDIM_Z + 2, n / BDIM_Y + 2, n / BDIM_X + 2, RZ, RY, RX, BZ, BY, BX);
  brick_list blist_dev = cuda_copy(blist);
#ifdef _EX_cns
  brick qBricks(&binfo, 4, sizeof(float));
  brick consBricks(&binfo, 4, sizeof(float));
  brick fluxBricks(&binfo, 5, sizeof(float));
  brick fluxBricks_ref(&binfo, 5, sizeof(float));
  brickd q[5] = {{}, // Not used
                 {qBricks, 0},
                 {qBricks, 1},
                 {qBricks, 2},
                 {qBricks, 3}};
  brickd cons[5] = {{}, // Not used
                    {consBricks, 0},
                    {consBricks, 1},
                    {consBricks, 2},
                    {consBricks, 3}};
  brickd flux[5] = {{fluxBricks, 0},
                    {fluxBricks, 1},
                    {fluxBricks, 2},
                    {fluxBricks, 3},
                    {fluxBricks, 4}};
  float coeff[] = {0.1, 0.2, 0.3, 0.4, 0.5};
  cuda_cns_setup(coeff);
  brick qB_dev = cuda_copy(qBricks);
  brick cB_dev = cuda_copy(consBricks);
  brick fB_dev = cuda_copy(fluxBricks);
  brickd q_set[5] = {{}, // Not used
                 {qB_dev, 0},
                 {qB_dev, 1},
                 {qB_dev, 2},
                 {qB_dev, 3}};
  brickd cons_set[5] = {{}, // Not used
                    {cB_dev, 0},
                    {cB_dev, 1},
                    {cB_dev, 2},
                    {cB_dev, 3}};
  brickd flux_set[5] = {{fB_dev, 0},
                    {fB_dev, 1},
                    {fB_dev, 2},
                    {fB_dev, 3},
                    {fB_dev, 4}};
  brickd *q_dev, *cons_dev, *flux_dev;
  cudaCheck(cudaMalloc(&q_dev, 5 * sizeof(brickd)));
  cudaCheck(cudaMemcpy(q_dev, q_set, 5 * sizeof(brickd), cudaMemcpyHostToDevice));
  cudaCheck(cudaMalloc(&cons_dev, 5 * sizeof(brickd)));
  cudaCheck(cudaMemcpy(cons_dev, cons_set, 5 * sizeof(brickd), cudaMemcpyHostToDevice));
  cudaCheck(cudaMalloc(&flux_dev, 5 * sizeof(brickd)));
  cudaCheck(cudaMemcpy(flux_dev, flux_set, 5 * sizeof(brickd), cudaMemcpyHostToDevice));
#elif defined _EX_iso3dfd
  brickd ptr_next(&binfo);
  brickd ptr_prev(&binfo);
  brickd ptr_vel(&binfo);
  ptr_next.random();
  ptr_prev.random();
  ptr_vel.random();
  float coeff[] = {0.1, 0.2, 0.3, 0.4, 0.5};
  cuda_iso3dfd_setup(coeff);
  brickd ptr_next_dev = cuda_copy(ptr_next);
  brickd ptr_prev_dev = cuda_copy(ptr_prev);
  brickd ptr_vel_dev = cuda_copy(ptr_vel);
#else
  brickd inBox(&binfo);
  brickd outBox(&binfo);
#endif
  int comm;
  double tm;
  long totn = blist.len * binfo.bri_sz;
  long iter = (long) (TOT / totn);
  omp_set_nested(1);
  // ---- Benchmarking ----
  testcase *ptr = &testcases[0];
  while (ptr->name != NULL) {
    //std::cout << ptr->name << std::endl;
    comm = (ptr->fun)(ARGS_DEV);
    cudaEvent_t start, stop;
    float elapsed;
    cudaCheck(cudaDeviceSynchronize());
    cudaCheck(cudaEventCreate(&start));
    cudaCheck(cudaEventCreate(&stop));
    cudaCheck(cudaEventRecord(start, 0));
    for (long t = 0; t < iter; ++t)
      (ptr->fun)(ARGS_DEV);
    cudaCheck(cudaEventRecord(stop));
    cudaCheck(cudaEventSynchronize(stop));
    cudaCheck(cudaEventElapsedTime(&elapsed, start, stop));
    tm = elapsed / 1000.0 / iter;
    //std::cout << tm << "s" << std::endl;
    //std::cout << (blist.len * binfo.bri_sz) * comm * 1e-9 / tm << "\t" UNIT << std::endl;
    std::cout << (blist.len * binfo.bri_sz) * comm * 1e-9 / tm << std::endl;
    ++ptr;
  }
  cuda_free(blist_dev);
  return 0;
}
