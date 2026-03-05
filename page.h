#ifndef PAGE_H
#define PAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "bitmap.h"
#include <stdlib.h>

#define PAGE_SIZE 4096
#define PAGES_PER_SLAB 256
#define SLAB_SIZE (PAGE_SIZE * PAGES_PER_SLAB)

typedef struct {
  void* base;
  u64 free_bitmap;
  u64 used_bitmap;
} page_arena_t;

static inline page_arena_t* page_arena_create(void) {
  page_arena_t* arena = (page_arena_t*)malloc(sizeof(page_arena_t));
  if (!arena)
    return NULL;

  arena->base = malloc(SLAB_SIZE);
  if (!arena->base) {
    free(arena);
    return NULL;
  }

  arena->free_bitmap = ~0ULL;
  arena->used_bitmap = 0ULL;

  return arena;
}

static inline void page_arena_destroy(page_arena_t* arena) {
  if (!arena)
    return;
  free(arena->base);
  free(arena);
}

static inline void* page_alloc(page_arena_t* arena) {
  if (!arena)
    return NULL;

  int bit = bitmap_ffs(&arena->free_bitmap);
  if (bit == NO_BIT) {
    return NULL;
  }

  bitmap_clear(&arena->free_bitmap, bit);
  bitmap_set(&arena->used_bitmap, bit);

  void* ptr = (char*)arena->base + (bit * PAGE_SIZE);
  return ptr;
}

static inline void page_free(page_arena_t* arena, void* ptr) {
  if (!arena || !ptr)
    return;

  u64 offset = (char*)ptr - (char*)arena->base;
  int bit = offset / PAGE_SIZE;

  if (bit < 0 || bit >= 64)
    return;

  bitmap_set(&arena->free_bitmap, bit);
  bitmap_clear(&arena->used_bitmap, bit);
}

#ifdef PAGE_IMPLEMENTATION
/* Implementation */
#endif

#ifdef __cplusplus
}
#endif

#endif
