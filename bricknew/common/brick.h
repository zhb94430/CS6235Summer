//
// Created by Tuowen Zhao on 12/3/18.
//

#ifndef BRICK_H
#define BRICK_H

#include <stdlib.h>
#include <type_traits>

#include "defs.h"

#define ALIGN 2048

#ifdef __CUDACC__
#define FORCUDA __host__ __device__
#else
#define FORCUDA
#endif

template<unsigned base, unsigned exp>
struct static_power {
  static constexpr unsigned value = base * static_power<base, exp - 1>::value;
};
template<unsigned base>
struct static_power<base, 0> {
  static constexpr unsigned value = 1;
};

struct BrickStorage {
  bElem *dat;
  long chunks, step;

  static BrickStorage allocate(long chunks, long step) {
    BrickStorage b;
    b.chunks = chunks;
    b.step = step;
    b.dat = (bElem *) aligned_alloc(ALIGN, chunks * step * sizeof(bElem));
    return b;
  }
};

template<unsigned dims>
struct BrickInfo {
  typedef unsigned (*adjlist)[static_power<3, dims>::value];
  adjlist adj;
  unsigned nbricks;

  explicit BrickInfo(unsigned nbricks) : nbricks(nbricks) {
    adj = (adjlist) malloc(nbricks * static_power<3, dims>::value * sizeof(unsigned));
  }

  BrickStorage allocate(long step) {
    return BrickStorage::allocate(nbricks, step);
  }
};

template<unsigned ... Ds>
struct Dim {
};


template<unsigned ... xs>
struct cal_size;

template<unsigned x>
struct cal_size<x> {
  static constexpr unsigned value = x;
};

template<unsigned x, unsigned ... xs>
struct cal_size<x, xs...> {
  static constexpr unsigned value = x * cal_size<xs ...>::value;
};

template<unsigned ... offs>
struct cal_offs;

template<unsigned off>
struct cal_offs<1, off> {
  static constexpr unsigned value = off;
};

template<unsigned dim, unsigned off, unsigned ...offs>
struct cal_offs<dim, off, offs...> {
  static constexpr unsigned value = off * static_power<3, dim - 1>::value + cal_offs<dim - 1, offs...>::value;
};

template<typename...>
struct _BrickAccessor;

template<typename T,
    unsigned D,
    unsigned F>
struct _BrickAccessor<T, Dim<D>, Dim<F>, bool> {
  T *par;
  unsigned b, pos, nvec, wvec;

  FORCUDA
  _BrickAccessor(T *par, unsigned b, unsigned pos, unsigned nvec, unsigned wvec) :
      par(par), b(b), pos(pos), nvec(nvec), wvec(wvec) {
  }

  FORCUDA
  inline bElem &operator[](unsigned i) {
    // change pos
    unsigned dir = i + D;
    unsigned d = pos * 3 + dir / D;
    // new vec position
    unsigned l = dir % D;
    unsigned w = wvec * F + l % F;
    unsigned n = nvec * (D / F) + l / F;
    unsigned offset = n * par->VECLEN + w;

    return par->dat[par->bInfo->adj[b][d] * par->bStorage->step + offset];
  }
};

template<typename T,
    unsigned D,
    unsigned F,
    unsigned ... BDims,
    unsigned ... Folds>
struct _BrickAccessor<T, Dim<D, BDims...>, Dim<F, Folds...>, bool> {
  T *par;
  unsigned b, pos, nvec, wvec;

  FORCUDA
  _BrickAccessor(T *par, unsigned b, unsigned pos, unsigned nvec, unsigned wvec) :
      par(par), b(b), pos(pos), nvec(nvec), wvec(wvec) {
  }

  FORCUDA
  inline _BrickAccessor<T, Dim<BDims...>, Dim<Folds...>, bool> operator[](unsigned i) {
    // change pos
    unsigned dir = i + D;
    unsigned d = pos * 3 + dir / D;
    // new vec position
    unsigned l = dir % D;
    unsigned w = wvec * F + l % F;
    unsigned n = nvec * (D / F) + l / F;
    return _BrickAccessor<T, Dim<BDims...>, Dim<Folds...>, bool>(par, b, d, n, w);
  }
};

template<typename T,
    unsigned D,
    unsigned ... BDims,
    unsigned ... Folds>
struct _BrickAccessor<T, Dim<D, BDims...>, Dim<Folds...>, void> {
  T *par;
  unsigned b, pos, nvec, wvec;

  FORCUDA
  _BrickAccessor(T *par, unsigned b, unsigned pos, unsigned nvec, unsigned wvec) :
      par(par), b(b), pos(pos), nvec(nvec), wvec(wvec) {
  }

  FORCUDA
  inline _BrickAccessor<T, Dim<BDims...>, Dim<Folds...>,
      typename std::conditional<sizeof...(BDims) == sizeof...(Folds), bool, void>::type>
  operator[](unsigned i) {
    // change pos
    unsigned dir = i + D;
    unsigned d = pos * 3 + dir / D;
    // new vec position
    unsigned l = dir % D;
    unsigned w = wvec;
    unsigned n = nvec * D + l;
    return _BrickAccessor<T, Dim<BDims...>, Dim<Folds...>,
        typename std::conditional<sizeof...(BDims) == sizeof...(Folds), bool, void>::type>(par, b, d, n, w);
  }
};

template<typename...>
struct Brick;

template<
    unsigned ... BDims,
    unsigned ... Folds>
struct Brick<Dim<BDims...>, Dim<Folds...> > {
  typedef Brick<Dim<BDims...>, Dim<Folds...> > mytype;
  typedef BrickInfo<sizeof...(BDims)> myBrickInfo;
  myBrickInfo *bInfo;
  BrickStorage *bStorage;
  unsigned step;
  bElem *dat;

  static constexpr unsigned VECLEN = cal_size<Folds...>::value;
  static constexpr unsigned BRICKSIZE = cal_size<BDims...>::value;

  FORCUDA
  inline _BrickAccessor<mytype, Dim<BDims...>, Dim<Folds...>,
      typename std::conditional<sizeof...(BDims) == sizeof...(Folds), bool, void>::type> operator[](unsigned b) {
    return _BrickAccessor<mytype, Dim<BDims...>, Dim<Folds...>,
        typename std::conditional<sizeof...(BDims) == sizeof...(Folds), bool, void>::type>(this, b, 0, 0, 0);
  }

  FORCUDA
  inline bElem *neighbor(unsigned b) {
    return &dat[b * bStorage->step];
  }

  FORCUDA
  Brick(myBrickInfo *bInfo, BrickStorage *bStorage, unsigned offset) : bInfo(bInfo), bStorage(bStorage) {
    dat = bStorage->dat + offset;
    step = (unsigned) bStorage->step;
  }
};

inline void elemcpy(bElem *dst, const bElem *src, unsigned long size) {
  #pragma omp simd
  for (unsigned long i = 0; i < size; ++i)
    dst[i] = src[i];
}

#endif //BRICK_H
