#include "common.h"

void func_8007F344(void) {
}

void func_8007FBB0(UnkStruct_21 **arg0, u32 arg1) {
  main_8004A34C_threeliner();
  /*
  *arg0 = (UnkStruct_21 *)n64HeapAlloc(FUN_03A750_80074888_twelveliner((u32)&D_273A00, arg1));
  FUN_03A750_800746c0_twentyliner((u32) &D_273A00, (u8 *) *arg0, arg1);
  */
  *arg0 = (UnkStruct_21 *)n64HeapAlloc(sizeof(UnkStruct_21));
  (*arg0)->width = 40;
  (*arg0)->height = 30;
}
