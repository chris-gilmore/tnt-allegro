#include "common.h"

extern int g_screen;

extern s8 D_800CF838;  // TODO: move this out of here

static u8 D_800D3D98[4] = { 0, 0, 0, 0 };  // handicap_arr

void func_800905E8(u8) {
  // init rand
  func_800A3550();
}

void func_80090E08(void) {
  main_8004A34C_threeliner();
  //func_80090A44();
  D_800CFEE8 = 9;
  if (D_800CF838 >= 7) {
    g_game.unkE4F8 = func_800A35EC(0, 7);
  } else {
    g_game.unkE4F8 = func_800A35EC(0, D_800CF838);
  }

  if (g_screen != -1) {
    g_game.unkE4F8 = g_screen;
  }
  printf("Screen: '%d'\n", g_game.unkE4F8);

  FUN_027BF0_check_music_settings_and_play(g_game.unkE4F8);
  Audio_LoadSFX(&D_800D3A90);
  Game_Init(D_800CFED4, D_800D3D98);
  /*
  if (D_800D3D20 != 0) {
    D_800D3D20 = 0;
  }
  D_800D3CF0 = 0;
  */
  main_8004A34C_threeliner();
}
