//
// Created by Tuowen Zhao on 12/30/17.
//

#include "brick-mpi.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "omp.h"

using brick_dim::dim3;

#define shift(a, amount, b) ((a) + (amount) + (b)) % b

void brick_decomp::make_edge(brick_rect &brect, brick_dim::dim3 p) {
  brect.allocate(p, {p.z + dz, p.y + dy, p.x + dx});
  brect.allocate({p.z, p.y, p.x + dx}, {p.z + dz, p.y + dy, p.x + domain.x - dx});
  brect.allocate({p.z, p.y, p.x + domain.x - dx}, {p.z + dz, p.y + dy, p.x + domain.x});
}

brick_decomp::brick_decomp(dim3 dom, dim3 region, dim3 thread, dim3 bdim, MPI_Comm com, long depth)
    : binfo(bdim.z, bdim.y, bdim.x), d(depth), domain(dom), region(region), thread(thread) {
  // Calculate effective domain
  int mpi_size, mpi_rank;
  MPI_Comm_rank(com, &mpi_rank);
  MPI_Comm_size(com, &mpi_size);
  // Allocation
  dims[0] = dims[1] = dims[2] = 0;
  MPI_Dims_create(mpi_size, 3, dims);
  int prd[3] = {1, 1, 1};
  MPI_Cart_create(com, 3, dims, prd, 0, &comm);
  if (comm != MPI_COMM_NULL) {
    MPI_Cart_get(comm, 3, dims, prd, coo);
    long tmp = (domain.z + dims[0] - 1) / dims[0];
    domain.z = std::min(tmp, domain.z - tmp * coo[0]);
    tmp = (domain.y + dims[1] - 1) / dims[1];
    domain.y = std::min(tmp, domain.y - tmp * coo[1]);
    tmp = (domain.x + dims[2] - 1) / dims[2];
    domain.x = std::min(tmp, domain.x - tmp * coo[2]);
    domain.z /= bdim.z;
    domain.y /= bdim.y;
    domain.x /= bdim.x;
    // Generate brick_list
    // One ghost and one guard on each side
    // Inner: 1 + d <---> domain + 1 + d
    dz = d / bdim.z;
    dy = d / bdim.y;
    dx = d / bdim.x;
    rect = new brick_rect(dim3(domain.z + 2 + 2 * dz, domain.y + 2 + 2 * dy, domain.x + 2 + 2 * dx));
    brick_rect &brect = *rect;

    // Let's setup the guard
    brect.allocate({0, 0, 0}, {1, 1, 1});
    brect.assign({0, 0, 0}, {domain.z + 2 + 2 * dz, domain.y + 2 + 2 * dy, 1}, brect.brick_index({0, 0, 0}));
    brect.assign({0, 0, 0}, {1, domain.y + 2 + 2 * dy, domain.x + 2 + 2 * dx}, brect.brick_index({0, 0, 0}));
    brect.assign({0, 0, 0}, {domain.z + 2 + 2 * dz, 1, domain.x + 2 + 2 * dx}, brect.brick_index({0, 0, 0}));
    brect.assign({0, 0, domain.x + 1 + 2 * dx},
                 {domain.z + 2 + 2 * dz, domain.y + 2 + 2 * dy, domain.x + 2 + 2 * dx}, brect.brick_index({0, 0, 0}));
    brect.assign({domain.z + 1 + 2 * dz, 0, 0},
                 {domain.z + 2 + 2 * dz, domain.y + 2 + 2 * dy, domain.x + 2 + 2 * dx}, brect.brick_index({0, 0, 0}));
    brect.assign({0, domain.y + 1 + 2 * dy, 0},
                 {domain.z + 2 + 2 * dz, domain.y + 2 + 2 * dy, domain.x + 2 + 2 * dx}, brect.brick_index({0, 0, 0}));

    // Let's make a roll from the Z-Y cross section

    // Inner roll
    // Bottom
    make_edge(brect, {1 + dz, 1 + dy, 1 + dx});
    brect.allocate({1 + dz, 1 + dy * 2, 1 + dx}, {1 + dz * 2, 1 + domain.y, 1 + dx + domain.x});
    make_edge(brect, {1 + dz, 1 + domain.y, 1 + dx});
    // Right
    brect.allocate({1 + 2 * dz, 1 + domain.y, 1 + dx}, {1 + domain.z, 1 + dy + domain.y, 1 + dx + domain.x});
    make_edge(brect, {1 + domain.z, 1 + domain.y, 1 + dx});
    // Top
    brect.allocate({1 + domain.z, 1 + dy * 2, 1 + dx}, {1 + dz + domain.z, 1 + domain.y, 1 + dx + domain.x});
    make_edge(brect, {1 + domain.z, 1 + dy, 1 + dx});
    // Left
    brect.allocate({1 + 2 * dz, 1 + dy, 1 + dx}, {1 + domain.z, 1 + 2 * dy, 1 + dx + domain.x});

    // Outer roll - corresponds to inner roll
    // Top - Inner bottom
    make_edge(brect, {1 + dz + domain.z, 1 + dy, 1 + dx});
    brect.allocate({1 + dz + domain.z, 1 + dy * 2, 1 + dx}, {1 + dz * 2 + domain.z, 1 + domain.y, 1 + dx + domain.x});
    make_edge(brect, {1 + dz + domain.z, 1 + domain.y, 1 + dx});

    // Left
    // Inner bottom
    make_edge(brect, {1 + dz, 1, 1 + dx});

    // Inner right
    brect.allocate({1 + 2 * dz, 1, 1 + dx}, {1 + domain.z, 1 + dy, 1 + dx + domain.x});
    make_edge(brect, {1 + domain.z, 1, 1 + dx});

    // Bottom
    // Inner right
    make_edge(brect, {1, 1 + domain.y, 1 + dx});

    // Inner top
    brect.allocate({1, 1 + dy * 2, 1 + dx}, {1 + dz, 1 + domain.y, 1 + dx + domain.x});
    make_edge(brect, {1, 1 + dy, 1 + dx});

    // Right
    // Inner top
    make_edge(brect, {1 + domain.z, 1 + dy + domain.y, 1 + dx});

    // Inner left
    brect.allocate({1 + 2 * dz, 1 + dy + domain.y, 1 + dx}, {1 + domain.z, 1 + 2 * dy + domain.y, 1 + dx + domain.x});

    // Inner bottom
    make_edge(brect, {1 + dz, 1 + dy + domain.y, 1 + dx});

    // Roll edges
    // (0, 0) -> (1, 1)
    make_edge(brect, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx});
    // (0, 1) -> (1, 0)
    make_edge(brect, {1 + dz + domain.z, 1, 1 + dx});
    // (1, 1) -> (0, 0)
    make_edge(brect, {1, 1, 1 + dx});
    // (1, 0) -> (0, 1)
    make_edge(brect, {1, 1 + dy + domain.y, 1 + dx});

    // Make rest of reception area
    // 8 nodes
    // Node (0,0,0)
    brect.allocate({1, 1, 1}, {1 + dz, 1 + dy, 1 + dx});
    // Node (0,0,1)
    brect.allocate({1, 1, 1 + dx + domain.x}, {1 + dz, 1 + dy, 1 + 2 * dx + domain.x});
    // Node (0,1,0)
    brect.allocate({1, 1 + dy + domain.y, 1}, {1 + dz, 1 + 2 * dy + domain.y, 1 + dx});
    // Node (0,1,1)
    brect.allocate({1, 1 + dy + domain.y, 1 + dx + domain.x}, {1 + dz, 1 + 2 * dy + domain.y, 1 + 2 * dx + domain.x});
    // Node (1,0,0)
    brect.allocate({1 + dz + domain.z, 1, 1}, {1 + 2 * dz + domain.z, 1 + dy, 1 + dx});
    // Node (1,0,1)
    brect.allocate({1 + dz + domain.z, 1, 1 + dx + domain.x}, {1 + 2 * dz + domain.z, 1 + dy, 1 + 2 * dx + domain.x});
    // Node (1,1,0)
    brect.allocate({1 + dz + domain.z, 1 + dy + domain.y, 1}, {1 + 2 * dz + domain.z, 1 + 2 * dy + domain.y, 1 + dx});
    // Node (1,1,1)
    brect.allocate({1 + dz + domain.z, 1 + dy + domain.y, 1 + dx + domain.x},
                   {1 + 2 * dz + domain.z, 1 + 2 * dy + domain.y, 1 + 2 * dx + domain.x});
    // 8 edges
    // 0 - Bottom
    brect.allocate({1, 1 + dy, 1}, {1 + dz, 1 + dy + domain.y, 1 + dx});
    // 0 - Right
    brect.allocate({1 + dz, 1 + dy + domain.y, 1}, {1 + dz + domain.z, 1 + 2 * dy + domain.y, 1 + dx});
    // 0 - Top
    brect.allocate({1 + dz + domain.z, 1 + dy, 1}, {1 + 2 * dz + domain.z, 1 + dy + domain.y, 1 + dx});
    // 0 - Left
    brect.allocate({1 + dz, 1, 1}, {1 + dz + domain.z, 1 + dy, 1 + dx});

    // 1 - Bottom
    brect.allocate({1, 1 + dy, 1 + dx + domain.x}, {1 + dz, 1 + dy + domain.y, 1 + 2 * dx + domain.x});
    // 1 - Right
    brect.allocate({1 + dz, 1 + dy + domain.y, 1 + dx + domain.x},
                   {1 + dz + domain.z, 1 + 2 * dy + domain.y, 1 + 2 * dx + domain.x});
    // 1 - Top
    brect.allocate({1 + dz + domain.z, 1 + dy, 1 + dx + domain.x},
                   {1 + 2 * dz + domain.z, 1 + dy + domain.y, 1 + 2 * dx + domain.x});
    // 1 - Left
    brect.allocate({1 + dz, 1, 1 + dx + domain.x}, {1 + dz + domain.z, 1 + dy, 1 + 2 * dx + domain.x});

    // 2 faces
    // 0
    brect.allocate({1 + dz, 1 + dy, 1}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx});
    // 1
    brect.allocate({1 + dz, 1 + dy, 1 + dx + domain.x}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + 2 * dx + domain.x});

    // Rest
    brect.allocate(dim3(1 + dz * 2, 1 + dy * 2, 1 + dx), dim3(1 + domain.z, 1 + domain.y, 1 + dx + domain.x));

    std::vector<long> bvec;
    std::vector<long> tvec(1, 0);
    std::vector<long> rvec(1, 0);

    for (long rk = 1; rk < domain.z + 1 + 2 * dz; rk += region.z)
      for (long rj = 1; rj < domain.y + 1 + 2 * dy; rj += region.y)
        for (long ri = 1; ri < domain.x + 1 + 2 * dx; ri += region.x) {
          for (long bk = rk; bk < std::min(rk + region.z, domain.z + 2 * dz); bk += thread.z)
            for (long bj = rj; bj < std::min(rj + region.y, domain.y + 2 * dy); bj += thread.y)
              for (long bi = ri; bi < std::min(ri + region.x, domain.x + 2 * dx); bi += thread.x) {
                brect.push_rect(bvec, brick_dim::dim3(bk, bj, bi),
                                brick_dim::dim3(std::min(std::min(bk + thread.z, domain.z + 2 * dz), rk + region.z),
                                                std::min(std::min(bj + thread.y, domain.y + 2 * dy), rj + region.y),
                                                std::min(std::min(bi + thread.x, domain.x + 2 * dx), ri + region.x)));
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

    binfo = brect.get_brick_info();
    binfo.set_brick(bdim.z, bdim.y, bdim.x);

    // OMP schedules
    // On knl 2 cores is one tile
    blist.lv1 = omp_get_num_procs() / 1;
    blist.lv2 = omp_get_num_procs() / blist.lv1;
  }
}

void
brick_decomp::pack_exchange(brick &b, brick_dim::dim3 p0, brick_dim::dim3 p1, brick_dim::dim3 pghost, int dst, int src,
                            std::vector<void *> &bufs, std::vector<MPI_Request> &reqs, int tag) {
  int cnt = static_cast<int>((p1.z - p0.z) * (p1.y - p0.y) * (p1.x - p0.x) * b.step);
  std::vector<long> area;
  rect->push_rect(area, p0, p1);
  float *buf = (float *) malloc(cnt * sizeof(float));
  for (long i = 0; i < area.size(); ++i)
    memcpy(&buf[i * b.step], &static_cast<float *>(b.dat)[area[i] * b.step],
           static_cast<size_t>(b.step * b.elem_sz));
  reqs.emplace_back();
  MPI_Isend(buf, cnt, MPI_FLOAT, dst, tag, comm, &(reqs.back()));
  reqs.emplace_back();
  MPI_Irecv(&static_cast<float *>(b.dat)[rect->brick_index(pghost) * b.step], cnt,
            MPI_FLOAT, src, tag, comm, &(reqs.back()));
  bufs.push_back((void *) buf);
}

void brick_decomp::exchange(brick &b) {
  int tag = 0;
  std::vector<MPI_Request> reqs;
  int dest[3];

  // Those that need packing first
  std::vector<void *> bufs;
  // 8 edges
  // 0 - Bottom, to top
  auto mpi_shift = [this](brick_dim::dim3 p, int &dst, int &src) {
    int dest[3];
    dest[2] = shift(coo[2], (int) p.z, dims[2]);
    dest[1] = shift(coo[1], (int) p.y, dims[1]);
    dest[0] = shift(coo[0], (int) p.x, dims[0]);
    MPI_Cart_rank(comm, dest, &dst);
    dest[2] = shift(coo[2], -(int) p.z, dims[2]);
    dest[1] = shift(coo[1], -(int) p.y, dims[1]);
    dest[0] = shift(coo[0], -(int) p.x, dims[0]);
    MPI_Cart_rank(comm, dest, &src);
  };

  auto mpi_exchange = [this, &reqs, &b, &tag](brick_dim::dim3 ps, brick_dim::dim3 pd, int dst, int src, int cnt) {
    reqs.emplace_back();
    MPI_Isend(&static_cast<float *>(b.dat)[rect->brick_index(ps) * b.step], cnt,
              MPI_FLOAT, dst, tag, comm, &(reqs.back()));
    reqs.emplace_back();
    MPI_Irecv(&static_cast<float *>(b.dat)[rect->brick_index(pd) * b.step], cnt,
              MPI_FLOAT, src, tag, comm, &(reqs.back()));
  };

  {
    int src, dst;
    mpi_shift({1, 0, 1}, dst, src);
    pack_exchange(b, {1 + domain.z, 1 + dy, 1 + domain.x}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx + domain.x},
                  {1, 1 + dy, 1}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 0 - Right, to left
  {
    int src, dst;
    mpi_shift({0, -1, 1}, dst, src);
    pack_exchange(b, {1 + dz, 1 + domain.y, 1 + domain.x}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx + domain.x},
                  {1 + dz, 1 + dy + domain.y, 1}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 0 - Top, to bottom
  {
    int src, dst;
    mpi_shift({-1, 0, 1}, dst, src);
    pack_exchange(b, {1 + dz, 1 + dy, 1 + domain.x}, {1 + 2 * dz, 1 + dy + domain.y, 1 + dx + domain.x},
                  {1 + dz + domain.z, 1 + dy, 1}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 0 - Left, to right
  {
    int src, dst;
    mpi_shift({0, 1, 1}, dst, src);
    pack_exchange(b, {1 + dz, 1 + domain.y, 1 + domain.x}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx + domain.x},
                  {1 + dz, 1, 1}, dst, src, bufs, reqs, tag);
  }
  ++tag;

  // 1 - Bottom, to top
  {
    int src, dst;
    mpi_shift({1, 0, -1}, dst, src);
    pack_exchange(b, {1 + domain.z, 1 + dy, 1 + dx}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + 2 * dx},
                  {1, 1 + dy, 1 + dx + domain.x}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 1 - Right, to left
  {
    int src, dst;
    mpi_shift({0, -1, -1}, dst, src);
    pack_exchange(b, {1 + dz, 1 + domain.y, 1 + dx}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + 2 * dx},
                  {1 + dz, 1 + dy + domain.y, 1 + dx + domain.x}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 1 - Top, to bottom
  {
    int src, dst;
    mpi_shift({-1, 0, -1}, dst, src);
    pack_exchange(b, {1 + dz, 1 + dy, 1 + dx}, {1 + 2 * dz, 1 + dy + domain.y, 1 + 2 * dx},
                  {1 + dz + domain.z, 1 + dy, 1 + dx + domain.x}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 1 - Left, to right
  {
    int src, dst;
    mpi_shift({0, 1, -1}, dst, src);
    pack_exchange(b, {1 + dz, 1 + domain.y, 1 + dx}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + 2 * dx},
                  {1 + dz, 1, 1 + dx + domain.x}, dst, src, bufs, reqs, tag);
  }
  ++tag;

  // 2 faces
  // 0, to behind
  {
    int src, dst;
    MPI_Cart_shift(comm, 0, 1, &src, &dst);
    pack_exchange(b, {1 + dz, 1 + dy, 1 + domain.x}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx + domain.x},
                  {1 + dz, 1 + dy, 1}, dst, src, bufs, reqs, tag);
  }
  ++tag;
  // 1, to front
  {
    int src, dst;
    MPI_Cart_shift(comm, 0, -1, &src, &dst);
    pack_exchange(b, {1 + dz, 1 + dy, 1 + dx}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + 2 * dx},
                  {1 + dz, 1 + dy, 1 + dx + domain.x}, dst, src, bufs, reqs, tag);
  }
  ++tag;

  // Lets do the roll update on Y - Z
  // Bottom -> Top
  {
    int src, dst;
    MPI_Cart_shift(comm, 2, -1, &src, &dst);
    int cnt = static_cast<int>(domain.x * domain.y * dz * b.step);
    mpi_exchange({1 + dz, dy + 1, dx + 1}, {1 + dz + domain.z, dy + 1, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // Right -> Left
  {
    int src, dst;
    MPI_Cart_shift(comm, 1, 1, &src, &dst);
    int cnt = static_cast<int>(domain.x * domain.z * dy * b.step);
    mpi_exchange({1 + dz, 1 + domain.y, dx + 1}, {1 + dz, 1, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // Top -> Bottom
  {
    int src, dst;
    MPI_Cart_shift(comm, 2, 1, &src, &dst);
    int cnt = static_cast<int>(domain.x * domain.y * dz * b.step);
    mpi_exchange({1 + domain.z, 1 + domain.y, dx + 1}, {1, 1 + domain.y, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // Left -> Right
  {
    int src, dst;
    MPI_Cart_shift(comm, 1, -1, &src, &dst);
    // First section
    int cnt = static_cast<int>(domain.x * (domain.z - dz) * dy * b.step);
    mpi_exchange({1 + domain.z, 1 + dy, dx + 1}, {1 + domain.z, 1 + dy + domain.y, dx + 1}, dst, src, cnt);
    // Second section
    cnt = static_cast<int>(domain.x * dz * dy * b.step);
    mpi_exchange({1 + dz, 1 + dy, dx + 1}, {1 + dz, 1 + dy + domain.y, dx + 1}, dst, src, cnt);
  }
  ++tag;

  // Roll edges
  // (0, 0) -> (1, 1)
  {
    int src, dst;
    mpi_shift({-1, -1, 0}, dst, src);
    int cnt = static_cast<int>(domain.x * dz * dy * b.step);
    mpi_exchange({1 + dz, 1 + dy, dx + 1}, {1 + dz + domain.z, 1 + dy + domain.y, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // (0, 1) -> (1, 0)
  {
    int src, dst;
    mpi_shift({-1, 1, 0}, dst, src);
    int cnt = static_cast<int>(domain.x * dz * dy * b.step);
    mpi_exchange({1 + dz, 1 + domain.y, dx + 1}, {1 + dz + domain.z, 1, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // (1, 1) -> (0, 0)
  {
    int src, dst;
    mpi_shift({1, 1, 0}, dst, src);
    int cnt = static_cast<int>(domain.x * dz * dy * b.step);
    mpi_exchange({1 + domain.z, 1 + domain.y, dx + 1}, {1, 1, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // (1, 0) -> (0, 1)
  {
    int src, dst;
    mpi_shift({1, -1, 0}, dst, src);
    int cnt = static_cast<int>(domain.x * dz * dy * b.step);
    mpi_exchange({1 + domain.z, 1 + dy, dx + 1}, {1, 1 + dy + domain.y, dx + 1}, dst, src, cnt);
  }
  ++tag;
  // 8 nodes
  // Node (0,0,0)
  int cnt = static_cast<int>(dx * dz * dy * b.step);
  {
    int src, dst;
    mpi_shift({1, 1, 1}, dst, src);
    mpi_exchange({1 + domain.z, 1 + domain.y, 1 + domain.x}, {1, 1, 1}, dst, src, cnt);
  }
  ++tag;
  // Node (0,0,1)
  {
    int src, dst;
    mpi_shift({1, 1, -1}, dst, src);
    mpi_exchange({1 + domain.z, 1 + domain.y, 1 + dx}, {1, 1, 1 + dx + domain.x}, dst, src, cnt);
  }
  ++tag;
  // Node (0,1,0)
  {
    int src, dst;
    mpi_shift({1, -1, 1}, dst, src);
    mpi_exchange({1 + domain.z, 1 + dy, 1 + domain.x}, {1, 1 + dy + domain.y, 1}, dst, src, cnt);
  }
  ++tag;
  // Node (0,1,1)
  {
    int src, dst;
    mpi_shift({1, -1, -1}, dst, src);
    mpi_exchange({1 + domain.z, 1 + dy, 1 + dx}, {1, 1 + dy + domain.y, 1 + dx + domain.x}, dst, src, cnt);
  }
  ++tag;
  // Node (1,0,0)
  {
    int src, dst;
    mpi_shift({-1, 1, 1}, dst, src);
    mpi_exchange({1 + dz, 1 + domain.y, 1 + domain.x}, {1 + dz + domain.z, 1, 1}, dst, src, cnt);
  }
  ++tag;
  // Node (1,0,1)
  {
    int src, dst;
    mpi_shift({-1, 1, -1}, dst, src);
    mpi_exchange({1 + dz, 1 + domain.y, 1 + dx}, {1 + dz + domain.z, 1, 1 + dx + domain.x}, dst, src, cnt);
  }
  ++tag;
  // Node (1,1,0)
  {
    int src, dst;
    mpi_shift({-1, -1, 1}, dst, src);
    mpi_exchange({1 + dz, 1 + dy, 1 + domain.x}, {1 + dz + domain.z, 1 + dy + domain.y, 1}, dst, src, cnt);
  }
  ++tag;
  // Node (1,1,1)
  {
    int src, dst;
    mpi_shift({-1, -1, -1}, dst, src);
    mpi_exchange({1 + dz, 1 + dy, 1 + dx}, {1 + dz + domain.z, 1 + dy + domain.y, 1 + dx + domain.x}, dst, src, cnt);
  }
  ++tag;

  // Wait for all to complete
  std::vector<MPI_Status> stats(reqs.size());
  MPI_Waitall(static_cast<int>(reqs.size()), reqs.data(), stats.data());

  for (auto i: bufs)
    free(i);
}