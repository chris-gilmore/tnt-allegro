#include "common.h"

extern char p0_name[];

void FUN_027BF0_Init(u8) {
}

void FUN_027BF0_Deinit(s32) {
}

void FUN_027BF0_800636C0_display_game_stats_screen_q(void) {
  register Game *game_ptr = &g_game;
  char sp84[24];
  u32 temp_t3;
  u32 temp_t4;
  u32 var_s0;

  displayText_XY_RGBA_2(&g_gdl, game_ptr->unk8, 0x125, 0xCA, p0_name, 0xFF, 0xFF, 0xFF, 0xFF);

  if (game_ptr->gameType == GAMETYPE_SPRINT) {
    temp_t4 = game_ptr->unkE4E8;  // elapsed time
    temp_t3 = game_ptr->unkE4F0;  // 3 minutes
    if (temp_t4 < temp_t3) {
      var_s0 = temp_t3 - temp_t4;
    } else {
      var_s0 = 0;
    }
    func_8005BBFC(&g_gdl);
    displayTimeFormatted_XY_RGBA(var_s0, game_ptr->unk8, 343, 230, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8005BE40(&g_gdl);
  }

  if (game_ptr->gameType == GAMETYPE_ULTRA) {
    func_8005BBFC(&g_gdl);
    displayTimeFormatted_XY_RGBA(game_ptr->unkE4E8, game_ptr->unk8, 343, 230, 0xFF, 0xFF, 0xFF, 0xFF);
    sprintf(sp84, "%d", game_ptr->unkE4F4);
    displayText_XY_RGBA_2(&g_gdl, game_ptr->unk8, 280, 260, sp84, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8005BE40(&g_gdl);
  }
}
