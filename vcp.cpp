#include "mbed.h"
#include <stdio.h>
#include <stdarg.h>
#include "mbedapi.h"

static Serial vcp(USBTX, USBRX);

MBEDAPI int
mbedPrintf(const char *format, ...)
{
  va_list args;
  int len;

  while (!vcp.writeable()) {
    wait_us(1);
  }
  va_start(args, format);
  len = vcp.vprintf(format, args);
  va_end(args);

  return len;
}

MBEDAPI void
mbedPutc(char c)
{
  vcp.putc(c);
}

MBEDAPI int
mbedGetc(void)
{
  return vcp.getc();
}
