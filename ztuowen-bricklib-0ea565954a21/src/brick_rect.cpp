//
// Created by Tuowen Zhao on 12/29/17.
//

#include <cstring>
#include <stdexcept>
#include "brick_rect.h"

using brick_dim::dim3;

brick_rect::brick_rect(dim3 dims) : dims(dims), curr(0), valid(false), binfo(0, 0, 0) {
  size_t sz = sizeof(long) * dims.x * dims.y * dims.z;
  rect = (long *) malloc(sz);
  memset(rect, 0xff, sz);
}

void brick_rect::allocate(dim3 p0, dim3 p1, bool skip) {
  // Invalidate the cached brick_info
  valid = false;
  for (long z = p0.z; z < p1.z; ++z)
    for (long y = p0.y; y < p1.y; ++y)
      for (long x = p0.x; x < p1.x; ++x) {
        long idx = x + (y + z * dims.y) * dims.x;
        if (rect[idx] < 0)
          rect[idx] = curr++;
        else
          if (!skip)
            ++curr;
      }
}

void brick_rect::assign(brick_dim::dim3 p0, brick_dim::dim3 p1, long bidx) {
  valid = false;
  for (long z = p0.z; z < p1.z; ++z)
    for (long y = p0.y; y < p1.y; ++y)
      for (long x = p0.x; x < p1.x; ++x) {
        long idx = x + (y + z * dims.y) * dims.x;
        if (rect[idx] < 0)
          rect[idx] = bidx;
      }
}

brick_info brick_rect::get_brick_info() {
  if (valid)
    return binfo;
  // Sanity check
  for (long z = 0; z < dims.z; ++z)
    for (long y = 0; y < dims.y; ++y)
      for (long x = 0; x < dims.x; ++x)
        if (rect[x + (y + z * dims.y) * dims.x] < 0)
          throw std::runtime_error("brick_info is get with invalid address");
  // TODO construction
  binfo.bri_n = curr;
  // FIXME: downside of over provisioning: duplicate adjlist
  binfo.adj = (adjlist) malloc(sizeof(long) * 26 * curr);
  for (long z = 0; z < dims.z; ++z)
    for (long y = 0; y < dims.y; ++y)
      for (long x = 0; x < dims.x; ++x) {
        long pos = 0;
        long idx = x + (y + z * dims.y) * dims.x;
        for (long dz = -1; dz < 2; ++dz)
          for (long dy = -1; dy < 2; ++dy)
            for (long dx = -1; dx < 2; ++dx)
              if ((dz | dy | dx) != 0) {
                long nidx = (x + dx + dims.x) % dims.x +
                            ((y + dy + dims.y) % dims.y + (z + dz + dims.z) % dims.z * dims.y) * dims.x;
                binfo.adj[rect[idx]][pos++] = rect[nidx];
              }
      }
  valid = true;
  return binfo;
}

void brick_rect::push_rect(std::vector<long> &p, dim3 p0, dim3 p1) {
  for (long z = p0.z; z < p1.z; ++z)
    for (long y = p0.y; y < p1.y; ++y)
      for (long x = p0.x; x < p1.x; ++x) {
        long idx = x + (y + z * dims.y) * dims.x;
        if (rect[idx] < 0)
          throw std::runtime_error("brick_info is get with invalid address");
        else
          p.push_back(rect[idx]);
      }
}

long brick_rect::brick_index(dim3 p) {
  long idx = p.x + (p.y + p.z * dims.y) * dims.x;
  return rect[idx];
}
