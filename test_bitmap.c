#include <assert.h>
#include <stdio.h>

#include "bitmap.h"

#include <assert.h>
#include <limits.h>

void test_bitmap_get_set_clear_toggle(void) {
  bitmap_t bm = 0;

  // set
  bitmap_set(&bm, 0);
  bitmap_set(&bm, 63);
  assert(bitmap_get(&bm, 0) == true);
  assert(bitmap_get(&bm, 63) == true);

  // clear
  bitmap_clear(&bm, 0);
  assert(bitmap_get(&bm, 0) == false);

  // toggle
  bitmap_toggle(&bm, 1);
  assert(bitmap_get(&bm, 1) == true);
  bitmap_toggle(&bm, 1);
  assert(bitmap_get(&bm, 1) == false);

  printf("test_bitmap_get_set_clear_toggle passed\n");
}

void test_bitmap_ffs(void) {
  bitmap_t bm = 0;

  // no bits set
  assert(bitmap_ffs(&bm) == NO_BIT);

  bitmap_set(&bm, 5);
  assert(bitmap_ffs(&bm) == 5);

  bitmap_set(&bm, 2);
  assert(bitmap_ffs(&bm) == 2);

  printf("test_bitmap_ffs passed\n");
}

void test_bitmap_fff(void) {
  bitmap_t bm = 0;

  // first free in empty bitmap
  assert(bitmap_fff(&bm) == 0);

  // fill first few bits
  bitmap_set(&bm, 0);
  bitmap_set(&bm, 1);
  bitmap_set(&bm, 2);

  assert(bitmap_fff(&bm) == 3);

  // special case from your implementation:
  bm = ~0ULL; // bits 0–62 set, bit 63 free
  assert(bitmap_fff(&bm) == NO_BIT);

  printf("test_bitmap_fff passed\n");
}

void test_bitmap_fcf(void) {
  bitmap_t bm = 0;

  // empty bitmap → should find at 0
  assert(bitmap_fcf(&bm, 4) == 0);

  // block first 5 bits
  bitmap_cset(&bm, 0, 5);

  assert(bitmap_fcf(&bm, 4) == 5);

  // fill everything
  bm = ~0ULL;
  assert(bitmap_fcf(&bm, 2) == -1);

  printf("test_bitmap_fcf passed\n");
}

void test_bitmap_cset_cclear(void) {
  bitmap_t bm = 0;

  bitmap_cset(&bm, 10, 5);

  for (int i = 10; i < 15; i++)
    assert(bitmap_get(&bm, i) == true);

  bitmap_cclear(&bm, 11, 3);

  assert(bitmap_get(&bm, 10) == true);
  assert(bitmap_get(&bm, 11) == false);
  assert(bitmap_get(&bm, 12) == false);
  assert(bitmap_get(&bm, 13) == false);
  assert(bitmap_get(&bm, 14) == true);

  printf("test_bitmap_cset_cclear passed\n");
}

void test_bitmap_nfree(void) {
  bitmap_t bm = 0;

  // empty bitmap
  assert(bitmap_nfree(&bm, 3) == 0);

  bitmap_cset(&bm, 0, 4); // block first 4 bits

  assert(bitmap_nfree(&bm, 3) == 4);

  bm = ~0ULL;
  assert(bitmap_nfree(&bm, 1) == -1);

  printf("test_bitmap_nfree passed\n");
}

void test_bitmap_countset(void) {
  bitmap_t bm = 0;

  assert(bitmap_countset(&bm) == 0);

  bitmap_set(&bm, 0);
  bitmap_set(&bm, 1);
  bitmap_set(&bm, 63);

  assert(bitmap_countset(&bm) == 3);

  bm = ~0ULL;
  assert(bitmap_countset(&bm) == 64);

  printf("test_bitmap_countset passed\n");
}

void test_bitmap_isfull(void) {
  bitmap_t bm = 0;

  assert(bitmap_isfull(&bm) == false);

  bm = ~0ULL;
  assert(bitmap_isfull(&bm) == true);

  printf("test_bitmap_isfull passed\n");
}

int main(void) {
  test_bitmap_get_set_clear_toggle();
  test_bitmap_ffs();
  test_bitmap_fff();
  test_bitmap_fcf();
  test_bitmap_cset_cclear();
  test_bitmap_nfree();
  test_bitmap_countset();
  test_bitmap_isfull();

  printf("\nAll bitmap tests passed\n");
  return 0;
}
