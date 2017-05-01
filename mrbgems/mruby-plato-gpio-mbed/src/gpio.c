#include "mruby.h"
#include "mruby/variable.h"
#include "mbedapi.h"

void
mrb_mruby_plato_gpio_mbed_gem_init(mrb_state *mrb)
{
  struct RClass *plato  = mrb_module_get(mrb, "Plato");
  struct RClass *gpio   = mrb_class_get_under(mrb, plato, "GPIO");

  mrb_mod_cv_set(mrb, gpio, mrb_intern_lit(mrb, "LED1"), mrb_fixnum_value(MBED_LED1));
  mrb_mod_cv_set(mrb, gpio, mrb_intern_lit(mrb, "LED2"), mrb_fixnum_value(MBED_LED2));
  mrb_mod_cv_set(mrb, gpio, mrb_intern_lit(mrb, "LED3"), mrb_fixnum_value(MBED_LED3));
  mrb_mod_cv_set(mrb, gpio, mrb_intern_lit(mrb, "LED4"), mrb_fixnum_value(MBED_LED4));
  mrb_mod_cv_set(mrb, gpio, mrb_intern_lit(mrb, "BUTTON1"), mrb_fixnum_value(MBED_BUTTON1));
}

void
mrb_mruby_plato_gpio_mbed_gem_final(mrb_state *mrb)
{
}
