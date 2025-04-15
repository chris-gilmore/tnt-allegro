#include "common.h"

static u8 D_800D3D98[4] = { 0, 0, 0, 0 };  // handicap_arr

void func_800905E8(u8) {
}

void func_80090E08(void) {
  main_8004A34C_threeliner();
  //func_80090A44();
  D_800CFEE8 = 9;
  /*
  if (D_800CF838 >= 7) {
    var_v0 = func_800A35EC(0, 7);
    var_at = &g_game + 0x7FFF;
  } else {
    var_v0 = func_800A35EC(0, D_800CF838);
    var_at = &g_game + 0x7FFF;
  }
  */
  //var_at->unk64F9 = var_v0;  // screen (unkE4F8)
  g_game.unkE4F8 = 7;  // screen
  //FUN_027BF0_check_music_settings_and_play(g_game.unkE4F8);
  //Audio_LoadSFX(&D_800D3A90);
  Game_Init(D_800CFED4, D_800D3D98);
  /*
  if (D_800D3D20 != 0) {
    D_800D3D20 = 0;
  }
  D_800D3CF0 = 0;
  */
  main_8004A34C_threeliner();
}
