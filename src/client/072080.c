#include "common.h"

// load asset from rom
void func_800ABFF0(void *devAddr, void *dramAddr, u32 len) {
  printf("-- func_800ABFF0\n");
}

// load from sram
u32 func_800AC1A8(void *dramAddr, void *devAddr, u32 len) {
  printf("-- func_800AC1A8\n");
}

// save to sram
u32 func_800AC22C(void *dramAddr, void *devAddr, u32 len) {
  printf("-- func_800AC22C\n");
}
