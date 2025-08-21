#include "common.h"

extern unsigned int game_id;

////////////////////////////////////////

extern s8 D_800CF838;

////////////////////////////////////////

Sram *g_sram_ptr;

PlayerNode D_800D2D80 = {
  { 'G', 'U', 'E', 'S', 'T', 0, 0, 0, 0 },
  { 0x20, 0x20 },
  0xE,
  NULL,
  &D_800D2D98,
  &D_800D2D98
};
PlayerNode D_800D2D98 = {
  { 'N', 'E', 'W', ' ', 'N', 'A', 'M', 'E', 0 },
  { 0x20, 0x20 },
  0xF,
  NULL,
  &D_800D2D80,
  &D_800D2D80
};
PlayerNode D_800D2DB0 = {
  { 'G', 'L', 'O', 'B', 'A', 'L', 0, 0, 0 },
  { 0x20, 0x20 },
  0x9,
  NULL,
  &D_800D2DB0,
  &D_800D2DB0
};
PlayerNode D_800D2DC8 = {
  { 0x20, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0 },
  0x5,
  NULL,
  &D_800D2DC8,
  &D_800D2DC8
};
PlayerNode D_800D2DE0 = {
  { 'C', 'H', 'O', 'O', 'S', 'E', 0, 0, 0 },
  { 0xFF, 0xFF },
  0x4,
  NULL,
  &D_800D2DE0,
  &D_800D2DE0
};

// /* 099078 800D2DF8 800D2D98 */ .word D_800D2D98

static u8 D_800D2DFC[30] = {
  3, 7, 10, 13, 17, 20, 23, 27, 30, 33,
  37, 40, 43, 47, 50, 53, 57, 60, 63, 67,
  70, 73, 77, 80, 83, 87, 90, 93, 97, 100
};

// calculating rank
u8 FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(Player *arg0) {
  s32 i;
  s32 lines_per_minute;

  if ((arg0->time_in_seconds != 0) && ((arg0->time_in_seconds / 60) != 0)) {
    lines_per_minute = arg0->lines / (f32) ((f32) arg0->time_in_seconds / 60.0);

    i = 0;
    do {
      if (lines_per_minute < D_800D2DFC[i]) {
        return i;
      }
    } while (++i < 30);

    return 29;
  }

  return 0;
}

// calculating rank, too
u8 FUN_SRAM_80078424_twelveliner_div60_loop_30t_b(u16 time_in_seconds, u16 lines) {
  s32 i;
  s32 lines_per_minute;

  if ((time_in_seconds != 0) && ((time_in_seconds / 60) != 0)) {
    lines_per_minute = lines / (f32) ((f32) time_in_seconds / 60.0);

    i = 0;
    do {
      if (lines_per_minute < D_800D2DFC[i]) {
        return i;
      }
    } while (++i < 30);

    return 29;
  }

  return 0;
}

PlayerNode *FUN_SRAM_8007868c_tenliner_loop_arg0_t(PlayerNode *arg0) {
  PlayerNode *sp1C;
  s32 sp18;

  sp18 = 0;
  sp1C = arg0;
  do {
    if (((sp1C->pack & 0xF) == 0xF) || ((sp1C->pack & 0xF) == 0xE) || ((sp1C->pack & 0xF) == 0xA) || ((sp1C->pack & 0xF) == 9) || ((sp1C->pack & 0xF) == 8) || ((sp1C->pack & 0xF) == 6) || ((sp1C->pack & 0xF) == 5) || ((sp1C->pack & 0xF) == 4) || ((sp1C->pack & 0xF) == 0xB)) {
      sp18++;
      if (sp18 == 100) {
        break;
      }
    } else {
      func_8007AEB0(sp1C);
    }

    sp1C = sp1C->next;
  } while (sp1C != arg0);

  return sp1C;
}

void FUN_SRAM_8007875c_check_gameover_conditions(Player *arg0, GameResults *arg1, u8 arg2) {
  printf("FUN_SRAM_8007875c_check_gameover_conditions()\n");
}

PlayerNode *func_8007AA5C(PlayerNode *arg0, PlayerNode *arg1) {
  PlayerNode *sp4;

  sp4 = arg0;
  do {
    if ((sp4->salt[0] == arg1->salt[0]) && (sp4->salt[1] == arg1->salt[1]) && (sp4->name[0] == arg1->name[0])) {
      return sp4;
    }
    sp4 = sp4->next;
  } while (sp4 != arg0);

  return NULL;
}

u8 func_8007AADC(u8 *arg0, u8 arg1, u8 arg2) {
  if ((arg0[6] == arg1) && (arg0[7] == arg2)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

PlayerNode *func_8007AEB0(PlayerNode *arg0) {
  PlayerNode *sp1C;

  if (((arg0->pack & 0xF) != 0xE) && ((arg0->pack & 0xF) != 0xF) && ((arg0->pack & 0xF) != 0xA) && ((arg0->pack & 0xF) != 5)) {
    arg0->last->next = arg0->next;

    if (arg0->next != NULL) {
      arg0->next->last = arg0->last;
    }

    sp1C = arg0->last;

    if (arg0->ptr != NULL) {
      n64HeapUnalloc(arg0->ptr);
      arg0->ptr = NULL;
    }

    n64HeapUnalloc(arg0);
    return sp1C;
  }

  return arg0;
}

void func_8007AF88(Player *arg0, u8 *arg1, s32 arg2) {
  printf("func_8007AF88()\n");
}

void func_8007B38C(PlayerNode *arg0) {
  rmonPrintf("Name: %s\n", arg0->name);
  rmonPrintf("Salt: %x %x\n", arg0->salt[0], arg0->salt[1]);
  rmonPrintf("Pack: %x\n", arg0->pack);
  rmonPrintf("Ptr: %x\n", arg0->ptr);
  rmonPrintf("Next: %x\n", arg0->next);
  rmonPrintf("Last: %x\n", arg0->last);
}

void func_8007B420(Player *arg0) {
  s32 unused;
}

void load_from_sram(u8 arg0) {
  register Sram *sram_ptr;

  if (arg0 == FALSE) {
    g_sram_ptr = (Sram *) n64HeapAlloc(0x1900);
    sram_ptr = g_sram_ptr;
    func_800AC1A8(sram_ptr, (void *)0x08000000, 0x1900);

    sram_ptr->music_mode = 1;
  }
  sram_ptr = g_sram_ptr;

  if (arg0 == TRUE) {
    sram_ptr->unk18F4 = game_id;
  }

  g_game.unkE4F8 = D_800CF838;
}

void func_8007C5CC(Sram *sram_ptr) {
  //sram_ptr->unk18F4 = osGetTime();
  sram_ptr->unk18F4 = game_id;
}
