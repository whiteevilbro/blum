#include "memmgnt.h"
#include "vector.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_K 8

GEN_VECTOR(uint16_t, vector16, 8)
GEN_VECTOR(uint32_t, vector32, DEFAULT_K)

typedef struct {
  vector16 bitset;
  size_t m;
  vector32 hashes;
} blum_filter;

size_t hash(uint32_t a, uint32_t ip) {
  size_t res = 0;
  for (size_t i = 0; i < 4; i++) {
    res += (size_t) ((uint8_t) a) * (size_t) ((uint8_t) ip);
    a >>= 8;
    ip >>= 8;
  }
  return res;
}

void blum_init(blum_filter* f, size_t obj_c, double faultness) {
  vector16* bs = &(f->bitset);
  vector32* h = &(f->hashes);

  double t = -log2(faultness);
  size_t k = (size_t) ceil(t);
  t = t / log(2);
  size_t b = (size_t) ceil(t);
  size_t n = b * obj_c;
  size_t u = (n + 15) / 16;
  f->m = n;
  vector16_init(bs);
  vector16_fill(bs, u, 0);

  vector32_init(h);
  vector32_ensure_capacity(h, k);
  for (size_t i = 0; i < k; i++) {
    vector32_add_tail(h, (uint32_t) rand());
  }
}

void insert(blum_filter* f, uint32_t val) {
  vector32* h = &(f->hashes);
  vector16* b = &(f->bitset);
  size_t l = vector32_get_length(h);
  for (size_t i = 0; i < l; i++) {
    size_t r = hash(vector32_get(h, i), val) % f->m;
    size_t quot = r / 16; // compiler will optimize anyway
    size_t rem = r % 16;

    vector16_set(b, quot, vector16_get(b, quot) | (1 << rem));
  }
}

int lookup(blum_filter* f, uint32_t val) {
  vector32* h = &(f->hashes);
  vector16* b = &(f->bitset);
  size_t l = vector32_get_length(h);
  for (size_t i = 0; i < l; i++) {
    size_t r = hash(vector32_get(h, i), val) % f->m;
    size_t quot = r / 16; // compiler will optimize anyway
    size_t rem = r % 16;

    uint16_t t = vector16_get(b, quot) & (1 << rem);
    if (!t)
      return 0;
  }
  return 1;
}

int main(void) {
  uint32_t ip;
  blum_filter f;
  size_t c;
  double e;
  scanf("%zu%lf", &c, &e);
  blum_init(&f, c, e);

  for (size_t i = 0; i < c; i++) {
    scanf("%ud", &ip);
    insert(&f, ip);
  }
  scanf("%zu", &c);
  for (size_t i = 0; i < c; i++) {
    scanf("%ud", &ip);
    int r = lookup(&f, ip);
    if (r)
      printf("GOTCHA\n");
    else
      printf("Officer, I've never seen him in my life\n");
  }
  return 0;
}