/* coefficients for polynomial approximation of sin on +/- pi/2 */

/* ====================================================================
 *
 * FunctionName         coss
 *
 * Description          computes cosine of arg
 *
 * ====================================================================
 */

extern signed short sins(unsigned short angle);

signed short coss(unsigned short x) {
  /* 0 <= x < 0x10000  ==>  0 <= x < 2PI */

  return sins ((unsigned short) (x + 0x4000));
}
