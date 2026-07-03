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

static s32 D_800D31D4 = 0;
static s32 D_800D31D8 = 2;  // TODO: change back to 0
static s32 D_800D31DC = 0;
static s32 D_800D31E0 = TRUE;
static s32 D_800D31E4 = 0;

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
    al_draw_filled_rectangle(0, 0, 400, 300, al_premul_rgba(0x00, 0x00, 0x00, D_801201E4 * 255));

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
    al_draw_filled_rectangle(0, 0, 400, 300, al_premul_rgba(0x00, 0x00, 0x00, D_801201EC * 255));

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
    al_draw_filled_rectangle(0, 0, 400, 300, al_premul_rgba(0xFF, 0xFF, 0xFF, D_801201F4 * 255));

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
    al_draw_filled_rectangle(0, 0, 400, 300, al_premul_rgba(0xFF, 0xFF, 0xFF, D_801201FC * 255));

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
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  /*
  switch (D_800D31DC) {
  case 1:
    if (D_800D31A0.unk0->unk6 >= 4) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_0);
      D_800D31DC = 2;
    }
    break;
  case 2:
    if (D_800D31A0.unk0->unk6 >= 816) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_1);
      D_800D31DC = 3;
    }
    break;
  case 3:
    if (D_800D31A0.unk0->unk6 >= 1067) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_2);
      D_800D31DC = 4;
    }
    break;
  case 4:
    if (D_800D31A0.unk0->unk6 >= 1272) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_3);
      D_800D31DC = 5;
    }
    break;
  case 5:
    if (D_800D31A0.unk0->unk6 >= 1605) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_4);
      D_800D31DC = 6;
    }
    break;
  case 6:
    if (D_800D31A0.unk0->unk6 >= 1885) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_5);
      D_800D31DC = 7;
    }
    break;
  case 7:
    if (D_800D31A0.unk0->unk6 >= 2060) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_6);
      D_800D31DC = 8;
    }
    break;
  case 8:
    if (D_800D31A0.unk0->unk6 >= 2733) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_7);
      D_800D31DC = 9;
    }
    break;
  case 9:
    if (D_800D31A0.unk0->unk6 >= 2789) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_8);  // (bug?) ropes falling, but can't be heard
      D_800D31DC = 10;
    }
    break;
  case 10:
    if (D_800D31A0.unk0->unk6 >= 2987) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_9);
      D_800D31DC = 11;
    }
    break;
  case 11:
    if (D_800D31A0.unk0->unk6 >= 3340) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_10);
      D_800D31DC = 12;
    }
    break;
  case 12:
    if (D_800D31A0.unk0->unk6 >= 3750) {
      Audio2_Play_SFX(&D_801235B0, &g_introSfxBank, SFX_INTRO_11);
      D_800D31DC = 13;
    }
    break;
  }

  if (D_800D31D8 == 0) {
    if (D_800D31E0) {
      func_8007F2C0();  // init
      D_800D31DC = 1;
      D_800D31E0 = FALSE;
    }

    // A_BUTTON / CONT_A || START_BUTTON / CONT_START
    if ((g_PV_arr[0].unk24 & 0x8000) || (g_PV_arr[0].unk24 & 0x1000) || (D_800D31A0.unk0->unk6 >= D_800D31D0)) {
      func_8007EFB0(20);
      D_800D31DC = 13;
      Audio2_GFXDone_SendStopMessage(&D_801235B0);
      D_800D31E0 = TRUE;
      D_800D31D8 = 1;
    }

    func_80077098(&D_800D31A0);  // render
  }

  if (D_800D31D8 == 1) {
    if (D_800D31E0) {
      D_800D31E0 = FALSE;
    } else {
      func_80077098(&D_800D31A0);  // render
    }

    if (func_8007ED00() == 1) {  // fade to white
      main_8004A34C_threeliner();
      func_8007F320();  // deinit
      D_800D31E0 = TRUE;
      D_800D31D8 = 2;
      return;
    }
  }
  */

  if ((D_800D31D8 == 2) && D_800D31E0) {
    main_8004A34C_threeliner();
    D_80120200 = al_load_bitmap(config_setting_get_string_elem(images, IMG_TETRIS_START));

    D_800D31E0 = TRUE;
    D_800D31D8 = 3;
    func_8007F288(20);
    func_8007EFE4();  // fade from white
    return;
  }

  if (D_800D31D8 == 3) {
    func_8005BBFC(&g_gdl);
    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_80120200, NULL, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8005BE40(&g_gdl);
    if (func_8007EFE4() == 1) {  // fade from white
      D_800D31D8 = 4;
      D_800D31E4 = 0;
    }
  }

  if (D_800D31D8 == 4) {
    // A_BUTTON / CONT_A || START_BUTTON / CONT_START
    if (((g_PV_arr[0].unk24 & 0x8000) && (D_800D31E4 >= 60)) || ((g_PV_arr[0].unk24 & 0x1000) && (D_800D31E4 >= 60)) || (D_800D31E4 >= 300)) {
      /*
      func_80060D58(1);
      */
      main_8004A34C_threeliner();
      al_destroy_bitmap(D_80120200);

      Audio_LoadSFX(&g_menuSfxBank);
      func_800905E8(0);
      D_800CFD48 = TRUE;
      /*
      func_80061134(400, 300);
      */
      D_800D31D8++;
      return;
    }

    func_8005BBFC(&g_gdl);
    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_80120200, NULL, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8005BE40(&g_gdl);
    D_800D31E4 += 1;
  }

  switch (D_800D31D8) {
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    D_800D31D8++;
    break;
  case 10:
    D_800D31E4 = 0;
    /*
    func_80060D58(0);
    */
    D_800CFEE8 = 4;
    D_800D31D8 = 0;
    D_800D31D4 = 1;
    break;
  }
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
