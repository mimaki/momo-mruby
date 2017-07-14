#include "mruby.h"
#include "mruby/class.h"

#ifndef NO_MBED
  #include "mbedapi.h"
#endif

static mrb_value
mrb_stdout_putc(mrb_state *mrb, mrb_value self)
{
  mrb_int c;
  mrb_get_args(mrb, "i", &c);
#ifdef NO_MBED
#else
  mbedPutc((char)c);
#endif
  return mrb_nil_value();
}

static mrb_value
mrb_stdin_getc(mrb_state *mrb, mrb_value self)
{
  mrb_int c = -1;
#ifdef NO_MBED
#else
  c = mbedGetc();
#endif
  return mrb_fixnum_value(c);
}

void
mrb_mruby_stdio_grpeach_gem_init(mrb_state *mrb)
{
  struct RClass *cin  = mrb_define_class(mrb, "STDIN",  mrb->object_class);
  struct RClass *cout = mrb_define_class(mrb, "STDOUT", mrb->object_class);

  mrb_define_class_method(mrb, cin,   "_getc", mrb_stdin_getc,  MRB_ARGS_NONE());
  mrb_define_class_method(mrb, cout,  "_putc", mrb_stdout_putc, MRB_ARGS_REQ(1));
}

void
mrb_mruby_stdio_grpeach_gem_final(mrb_state *mrb)
{
}
