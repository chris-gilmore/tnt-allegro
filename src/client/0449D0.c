#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

extern config_t g_images_cfg;

////////////////////////////////////////

static f32 D_801201E0;
static f32 D_801201E4;

// fade to black
u8 func_8007E750(void) {
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
      return TRUE;
    }

    return FALSE;
  }

  return TRUE;
}

void func_8007E9F8(f32 arg0) {
  D_801201E0 = 1.0 / arg0;
  D_801201E4 = 0;
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
