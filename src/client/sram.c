#include "common.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

extern ALLEGRO_FONT* font;
extern unsigned int game_id;

extern s8 D_800CF838;  // TODO: move this out of here

Sram *g_sram_ptr;

void FUN_SRAM_n64HeapUnalloc_and_set_to_NULL(Font *) {}

void FUN_SRAM_80077408_twentyliner_loops_46t(Font *, s32) {}

void displayText_XY_RGBA_2(Gfx **arg0, Font *arg1, s32 x, s32 y, char *text, s32 red, s32 green, s32 blue, s32 alpha) {
  al_draw_textf(font, al_map_rgba(red, green, blue, alpha), x, y, 0, text);
}

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
