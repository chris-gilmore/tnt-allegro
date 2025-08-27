#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

static ALLEGRO_BITMAP *img;

////////////////////////////////////////

extern u16 draw_buffer;

////////////////////////////////////////

void FUN_046770_800804f0_many_heapallocs_for_arg0_elems(UnkStruct_12 *arg0) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  ALLEGRO_BITMAP *bitmap;

  s32 width;
  s32 height;
  ALLEGRO_LOCKED_REGION *locked;
  u8 *rptr;
  RGB *cptr;
  u8 *wptr;
  RGB *rgbptr;

  u8 *sp4C;  // greyscale image used as height field
  register s32 i;
  register s32 j;
  register Gradient2D *var_s2;
  register u8 *var_s3;
  PaletteInfo palInfo_1;
  PaletteInfo palInfo_2;

  // (200 x 150)  I - IMG_UNKNOWN_0X49B274
  sp4C = (u8 *) n64HeapAlloc(200 * 150 * sizeof(u8));

  // gradients for above height field
  arg0->unk8 = (Gradient2D *) n64HeapAlloc(200 * 150 * sizeof(Gradient2D));

  // (200 x 150) CI - IMG_UNKNOWN_0X4946FE
  arg0->unk0 = (u8 *) n64HeapAlloc(200 * 150 * sizeof(u8));

  // (RGB palette)  - IMG_UNKNOWN_0X49AFAC
  arg0->unk4 = (RGB *) n64HeapAlloc(256 * sizeof(RGB));

  // (128 x 128) CI - IMG_UNKNOWN_0X4A1C4C
  arg0->unkC = (u8 *) n64HeapAlloc(128 * 128 * sizeof(u8));

  // (RGB palette)  - IMG_UNKNOWN_0X4A3BBC
  arg0->unk10 = (RGB *) n64HeapAlloc(256 * sizeof(RGB));

  arg0->unk14[0] = n64HeapAlloc(60008);
  arg0->unk14[1] = n64HeapAlloc(60008);

  img = al_create_bitmap(200, 150);

  main_8004A34C_threeliner();

  //FUN_03A750_800746c0_twentyliner(&D_273A00, arg0->unk0, IMG_UNKNOWN_0X4946FE);
  bitmap = al_load_bitmap_flags(config_setting_get_string_elem(images, IMG_UNKNOWN_0X4946FE), ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  if (bitmap == NULL) {
    return;
  }
  width = al_get_bitmap_width(bitmap);
  height = al_get_bitmap_height(bitmap);
  locked = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_SINGLE_CHANNEL_8, ALLEGRO_LOCK_READONLY);
  wptr = arg0->unk0;
  for (j = 0; j < height; j++) {
    rptr = (u8 *)locked->data + (j * locked->pitch);
    for (i = 0; i < width; i++) {
      *wptr++ = *rptr++;
    }
  }
  al_unlock_bitmap(bitmap);
  al_destroy_bitmap(bitmap);

  //FUN_03A750_800746c0_twentyliner(&D_273A00, arg0->unk4, IMG_UNKNOWN_0X49AFAC);
  bitmap = al_load_bitmap_flags(config_setting_get_string_elem(images, IMG_UNKNOWN_0X49AFAC), ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  if (bitmap == NULL) {
    return;
  }
  width = al_get_bitmap_width(bitmap);
  height = al_get_bitmap_height(bitmap);
  locked = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_BGR_888, ALLEGRO_LOCK_READONLY);
  rgbptr = arg0->unk4;
  for (j = 0; j < height; j++) {
    rptr = (u8 *)locked->data + (j * locked->pitch);
    cptr = (RGB *)rptr;
    for (i = 0; i < width; i++) {
      *rgbptr++ = *cptr++;
    }
  }
  al_unlock_bitmap(bitmap);
  al_destroy_bitmap(bitmap);

  //FUN_03A750_800746c0_twentyliner(&D_273A00, sp4C, IMG_UNKNOWN_0X49B274);
  bitmap = al_load_bitmap_flags(config_setting_get_string_elem(images, IMG_UNKNOWN_0X49B274), ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  if (bitmap == NULL) {
    return;
  }
  width = al_get_bitmap_width(bitmap);
  height = al_get_bitmap_height(bitmap);
  locked = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_SINGLE_CHANNEL_8, ALLEGRO_LOCK_READONLY);
  wptr = sp4C;
  for (j = 0; j < height; j++) {
    rptr = (u8 *)locked->data + (j * locked->pitch);
    for (i = 0; i < width; i++) {
      *wptr++ = *rptr++;
    }
  }
  al_unlock_bitmap(bitmap);
  al_destroy_bitmap(bitmap);

  //FUN_03A750_800746c0_twentyliner(&D_273A00, arg0->unkC, IMG_UNKNOWN_0X4A1C4C);
  bitmap = al_load_bitmap_flags(config_setting_get_string_elem(images, IMG_UNKNOWN_0X4A1C4C), ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  if (bitmap == NULL) {
    return;
  }
  width = al_get_bitmap_width(bitmap);
  height = al_get_bitmap_height(bitmap);
  locked = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_SINGLE_CHANNEL_8, ALLEGRO_LOCK_READONLY);
  wptr = arg0->unkC;
  for (j = 0; j < height; j++) {
    rptr = (u8 *)locked->data + (j * locked->pitch);
    for (i = 0; i < width; i++) {
      *wptr++ = *rptr++;
    }
  }
  al_unlock_bitmap(bitmap);
  al_destroy_bitmap(bitmap);

  //FUN_03A750_800746c0_twentyliner(&D_273A00, arg0->unk10, IMG_UNKNOWN_0X4A3BBC);
  bitmap = al_load_bitmap_flags(config_setting_get_string_elem(images, IMG_UNKNOWN_0X4A3BBC), ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  if (bitmap == NULL) {
    return;
  }
  width = al_get_bitmap_width(bitmap);
  height = al_get_bitmap_height(bitmap);
  locked = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_BGR_888, ALLEGRO_LOCK_READONLY);
  rgbptr = arg0->unk10;
  for (j = 0; j < height; j++) {
    rptr = (u8 *)locked->data + (j * locked->pitch);
    cptr = (RGB *)rptr;
    for (i = 0; i < width; i++) {
      *rgbptr++ = *cptr++;
    }
  }
  al_unlock_bitmap(bitmap);
  al_destroy_bitmap(bitmap);

  var_s3 = sp4C;
  var_s2 = arg0->unk8;
  for (j = 0; j < 149; j++) {
    for (i = 0; i < 199; i++) {
      // calculate gradient
      var_s2->y = var_s3[0] - var_s3[200];
      var_s2->x = var_s3[0] - var_s3[1];
      var_s2++;
      var_s3++;
    }
    var_s2->y = 0;
    var_s2->x = 0;
    var_s2++;
    var_s3++;
  }
  n64HeapUnalloc(sp4C);

  palInfo_1.unk4 = 0;
  palInfo_1.num_entries = 256;
  palInfo_1.pal = arg0->unk4;

  palInfo_2.unk4 = 0;
  palInfo_2.num_entries = 256;
  palInfo_2.pal = arg0->unk10;

  arg0->unk1C.unk8.unk8 = 0;
  arg0->unk1C.unk8.unk9 = 2;
  func_80075480(&arg0->unk1C.unk8, &palInfo_1, &palInfo_2);
  func_80075830(&arg0->unk1C);
  func_80075760(&arg0->unk1C, 1);
  func_800757BC(&arg0->unk1C, arg0->unkC, 128, 128);

  arg0->unk7C = 0;
  arg0->unk7E = 0;
  arg0->unk80 = 0;
}

void FUN_046770_8008074c_nineliner_calls_9funcs_warg0_elems(UnkStruct_12 *arg0) {
  func_800756A8(&arg0->unk1C.unk8);
  n64HeapUnalloc(arg0->unk8);
  n64HeapUnalloc(arg0->unk14[0]);
  n64HeapUnalloc(arg0->unk14[1]);
  al_destroy_bitmap(img);
  n64HeapUnalloc(arg0->unk4);
  n64HeapUnalloc(arg0->unk0);
  n64HeapUnalloc(arg0->unkC);
  n64HeapUnalloc(arg0->unk10);
  func_80075870(&arg0->unk1C);
}

void FUN_046770_8008080c_threeliner_sets_arg0(UnkStruct_12 *arg0, s32 arg1) {
  arg0->unk7C += arg1 * 129;
  arg0->unk7E += arg1 * 53;
  arg0->unk80 += arg1 * 17;
}

void FUN_046770_magic_150_is_it_ultra_related(UnkStruct_12 *arg0) {
  register UnkStruct_24 *temp_s0;
  register u16 *temp_s1;
  register s32 temp_s2;
  register s32 temp_s3;
  register s32 temp_s4;

  temp_s0 = &arg0->unk1C.unk14;

  temp_s1 = arg0->unk14[draw_buffer];
  *temp_s1++ = 200;
  *temp_s1++ = 150;
  *temp_s1++ = 0;
  *temp_s1++ = 0;

  temp_s0->unk4 = temp_s1;

  temp_s2 = sins(arg0->unk7C) << 7;
  temp_s3 = coss(arg0->unk7E) << 7;
  temp_s4 = (sins(arg0->unk80) << 7) + 0xF00000;
  //temp_s4 = (sins(arg0->unk80) << 7) + 0x2400000;  // try this

  temp_s2 += temp_s3 >> 1;

  temp_s0->unk24[0].unk0 = temp_s2;
  temp_s0->unk24[0].unk4 = temp_s3;

  temp_s0->unk24[1].unk0 = temp_s2 + temp_s4;
  temp_s0->unk24[1].unk4 = temp_s3;

  temp_s0->unk24[2].unk4 = temp_s3 + temp_s4;
  temp_s0->unk24[2].unk0 = temp_s2;

  temp_s0->unk24[3].unk0 = (temp_s2 + temp_s4) >> 1;
  temp_s0->unk24[3].unk4 = temp_s3 + (temp_s4 / 2);

  func_80075700(temp_s0, 200, 150, 2);
  temp_s0->unk8 = arg0->unk0;
  temp_s0->unk0 = arg0->unk8;
  arg0->unk1C.unk58(&arg0->unk1C);

  ALLEGRO_LOCKED_REGION *locked;
  u8 *ptr;
  u16 *cptr;
  u16 *p_val = temp_s1;

  locked = al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_RGBA_5551, ALLEGRO_LOCK_WRITEONLY);
  for (int j = 0; j < 150; j++) {
    ptr = (u8 *)locked->data + (j * locked->pitch);
    cptr = (u16 *)ptr;

    for (int i = 0; i < 200; i++, p_val++, cptr++) {
      *cptr = *p_val;
    }
  }
  al_unlock_bitmap(img);

  gDPSetScissor(g_gdl++, G_SC_NON_INTERLACE, 0, 0, 399, 299);

  func_8005BBFC(&g_gdl);
  /*
  weird_lots_of_magic_number_setting_66xrefs(&g_gdl, arg0->unk14[draw_buffer], NULL, 103, 70, 0xFF, 0xFF, 0xFF, 0xFF);
  */
  weird_lots_of_magic_number_setting_66xrefs(&g_gdl, img, NULL, 103, 70, 0xFF, 0xFF, 0xFF, 0xFF);
  func_8005BE40(&g_gdl);
}
