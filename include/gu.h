#ifndef _GU_H_
#define _GU_H_

extern void   guMtxIdentF(f32 mf[4][4]);
extern void   guNormalize(f32 *x, f32 *y, f32 *z);
extern int    guRandom(void);
extern s16    sins(u16 angle);
extern s16    coss(u16 angle);

#endif /* !_GU_H_ */
