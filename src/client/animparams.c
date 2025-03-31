#include "common.h"

void func_8007635C(void) {}

void func_800763B4(void) {}

void func_800763EC(u32) {}

void func_8007641C(UnkStruct_14 *arg0, UnkStruct_23 *arg1) {
  arg1->unk0 = arg0->unk0.p.x * 0xA00 + 0x800000;
  arg1->unk4 = arg0->unk0.p.y * 0xA00 + 0x800000;
}
