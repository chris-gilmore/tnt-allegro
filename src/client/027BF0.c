#include "common.h"

extern char p0_name[];
extern char p1_name[];
extern char p2_name[];
extern char p3_name[];

void FUN_027BF0_Init(s32) {
}

void FUN_027BF0_Deinit(s32) {
}

void FUN_027BF0_800636C0_display_game_stats_screen_q(void) {
  register Game *game_ptr = &g_game;
  char sp84[20];
  char sp70[20];
  char sp58[20];
  char sp40[20];
  u32 temp_t3;
  u32 temp_t4;
  u32 var_s0;

  if (D_800CFED4 == 1) {
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0x122, 0xCA, p0_name, 0xFF, 0xFF, 0xFF, 0xFF);

    if (game_ptr->gameType == GAMETYPE_SPRINT) {
      temp_t4 = game_ptr->unkE4E8;  // elapsed time
      temp_t3 = game_ptr->unkE4F0;  // 3 minutes
      if (temp_t4 < temp_t3) {
        var_s0 = temp_t3 - temp_t4;
      } else {
        var_s0 = 0;
      }
      displayTimeFormatted_XY_RGBA(var_s0, &game_ptr->font, 343, 230, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    if (game_ptr->gameType == GAMETYPE_ULTRA) {
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4E8, &game_ptr->font, 343, 230, 0xFF, 0xFF, 0xFF, 0xFF);
      sprintf(sp84, "%d", game_ptr->unkE4F4);
      displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 280, 260, sp84, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  }

  if (D_800CFED4 == 2) {
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xA9, 0xC8, p0_name, 0xFF, 0, 0, 0xFF);
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xA9, 0xE7, p1_name, 0, 0xFF, 0, 0xFF);

    if (game_ptr->gameType == GAMETYPE_SPRINT) {
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4F0 - game_ptr->unkE4E8, &game_ptr->font, 0xAA + /* D_8011FB04 */ + 50, 0xF6 + /* D_8011FB08 */ + 15, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    // /* 096ED4 800D0C54 000000AA */ .word 0x000000AA
    // /* 096ED8 800D0C58 000000F6 */ .word 0x000000F6

    if (game_ptr->gameType == GAMETYPE_ULTRA) {
      sprintf(sp70, "%d", game_ptr->unkE4F4);
      displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xBE, 0x117, sp70, 0xFF, 0xFF, 0xFF, 0xFF);
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4E8, &game_ptr->font, 0xAA + /* D_8011FB04 */ + 50, 0xF6 + /* D_8011FB08 */ + 15, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  }

  if (D_800CFED4 == 3) {
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0x27, 0xEA, p0_name, 0xFF, 0, 0, 0xFF);
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0x7B, 0xEA, p1_name, 0, 0xFF, 0, 0xFF);
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xCF, 0xEA, p2_name, 0, 0, 0xFF, 0xFF);

    if (game_ptr->gameType == GAMETYPE_SPRINT) {
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4F0 - game_ptr->unkE4E8, &game_ptr->font, 0xD8, 0x10A, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    if (game_ptr->gameType == GAMETYPE_ULTRA) {
      sprintf(sp58, "%d", game_ptr->unkE4F4);
      displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xBC, 0x109, sp58, 0xFF, 0xFF, 0xFF, 0xFF);
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4E8, &game_ptr->font, 0xD9, 0x116, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  }

  if (D_800CFED4 == 4) {
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0x27, 0xEA, p0_name, 0xFF, 0, 0, 0xFF);
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0x7B, 0xEA, p1_name, 0, 0xFF, 0, 0xFF);
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xCF, 0xEA, p2_name, 0, 0, 0xFF, 0xFF);
    displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0x124, 0xEA, p3_name, 0xFF, 0xFF, 0, 0xFF);

    if (game_ptr->gameType == GAMETYPE_SPRINT) {
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4F0 - game_ptr->unkE4E8, &game_ptr->font, 0xD8, 0x10A, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    if (game_ptr->gameType == GAMETYPE_ULTRA) {
      sprintf(sp40, "%d", game_ptr->unkE4F4);
      displayText_XY_RGBA_2(&g_gdl, &game_ptr->font, 0xBC, 0x109, sp40, 0xFF, 0xFF, 0xFF, 0xFF);
      displayTimeFormatted_XY_RGBA(game_ptr->unkE4E8, &game_ptr->font, 0xD9, 0x116, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  }
}
