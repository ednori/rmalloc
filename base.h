#ifndef BASE_H
#define BASE_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* MACROS */
#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, l, h) (MAX((l), MIN((x), (h))))

#define UNUSED(x) ((void)(x))

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

/* integers */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/* floats */
typedef float f32;
typedef double f64;

/* sizes */
typedef size_t usize;
typedef intptr_t isize;

/* booleans */
typedef bool b8;

/* Alignment */
#define ALIGNMENT 8
#define ALIGN_POW2(n) (((n) + ALIGNMENT - 1) & ~(ALIGNMENT - 1))
#define IS_ALIGNED(n) (((n) & (ALIGNMENT - 1)) == 0)


/* Memory ops */
#define MEMSET __builtin_memset
#define MEMCPY __builtin_memcpy
#define MEMMOVE __builtin_memmove

/* Bit ops */
#define BIT(n) (1ULL << (n))
#define BIT_GET(v, n) (((v) >> (n)) & 1ULL)
#define BIT_SET(v, n) ((v) | BIT(n))
#define BIT_CLEAR(v, n) ((v) & ~BIT(n))

/* Math */
#define PI 3.14159265358979323846
static inline f32 lerp(f32 a, f32 b, f32 t) { return a + t * (b - a); }

/* Assertions */
#define ASSERT_MSG(cond, msg)                                                  \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fprintf(stderr,                                                          \
              "ASSERT FAILED: %s\n"                                            \
              "MESSAGE: %s\n"                                                  \
              "FILE: %s\n"                                                     \
              "LINE: %d\n",                                                    \
              #cond, msg, __FILE__, __LINE__);                                 \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#endif

#define ASSERT(x) ASSERT_MSG(x, "Assertion failed")
