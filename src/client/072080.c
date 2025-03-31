#include "common.h"

extern unsigned int game_id;

u32 func_800AC1A8(void *dramAddr, void *devAddr, u32 len) {
  Sram *sram = dramAddr;

  sram->unk18F4 = game_id;
}
