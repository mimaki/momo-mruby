#include "mbed.h"
#include "mruby.h"
#include "mruby/irep.h"
#include "mruby/_string.h"
#include "mbedapi.h"

DigitalOut ledr(LED1);
DigitalOut ledg(LED2);
DigitalOut ledb(LED3);

extern "C" int mirb(mrb_state *mrb);

int main(void)
{
  extern const uint8_t appbin[];
  mrb_value v, s;
  mrb_state *mrb = mrb_open();

  MBED_printf("Hello, mbed!\n");

  ledr = 1;
  v = mrb_load_irep(mrb, appbin);
  s = mrb_obj_as_string(mrb, v);
  MBED_printf(mrb_str_to_cstr(mrb, s));
  MBED_printf("\n");
  ledg = 1;

  wait(1);
  ledr = 0;
  ledg = 0;

  mirb(mrb);

  MBED_printf("mirb done.\n");

  while (1) {
      ledb = !ledb;
      wait(0.1);
  }

  mrb_close(mrb);

  return 0;
}
