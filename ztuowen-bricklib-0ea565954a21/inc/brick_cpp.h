//
// Created by Tuowen Zhao on 5/18/17.
//

#ifndef BRICKLIB_BRICK_CPP_H
#define BRICKLIB_BRICK_CPP_H

#include "brick.h"

/**
 * @file Testing C++ template for bricks
 *
 * This file is obsolete, only intended for cross comparison in stencil example
 */

//! This is C++ accessor for bricks with sizes (possibly) defined at compile-time
template<long dim_z, long dim_y, long dim_x, typename T>
class cppaccess {
  //! Meta data for bricks
  brick_info *binfo;
  long step;
  //! The actual data array
  T *dat;
public:
  //! Creating the accessor from meta data and the actual data array
  cppaccess(brick_info *binfo, long step, T *dat) : binfo(binfo), dat(dat), step(step) {}

  //! Access the data
  inline T &operator()(long no, long z, long y, long x) {
    long bri_sz = dim_z * dim_y * dim_x;
    if (x > -1 && x < dim_x && y > -1 && y < dim_y && z > -1 && z < dim_z) {
      no = no * step + x + (y + z * dim_y) * dim_x;
      return dat[no];
    }
    x = x + dim_x;
    long x_idx = x / dim_x;
    x = x % dim_x;
    y = y + dim_y;
    long y_idx = y / dim_y;
    y = y % dim_y;
    z = z + dim_z;
    long z_idx = z / dim_z;
    z = z % dim_z;
    // Ensure that it doesn't reach neighbor's neighbor
    assert(x > -1 && x_idx < dim_x && y > -1 && y_idx < dim_y && z > -1 && z_idx < dim_z &&
           "Brick access trying to reach further than its neighbor");
    // Translate from the shift index to actual index
    long idx = x_idx + (y_idx + z_idx * 3) * 3;
    idx = idx > 12 ? idx - 1 : idx;
    no = binfo->adj[no][idx];
    no = no * step + x + (y + z * dim_y) * dim_x;
    return dat[no];
  }
};

#endif //BRICKLIB_BRICK_CPP_H
