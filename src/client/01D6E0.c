#include "common.h"
#include <allegro5/allegro5.h>

void weird_lots_of_magic_number_setting_66xrefs(Gfx **gdl_ptr, void *img, void *pal, s32 x, s32 y, s32 red, s32 green, s32 blue, s32 alpha) {
  int width;
  int height;

  if ((img == NULL) || (alpha == 0)) {
    return;
  }

  width  = al_get_bitmap_width(img);
  height = al_get_bitmap_height(img);

  if ((width > 0) && (height > 0)) {
    if ((alpha == 0xFF) && (red == 0xFF) && (green == 0xFF) && (blue == 0xFF)) {
      al_draw_bitmap(img, x, y, 0);
    } else {
      al_draw_tinted_bitmap(img, al_premul_rgba(red, green, blue, alpha), x, y, 0);
    }
  }
}

void display_one_text_character_rgb(Gfx **gdl_ptr, void *img, s32 sl, s32 tl, s32 sh, s32 th, s32 x, s32 y, s32 red, s32 green, s32 blue, s32 alpha) {
  int width;
  int height;

  if ((img == NULL) || (alpha == 0)) {
    return;
  }

  width  = al_get_bitmap_width(img);
  height = al_get_bitmap_height(img);

  if ((width > 0) && (height > 0) && (sh >= sl) && (th >= tl)) {
    if ((alpha == 0xFF) && (red == 0xFF) && (green == 0xFF) && (blue == 0xFF)) {
      al_draw_bitmap_region(img, sl, tl, (sh - sl) + 1, (th - tl) + 1, x, y, 0);
    } else {
      al_draw_tinted_bitmap_region(img, al_premul_rgba(red, green, blue, alpha), sl, tl, (sh - sl) + 1, (th - tl) + 1, x, y, 0);
    }
  }
}

void FUN_8005aa9c_prob_display_text_rgb_as_well(Gfx **arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, s32 argE) {
}

void func_8005BBFC(Gfx **) {}

void func_8005BE40(Gfx **) {}
