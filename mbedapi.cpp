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

static I2C _i2c(I2C_SDA, I2C_SCL);


/* Time functions */
MBEDAPI void
MBED_wait_ms(int ms)
{
  wait_ms(ms);
}

MBEDAPI void
MBED_wait_us(int us)
{
  wait_us(us);
}

static void
tick_handler(void)
{
  _tick++;
}

MBEDAPI void
MBED_start_ticker(void)
{
  _ticker.attach(&tick_handler, 0.001);
}

MBEDAPI long
MBED_millis(void)
{
  return (long)_tick;
}

/* Digital IO functions */

MBEDAPI void
digitalWrite(int pin, int value)
{
  if (pin < 0 || pin >= MBED_GPIO_PINS) {
    return;
  }
  DigitalOut io(_pins[pin]);
  io = value;
}

MBEDAPI int
digitalRead(int pin)
{
  int v = 0;
  if (pin < 0 || pin >= MBED_GPIO_PINS) {
    return 0;
  }
  DigitalIn io(_pins[pin]);
  v = (int)io;
  return v;
}

/* I2C functions */

MBEDAPI int
i2cWrite(int addr, const char *cmd, int length, uint8_t repeat)
{
  return _i2c.write(addr, cmd, length, (bool)repeat);
}

MBEDAPI int
i2cRead(int addr, char *data, int length)
{
  return _i2c.read(addr, data, length);
}

MBEDAPI void
i2cStart(void)
{
  _i2c.start();
}

MBEDAPI void
i2cEnd(void)
{
  _i2c.stop();
}

// MBEDAPI int
// i2cWriteRaw(int data)
// {
//   return _i2c.write(data);
// }

// MBEDAPI int
// i2cReadRaw(int ack)
// {
//   return _i2c.read(ack);
// }
