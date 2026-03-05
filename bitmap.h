#ifndef BITMAP_H
#define BITMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

typedef uint64_t bitmap_t;

#define NO_BIT 65

static inline bool bitmap_get(bitmap_t* bm, u8 pos) {
  return (*bm >> pos) & 1ULL;
}

static inline void bitmap_set(bitmap_t* bm, u8 pos) {
  *bm |= (1ULL << pos);
}
static inline void bitmap_clear(bitmap_t* bm, u8 pos) {
  *bm &= ~(1ULL << pos);
}
static inline void bitmap_toggle(bitmap_t* bm, u8 pos) {
  *bm ^= (1ULL << pos);
}

static inline u8 bitmap_ffs(bitmap_t* bm) {
  return (*bm == 0) ? NO_BIT : (u8)__builtin_ctzll(*bm);
}

static inline u8 bitmap_fff(bitmap_t* bm) {
  return (*bm == ~0ULL) ? NO_BIT : (u8)__builtin_ctzll(~*bm);
}

static inline int bitmap_fcf(bitmap_t* bm, u8 n) {
  u64 mask = (1ULL << n) - 1;
  for (int i = 0; i <= 64 - n; i++) {
    if (((*bm >> i) & mask) == 0)
      return i;
  }
  return -1;
}

static inline void bitmap_cset(bitmap_t* bm, u8 pos, u8 n) {
  u64 mask = ((1ULL << n) - 1) << pos;
  *bm |= mask;
}

static inline void bitmap_cclear(bitmap_t* bm, u8 pos, u8 n) {
  u64 mask = ((1ULL << n) - 1) << pos;
  *bm &= ~mask;
}

static inline int bitmap_nfree(bitmap_t* bm, u8 n) {
  u64 mask = (1ULL << n) - 1;
  for (int i = 0; i <= 64 - n; i++) {
    if (((*bm >> i) & mask) == 0)
      return i;
  }
  return -1;
}

static inline int bitmap_countset(bitmap_t* bm) {
  return __builtin_popcountll(*bm);
}

static inline bool bitmap_isfull(bitmap_t* bm) {
  return *bm == ~0ULL;
}

#ifdef BITMAP_IMPLEMENTATION
/* Implementation */
#endif

#ifdef __cplusplus
}
#endif

#endif
