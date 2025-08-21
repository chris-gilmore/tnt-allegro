#include "common.h"

extern u16 draw_buffer;

////////////////////////////////////////

s32 D_80129030;
s32 D_80129034;
s32 D_80129038;
s32 D_8012903C;
static Mtx D_80129040[2];
static u16 D_801290C0;

static u8 D_800D3E50[64] = {
  0x05, 0x05, 0x05, 0x05, 0x15, 0x15, 0x15, 0x15,
  0x25, 0x25, 0x25, 0x25, 0x35, 0x35, 0x35, 0x35,
  0x45, 0x45, 0x45, 0x45, 0x55, 0x55, 0x55, 0x55,
  0x65, 0x65, 0x65, 0x65, 0x75, 0x75, 0x75, 0x75,
  0x85, 0x85, 0x85, 0x85, 0x95, 0x95, 0x95, 0x95,
  0xA5, 0xA5, 0xA5, 0xA5, 0xB5, 0xB5, 0xB5, 0xB5,
  0xC5, 0xC5, 0xC5, 0xC5, 0xD5, 0xD5, 0xD5, 0xD5,
  0xE5, 0xE5, 0xE5, 0xE5, 0xF5, 0xF5, 0xF5, 0xF5
};
static u8 D_800D3E90[64] = {
  0x05, 0x25, 0x45, 0x65, 0x85, 0xA5, 0xC5, 0xE5,
  0x05, 0x25, 0x45, 0x65, 0x85, 0xA5, 0xC5, 0xE5,
  0x05, 0x25, 0x45, 0x65, 0x85, 0xA5, 0xC5, 0xE5,
  0x05, 0x25, 0x45, 0x65, 0x85, 0xA5, 0xC5, 0xE5,
  0x15, 0x35, 0x55, 0x75, 0x95, 0xB5, 0xD5, 0xF5,
  0x15, 0x35, 0x55, 0x75, 0x95, 0xB5, 0xD5, 0xF5,
  0x15, 0x35, 0x55, 0x75, 0x95, 0xB5, 0xD5, 0xF5,
  0x15, 0x35, 0x55, 0x75, 0x95, 0xB5, 0xD5, 0xF5
};
static u8 D_800D3ED0[64] = {
  0x04, 0x14, 0x14, 0x14, 0x45, 0x45, 0x45, 0x45,
  0x04, 0x04, 0x14, 0x34, 0x55, 0x55, 0x55, 0x55,
  0x04, 0x24, 0x34, 0x34, 0x60, 0x60, 0x60, 0x70,
  0x24, 0x24, 0x24, 0x34, 0x60, 0x70, 0x70, 0x70,
  0x85, 0x96, 0x96, 0xB1, 0xC5, 0xF3, 0xE0, 0xE0,
  0x85, 0x96, 0x96, 0xB1, 0xC5, 0xF3, 0xF3, 0xE0,
  0x85, 0xA1, 0xB1, 0xB1, 0xC5, 0xD1, 0xF3, 0xE0,
  0x85, 0xA1, 0xA1, 0xA1, 0xC5, 0xD1, 0xD1, 0xD1
};

static Vp D_800D3F10 = {
  {
    { 800, 600, 511, 0 },
    { 800, 600, 511, 0 }
  }
};

/*
static Gfx D_800D3F20[] = {
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPPipelineMode(G_PM_1PRIMITIVE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 400, 300),
  gsDPSetTextureLOD(G_TL_TILE),
  gsDPSetTextureLUT(G_TT_NONE),
  gsDPSetTextureDetail(G_TD_CLAMP),
  gsDPSetTexturePersp(G_TP_PERSP),
  gsDPSetTextureFilter(G_TF_BILERP),
  gsDPSetTextureConvert(G_TC_FILT),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetCombineKey(G_CK_NONE),
  gsDPSetAlphaCompare(G_AC_NONE),
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetColorDither(G_CD_DISABLE),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};
*/

static f32 D_800D3FA0 = -100;
static f32 D_800D3FA4 = 900;
static f32 D_800D3FA8 = 110;
static f32 D_800D3FAC = -710;

static void   func_8009D940(u8);
static void   func_8009D948(UnkStruct_78 *, u8);
static void   func_8009DBEC(u8 *, UnkStruct_78 *);
static void   func_8009DE40(UnkStruct_78 *, u8);
static void   func_8009DFF8(UnkStruct_78 *);
static void   func_8009E44C(UnkStruct_78 *, u8, u8);
static void   func_8009EED4(UnkStruct_78 *, u8);
static void   func_8009F3A8(UnkStruct_78 *, u8, s32, f32, f32, f32, f32, f32, f32, u8);
static void   func_8009FF08(UnkStruct_78 *, u8);

static void func_8009D940(u8 arg0) {
}

static void func_8009D948(UnkStruct_78 *arg0, u8 arg1) {
  s32 spC;  // x
  s32 sp8;  // y
  register Vtx *temp_a2 = arg0->unk12C;
  u8 sp3;
  u8 sp2;
  u8 sp1;
  u8 sp0;

  sp3 = arg0->unk130[arg1].unk0[0];
  sp2 = arg0->unk130[arg1].unk0[1];
  sp1 = arg0->unk130[arg1].unk0[2];
  sp0 = arg0->unk130[arg1].unk0[3];

  spC = temp_a2[sp3 * 8].v.ob[0];
  spC += temp_a2[sp3 * 8 + 1].v.ob[0];
  spC += temp_a2[sp2 * 8].v.ob[0];
  spC += temp_a2[sp2 * 8 + 1].v.ob[0];
  spC += temp_a2[sp1 * 8].v.ob[0];
  spC += temp_a2[sp1 * 8 + 1].v.ob[0];
  spC += temp_a2[sp0 * 8].v.ob[0];
  spC += temp_a2[sp0 * 8 + 1].v.ob[0];

  sp8 = temp_a2[sp3 * 8].v.ob[1];
  sp8 += temp_a2[sp3 * 8 + 1].v.ob[1];
  sp8 += temp_a2[sp2 * 8].v.ob[1];
  sp8 += temp_a2[sp2 * 8 + 1].v.ob[1];
  sp8 += temp_a2[sp1 * 8].v.ob[1];
  sp8 += temp_a2[sp1 * 8 + 1].v.ob[1];
  sp8 += temp_a2[sp0 * 8].v.ob[1];
  sp8 += temp_a2[sp0 * 8 + 1].v.ob[1];

  spC >>= 3;
  sp8 >>= 3;
  arg0->unk130[arg1].unk4 = spC;
  arg0->unk130[arg1].unk8 = sp8;
  arg0->unk130[arg1].unkC = 0;
}

static void func_8009DBEC(u8 *arg0, UnkStruct_78 *arg1) {
  s32 i;
  s32 j;
  u8 sp1F;
  u8 sp1E;

  for (i = 0; i < 16; i++) {
    arg1->unk130[i].unk0[0] = 0xFF;
    arg1->unk130[i].unk0[1] = 0xFF;
    arg1->unk130[i].unk0[2] = 0xFF;
    arg1->unk130[i].unk0[3] = 0xFF;
  }

  for (i = 0; i < 64; i++) {
    sp1E = arg0[i] & 0xF;
    sp1F = (arg0[i] >> 4) & 0xF;

    for (j = 0; j < 4; j++) {
      if (arg1->unk130[sp1F].unk0[j] == 0xFF) {
        arg1->unk130[sp1F].unk0[j] = i;
        arg1->unk130[sp1F].unk1A8 = sp1E;
        break;
      }
    }
  }

  for (i = 0; i < 16; i++) {
    func_8009D948(arg1, i);
    func_8009DE40(arg1, i);
  }
}

void func_8009DDF4(UnkStruct_78 *arg0) {
  s32 i = 0;

  for (i = 0; i < 16; i++) {
    func_8009DE40(arg0, i);
  }
}

static void func_8009DE40(UnkStruct_78 *arg0, u8 arg1) {
  arg0->unk130[arg1].unk10 = 0;
  arg0->unk130[arg1].unk14 = 0;
  arg0->unk130[arg1].unk18 = 0;
  arg0->unk130[arg1].unk1C = 0;
  arg0->unk130[arg1].unk20 = 0;
  arg0->unk130[arg1].unk24 = 0;
  arg0->unk130[arg1].unk1AC = 0;
  arg0->unk130[arg1].unk1B4 = 0;
  arg0->unk130[arg1].unk1B0 = 0;
  arg0->unk130[arg1].unk1B8 = 0;
  arg0->unk130[arg1].unk1BC = 0;
  arg0->unk130[arg1].unk1C4 = 1;
}

static void func_8009DFF8(UnkStruct_78 *arg0) {
  register Vtx *temp_a1 = arg0->unk12C;
  s32 sp10;
  s32 spC;
  s32 i;
  s32 sp4 = 64;

  for (i = 0; i < sp4; i++) {
    spC = i / 8;
    sp10 = i % 8;

    temp_a1[i * 8].v.ob[0] = (sp10 * 100) - 400;
    temp_a1[i * 8].v.ob[1] = (spC * 100) - 400;
    temp_a1[i * 8].v.ob[2] = 0;

    temp_a1[i * 8 + 1].v.ob[0] = (sp10 * 100) - 300;
    temp_a1[i * 8 + 1].v.ob[1] = (spC * 100) - 400;
    temp_a1[i * 8 + 1].v.ob[2] = 0;

    temp_a1[i * 8 + 2].v.ob[0] = (sp10 * 100) - 300;
    temp_a1[i * 8 + 2].v.ob[1] = (spC * 100) - 300;
    temp_a1[i * 8 + 2].v.ob[2] = 0;

    temp_a1[i * 8 + 3].v.ob[0] = (sp10 * 100) - 400;
    temp_a1[i * 8 + 3].v.ob[1] = (spC * 100) - 300;
    temp_a1[i * 8 + 3].v.ob[2] = 0;

    temp_a1[i * 8].v.flag = 0;
    temp_a1[i * 8].v.tc[0] = (s16) (D_80129038 * sp10) << 6;
    temp_a1[i * 8].v.tc[1] = (s16) (D_8012903C * spC) << 6;

    temp_a1[i * 8 + 1].v.flag = 0;
    temp_a1[i * 8 + 1].v.tc[0] = (s16) ((sp10 + 1) * D_80129038) << 6;
    temp_a1[i * 8 + 1].v.tc[1] = (s16) (D_8012903C * spC) << 6;

    temp_a1[i * 8 + 2].v.flag = 0;
    temp_a1[i * 8 + 2].v.tc[0] = (s16) ((sp10 + 1) * D_80129038) << 6;
    temp_a1[i * 8 + 2].v.tc[1] = (s16) ((spC + 1) * D_8012903C) << 6;

    temp_a1[i * 8 + 3].v.flag = 0;
    temp_a1[i * 8 + 3].v.tc[0] = (s16) (D_80129038 * sp10) << 6;
    temp_a1[i * 8 + 3].v.tc[1] = (s16) ((spC + 1) * D_8012903C) << 6;
  }
}

static void func_8009E44C(UnkStruct_78 *arg0, u8 arg1, u8 arg2) {
  printf("-- func_8009E44C\n");
}

static void func_8009EED4(UnkStruct_78 *arg0, u8 arg1) {
  //printf("-- func_8009EED4 : %d\n", arg1);
}

void func_8009F2DC(UnkStruct_78 *arg0) {
  arg0->unk12C = n64HeapAlloc(64 * 8 * sizeof(Vtx));
  arg0->unk130 = n64HeapAlloc(16 * sizeof(UnkStruct_81));
  func_8009DFF8(arg0);
  func_8009DBEC(D_800D3ED0, arg0);
}

void func_8009F338(UnkStruct_78 *arg0) {
  if (arg0->unk12C != NULL) {
    n64HeapUnalloc(arg0->unk12C);
    arg0->unk12C = NULL;
  }
  if (arg0->unk130 != NULL) {
    n64HeapUnalloc(arg0->unk130);
    arg0->unk130 = NULL;
  }
}

static void func_8009F3A8(UnkStruct_78 *arg0, u8 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9) {
  arg0->unk130[arg1].unk1BC = arg8;
  arg0->unk130[arg1].unk1B8 = arg7;
  arg0->unk130[arg1].unk1C0 = arg2;
  arg0->unk130[arg1].unk1AC = arg3;
  arg0->unk130[arg1].unk1B0 = arg4;
  arg0->unk130[arg1].unk1B4 = arg5;
  arg0->unk130[arg1].unk1C = 0;
  arg0->unk130[arg1].unk20 = 0;
  arg0->unk130[arg1].unk24 = 0;
  arg0->unk128 = arg6;
  arg0->unk114 = 0;
  arg0->unk130[arg1].unk1C4 = 0;
  arg0->unk130[arg1].unk1C8 = arg9;
}

void func_8009F544(UnkStruct_78 *arg0) {
  func_8009F3A8(arg0, 0xE,  1, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0xF,  2, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0xA,  3, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0xB,  4, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0xC,  5, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0xD,  6, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x8,  7, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x9,  8, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0 - 5, 3);
  func_8009F3A8(arg0, 0x6,  9, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x7, 10, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x1, 11, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x0, 12, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x2, 13, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x3, 14, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x4, 15, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
  func_8009F3A8(arg0, 0x5, 16, 0, 0, 0, D_800D3FA4, 0, D_800D3FA0, 3);
}

void func_8009FA2C(UnkStruct_78 *arg0) {
  func_8009F3A8(arg0, 0xA,  1, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x8,  3, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0xD,  2, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0xC,  5, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0xB,  8, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0xF, 10, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0xE, 11, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x9, 11, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x2, 13, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x7, 14, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x3, 16, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x6, 17, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x0, 17, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x5, 19, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x1, 20, 0, 0, 0, 0, -900, D_800D3FA8, 2);
  func_8009F3A8(arg0, 0x4, 21, 0, 0, 0, 0, -900, D_800D3FA8, 2);
}

static void func_8009FF08(UnkStruct_78 *arg0, u8 arg1) {
  register UnkStruct_81 *temp_s0 = arg0->unk130 + arg1;
  register f32 var_fs0;
  register f32 var_fs1;

  if (temp_s0->unk1BC == 0) {
    return;
  }

  if (temp_s0->unk1C0 != 0) {
    temp_s0->unk1C0--;
    return;
  }

  if (temp_s0->unk1C8 == 3) {
    if (temp_s0->unk1B8 >= 0) {
      var_fs1 = temp_s0->unk1B8;
    } else {
      var_fs1 = -temp_s0->unk1B8;
    }

    if (arg0->unk128 >= 0) {
      var_fs0 = arg0->unk128;
    } else {
      var_fs0 = -arg0->unk128;
    }

    if (var_fs0 <= var_fs1) {
      temp_s0->unk1C4 = 1;
      temp_s0->unk1BC = 0;
    }
  } else {
    if ((temp_s0->unk1B8 + temp_s0->unk1BC) >= arg0->unk128) {
      temp_s0->unk1BC = arg0->unk128 - temp_s0->unk1B8;
    }

    if (temp_s0->unk1B8 >= arg0->unk128) {
      temp_s0->unk1C4 = 1;
      temp_s0->unk1BC = 0;
      temp_s0->unk1B8 = arg0->unk128;
      Audio2_Play_SFX(&D_801235B0, &D_800D3988, 0);
    }
  }

  temp_s0->unk1B8 += temp_s0->unk1BC;

  if ((temp_s0->unk1AC != 0) || (temp_s0->unk1B0 != 0) || (temp_s0->unk1B4 != 0)) {
    temp_s0->unk1C += temp_s0->unk1AC;
    temp_s0->unk20 += temp_s0->unk1B0;
    temp_s0->unk24 += temp_s0->unk1B4;
    if (((s32) temp_s0->unk1C % 360) == 0) {
      temp_s0->unk1AC = 0;
    }
    if (((s32) temp_s0->unk20 % 360) == 0) {
      temp_s0->unk1B0 = 0;
    }
    if (((s32) temp_s0->unk24 % 360) == 0) {
      temp_s0->unk1B4 = 0;
    }
  }
}

void func_800A0228(UnkStruct_78 *arg0) {
  register s32 i;
  Mtx sp48;

  /*
  guLookAt(&sp48, 0, 0, D_800D3FAC, 0, 0, 0, 0, -1, 0);
  gSPPerspNormalize(g_gdl++, D_801290C0);
  guPerspective(&D_80129040[draw_buffer], &D_801290C0, 59, 1, 1, 1500, 1);
  guMtxCatL(&sp48, &D_80129040[draw_buffer], &D_80129040[draw_buffer]);
  gSPViewport(g_gdl++, &D_800D3F10);
  gSPMatrix(g_gdl++, &D_80129040[draw_buffer], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  */

  if (TRUE) {
    s32 sp38 = 0;

    for (i = 0; i < 16; i++) {
      func_8009EED4(arg0, i);
      func_8009FF08(arg0, i);
    }

    if (arg0->unk114 == 0) {
      sp38 = 0;
      for (i = 0; i < 16; i++) {
        sp38 += arg0->unk130[i].unk1C4;
      }
      if (sp38 == 16) {
        arg0->unk114 = 1;
      }
    }
  }
}
