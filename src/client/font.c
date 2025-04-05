#include "common.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

extern ALLEGRO_FONT* font;

void Font_Deinit(Font *) {}

void Font_Init46Char(Font *, u32) {}

void displayText_XY_RGBA_2(Gfx **arg0, Font *arg1, s32 x, s32 y, char *text, s32 red, s32 green, s32 blue, s32 alpha) {
  al_draw_textf(font, al_map_rgba(red, green, blue, alpha), x, y, 0, text);
}

s32 get_text_width(Font *arg0, char *arg1) {
  return al_get_text_width(font, arg1);
}
