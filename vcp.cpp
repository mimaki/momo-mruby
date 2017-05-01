#include "mbed.h"
#include <stdio.h>
#include <stdarg.h>
#include "mbedapi.h"

static Serial vcp(USBTX, USBRX);

MBEDAPI int
MBED_printf(const char *format, ...)
{
  va_list args;
  int len;

  va_start(args, format);
  len = vcp.vprintf(format, args);
  va_end(args);

  return len;
}

MBEDAPI void
MBED_putc(char c)
{
  vcp.putc(c);
}

MBEDAPI int
MBED_getc(void)
{
  return vcp.getc();
}
