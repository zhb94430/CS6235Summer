//
// Created by Tuowen Zhao on 5/17/17.
//

#ifndef BRICKLIB_BRICK_H
#define BRICKLIB_BRICK_H

#include <assert.h>
#include <stdio.h>

typedef long (*adjlist)[26];

typedef float vfloat256[256] __attribute__((aligned(64)));
typedef float vfloat64[64] __attribute__((aligned(64)));
typedef float vfloat16[16] __attribute__((aligned(64)));
typedef float vfloat8[8] __attribute__((aligned(32)));

struct brick_list;

//! Meta data for bricks
struct brick_info {
  long bri_n, bri_sz; // Number of bricks: x is the continuous dimension
  long dim_z, dim_y, dim_x; // The three sizes - x is the continuous dimension
  struct brick_info *dev_ptr;

  brick_list genList(long bz, long by, long bx, long rz, long ry, long rx, long tz, long ty, long tx);

  //! Adjacency list for each of the brick
  adjlist adj;

  //! Create empty meta data
  brick_info(long z, long y, long x) {
    dev_ptr = nullptr;
    set_brick(z, y, x);
  }

  void set_brick(long z, long y, long x) {
    dim_z = z;
    dim_y = y;
    dim_x = x;
    bri_sz = x * y * z;
  }

  //! The total number of elements
  inline long size() {
    return bri_sz * bri_n;
  }

  //! Return the offset(in the whole data space) of the (z,y,x) element in block no
  inline long access(long no, long z, long y, long x, long step) {
    if (x > -1 && x < dim_x && y > -1 && y < dim_y && z > -1 && z < dim_z) {
      no = no * step + x + (y + z * dim_y) * dim_x;
      return no;
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
    no = adj[no][idx];
    no = no * step + x + (y + z * dim_y) * dim_x;
    return no;
  }
};

//! Denoting a list of bricks by their relative position
struct brick_list {
  int lv1, lv2;
  long rlen, len;
  long *dat, *rdat, *bdat;
};

//! A chunk of memory that hold bricks with subfields
struct brick {
  void *dat;
  brick_info *info;
  long step, bri_n, elem_sz, bri_sz;

  brick(brick_info *binfo, long nfields, long size);
};

//! Bricked data consisting of floats
struct brickd {
  //! Meta data
  brick_info *info;
  long step;
  //! Actual data of the bricks
  float *dat;

  brickd() : info(NULL), step(0), dat(NULL) {}

  //! Creating empty bricked data from meta data
  brickd(brick_info *binfo);

  brickd(brick &b, long field);

  //! zeroing out
  void zero();

  //! Initialize to random
  void random();

  //! Access element in a brick
  inline float &elem(long no, long z, long y, long x) {
    no = info->access(no, z, y, x, step);
    return dat[no];
  }
};

#endif //BRICKLIB_BRICK_H
