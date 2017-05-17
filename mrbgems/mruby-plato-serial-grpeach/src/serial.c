#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include "mruby/_string.h"
#include "mruby/array.h"
#include "mruby/data.h"
#include <string.h>

#ifndef NO_MBED
  #include "mbedapi.h"
#endif

typedef struct mrb_mbed_serial {
  void *serial;   /* Serial object */
} mrb_mbed_serial;

static void
mrb_mbed_serial_free(mrb_state *mrb, void *ptr)
{
  mrb_mbed_serial *ser = (mrb_mbed_serial*)ptr;
  if (ser->serial) {
#ifndef NO_MBED
    mbedSerialClose(ser->serial);
#endif
  }
  mrb_free(mrb, ptr);
}

static const struct mrb_data_type mrb_serial_type = {"mbedSerial", mrb_mbed_serial_free};

static mrb_value
mrb_serial_init(mrb_state *mrb, mrb_value self)
{
  mrb_int baud;
  mrb_int dbits=8, start=1, stop=1;
  mrb_mbed_serial *ser;
  mrb_sym sympari = mrb_intern_lit(mrb, "none");
  int parity = 0;

  mrb_get_args(mrb, "i|iiin", &baud, &dbits, &start, &stop, &sympari);

#ifndef NO_MBED
  if (sympari == mrb_intern_lit(mrb, "odd")) {
    parity = MBED_SERIAL_PARITY_ODD;
  }
  else if (sympari == mrb_intern_lit(mrb, "even")) {
    parity = MBED_SERIAL_PARITY_EVEN;
  }
  else {
    parity = MBED_SERIAL_PARITY_NONE;
  }
#endif

  ser = (mrb_mbed_serial*)mrb_malloc(mrb, sizeof(mrb_mbed_serial));

  /* initialize Serial object */
#ifdef NO_MBED
  ser->serial = NULL;
#else /* MBED */
  ser->serial = mbedSerialInit(baud, dbits, start, stop, parity);
#endif
  mrb_data_init(self, ser, &mrb_serial_type);
 return self;
}

static mrb_value
mrb_serial_read(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_serial *ser = DATA_PTR(self);
  mrb_int val = -1;
#ifndef NO_MBED
  if (!ser->serial) mrb_raise(mrb, E_RUNTIME_ERROR, "Serial port is already closed.");
  /* read data from Serial */
  val = mbedSerialRawRead(ser->serial);
#endif
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_serial_write(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_serial *ser = DATA_PTR(self);
  mrb_int val;
#ifndef NO_MBED
  if (!ser->serial) mrb_raise(mrb, E_RUNTIME_ERROR, "Serial port is already closed.");
#endif
  mrb_get_args(mrb, "i", &val);
#ifndef NO_MBED
  /* write data to Serial */
  mbedSerialRawWrite(ser->serial, val);
#endif
  return mrb_nil_value();
}

static mrb_value
mrb_serial_available(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_serial *ser = DATA_PTR(self);
  mrb_int len = 0;
#ifndef NO_MBED
  if (!ser->serial) mrb_raise(mrb, E_RUNTIME_ERROR, "Serial port is already closed.");
  len = mbedSerialAvailable(ser->serial);
#endif
  return mrb_fixnum_value(len);
}

static mrb_value
mrb_serial_flush(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_serial *ser = DATA_PTR(self);
#ifndef NO_MBED
  if (!ser->serial) mrb_raise(mrb, E_RUNTIME_ERROR, "Serial port is already closed.");
  // TODO
#endif
  return mrb_nil_value();
}

static mrb_value
mrb_serial_close(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_serial *ser = DATA_PTR(self);
  if (ser->serial) {
#ifndef NO_MBED
    mbedSerialClose(ser->serial);
#endif
    ser->serial = NULL;
  }
  return mrb_nil_value();
}

void
mrb_mruby_plato_serial_grpeach_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb_define_module(mrb, "PlatoPeach");
  struct RClass *ser = mrb_define_class_under(mrb, mod, "Serial", mrb->object_class);
  MRB_SET_INSTANCE_TT(ser, MRB_TT_DATA);

  mrb_define_method(mrb, ser, "initialize", mrb_serial_init,      MRB_ARGS_ARG(1, 4));
  mrb_define_method(mrb, ser, "_read",      mrb_serial_read,      MRB_ARGS_NONE());
  mrb_define_method(mrb, ser, "_write",     mrb_serial_write,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ser, "available",  mrb_serial_available, MRB_ARGS_NONE());
  mrb_define_method(mrb, ser, "close",      mrb_serial_close,     MRB_ARGS_NONE());
}

void
mrb_mruby_plato_serial_grpeach_gem_final(mrb_state *mrb)
{
}
