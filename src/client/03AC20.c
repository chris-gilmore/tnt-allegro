#include "common.h"
#include <allegro5/allegro5.h>

extern u16 draw_buffer;

////////////////////////////////////////

static ALLEGRO_BITMAP *img;

static void   func_800749A0(UnkStruct_33 *, s32, s32);
static void   func_80074B80(UnkStruct_33 *, u32, s32, s32);
static void   func_80074C80(UnkStruct_33 *, u32, s32, s32, u8 *);
static void   func_80074D7C(UnkStruct_30 *);
static void   func_80074E3C(UnkStruct_30 *);

static void func_800749A0(UnkStruct_33 *arg0, s32 arg1, s32 arg2) {
  register s16 temp_s0;
  register s32 temp_s1;

  temp_s0 = (FUN_026900_PRNG_1() % 120) + 0xF;
  arg0->unk12 = temp_s0;
  arg0->unk4 = (arg2 - 1) << 8;
  temp_s1 = (arg0->unk4 - (FUN_026900_PRNG_1() % (arg2 << 5)));
  arg0->unk6 = -temp_s1 / temp_s0;
  arg0->unk0 = (FUN_026900_PRNG_1() & 0xFF) << 8;
  arg0->unk2 = -arg0->unk0 / temp_s0;
  arg0->unk8 = FUN_026900_PRNG_1() & 0xFFFF;
  arg0->unkA = (FUN_026900_PRNG_1() & 0x3FF) - 0x200;
  arg0->unkC = FUN_026900_PRNG_1() % (arg1 * 120);
  arg0->unkE = -arg0->unkC / temp_s0;
  arg0->unk10 = (FUN_026900_PRNG_1() & 0x3F) - 0x1F;
}

static void func_80074B80(UnkStruct_33 *arg0, u32 arg1, s32 arg2, s32 arg3) {
  while (arg1 > 0) {
    arg0->unk0 += arg0->unk2;
    arg0->unkC += arg0->unkE;
    arg0->unk4 += arg0->unk6;
    arg0->unk8 += arg0->unkA;
    arg0->unk12--;
    if (arg0->unk12 == 0) {
      func_800749A0(arg0, arg2, arg3);
    }
    arg0++;
    arg1--;
  }
}

static void func_80074C80(UnkStruct_33 *arg0, u32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
  register s32 temp_s0 = 0;
  register s32 temp_t3;

  while (arg1 > 0) {
    temp_s0 = sins(arg0->unk8) * arg0->unkC;
    temp_s0 >>= 23;
    temp_s0 += arg2 >> 1;
    temp_t3 = arg0->unk4 >> 8;
    if ((temp_s0 < 0) || (temp_s0 >= arg2) || (temp_t3 < 0) || (temp_t3 >= arg3)) {
      return;
    }

    arg4[temp_s0 + (temp_t3 * arg2)] = arg0->unk0 >> 8;
    arg0++;
    arg1--;
  }
}

static void func_80074D7C(UnkStruct_30 *arg0) {
  register u8 *var_a1 = arg0->unkC[draw_buffer ^ 1] + 1;
  register u8 *var_a2 = arg0->unkC[draw_buffer] + 1;
  register s32 i;
  register s32 j;
  register s32 temp_t1 = arg0->unk14.width;
  register s32 var_t2;

  for (j = arg0->unk14.height - 1; j > 0; j--, var_a1 += 2, var_a2 += 2) {
    for (i = arg0->unk14.width - 2; i > 0; i--, var_a1++, var_a2++) {
      var_t2 = ((var_a1[temp_t1 - 1] + var_a1[temp_t1 + 1] + var_a1[temp_t1] + *var_a1) >> 2) - 4;
      if (var_t2 < 0) {
        var_t2 = 0;
      }
      *var_a2 = var_t2;
    }
  }
}

// unused
static void func_80074E3C(UnkStruct_30 *arg0) {
  register u8 *var_s0;
  register s32 i;

  var_s0 = arg0->unkC[draw_buffer ^ 1];
  var_s0 += arg0->unk14.width * (arg0->unk14.height - 1) + 1;
  for (i = arg0->unk14.width - 2; i > 0; i--, var_s0++) {
    *var_s0 = FUN_026900_PRNG_1() & 0xFF;
  }
}

void func_80074EC4(UnkStruct_30 *arg0) {
  func_80074D7C(arg0);
  func_80074B80(arg0->unk8, arg0->unk4, arg0->unk14.width, arg0->unk14.height);
  func_80074C80(arg0->unk8, arg0->unk4, arg0->unk14.width, arg0->unk14.height, arg0->unkC[draw_buffer]);
}

/*
  G_CC_BLENDPE - This mode is intended to be used with an intensity (I) texture.  It uses the intensity to interpolate between the environment color and primitive color.
  G_CC_BLENDPEDECALA - This mode is like G_CC_BLENDPE, except it uses the texture only as the alpha source.

  |   primitive color | 0xFF, 0x00, 0x00, 0xFF | red
  | environment color | 0xFF, 0xFF, 0x00, 0xFF | yellow
*/
void func_80074F3C(UnkStruct_30 *arg0) {
  ALLEGRO_LOCKED_REGION *locked;
  u8 *ptr;
  u32 *cptr;
  u8 *p_val = arg0->unkC[draw_buffer];

  locked = al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_RGBA_8888, ALLEGRO_LOCK_WRITEONLY);
  for (int j = 0; j < arg0->unk14.height; j++) {
    ptr = (u8 *)locked->data + (j * locked->pitch);
    cptr = (u32 *)ptr;

    for (int i = 0; i < arg0->unk14.width; i++, p_val++, cptr++) {
      /*
        interpolate between the environment color and primitive color,
        and premultiply alpha
        a = val
        rgb = (((val * env) + ((0xFF - val) * prim)) / 0xFF) * val / 0xFF
      */
      *cptr = *p_val << 24 | (*p_val * *p_val / 0xFF) << 16 | *p_val;
    }
  }
  al_unlock_bitmap(img);

  al_draw_bitmap_region(img, 0, 0, arg0->unk14.width, arg0->unk14.height - 3, arg0->unk0.x, arg0->unk0.y, 0);
}

void func_80075180(void) {
}

void func_800751C0(void) {
}

void func_80075218(UnkStruct_30 *arg0, s32 arg1, s32 arg2) {
  arg0->unk0.x = arg1 - (arg0->unk14.width >> 1);
  arg0->unk0.y = (arg2 - arg0->unk14.height) + 3;
}

u8 func_8007523C(UnkStruct_30 *arg0, UnkStruct_31 *arg1) {
  register s32 i;
  register UnkStruct_33 *var_s1;

  arg1->unk0.height += 3;
  arg0->unk14 = arg1->unk0;
  arg0->unk16 = arg0->unk14.width * arg0->unk14.height;
  arg0->unk18 = arg0->unk16;
  if (arg0->unk18 >= 0x1000) {
    return FALSE;
  }

  img = al_create_bitmap(arg0->unk14.width, arg0->unk14.height);

  arg0->unkC[0] = n64HeapAlloc(arg0->unk18);
  arg0->unkC[1] = n64HeapAlloc(arg0->unk18);
  bzero(arg0->unkC[0], arg0->unk18);
  bzero(arg0->unkC[1], arg0->unk18);
  arg0->unk4 = arg1->unk6;
  arg0->unk8 = n64HeapAlloc(arg0->unk4 * sizeof(UnkStruct_33));
  var_s1 = arg0->unk8;
  for (i = arg0->unk4; i > 0; i--) {
    func_800749A0(var_s1, arg0->unk14.width, arg0->unk14.height);
    var_s1++;
  }
  func_80075218(arg0, arg1->unk2.x, arg1->unk2.y);
  return TRUE;
}

void func_80075400(UnkStruct_30 *arg0) {
  n64HeapUnalloc(arg0->unk8);
  arg0->unk8 = NULL;
  n64HeapUnalloc(arg0->unkC[0]);
  n64HeapUnalloc(arg0->unkC[1]);
  arg0->unkC[0] = NULL;
  arg0->unkC[1] = NULL;

  al_destroy_bitmap(img);
  img = NULL;
}
