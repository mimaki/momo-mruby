#include "mruby.h"
#include "mruby/_string.h"

#ifdef NO_MBED
  #include <stdio.h>
#else
  #include "mbedapi.h"
#endif

static mrb_value
mrb_delay(mrb_state *mrb, mrb_value self)
{
  mrb_int ms;
  mrb_get_args(mrb, "i", &ms);

  // wait for ms milliseconds
#ifdef NO_MBED
#else /* mbed */
  MBED_wait_ms(ms);
#endif
	
  return mrb_nil_value();
}

static mrb_value
mrb_delay_us(mrb_state *mrb, mrb_value self)
{
  mrb_int us;
  mrb_get_args(mrb, "i", &us);

  // wait for us microseconds
#ifdef NO_MBED
#else /* mbed */
  MBED_wait_us(us);
#endif

  return mrb_nil_value();
}

static mrb_value
mrb_millis(mrb_state *mrb, mrb_value self)
{
  mrb_int ms = 0;

  // get tick-count (milliseconds)
#ifdef NO_MBED
#else /* MBED */
  ms = (mrb_int)MBED_millis();
#endif

  return mrb_fixnum_value(ms);
}

// static mrb_value
// mrb_micros(mrb_state *mrb, mrb_value self)
// {
//   mrb_int us = 0;

//   // TODO: get tick-count (microseconds)

//   return mrb_fixnum_value(us);
// }

void
mrb_mruby_plato_machine_grpeach_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb_define_module(mrb, "PlatoPeach");
  struct RClass *mach = mrb_define_class_under(mrb, mod, "Machine", mrb->object_class);

#ifndef NO_MBED
  /* start tick count */
  MBED_start_ticker();
#endif

  mrb_define_class_method(mrb, mach, "delay",     mrb_delay,    MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mach, "delay_us",  mrb_delay_us, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mach, "millis",    mrb_millis,   MRB_ARGS_NONE());
  // mrb_define_class_method(mrb, mach, "micros",    mrb_micros,   MRB_ARGS_NONE());
}

void
mrb_mruby_plato_machine_grpeach_gem_final(mrb_state *mrb)
{
}
