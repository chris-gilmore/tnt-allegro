#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

////////////////////////////////////////

static void *D_8011FAD0;
static s32 D_8011FAD8;
static s32 D_8011FADC;

static u32 D_800D02A0 = 0;

void FUN_0279C0_80061740_switch_0to8_1to6_same(void) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  switch (D_800D02A0) {
  case 0:
    main_8004A34C_threeliner();
    //FUN_026900_80060d58_elevenliner(1);

    D_8011FAD0 = al_load_bitmap(config_setting_get_string_elem(images, IMG_WARNING_NO_CONTROLLER));

    func_8007CF40(0);
    func_800875EC(0x6000, &g_songPlayer);
    //func_80061134(400, 300);
    D_800D02A0++;
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    D_800D02A0++;
    break;
  case 7:
    //FUN_026900_80060d58_elevenliner(0);
    D_800D02A0++;
    break;
  case 8:
    g_gdl = func_8007DA00(g_gdl);
    D_8011FAD8 = (screen_1_width >> 1) - (al_get_bitmap_width(D_8011FAD0) >> 1);
    D_8011FADC = (screen_1_height >> 1) - (al_get_bitmap_height(D_8011FAD0) >> 1);
    func_8005BBFC(&g_gdl);
    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_8011FAD0, NULL, D_8011FAD8, D_8011FADC, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8005BE40(&g_gdl);
    break;
  }
}
