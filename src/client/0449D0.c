#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

extern config_t g_images_cfg;

////////////////////////////////////////

static f32 D_801201E0;
static f32 D_801201E4;
static f32 D_801201E8;
static f32 D_801201EC;
static f32 D_801201F0;
static f32 D_801201F4;
static f32 D_801201F8;
static f32 D_801201FC;
static void *D_80120200;  // IMG_TETRIS_START
static void *D_80120204;  // IMG_TETRIS_START_PAL

// fade to black
s32 func_8007E750(void) {
  if (D_801201E4 <= 1.0) {
    /*
    gDPPipeSync(g_gdl++);
    gDPSetCycleType(g_gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g_gdl++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gDPSetRenderMode(g_gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(g_gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(g_gdl++, 0, 0, 0x00, 0x00, 0x00, D_801201E4 * 255);
    gDPFillRectangle(g_gdl++, 0, 0, 400, 300);
    gDPPipeSync(g_gdl++);
    */
    al_draw_filled_rectangle(0, 0, 400, 300, al_map_rgba(0, 0, 0, D_801201E4 * 255));

    D_801201E4 += D_801201E0 * frametime_delta();
    if (D_801201E4 >= 1.0) {
      return 1;
    }

    return 0;
  }

  return 1;
}

void func_8007E9F8(f32 arg0) {
  D_801201E0 = 1.0 / arg0;
  D_801201E4 = 0;
}

// fade from black
s32 func_8007EA2C(void) {
  if (D_801201EC >= 0.0) {
    /*
    gDPPipeSync(g_gdl++);
    gDPSetCycleType(g_gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g_gdl++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gDPSetRenderMode(g_gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(g_gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(g_gdl++, 0, 0, 0x00, 0x00, 0x00, D_801201EC * 255);
    gDPFillRectangle(g_gdl++, 0, 0, 400, 300);
    gDPPipeSync(g_gdl++);
    */
    al_draw_filled_rectangle(0, 0, 400, 300, al_map_rgba(0x00, 0x00, 0x00, D_801201EC * 255));

    D_801201EC -= D_801201E8 * frametime_delta();
    if (D_801201EC <= 0.0) {
      return 1;
    }

    return 0;
  }

  return 1;
}

void func_8007ECC8(f32 arg0) {
  D_801201E8 = 1.0 / arg0;
  D_801201EC = 1;
}

// fade to white
s32 func_8007ED00(void) {
  if (D_801201F4 <= 1.0) {
    /*
    gDPPipeSync(g_gdl++);
    gDPSetCycleType(g_gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g_gdl++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gDPSetRenderMode(g_gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(g_gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(g_gdl++, 0, 0, 0xFF, 0xFF, 0xFF, D_801201F4 * 255);
    gDPFillRectangle(g_gdl++, 0, 0, 400, 300);
    gDPPipeSync(g_gdl++);
    */
    al_draw_filled_rectangle(0, 0, 400, 300, al_map_rgba(0xFF, 0xFF, 0xFF, D_801201E4 * 255));

    D_801201F4 += D_801201F0 * frametime_delta();
    if (D_801201F4 >= 1.0) {
      return 1;
    }

    return 0;
  }

  return 1;
}

void func_8007EFB0(f32 arg0) {
  D_801201F0 = 1.0 / arg0;
  D_801201F4 = 0;
}

// fade from white
s32 func_8007EFE4(void) {
  if (D_801201FC >= 0.0) {
    /*
    gDPPipeSync(g_gdl++);
    gDPSetCycleType(g_gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g_gdl++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gDPSetRenderMode(g_gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(g_gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(g_gdl++, 0, 0, 0xFF, 0xFF, 0xFF, D_801201FC * 255);
    gDPFillRectangle(g_gdl++, 0, 0, 400, 300);
    gDPPipeSync(g_gdl++);
    */
    al_draw_filled_rectangle(0, 0, 400, 300, al_map_rgba(0xFF, 0xFF, 0xFF, D_801201FC * 255));

    D_801201FC -= D_801201F8 * frametime_delta();
    if (D_801201FC <= 0.0) {
      return 1;
    }

    return 0;
  }

  return 1;
}

void func_8007F288(f32 arg0) {
  D_801201F8 = 1.0 / arg0;
  D_801201FC = 1;
}

void func_8007F344(void) {
  printf("-- func_8007F344\n");
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
