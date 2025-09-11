#include "common.h"

s16 *func_800A8FC8(s16 *arg0, s32 arg1, s32 arg2) {
  for (*arg0 = arg2; arg1 != 0; arg1--) {
    *arg0++ = arg2;
  }
  return arg0;
}
