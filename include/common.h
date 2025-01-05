#ifndef _COMMON_H_
#define	_COMMON_H_

typedef unsigned char       u8;     /* unsigned  8-bit */
typedef unsigned short      u16;    /* unsigned 16-bit */
typedef unsigned long       u32;    /* unsigned 32-bit */
typedef unsigned long long  u64;    /* unsigned 64-bit */

typedef signed char         s8;     /* signed  8-bit */
typedef short               s16;    /* signed 16-bit */
typedef long                s32;    /* signed 32-bit */
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
#define NULL    0
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

extern u64   __ull_div(u64, u64);
extern u64   __ll_mul(u64, u64);


typedef struct {
  u16   button;
  s8    stick_x;  /* -80 <= stick_x <= 80 */
  s8    stick_y;  /* -80 <= stick_y <= 80 */
  //  u8    errno;
} OSContPad;

typedef struct {
} OSViMode;

typedef struct {
} Vtx;

typedef struct {
} Gfx;

typedef void *OSMesg;

#include "newtetris/n64heap.h"
#include "newtetris/sprite.h"
#include "newtetris/contq.h"
#include <math.h>
#include "newtetris/026900.h"
#include "newtetris/026C80.h"
#include "newtetris/026F90.h"
#include "newtetris/cubetiles.h"
#include "newtetris/color.h"
#include "newtetris/piecedefs.h"
#include <strings.h>
#include <stdio.h>
#include "newtetris/0497E0.h"
#include "newtetris/playervars.h"
#include "newtetris/gamevars.h"
#include "newtetris/033310.h"
#include "newtetris/minos.h"
#include "newtetris/mobilepiece.h"
#include "newtetris/ghostpiece.h"
#include "newtetris/003E40.h"
#include "newtetris/currentpiece.h"
#include "newtetris/piecehold.h"
#include "newtetris/boardinfo.h"
#include "newtetris/garbage.h"
#include "newtetris/landfill.h"
#include "newtetris/gamefinish.h"
#include "newtetris/aiplayer.h"
#include "newtetris/frameact.h"
#include "newtetris/cube.h"
#include "newtetris/ids.h"
#include "newtetris/0697D0.h"
#include "newtetris/boardpieces.h"
#include "newtetris/bag63.h"
#include "newtetris/nextpieces.h"
#include "newtetris/fallingcubes.h"
#include "newtetris/mobilecubes.h"
#include "newtetris/board.h"
#include "newtetris/keyspin.h"
#include "newtetris/multisquare.h"
#include "newtetris/lineeffect.h"
#include "newtetris/linescan.h"
#include "newtetris/01D6E0.h"
#include "newtetris/00E440.h"
#include "newtetris/sram.h"
#include "newtetris/066700.h"
#include "newtetris/gamestats.h"
#include "newtetris/032F00.h"
#include "newtetris/010870.h"
#include "newtetris/audio.h"
#include "newtetris/04BFD0.h"
#include "newtetris/multisquareglow.h"
#include "newtetris/pfgfx.h"
#include "newtetris/dbgprntrrl.h"
#include "newtetris/tetris.h"
#include "newtetris/game.h"
#include "newtetris/setplayer.h"

#endif /* !_COMMON_H_ */
