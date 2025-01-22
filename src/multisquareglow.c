#include "common.h"

void MultisquareGlow_8006a740_thirtyfiveliner(UnkStruct_12 *arg0) {
  BoundingBox sp30;
  s16 sp2E;
  s16 sp2C;
  s16 sp2A;
  s16 sp28;
  s32 sp24;
  s32 sp20;
  u8 sp1F;

  CurrentPiece_80067c1c_fifteenliner_loops3times(g_currentPiece_ptr, &sp30);
  sp28 = sp30.x_max - 3;
  sp2A = sp30.y_max - 3;
  sp2C = sp30.x_min;
  sp2E = sp30.y_min;
  if (sp28 < 0) {
    sp28 = 0;
  }
  if (sp2C >= 7) {
    sp2C = 6;
  }
  if (sp2A < 0) {
    sp2A = 0;
  }
  if (sp2E >= 17) {
    sp2E = 0x10;
  }
  sp20 = sp2A;
  if (sp2E >= sp2A) {
  loop_9:
    sp24 = sp28;
    if (sp2C >= sp28) {
    loop_10:
      sp1F = Multisquares_Test4x4byType(sp24, sp20, g_currentPiece_ptr->pieceType);
      if (sp1F != 2) {
        sp24++;
        if (sp2C >= sp24) {
          goto loop_10;
        }
      }
    }
    if (sp1F != 2) {
      sp20++;
      if (sp2E >= sp20) {
        goto loop_9;
      }
    }
  }
  if (sp1F == 2) {
    Multisquare_8006a050_extralarge_manyloops_interesting(sp24, sp20, 2);
    Multisquare_8006a6f0_threeliner_sets_arg0_stuff(arg0);
    return;
  }
  sp20 = sp2A;
  if (sp2E >= sp2A) {
  loop_17:
    sp24 = sp28;
    if (sp2C >= sp28) {
    loop_18:
      sp1F = Multisquares_Test4x4byType(sp24, sp20, g_currentPiece_ptr->pieceType);
      if (sp1F != 1) {
        sp24++;
        if (sp2C >= sp24) {
          goto loop_18;
        }
      }
    }
    if (sp1F != 1) {
      sp20++;
      if (sp2E >= sp20) {
        goto loop_17;
      }
    }
  }
  if (sp1F == 1) {
    Multisquare_8006a050_extralarge_manyloops_interesting(sp24, sp20, 1);
    Multisquare_8006a6f0_threeliner_sets_arg0_stuff(arg0);
    return;
  }
  arg0->unk1 = 1;
}


void MultisquareGlow_8006a9bc_fiveliner_sets_arg0_struct(UnkStruct_12 *arg0) {
  if (arg0->unk2 == 0) {
    arg0->unk0 = 0;
    arg0->unk1 = 3;
    return;
  }

  arg0->unk1 = 0;
  arg0->unk2--;
}

void MultisquareGlow_8006a9f4_twentyliner_loops_t7_t17(UnkStruct_12 *arg0) {
  Cell *temp_s0;
  Cell *temp_s0_2;
  s32 var_s1;
  s32 var_s1_2;
  s32 var_s2;
  s32 var_s2_2;

  var_s2 = 0;
  if (0 < 0x11) {
    do {
      var_s1 = 0;
      if (0 < 7) {
        do {
          temp_s0 = g_boardPieces_ptr->cell_ptr_arr[var_s1 + (var_s2 * 0xA)];
          if ((temp_s0->piece_type != 7) && (temp_s0->square_id == 0xFF) && (Multisquare_8006a6bc_oneliner_calls_fun(temp_s0) == 2)) {
            Multisquare_8006a050_extralarge_manyloops_interesting(var_s1, var_s2, 2);
          }
          var_s1 += 1;
        } while (var_s1 < 7);
      }
      var_s2 += 1;
    } while (var_s2 < 0x11);
  }
  var_s2_2 = 0;
  if (0 < 0x11) {
    do {
      var_s1_2 = 0;
      if (0 < 7) {
        do {
          temp_s0_2 = g_boardPieces_ptr->cell_ptr_arr[var_s1_2 + (var_s2_2 * 0xA)];
          if ((temp_s0_2->piece_type != 7) && (temp_s0_2->square_id == 0xFF) && (Multisquare_8006a6bc_oneliner_calls_fun(temp_s0_2) == 1)) {
            Multisquare_8006a050_extralarge_manyloops_interesting(var_s1_2, var_s2_2, 1);
          }
          var_s1_2 += 1;
        } while (var_s1_2 < 7);
      }
      var_s2_2 += 1;
    } while (var_s2_2 < 0x11);
  }
  arg0->unk1 = 3;
}

u8 MultisquareGlow_isArg0_lessthan_44(u8 arg0) {
  if (arg0 < 44) {
    return 1;
  }

  return 0;
}

s32 MultisquareGlow_8006ac2c_loops_10_times(s32, s32) { return 0; }

u8 MultisquareGlow_8006ad0c_checks_1_2_3_4(void) {
  UnkStruct_12 *temp_s0;
  u8 temp_s1;

  temp_s0 = D_8011FBA0;
  temp_s1 = temp_s0->unk0;
  switch (temp_s1) {
  case 1:
    // either sets unk1 to 1 or leaves it alone
    MultisquareGlow_8006a740_thirtyfiveliner(temp_s0);
    break;
  case 2:
    // sets unk1 to either 2 or 0
    Multisquare_8006a708_fiveliner_sets_arg0_stuff(temp_s0);
    break;
  case 3:
    // sets unk1 to 3
    MultisquareGlow_8006a9f4_twentyliner_loops_t7_t17(temp_s0);
    break;
  case 4:
    // sets unk1 to either 3 or 0
    MultisquareGlow_8006a9bc_fiveliner_sets_arg0_struct(temp_s0);
    break;
  }
  return temp_s0->unk1;
}

void MultisquareGlow_8006ada4_Init2(void) {}
void MultisquareGlow_Deinit_doesnothing(void) {}
void Multisquares_UpdateGlows(UnkStruct_12 *, u32) {}
void Multisquares_RenderGlows(UnkStruct_12 *) {}
