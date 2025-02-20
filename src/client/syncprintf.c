#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void rmonPrintf(const char* fmt, ...) {
  int ans;
  va_list ap;

  va_start(ap, fmt);
  ans = vprintf(fmt, ap);
  va_end(ap);
}
