#include "common.h"

// load asset from rom
void func_800ABFF0(void *devAddr, void *dramAddr, u32 len) {
  printf("-- func_800ABFF0\n");
}

// load from sram
u32 func_800AC1A8(void *dramAddr, void *devAddr, u32 len) {
  FILE *file = fopen("tnt.sra", "rb");
  if (file == NULL) {
    return 0;
  }
  len = fread(dramAddr, 1, len, file);
  fclose(file);
  return len;
}

// save to sram
u32 func_800AC22C(void *dramAddr, void *devAddr, u32 len) {
  FILE *file = fopen("tnt.sra", "wb");
  if (file == NULL) {
    return 0;
  }
  len = fwrite(dramAddr, 1, len, file);
  fclose(file);
  return len;
}
