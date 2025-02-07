#include "common.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

extern ALLEGRO_FONT* font;

s32 string_do_something_weird(void *arg0, s8 *arg1) {
  return al_get_text_width(font, arg1);
}

void displayTimeFormatted_XY_RGBA(u32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s8 sp44[20];
    u32 temp_hi;
    u32 temp_hi_2;
    u32 temp_hi_3;
    u32 temp_hi_4;
    u32 temp_hi_5;
    u32 temp_lo;
    u32 temp_lo_2;

    temp_lo = arg0 / 60U;
    arg0 = temp_lo;
    if ((u32) (temp_lo + 0xFFB0E600) < 0x34BC0U) {
        arg0 = 0U;
    }
    if (arg0 >= 0x8CA0U) {
        arg0 = 0x8C9FU;
    }
    if (arg0 < 0x258U) {
        temp_hi = arg0 % 60U;
        sprintf(sp44, "%1.1d:%1.1d%1.1d", (u32) ((u32) (arg0 / 60U) % 60U) % 10U, temp_hi / 10U, temp_hi % 10U);
    } else if (arg0 < 0xE11U) {
        temp_hi_2 = (u32) (arg0 / 60U) % 60U;
        temp_hi_3 = arg0 % 60U;
        sprintf(sp44, "%1.1d%1.1d:%1.1d%1.1d", temp_hi_2 / 10U, temp_hi_2 % 10U, temp_hi_3 / 10U, temp_hi_3 % 10U);
    } else {
        temp_lo_2 = arg0 / 60U;
        temp_hi_4 = temp_lo_2 % 60U;
        temp_hi_5 = arg0 % 60U;
        sprintf(sp44, "%1.1d:%1.1d%1.1d:%1.1d%1.1d", (u32) (temp_lo_2 / 60U) % 10U, temp_hi_4 / 10U, temp_hi_4 % 10U, temp_hi_5 / 10U, temp_hi_5 % 10U);
    }
    displayText_XY_RGBA_2(&g_gdl, arg1, arg2 - string_do_something_weird(arg1, sp44), arg3, sp44, arg4, arg5, arg6, arg7);
}
