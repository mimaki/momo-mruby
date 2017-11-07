#include "mbed.h"
#include "BufferedSerial.h"
#include <stdio.h>
#include <stdarg.h>
#include "mbedapi.h"

static BufferedSerial vcp(USBTX, USBRX, 1024);

MBEDAPI int
mbedPrintf(const char *format, ...)
{
  va_list args;
  int len;
  static char buf[1024];

  va_start(args, format);
  len = vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);
  vcp.write(buf, len);

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
  while (!vcp.readable()) {
    wait_us(1);
  }
  return vcp.getc();
}
