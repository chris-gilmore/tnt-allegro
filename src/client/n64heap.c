#include "common.h"

void *n64HeapAlloc(s32 size) {
  return malloc(size);
}

void n64HeapUnalloc(void *pBlock) {
  free(pBlock);
}
