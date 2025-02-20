#include "common.h"

extern unsigned int game_id;

s32 func_800AC1A8(Sram *sram_ptr, s32 arg1, s32 arg2) {
  sram_ptr->unk18F4 = game_id;
}
