/********************
* Taken from:
* https://github.com/DictumMortuum/clib
*
*********************/
#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdint.h>
#include <stdbool.h>

#define CLIB_WORD_BIT (int)(sizeof(int)*8)

typedef struct clib_bitmap {
  int *map;
  uint64_t size;
  bool (*get)(struct clib_bitmap *, int);
  void (*set)(struct clib_bitmap *, int);
  void (*reset)(struct clib_bitmap *, int);
} clib_bitmap;

clib_bitmap *clib_bitmap_init (uint64_t size);
void clib_bitmap_free (clib_bitmap *bitmap);

#endif /* BITMAP_H_ */