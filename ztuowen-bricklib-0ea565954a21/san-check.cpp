#include <iostream>
#include "brick.h"
#include "omp.h"
#include "stencils/example.h"
#include <cmath>

int main(int argc, char **argv) {
  // Usage: <this program> n
  //  n - elements on each dimension
  long n = std::stoi(argv[1]);
  long RZ, RY, RX;
  long BZ, BY, BX;
  sscanf(argv[2], "%ld,%ld,%ld", &RZ, &RY, &RX);
  sscanf(argv[3], "%ld,%ld,%ld", &BZ, &BY, &BX);
  if (n % BDIM_X != 0 || n % BDIM_Y != 0 || n & BDIM_Z != 0)
    std::cerr << "The size of the input dimension is not divisible by the size of the block" << std::endl;
  std::cout << "Benchmark running with " << n << " elements at each dimension for stencil sanity check" << std::endl;
  std::cout << "RZ " << RZ << ";RY " << RY << ";RX " << RX << std::endl;
  std::cout << "BZ " << BZ << ";BY " << BY << ";BX " << BX << std::endl;
  std::cout << "Running with " << omp_get_num_procs() << " procs" << std::endl;
  //  ---- Initialize data ----
  // Brick info
  brick_info binfo(BDIM_Z, BDIM_Y, BDIM_X);
  brick_list blist = binfo.genList(n / BDIM_Z + 2, n / BDIM_Y + 2, n / BDIM_X + 2, RZ, RY, RX, BZ, BY, BX);
  double maxerror = 0;
  double avg = 0;
  // Create bricks according to the mapping
#ifdef _EX_cns
  brick qBricks(&binfo, 4, sizeof(float));
  brick consBricks(&binfo, 4, sizeof(float));
  brick fluxBricks(&binfo, 5, sizeof(float));
  brick fluxBricks_ref(&binfo, 5, sizeof(float));
  brickd q[6] = {{}, // Not used
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
  brickd flux_ref[5] = {{fluxBricks_ref, 0},
                        {fluxBricks_ref, 1},
                        {fluxBricks_ref, 2},
                        {fluxBricks_ref, 3},
                        {fluxBricks_ref, 4}};
  float args[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
  q[1].random();
  q[2].random();
  q[3].random();
  q[4].random();
  cons[1].random();
  cons[2].random();
  cons[3].random();
  cons[4].random();
  flux[0].zero();
  flux[1].zero();
  flux[2].zero();
  flux[3].zero();
  flux[4].zero();
  flux_ref[0].zero();
  flux_ref[1].zero();
  flux_ref[2].zero();
  flux_ref[3].zero();
  flux_ref[4].zero();
  // ---- Benchmarking ----
  naive_cns(cons, q, flux_ref, blist, &args[0]);
  naive_cns(cons, q, flux, blist, &args[0]);
  for (long k = 0; k < 5; ++k)
    for (long i = 0; i < flux[k].info->bri_n; ++i)
      for (long j = 0; j < flux[k].info->bri_sz; ++j) {
        double diff = std::abs(flux[k].dat[i * flux[k].step + j] - flux_ref[k].dat[i * flux[k].step + j]);
        if (maxerror < diff)
          maxerror = diff;
        avg += diff * diff;
      }
  avg = avg / (5 * binfo.bri_n * binfo.bri_sz);
#elif defined _EX_iso3dfd
  brickd ptr_next(&binfo);
  brickd ptr_next_ref(&binfo);
  brickd ptr_prev(&binfo);
  brickd ptr_vel(&binfo);
  ptr_prev.random();
  ptr_vel.random();
  ptr_next.zero();
  ptr_next_ref.zero();
  float coeff[] = {0.1, 0.2, 0.3, 0.4, 0.5};
  // ---- Benchmarking ----
  naive_iso3dfd(ptr_next_ref, ptr_prev, ptr_vel, blist, &coeff[0]);
  generated_iso3dfd(ptr_next, ptr_prev, ptr_vel, blist, &coeff[0]);
  for (long i = 0; i < ptr_next.info->bri_n; ++i)
    for (long j = 0; j < ptr_next.info->bri_sz; ++j) {
      double diff = std::abs(ptr_next.dat[i * ptr_next.step + j] - ptr_next_ref.dat[i * ptr_next_ref.step + j]);
      if (maxerror < diff)
        maxerror = diff;
      avg += diff * diff;
    }
  avg = avg / (5 * binfo.bri_n * binfo.bri_sz);
#else
  brickd inbox(&binfo);
  brickd outbox_ref(&binfo);
  brickd outbox_gen(&binfo);
  inbox.random();
  outbox_ref.zero();
  outbox_gen.zero();
  // ---- Benchmarking ----
  cppaccess_stencil(inbox, outbox_ref, blist);
  generated_stencil(inbox, outbox_gen, blist);
  for (long i = 0; i < binfo.bri_sz * binfo.bri_n; ++i) {
    double diff = std::abs(outbox_gen.dat[i] - outbox_ref.dat[i]);
    if (maxerror < diff)
      maxerror = diff;
    avg += diff * diff;
  }
  avg = avg / (binfo.bri_n * binfo.bri_sz);
#endif
  std::cout << "Max error: " << maxerror << std::endl;
  std::cout << "Energy: " << avg << std::endl;
  return 0;
}
