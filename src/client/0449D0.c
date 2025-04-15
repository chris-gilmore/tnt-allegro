#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

void func_8007F344(void) {
}

void func_8007FBB0(void **arg0, u32 arg1) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  main_8004A34C_threeliner();

  *arg0 = al_load_bitmap(config_setting_get_string_elem(images, arg1));
  if (*arg0 == NULL) {
    *arg0 = al_create_bitmap(0, 0);
  }
}
