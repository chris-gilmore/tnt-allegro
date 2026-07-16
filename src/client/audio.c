#include "common.h"

extern int verbose_flag;

////////////////////////////////////////

SongPlayer g_songPlayer;

void Audio_InitAudio(void) {
  if (verbose_flag) {
    printf("-- Audio_InitAudio\n");
  }
}

// change song
void Audio_80084e20_twentyliner(s32 song, SongPlayer *arg1, u8 arg2) {
  if (verbose_flag) {
    printf("-- Audio_80084e20_twentyliner\n");
  }
}

void Audio_UnloadSFX(void) {
  if (verbose_flag) {
    printf("-- Audio_UnloadSFX\n");
  }
}

void Audio_LoadSFX(SfxBank *bank) {
  if (verbose_flag) {
    printf("-- Audio_LoadSFX\n");
  }
}
