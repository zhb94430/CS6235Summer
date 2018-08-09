//
// Created by Tuowen Zhao on 12/26/17.
//

#ifndef BRICKLIB_BRICK_MPI_H
#define BRICKLIB_BRICK_MPI_H

#include "mpi.h"
#include "brick.h"
#include "brick_rect.h"


//! Handle brick allocation in a distributed environment, assuming rectangular domain
class brick_decomp {
private:
  brick_info binfo;
  brick_list blist;
  MPI_Comm comm;
  brick_dim::dim3 domain, region, thread;
  int dims[3], coo[3];
  long d, dx, dy, dz; //!< depth of ghost region
  brick_rect *rect;

  void make_edge(brick_rect &brect, brick_dim::dim3 p);

  void pack_exchange(brick &b, brick_dim::dim3 p0, brick_dim::dim3 p1, brick_dim::dim3 pghost, int dst, int src,
                     std::vector<void *> &bufs, std::vector<MPI_Request> &reqs, int tag);

public:
  /**
   * Create a decomposition overall
   *
   * * One sub-domain for each rank
   * * Assuming periodic boundary.
   */
  brick_decomp(brick_dim::dim3 domain, brick_dim::dim3 region, brick_dim::dim3 thread, brick_dim::dim3 bdim,
               MPI_Comm comm, long depth = 1);

  //! allocate one brick instance with n field
  brick allocate(long n) {
    return brick(&binfo, n, sizeof(float));
  }

  //! generate brick list of inner n - some functions
  brick_list get_list() {
    return blist;
  }

  brick_info *get_info() {
    return &binfo;
  }

  //! ghost zone exchange
  void exchange(brick &b);
};

#endif //BRICKLIB_BRICK_MPI_H
