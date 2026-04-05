#include "common.h"

/*
  cvt.w.s    $ft0, $fa0
  mfc1       $v0, $ft0
  jr         $ra
   nop
*/

/*
  cvt.w.s converts float to integer
  rounding mode on the N64 uses FPCSR_RM_RN (round to nearest)
*/

s32 func_800A2EF0(f32 arg0) {
  return lroundf(arg0);
}
