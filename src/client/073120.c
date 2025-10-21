#include "common.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

static ALLEGRO_BITMAP *img;

static Gfx  *func_800AD2FC(Gfx *, UnkStruct_86 *, UnkStruct_32 *);

UnkStruct_86 *func_800ACEA0(u32 arg0, UnkStruct_44 *arg1) {
  UnkStruct_86 *sp2C;
  UnkStruct_87 *var_v0;
  Mtx *var_v1;
  s32 sp1C;
  u8 *ptr;
  s16 sc;
  s16 tc;

  sp1C = (sizeof(UnkStruct_86) + arg0 * sizeof(UnkStruct_87) + 0xF) & ~0xF;
  ptr = n64HeapAlloc(sp1C + arg0 * 2 * sizeof(Mtx));
  if (ptr == NULL) {
    return NULL;
  }

  int saved_flags = al_get_new_bitmap_flags();
  al_add_new_bitmap_flag(ALLEGRO_MAG_LINEAR);
  img = al_create_bitmap(16, 16);
  al_set_new_bitmap_flags(saved_flags);

  sp2C = (UnkStruct_86 *) ptr;
  sp2C->unkC0 = arg0;
  sp2C->unkC4 = (UnkStruct_87 *) (ptr + sizeof(UnkStruct_86));
  sp2C->unkC8 = 0;
  sp2C->unkCC = sp2C->unkC4;
  sp2C->unk11C = 0;

  if (arg1 == NULL) {
    sp2C->unkD0 = func_800B303C();
  } else {
    sp2C->unkD0 = arg1;
  }

  sp2C->unkD4 = 60;
  sp2C->unkDC = 1;
  sp2C->unkEC = 1;
  sp2C->unk104 = 0.5;
  sp2C->unk108 = 0.5;
  sp2C->unkD8 = 0;
  sp2C->unkE0 = 0;
  sp2C->unkE8 = 0;
  sp2C->unkF0 = 0;
  sp2C->unk10C = 16;
  sp2C->unk110 = 16;
  sp2C->unk114 = 0.995;
  sp2C->unk118 = 0;
  sp2C->unkF8 = 0;
  sp2C->unkFC = 0;
  sp2C->unk100 = 0;

  sc = sp2C->unkD0->unk8.unk2;
  tc = sp2C->unkD0->unk8.unk4;

  var_v1 = (Mtx *) (sp1C + ptr);
  var_v0 = sp2C->unkC4;

  sp2C->unk80[0].v.ob[0] = -256;
  sp2C->unk80[0].v.ob[1] = 256;
  sp2C->unk80[0].v.ob[2] = 0;
  sp2C->unk80[0].v.flag = 0;
  sp2C->unk80[0].v.tc[0] = 0;
  sp2C->unk80[0].v.tc[1] = 0;

  sp2C->unk80[1].v.ob[0] = 256;
  sp2C->unk80[1].v.ob[1] = 256;
  sp2C->unk80[1].v.ob[2] = 0;
  sp2C->unk80[1].v.flag = 0;
  sp2C->unk80[1].v.tc[0] = sc << 6;
  sp2C->unk80[1].v.tc[1] = 0;

  sp2C->unk80[2].v.ob[0] = 256;
  sp2C->unk80[2].v.ob[1] = -256;
  sp2C->unk80[2].v.ob[2] = 0;
  sp2C->unk80[2].v.flag = 0;
  sp2C->unk80[2].v.tc[0] = sc << 6;
  sp2C->unk80[2].v.tc[1] = tc << 6;

  sp2C->unk80[3].v.ob[0] = -256;
  sp2C->unk80[3].v.ob[1] = -256;
  sp2C->unk80[3].v.ob[2] = 0;
  sp2C->unk80[3].v.flag = 0;
  sp2C->unk80[3].v.tc[0] = 0;
  sp2C->unk80[3].v.tc[1] = tc << 6;

  for (sp1C = sp2C->unkC0; sp1C != 0; sp1C--, var_v0++) {
    var_v0->unk20[0] = var_v1++;
    var_v0->unk1C = -1;
    var_v0->unk0 = 1;
  }

  var_v0 = sp2C->unkC4;

  for (sp1C = sp2C->unkC0; sp1C != 0; sp1C--, var_v0++) {
    var_v0->unk20[1] = var_v1++;
  }

  return sp2C;
}

void func_800AD120(UnkStruct_86 *arg0) {
  n64HeapUnalloc(arg0);

  al_destroy_bitmap(img);
  img = NULL;
}

static Gfx *func_800AD2FC(Gfx *gdl, UnkStruct_86 *arg1, UnkStruct_32 *arg2) {
  UnkStruct_87 *var_s2;
  s32 var_s4;
  s32 sp11C;
  s32 var_s6;
  f32 temp_fs0;
  f32 temp_fs1;
  f32 var_fv0;
  f32 tmp;
  UnkStruct_84 spF8;
  UnkStruct_84 spE8;
  MtxF spA8;
  u8 r, g, b, a;

  if (arg1->unk118 & 0x4) {
    sp11C = 0;
  } else {
    sp11C = 1;
  }

  gdl = func_800A4B98(gdl, arg1->unkD0);
  if (arg2->unk0 & 0x100) {
    /*
    gSPDisplayList(gdl++, D_800D9248);
    */
  } else {
    /*
    gSPDisplayList(gdl++, D_800D9208);
    */
  }

  var_s2 = arg1->unkCC;
  var_s4 = arg1->unkC8;
  for (var_s6 = arg1->unkC0; var_s6 != 0; var_s6--) {
    if (var_s4 == 0) {
      var_s4 = arg1->unkC0;
      var_s2 = arg1->unkC4 + var_s4;
    }
    var_s2--;
    var_s4--;
    if (var_s2->unk1C != -1) {
      temp_fs0 = (f32) var_s2->unk1C / arg1->unkD4;
      temp_fs1 = 1.0 - temp_fs0;
      spA8 = arg2->unk4C;
      spA8.m30 = var_s2->unk4.x * 16;
      spA8.m31 = var_s2->unk4.y * 16;
      spA8.m32 = var_s2->unk4.z * 16;
      if (arg1->unk118 & 0x1) {
        var_fv0 = var_s2->unk0;
      } else {
        var_fv0 = (arg1->unk10C * temp_fs1) + (arg1->unk110 * temp_fs0);
      }
      var_fv0 *= 0.0625;
      spA8.m00 *= var_fv0;
      spA8.m10 *= var_fv0;
      spA8.m20 *= var_fv0;
      spA8.m01 *= var_fv0;
      spA8.m11 *= var_fv0;
      spA8.m21 *= var_fv0;
      spA8.m02 *= var_fv0;
      spA8.m12 *= var_fv0;
      spA8.m22 *= var_fv0;
      /*
      guMtxF2L((f32 (*)[4]) &spA8, var_s2->unk20[sp11C]);
      */
      spF8.unk0 = (arg1->unkD8 * temp_fs1) + (arg1->unkE8 * temp_fs0);
      spF8.unk4 = (arg1->unkDC * temp_fs1) + (arg1->unkEC * temp_fs0);
      spF8.unk8 = (arg1->unkE0 * temp_fs1) + (arg1->unkF0 * temp_fs0);
      func_800B11C4(&spF8, &spE8);

      tmp = (arg1->unk104 * temp_fs1) + (arg1->unk108 * temp_fs0);

      r = spE8.unk0 * 255.0;
      g = spE8.unk4 * 255.0;
      b = spE8.unk8 * 255.0;
      a = tmp * 255.0;


      ALLEGRO_TRANSFORM trans, backup;
      al_copy_transform(&backup, al_get_current_transform());

      memcpy(&trans, &spA8, sizeof(MtxF));
      al_use_transform(&trans);

      ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);
      ALLEGRO_VERTEX vtx[4] = {
        // x   y   z   u   v   color
        {  0,  0,  0,  0,  0,  white},
        {  0,  0,  0,  0,  0,  white},
        {  0,  0,  0,  0,  0,  white},
        {  0,  0,  0,  0,  0,  white}
      };
      static int indices[6] = {
        0, 1, 2,
        2, 3, 0
      };

      for (int i = 0; i < 4; i++) {
        vtx[i].x = arg1->unk80[i].v.ob[0];
        vtx[i].y = arg1->unk80[i].v.ob[1];
        vtx[i].u = arg1->unk80[i].v.tc[0] >> 6;
        vtx[i].v = arg1->unk80[i].v.tc[1] >> 6;
      }

      ALLEGRO_LOCKED_REGION *locked;
      u8 *ptr;
      u32 *cptr;
      u8 *p_val = (u8 *) arg1->unkD0->unk8.unkC;
      u8 alpha;

      locked = al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_RGBA_8888, ALLEGRO_LOCK_WRITEONLY);
      for (int j = 0; j < 16; j++) {
        ptr = (u8 *)locked->data + (j * locked->pitch);
        cptr = (u32 *)ptr;

        for (int i = 0; i < 16; i++, p_val++, cptr++) {
          alpha = (*p_val * a / 0xFF);
          *cptr = ((*p_val * r * alpha) / (0xFF * 0xFF)) << 24 | ((*p_val * g * alpha) / (0xFF * 0xFF)) << 16 | ((*p_val * b * alpha) / (0xFF * 0xFF)) << 8 | alpha;
        }
      }
      al_unlock_bitmap(img);

      al_draw_indexed_prim(vtx, NULL, img, indices, 6, ALLEGRO_PRIM_TRIANGLE_LIST);

      // restore transform
      al_use_transform(&backup);

      /*
      gSPMatrix(gdl++, var_s2->unk20[sp11C], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
      gDPPipeSync(gdl++);
      gDPSetPrimColor(gdl++, 0, 0, r, g, b, a);

      gSPVertex(gdl++, arg1->unk80, 4, 0);
      gSP1Triangle(gdl++, 0, 1, 2, 0);
      gSP1Triangle(gdl++, 2, 3, 0, 0);

      gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
      */
    }
  }
  arg1->unk118 ^= 0x4;

  return gdl;
}

Gfx *func_800AD970(Gfx *gdl, UnkStruct_86 *arg1, UnkStruct_32 *arg2) {
  /*
  gSPMatrix(gdl++, &D_800D9110, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  */

  return func_800AD2FC(gdl, arg1, arg2);
}
