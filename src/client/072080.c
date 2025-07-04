#include "common.h"

extern unsigned int game_id;

void func_800ABFF0(void *devAddr, void *dramAddr, u32 len) {
  printf("-- func_800ABFF0\n");
}

u32 func_800AC1A8(void *dramAddr, void *devAddr, u32 len) {
  Sram *sram = dramAddr;

  sram->unk18F4 = game_id;
}

void func_800AC308(s32 arg0, s32 arg1) {
}
