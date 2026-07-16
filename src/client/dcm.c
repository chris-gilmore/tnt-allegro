#include "common.h"

extern int verbose_flag;

////////////////////////////////////////

SfxPlayer D_801235B0;
SfxBank g_menuSfxBank;
SfxBank g_gameSfxBank;

// set music_level (volume)
void func_800875EC(u16 arg0, SongPlayer *arg1) {
  if (verbose_flag) {
    printf("-- dcm: func_800875EC\n");
  }
}

// set sfx_level (volume)
void Audio2_80087618_fourteenliner_loops_256t(u16 arg0) {
  if (verbose_flag) {
    printf("-- dcm: Audio2_80087618_fourteenliner_loops_256t\n");
  }
}

void Audio2_GFXDone_SendPlayMessage(SongPlayer *arg0) {
  if (verbose_flag) {
    printf("-- dcm: Audio2_GFXDone_SendPlayMessage\n");
  }
}

UnkStruct_95 *Audio2_Play_SFX(SfxPlayer *player, SfxBank *bank, u8 sfx_id) {
  if (verbose_flag) {
    printf("-- dcm: Audio2_Play_SFX, sfx_id = %d\n", sfx_id);
  }
}
