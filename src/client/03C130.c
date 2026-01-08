#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

void FUN_03C130_80075EB0_nineliner_allocs_heap(UnkStruct_21 *arg0) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  func_80075700(&arg0->unk0.unk14, 8, 8, 1);
  main_8004A34C_threeliner();

  // spotlight (128x128)
  arg0->unk64 = n64HeapAlloc(128 * 128);

  bzero(arg0->unk64, 128 * 128);

  ALLEGRO_BITMAP *img = al_load_bitmap_flags(config_setting_get_string_elem(images, IMG_SPOTLIGHT), ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  if (img != NULL) {
    ALLEGRO_LOCKED_REGION *locked = al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_SINGLE_CHANNEL_8, ALLEGRO_LOCK_READONLY);
    s32 width = al_get_bitmap_width(img);
    s32 height = al_get_bitmap_height(img);
    u8 *ptr;
    u8 *cptr = (u8 *) arg0->unk64;

    for (int j = 0; j < height; j++) {
      ptr = (u8 *)locked->data + (j * locked->pitch);
      for (int i = 0; i < width; i++) {
        *cptr++ = *ptr++;
      }
    }

    al_unlock_bitmap(img);
    al_destroy_bitmap(img);
  }

  func_80075830(&arg0->unk0);
  func_80075760(&arg0->unk0, 2);
  func_800757BC(&arg0->unk0, arg0->unk64, 128, 128);
}

void func_80075F5C(UnkStruct_21 *arg0) {
  func_80075870(&arg0->unk0);
  n64HeapUnalloc(arg0->unk64);
}
