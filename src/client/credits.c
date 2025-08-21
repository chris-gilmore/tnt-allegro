#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

extern u8 D_800CFD48;

////////////////////////////////////////

static void *D_80120240;
static u8 D_80120248[0x188];

static void   Credits_Init(void);
static void   Credits_80083450_oneliner_calls_80090a44(void);

static void Credits_Init(void) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  main_8004A34C_threeliner();
  //D_80120240 = (u8 *) n64HeapAlloc(240008);
  D_80120240 = al_create_bitmap(400, 300);
  /*
  ((u8 *) D_80120240)[0] = 1;
  ((u8 *) D_80120240)[1] = 0x90;
  ((u8 *) D_80120240)[2] = 1;
  ((u8 *) D_80120240)[3] = 0x2C;
  ((u8 *) D_80120240)[4] = 0;
  ((u8 *) D_80120240)[5] = 0;
  ((u8 *) D_80120240)[6] = 0;
  ((u8 *) D_80120240)[7] = 0;
  */
  //func_800A8FC8((s16 *) D_80120240, 120004, 0);
  ALLEGRO_BITMAP* cfbuffer = al_get_target_bitmap();
  al_set_target_bitmap(D_80120240);
  al_clear_to_color(al_map_rgba(0, 0, 0, 0));
  al_set_target_bitmap(cfbuffer);
  func_8008F280(&D_801290D0, -1, 400, 300, D_80120240);
  func_8008F360(&D_801290D0, D_800D6138, D_800D6128);
  D_800D3CF4 = 0;
  D_800D3CF8 = NULL;
  D_800D3CFC = NULL;
  D_801290D0.unk114 = 0;
  EndScroller_Init(D_80120248, g_credits_str);
}

static void Credits_80083450_oneliner_calls_80090a44(void) {
  func_80090A44();
}

void Credits_StateMachine_q(void) {
  static u32 D_800D3330 = 0;

  switch (D_800D3330) {
  case 0:
    Credits_Init();
    D_800D3330 = 1;
    return;
  case 1:
    func_8009D5E4();
    if (EndScroller_8008023c_line_452(D_80120248, 1) == 1) {
      D_800D3330 = 2;
      return;
    }
    EndScroller_80080400_line_502(D_80120248);
    return;
  case 2:
    EndScroller_Deinit(D_80120248);
    Credits_80083450_oneliner_calls_80090a44();
    func_8009035C(D_800D53C8, D_800D5378);
    D_800CFEE8 = 4;
    D_800CFD48 = TRUE;
    D_800D3330 = 0;
    return;
  }
}
