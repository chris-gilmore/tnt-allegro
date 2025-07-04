#ifndef _GBI_H_
#define _GBI_H_

/*
 * Data Structures
 *
 * NOTE:
 * The DMA transfer hardware requires 64-bit aligned, 64-bit multiple-
 * sized transfers. This important hardware optimization is unfortunately
 * reflected in the programming interface, with some structures
 * padded and alignment enforced.
 *
 * Since structures are aligned to the boundary of the "worst-case"
 * element, we can't depend on the C compiler to align things
 * properly.
 *
 * 64-bit structure alignment is enforced by wrapping structures with
 * unions that contain a dummy "long long int".  Why this works is
 * explained in the ANSI C Spec, or on page 186 of the second edition
 * of K&R, "The C Programming Language".
 *
 * The price we pay for this is a little awkwardness referencing the
 * structures through the union. There is no memory penalty, since
 * all the structures are at least 64-bits the dummy alignment field
 * does not increase the size of the union.
 *
 * Static initialization of these union structures works because
 * the ANSI C spec states that static initialization for unions
 * works by using the first union element. We put the dummy alignment
 * field last for this reason.
 *
 * (it's possible a newer 64-bit compiler from MIPS might make this
 * easier with a flag, but we can't wait for it...)
 *
 */

/*
 * Vertex (set up for use with colors)
 */
typedef struct {
  /* 0x0 */ s16   ob[3];  /* x, y, z */
  /* 0x6 */ u16   flag;
  /* 0x8 */ s16   tc[2];  /* texture coord */
  /* 0xC */ u8    cn[4];  /* color & alpha */
} Vtx_t; // 0x10 bytes

/*
 * Vertex (set up for use with normals)
 */
typedef struct {
  /* 0x0 */ s16   ob[3];  /* x, y, z */
  /* 0x6 */ u16   flag;
  /* 0x8 */ s16   tc[2];  /* texture coord */
  /* 0xC */ s8    n[3];   /* normal */
  /* 0xF */ u8    a;      /* alpha  */
} Vtx_tn; // 0x10 bytes

typedef union {
  Vtx_t    v;  /* Use this one for colors  */
  Vtx_tn   n;  /* Use this one for normals */
  s64      force_structure_alignment;
} Vtx;

/*
 * 4x4 matrix, fixed point s15.16 format.
 * First 8 words are integer portion of the 4x4 matrix
 * Last 8 words are the fraction portion of the 4x4 matrix
 */
typedef s32 Mtx_t[4][4];

typedef union {
  Mtx_t m;
  s64 force_structure_alignment;
} Mtx;

/*
 * Viewport
 */

/*
 *
 * This magic value is the maximum INTEGER z-range of the hardware
 * (there are also 16-bits of fraction, which are introduced during
 * any transformations). This is not just a good idea, it's the law.
 * Feeding the hardware eventual z-coordinates (after any transforms
 * or scaling) bigger than this, will not work.
 *
 * This number is DIFFERENT than G_MAXFBZ, which is the maximum value
 * you want to use to initialize the z-buffer.
 *
 * The reason these are different is mildly interesting, but too long
 * to explain here. It is basically the result of optimizations in the
 * hardware. A more generic API might hide this detail from the users,
 * but we don't have the ucode to do that...
 *
 */
#define G_MAXZ          0x03ff  /* 10 bits of integer screen-Z precision */

/*
 * The viewport structure elements have 2 bits of fraction, necessary
 * to accomodate the sub-pixel positioning scaling for the hardware.
 * This can also be exploited to handle odd-sized viewports.
 *
 * Accounting for these fractional bits, using the default projection
 * and viewing matrices, the viewport structure is initialized thusly:
 *
 *              (SCREEN_WD/2)*4, (SCREEN_HT/2)*4, G_MAXZ, 0,
 *              (SCREEN_WD/2)*4, (SCREEN_HT/2)*4, 0, 0,
 */
typedef struct {
  s16   vscale[4];  /* scale, 2 bits fraction */
  s16   vtrans[4];  /* translate, 2 bits fraction */
  /* both the above arrays are padded to 64-bit boundary */
} Vp_t;

typedef union {
  Vp_t   vp;
  s64    force_structure_alignment;
} Vp;

/*
 * Light structure.
 */

typedef struct {
  u8   col[3];   /* diffuse light value (rgba) */
  u8   pad1;
  u8   colc[3];  /* copy of diffuse light value (rgba) */
  u8   pad2;
  s8   dir[3];   /* direction of light (normalized) */
  u8   pad3;
} Light_t;

typedef union {
  Light_t   l;
  s64       force_structure_alignment[2];
} Light;

typedef struct {
  Light   l[2];
} LookAt;

/*
 * Generic Gfx Packet
 */
typedef struct {
  /* 0x0 */ u32   w0;
  /* 0x4 */ u32   w1;
} Gwords; // 0x8 bytes

/*
 * This union is the fundamental type of the display list.
 * It is, by law, exactly 64 bits in size.
 */
typedef union {
  Gwords   words;
  s64      force_structure_alignment;
} Gfx;

#define gSPClipRatio(pkt, r)
#define gDPSetScissor(pkt, mode, ulx, uly, lrx, lry)
#define gDPPipeSync(pkt)

#endif /* _GBI_H_ */
