#include "common.h"

OSTime osGetTime(void) {
  OSTime ret = 0;

  ret = rand();

  return ret;
}
