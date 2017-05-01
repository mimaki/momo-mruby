#include "mbed.h"
#include "mbedapi.h"

static const PinName _pins[] = {
  LED1,         // MBED_LED1
  LED2,         // MBED_LED2
  LED3,         // MBED_LED3
  LED4,         // MBED_LED4
  USER_BUTTON0  // MBED_BUTTON1
};

#define MBED_GPIO_PINS  (sizeof(_pins)/sizeof(_pins[0]))

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
