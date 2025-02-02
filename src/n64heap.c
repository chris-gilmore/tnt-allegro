#include "common.h"

u8 *n64HeapAlloc(s32 size) {
  return malloc(size);
}

void n64HeapUnalloc(u8 *pBlock) {
  free(pBlock);
}
