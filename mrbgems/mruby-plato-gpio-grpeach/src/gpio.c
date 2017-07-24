#include "mruby.h"
#include "mruby/variable.h"
#include "mbedapi.h"

static const char *pinname[] = {
  "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7",
  "D8", "D9", "D10", "D11", "D12", "D13", "D14", "D15",
  "A0", "A1", "A2", "A3", "A4", "A5",
  "LED1", "LED2", "LED3", "LED4",
  "BUTTON1"
};
#define MBED_GPIO_PINS (sizeof(pinname)/sizeof(pinname[0]))

void
mrb_mruby_plato_gpio_grpeach_gem_init(mrb_state *mrb)
{
  size_t i;
  struct RClass *plato  = mrb_module_get(mrb, "Plato");
  struct RClass *gpio   = mrb_class_get_under(mrb, plato, "GPIO");

  for (i=0; i<MBED_GPIO_PINS; i++) {
    mrb_mod_cv_set(mrb, gpio, mrb_intern_cstr(mrb, pinname[i]), mrb_fixnum_value(i));
  }
}

void
mrb_mruby_plato_gpio_grpeach_gem_final(mrb_state *mrb)
{
}
