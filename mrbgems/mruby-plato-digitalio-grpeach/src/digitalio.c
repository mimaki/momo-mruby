#include "mruby.h"
#include "mruby/variable.h"
#include "mbedapi.h"

// static mrb_value
// mrb_dio_init(mrb_state *mrb, mrb_value self)
// {
//   mrb_int pin;
//   mrb_get_args(mrb, "i", &pin);

//   mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@pin"), mrb_fixnum_value(pin));

//   // TODO: initialize GPIO pin

//   return self;
// }

static mrb_value
mrb_dio_read(mrb_state *mrb, mrb_value self)
{
  mrb_value vpin;
  mrb_int pin, v = 0;

  vpin = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@pin"));
  pin = mrb_fixnum(vpin);

#ifndef NO_MBED
  /* read data from digital pin */
  v = mbedDigitalRead(pin);
#endif

  return mrb_fixnum_value(v);
}

static mrb_value
mrb_dio_write(mrb_state *mrb, mrb_value self)
{
  mrb_value vpin;
  mrb_int pin, v;

  mrb_get_args(mrb, "i", &v);

  vpin = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@pin"));
  pin = mrb_fixnum(vpin);

#ifndef NO_MBED
  /* write data to digital pin */
  mbedDigitalWrite(pin, v);
#endif

  return mrb_nil_value();
}

void
mrb_mruby_plato_digitalio_grpeach_gem_init(mrb_state *mrb)
{
  struct RClass *plato  = mrb_module_get(mrb, "Plato");
  struct RClass *gpio   = mrb_class_get_under(mrb, plato, "GPIO");
  struct RClass *dio    = mrb_define_class_under(mrb, plato, "DigitalIO", gpio);

  // mrb_define_method(mrb, dio, "initialize", mrb_dio_init,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, dio, "read",       mrb_dio_read,  MRB_ARGS_NONE());
  mrb_define_method(mrb, dio, "write",      mrb_dio_write, MRB_ARGS_REQ(1));
}

void
mrb_mruby_plato_digitalio_grpeach_gem_final(mrb_state *mrb)
{
}
