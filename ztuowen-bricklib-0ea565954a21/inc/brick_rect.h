//
// Created by Tuowen Zhao on 12/29/17.
//

#ifndef BRICKLIB_BRICK_RECT_H
#define BRICKLIB_BRICK_RECT_H

#include "brick.h"
#include <cstdlib>
#include <vector>

//! @file Rectangular brick region

namespace brick_dim {
    struct dim3 {
    long z, y, x;

    dim3(long z, long y, long x) : z(z), y(y), x(x) {}

    long &operator[](unsigned i) {
      switch (i) {
        case 0:
          return z;
        case 1:
          return y;
        default:
        case 2:
          return x;
      }
    }

    long operator[](unsigned i) const {
      switch (i) {
        case 0:
          return z;
        case 1:
          return y;
        default:
        case 2:
          return x;
      }
    }
  };
}

//! Denoting a rectangular region of bricks
class brick_rect {
private:
  brick_info binfo;
  //! The current memory index
  long curr;
  //! Rect_index to memory mapping
  long *rect;
  //! Dimensions of the rectangular region
  brick_dim::dim3 dims;
  bool valid;
public:
  /**
   * Rectangular bricked region constructor
   *
   * Each parameter denote the number of bricks in each direction
   */
  brick_rect(brick_dim::dim3 dims);

  /**
   * Allocating a sub(rectangular)-region
   *
   * It doesn't keep track of over provisioning
   *
   * @param skip Control allocation over existing bricks
   *   * False: steps over allocated members but increments memory index (virtual buffer)
   *   * True: skip over and not increment memory index
   */
  void allocate(brick_dim::dim3 p0, brick_dim::dim3 p1, bool skip = true);

  /**
   * Assign a specific block index to block in the region
   *
   * @param bidx brick index of the target block
   */
  void assign(brick_dim::dim3 p0, brick_dim::dim3 p1, long bidx);

  /**
   * Get the brick info for memory allocation
   *
   * Boundary is always periodic for compatibility
   */
  brick_info get_brick_info();

  /**
   * Push a list of brick indices to a long vector
   *
   * This is intended to generate the brick_list for omp scheduling
   */
  void push_rect(std::vector<long> &p, brick_dim::dim3 p0, brick_dim::dim3 p1);

  /**
   * Get the memory index for brick p
   */
  long brick_index(brick_dim::dim3 p);

  ~brick_rect() {
    free(rect);
  }
};

#endif //BRICKLIB_BRICK_RECT_H
