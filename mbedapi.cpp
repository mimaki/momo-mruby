#include "mbed.h"
#include "mbedapi.h"

static const PinName _pins[] = {
  D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15, // MBED_D0..15
  A0, A1, A2, A3, A4, A5,   // MBED_A0..5
  LED1, LED2, LED3, LED4,   // MBED_LED1..4
  USER_BUTTON0              // MBED_BUTTON1
};

#define MBED_GPIO_PINS  (sizeof(_pins)/sizeof(_pins[0]))

static volatile long _tick = 0L;
static Ticker _ticker;

static I2C _i2c(I2C_SDA, I2C_SCL);  // TODO: Change to CV

/* Time functions */
MBEDAPI void
mbedDelay(int ms)
{
  wait_ms(ms);
}

MBEDAPI void
mbedDelay_us(int us)
{
  wait_us(us);
}

static void
tick_handler(void)
{
  _tick++;
}

MBEDAPI void
mbedStartTicker(void)
{
  _ticker.attach(&tick_handler, 0.001);
}

MBEDAPI long
mbedMillis(void)
{
  return (long)_tick;
}

/* Digital IO functions */

MBEDAPI void
mbedDigitalWrite(int pin, int value)
{
  if (pin < 0 || pin >= (int)MBED_GPIO_PINS) {
    return;
  }
  DigitalOut io(_pins[pin]);
  io = value;
}

MBEDAPI int
mbedDigitalRead(int pin)
{
  int v = 0;
  if (pin < 0 || pin >= (int)MBED_GPIO_PINS) {
    return 0;
  }
  DigitalIn io(_pins[pin]);
  v = (int)io;
  return v;
}

/* I2C functions */

MBEDAPI int
mbedI2CWrite(int addr, const char *cmd, int length, uint8_t repeat)
{
  return _i2c.write(addr, cmd, length, (bool)repeat);
}

MBEDAPI int
mbedI2CRead(int addr, char *data, int length)
{
  return _i2c.read(addr, data, length);
}

MBEDAPI void
mbedI2CStart(void)
{
  _i2c.start();
}

MBEDAPI void
mbedI2CStop(void)
{
  _i2c.stop();
}

/* Serial(UART) functions */
MBEDAPI void*
mbedSerialInit(int baud, int dbits, int start, int stop, int par)
{
  SerialBase::Parity parity;
  RawSerial *ser = new RawSerial(D1, D0, baud);
  if (ser) {
    switch(par) {
      case MBED_SERIAL_PARITY_ODD:
        parity = SerialBase::Odd;
        break;
      case MBED_SERIAL_PARITY_EVEN:
        parity = SerialBase::Even;
        break;
      default:
      case MBED_SERIAL_PARITY_NONE:
        parity = SerialBase::None;
        break;
    }
    ser->format(dbits, parity, stop);
  }
  return ser;
}

MBEDAPI int
mbedSerialRawRead(void *s)
{
  RawSerial *ser = (RawSerial*)s;
  if (ser->readable() == 0) {
    return -1;
  }
  return ser->getc();
}

MBEDAPI int
mbedSerialRawWrite(void *s, int c)
{
  RawSerial *ser = (RawSerial*)s;
  int retry;
  for (retry=0; retry<1000; retry++) {
    if (ser->writeable()) break;
    mbedDelay(1);
  }
  if (retry == 1000) {
    return -1;
  }
  return ser->putc(c);
}

MBEDAPI int
mbedSerialAvailable(void *s)
{
  RawSerial *ser = (RawSerial*)s;
  return ser->readable();
}

MBEDAPI int
mbedSerialFlush(void *s)
{
  return 0;
}

MBEDAPI int
mbedSerialClose(void *s)
{
  RawSerial *ser = (RawSerial*)s;
  delete ser;
  return 0;
}

MBEDAPI void *
mbedSPIInit(int mode, int freq)
{
  SPI *spi = new SPI(D11, D12, D13);
  spi->format(8, mode);
  spi->frequency(freq);
mbedPrintf("SPI init: mode=%d, freq=%d\n", mode, freq);
  return spi;
}

MBEDAPI int
mbedSPITransfer(void *spi, int sd)
{
  int v;
mbedPrintf("SPI transfer: sd=%d\n", sd);
  v = ((SPI*)spi)->write(sd);
mbedPrintf("SPI transfer: rd=%d\n", v);
  return v;
}

MBEDAPI void
mbedSPIClose(void *spi)
{
  if (spi) {
    delete (SPI*)spi;
  }
}
