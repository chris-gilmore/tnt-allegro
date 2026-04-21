#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

////////////////////////////////////////

void FUN_01D300_80057080_nevercalled(ImgParams *imgParams) {
  imgParams->img = NULL;
  imgParams->x = 0;
  imgParams->y = 0;
  imgParams->red = 0xFF, imgParams->green = 0xFF, imgParams->blue = 0xFF, imgParams->alpha = 0xFF;
}

void FUN_01D300_800570b0_fiveliner(ImgParams *imgParams, u32 img_id) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  main_8004A34C_threeliner();
  imgParams->img = al_load_bitmap(config_setting_get_string_elem(images, img_id));
}

void FUN_01D300_n64HeapUnalloc(ImgParams *imgParams) {
  al_destroy_bitmap(imgParams->img);
}

void FUN_01D300_80057140_sixliner(ImgParams *imgParams) {
  gDPPipeSync(g_gdl++);

  weird_lots_of_magic_number_setting_66xrefs(&g_gdl, imgParams->img, NULL, imgParams->x, imgParams->y, imgParams->red, imgParams->green, imgParams->blue, imgParams->alpha);
}

void FUN_01D300_800571d4_twentyliner(ImgPalParams *imgPalParams, u32 img_id, u32 pal_id) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  main_8004A34C_threeliner();
  imgPalParams->img = al_load_bitmap(config_setting_get_string_elem(images, img_id));
  imgPalParams->x = 0;
  imgPalParams->y = 0;
  imgPalParams->unkC = 0x400;
  imgPalParams->unkE = 0x400;
  imgPalParams->red = imgPalParams->green = imgPalParams->blue = imgPalParams->alpha = 0xFF;
}

void FUN_01D300_800572f8_twoliner(ImgPalParams *imgPalParams) {
  al_destroy_bitmap(imgPalParams->img);
}

void FUN_01D300_80057338_fifteenliner(ImgPalParams *imgPalParams) {
  gDPPipeSync(g_gdl++);

  if ((imgPalParams->unkC == 0x400) && (imgPalParams->unkE == 0x400)) {
    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, imgPalParams->img, imgPalParams->pal, imgPalParams->x, imgPalParams->y, imgPalParams->red, imgPalParams->green, imgPalParams->blue, imgPalParams->alpha);
  } else {
    printf("---- FUN_01D300_80057338_fifteenliner ----\n");
    // TODO
    //func_8005DB90(&g_gdl, imgPalParams->img, imgPalParams->pal, imgPalParams->x, imgPalParams->y, imgPalParams->red, imgPalParams->green, imgPalParams->blue, imgPalParams->alpha, imgPalParams->unkC, imgPalParams->unkE);
  }
}
