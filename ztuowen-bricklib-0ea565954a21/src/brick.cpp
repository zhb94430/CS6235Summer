//
// Created by Tuowen Zhao on 5/17/17.
//

#include "brick.h"
#include "stdlib.h"
#include "brick_rect.h"
#include <random>
#include <omp.h>
#include <cstring>

using brick_dim::dim3;

brick_list brick_info::genList(long bz, long by, long bx, long rz, long ry, long rx, long tz, long ty, long tx) {
  brick_rect brect(dim3(bz, by, bx));
  // Creating tiled format
  for (long tk = 1 - rz; tk < bz; tk += rz)
    for (long tj = 1 - ry; tj < by; tj += ry)
      for (long ti = 1 - rx; ti < bx; ti += rx)
        brect.allocate(dim3(std::max(tk, 0l), std::max(tj, 0l), std::max(ti, 0l)),
                       dim3(std::min(tk + rz, bz), std::min(tj + ry, by), std::min(ti + rx, bx)));
  brick_info brect_info = brect.get_brick_info();
  adj = brect_info.adj;
  bri_n = brect_info.bri_n;
  dev_ptr = nullptr;

  // Create the list of bricks for the calculation
  brick_list blist;
  std::vector<long> bvec;
  std::vector<long> tvec(1, 0);
  std::vector<long> rvec(1, 0);

  for (long rk = 1; rk < bz - 1; rk += rz)
    for (long rj = 1; rj < by - 1; rj += ry)
      for (long ri = 1; ri < bx - 1; ri += rx) {
        for (long bk = rk; bk < std::min(rk + rz, bz - 1); bk += tz)
          for (long bj = rj; bj < std::min(rj + ry, by - 1); bj += ty)
            for (long bi = ri; bi < std::min(ri + rx, bx - 1); bi += tx) {
              brect.push_rect(bvec, dim3(bk, bj, bi),
                              dim3(std::min(std::min(bk + tz, bz - 1), rk + rz),
                                   std::min(std::min(bj + ty, by - 1), rj + ry),
                                   std::min(std::min(bi + tx, bx - 1), ri + rx)));
              tvec.push_back(bvec.size());
            }
        rvec.push_back(tvec.size() - 1);
      }

  blist.len = bvec.size();
  blist.dat = (long *) malloc(sizeof(long) * bvec.size());
  memcpy(blist.dat, bvec.data(), sizeof(long) * bvec.size());
  blist.bdat = (long *) malloc(sizeof(long) * tvec.size());
  memcpy(blist.bdat, tvec.data(), sizeof(long) * tvec.size());
  blist.rlen = rvec.size() - 1;
  blist.rdat = (long *) malloc(sizeof(long) * rvec.size());
  memcpy(blist.rdat, rvec.data(), sizeof(long) * rvec.size());

  // OMP schedules
  // On knl 2 cores is one tile
  blist.lv1 = omp_get_num_procs() / 2;
  blist.lv2 = omp_get_num_procs() / blist.lv1;
  return blist;
}

brickd::brickd(brick_info *binfo) {
  info = binfo;
  step = info->bri_sz;
  dat = (float *) aligned_alloc(64, sizeof(float) * info->bri_n * info->bri_sz);
}

brickd::brickd(brick &b, long field) {
  assert(sizeof(float) == b.elem_sz);
  info = b.info;
  step = b.step;
  dat = &(((float *) b.dat)[field * b.bri_sz]);
}

void brickd::zero() {
  for (long i = 0; i < info->bri_n; ++i)
    for (long j = 0; j < info->bri_sz; ++j)
      dat[i * step + j] = 0;
}

void brickd::random() {
  std::random_device r;
  std::mt19937_64 mt(r());
  std::uniform_real_distribution<float> u(0, 1);
  for (long i = 0; i < info->bri_n; ++i)
    for (long j = 0; j < info->bri_sz; ++j)
      dat[i * step + j] = u(mt);
}

brick::brick(brick_info *binfo, long nfields, long size) {
  info = binfo;
  bri_sz = info->bri_sz;
  step = nfields * bri_sz; // TODO assuming aligned
  elem_sz = size;
  dat = aligned_alloc(64, (size_t) (info->bri_n * elem_sz * step));
}


