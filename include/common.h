#ifndef _COMMON_H_
#define	_COMMON_H_

typedef unsigned char       u8;     /* unsigned  8-bit */
typedef unsigned short      u16;    /* unsigned 16-bit */
typedef unsigned int        u32;    /* unsigned 32-bit */
typedef unsigned long long  u64;    /* unsigned 64-bit */

typedef signed char         s8;     /* signed  8-bit */
typedef short               s16;    /* signed 16-bit */
typedef int                 s32;    /* signed 32-bit */
typedef long long           s64;    /* signed 64-bit */

typedef float   f32;    /* single prec floating point */
typedef double  f64;    /* double prec floating point */

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL    (void *)0
#endif

typedef union {
  struct {
    u32 hi;
    u32 lo;
  } word;
  f64 d;
} du;

typedef union {
  u32 i;
  f32 f;
} fu;

extern u64 __ull_div(u64, u64);
extern u64 __ll_mul(u64, u64);


typedef struct {
  u16   button;
  s8    stick_x;  /* -80 <= stick_x <= 80 */
  s8    stick_y;  /* -80 <= stick_y <= 80 */
  //  u8    errno;
} OSContPad;

/* Buttons */

#define CONT_A      0x8000
#define CONT_B      0x4000
#define CONT_G      0x2000
#define CONT_START  0x1000
#define CONT_UP     0x0800
#define CONT_DOWN   0x0400
#define CONT_LEFT   0x0200
#define CONT_RIGHT  0x0100
#define CONT_L      0x0020
#define CONT_R      0x0010
#define CONT_E      0x0008
#define CONT_D      0x0004
#define CONT_C      0x0002
#define CONT_F      0x0001

/* Nintendo's official button names */

#define A_BUTTON        CONT_A
#define B_BUTTON        CONT_B
#define L_TRIG          CONT_L
#define R_TRIG          CONT_R
#define Z_TRIG          CONT_G
#define START_BUTTON    CONT_START
#define U_JPAD          CONT_UP
#define L_JPAD          CONT_LEFT
#define R_JPAD          CONT_RIGHT
#define D_JPAD          CONT_DOWN
#define U_CBUTTONS      CONT_E
#define L_CBUTTONS      CONT_C
#define R_CBUTTONS      CONT_F
#define D_CBUTTONS      CONT_D

typedef struct {
} OSViMode;

typedef struct {
} Vtx;

typedef struct {
} Gfx;

typedef void *OSMesg;

typedef struct {
} OSMesgQueue;

typedef struct {
} OSSched;

typedef struct {
} SuperThread;

typedef s32 OSId;
typedef s32 OSPri;

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include "rmon.h"
#include "os_time.h"
#include "os_cache.h"

#include "newtetris/img_defs.h"
#include "newtetris/anim_defs.h"
#include "newtetris/n64heap.h"
#include "newtetris/sprite.h"
#include "newtetris/contq.h"
#include "newtetris/026900.h"
#include "newtetris/026C80.h"
#include "newtetris/026F90.h"
#include "newtetris/0428D0.h"
#include "newtetris/cubetiles.h"
#include "newtetris/color.h"
#include "newtetris/piecedefs.h"
#include "newtetris/027BF0.h"
#include "newtetris/037700.h"
#include "newtetris/0449D0.h"
#include "newtetris/0497E0.h"
#include "newtetris/playervars.h"
#include "newtetris/033310.h"
#include "newtetris/0691B0.h"
#include "newtetris/006B30.h"
#include "newtetris/0073F0.h"
#include "newtetris/003E40.h"
#include "newtetris/boardinfo.h"
#include "newtetris/garbage.h"
#include "newtetris/landfill.h"
#include "newtetris/01D6E0.h"
#include "newtetris/gamefinish.h"
#include "newtetris/aiplayer.h"
#include "newtetris/0697D0.h"
#include "newtetris/00E440.h"
#include "newtetris/sram.h"
#include "newtetris/072080.h"
#include "newtetris/066700.h"
#include "newtetris/gamestats.h"
#include "newtetris/frametime.h"
#include "newtetris/bootmain.h"
#include "newtetris/credits.h"
#include "newtetris/009A90.h"
#include "newtetris/055500.h"
#include "newtetris/049380.h"
#include "newtetris/046DD0.h"
#include "newtetris/0279C0.h"
#include "newtetris/01B280.h"
#include "newtetris/00C680.h"
#include "newtetris/03B700.h"
//#include "newtetris/046770.h"
#include "newtetris/03C130.h"
#include "newtetris/gamevars.h"
#include "newtetris/03C220.h"
#include "newtetris/minos.h"
#include "newtetris/mobilepiece.h"
#include "newtetris/ghostpiece.h"
#include "newtetris/cube.h"
#include "newtetris/mobilecubes.h"
#include "newtetris/fallingcubes.h"
#include "newtetris/currentpiece.h"
#include "newtetris/ids.h"
#include "newtetris/boardpieces.h"
#include "newtetris/piecehold.h"
#include "newtetris/frameact.h"
#include "newtetris/bag63.h"
#include "newtetris/nextpieces.h"
#include "newtetris/multisquareglow.h"
#include "newtetris/multisquare.h"
#include "newtetris/0074E0.h"
#include "newtetris/board.h"
#include "newtetris/lineeffect.h"
#include "newtetris/linescan.h"
#include "newtetris/keyspin.h"
#include "newtetris/0379B0.h"
#include "newtetris/032F00.h"
#include "newtetris/010870.h"
#include "newtetris/audio.h"
#include "newtetris/imageparams.h"
#include "newtetris/animparams.h"
#include "newtetris/04BFD0.h"
#include "newtetris/pfgfx.h"
#include "newtetris/dbgprntrrl.h"
#include "newtetris/tetris.h"
#include "newtetris/game.h"
#include "newtetris/setplayer.h"

#endif /* !_COMMON_H_ */
