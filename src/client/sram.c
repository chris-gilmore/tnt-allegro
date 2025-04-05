#include "common.h"

extern unsigned int game_id;

extern s8 D_800CF838;  // TODO: move this out of here

Sram *g_sram_ptr;

void load_from_sram(u8 arg0) {
  register Sram *sram_ptr;

  if (arg0 == FALSE) {
    g_sram_ptr = (Sram *) n64HeapAlloc(0x1900);
    sram_ptr = g_sram_ptr;
    func_800AC1A8(sram_ptr, (void *)0x08000000, 0x1900);
  }
  sram_ptr = g_sram_ptr;

  if (arg0 == TRUE) {
    sram_ptr->unk18F4 = game_id;
  }

  g_game.unkE4F8 = D_800CF838;
}

void func_8007C5CC(Sram *sram_ptr) {
  //sram_ptr->unk18F4 = osGetTime();
  sram_ptr->unk18F4 = game_id;
}
