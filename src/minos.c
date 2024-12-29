#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "common.h"

UnkStruct_0 *D_8011FC10;

void Minos_Mino_Render(Mino *arg0, UnkStruct_8 *arg1) {
  s32 x, y;

  x = arg1->unk6.p.x + arg1->unk0.p.x;
  y = arg1->unk6.p.y + arg1->unk0.p.y;

  printf("Minos_Mino_Render()\n");
  printf("(%d, %d)\n", x, y);
  al_draw_filled_rectangle(x / 32 + 60, y / 32 + 60, (x / 32) + 8 + 60, (y / 32) + 8 + 60, al_map_rgb(255, 255, 0));
}

void Minos_800702e4_nineliner(Mino *) {}
void Minos_80070398_fourteenliner(Mino *, Mino *) {}
void Minos_80070528_Morph(Mino *) {}
void Minos_80070818_oneliner_sets_arg0_0x130_to_arg1(Mino *, s8 *) {}
void Minos_80070820_fiveliner_sets_arg0_2_4_8_12_to_arg1(Mino *, Color *) {}
void Minos_80070860_fortyliner(Mino *, Color *, s32) {}
void Minos_800709d8_threeliner_sets_arg0_1c_1e_1d(Mino *, u8) {}
void Minos_SetScale(u16 scale) {
  D_8011FC10->scale = scale;
  D_8011FC10->pattern |= 0x2;
}
void Minos_SetAlpha(u8 arg0) {}
void Minos_Init(UnkStruct_0 *, void *) {}
void Minos_Deinit_doesnothing(UnkStruct_0 *) {}
void Minos_BeginRender(UnkStruct_0 *) {}
void Minos_EndRender(UnkStruct_0 *) {}
void Minos_8007104c_fiveliner_nuts(Point *, s16, s16) {}
void Minos_SetVtxTransform(u8) {}
