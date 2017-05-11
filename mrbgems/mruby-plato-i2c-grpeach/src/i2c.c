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

typedef struct mrb_mbed_i2c {
  void *i2c;    /* I2C object */
  mrb_int addr; /* I2C slave address (offseted) */
  mrb_int wait; /* delay time */
} mrb_mbed_i2c;

static void
mrb_mbed_i2c_free(mrb_state *mrb, void *ptr)
{
  mrb_mbed_i2c *i2c = (mrb_mbed_i2c*)ptr;
  if (i2c->i2c) {
#ifndef NO_MBED
    mbedI2CClose(i2c->i2c);
#endif
  }
  mrb_free(mrb, ptr);
}

static const struct mrb_data_type mrb_i2c_type = { "mbedI2C", mrb_mbed_i2c_free };

static mrb_value
mrb_i2c_init(mrb_state *mrb, mrb_value self)
{
  mrb_int addr;
  mrb_int wait = 1000;
  mrb_mbed_i2c *i2c;

  mrb_get_args(mrb, "i|i", &addr, &wait);

  i2c = (mrb_mbed_i2c*)mrb_malloc(mrb, sizeof(mrb_mbed_i2c));
  /* initialize I2C object */
#ifdef NO_MBED
  i2c->i2c = NULL;
#else /* MBED */
  i2c->i2c = mbedI2CInit();
#endif
  i2c->addr = addr << 1;  /* left shift 1 bit for I2C lib. */
  i2c->wait = wait;
  mrb_data_init(self, i2c, &mrb_i2c_type);
  return self;
}

static mrb_value
mrb_i2c_read(mrb_state *mrb, mrb_value self)
{
  int i;
  mrb_int reg, len;
  uint8_t *buf;
  mrb_value v;
  mrb_sym type = mrb_intern_lit(mrb, "as_array");
#ifndef NO_MBED
  char creg;
  mrb_int wait;
#endif
  mrb_mbed_i2c *i2c = DATA_PTR(self);

  if (!i2c->i2c) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "I2C device is already closed.");
  }

  mrb_get_args(mrb, "ii|n", &reg, &len, &type);

  buf = mrb_malloc(mrb, len);

#ifdef NO_MBED
  memset(buf, 0, len);
#else /* MBED */
  /* write register */
  creg = (char)reg;
  mbedI2CWrite(i2c->i2c, i2c->addr, &creg, 1, FALSE);
  wait = mbedMillis() + i2c->wait;
  while (wait > mbedMillis()) {
    /* read data from I2C */
    if (mbedI2CRead(i2c->i2c, i2c->addr, (char*)buf, len) == 0) {
      break;  /* ACK */
    }
    /* wait ack condition */
    mbedDelay(1);
  }
#endif

  if (type == mrb_intern_lit(mrb, "as_string")) {
    /* as_string */
    v = mrb_str_buf_new(mrb, len);
    memcpy(RSTRING_PTR(v), buf, len);
    mrb_str_resize(mrb, v, len);
  }
  else {
    /* as_array or other */
    v = mrb_ary_new_capa(mrb, len);
    for (i=0; i<len; i++) {
      mrb_ary_push(mrb, v, mrb_fixnum_value(buf[i]));
    }
  }
  mrb_free(mrb, buf);

  return v;
}

static mrb_value
mrb_i2c_write(mrb_state *mrb, mrb_value self)
{
  mrb_int reg;
  mrb_bool rep = FALSE;
  mrb_value data, v;
  uint8_t *buf;
  size_t len;
  mrb_int i;
  mrb_mbed_i2c *i2c = DATA_PTR(self);

  if (!i2c->i2c) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "I2C device is already closed.");
  }

  mrb_get_args(mrb, "io|b", &reg, &data, &rep);

  if (mrb_string_p(data)) {
    len = RSTRING_LEN(data);
    buf = mrb_malloc(mrb, len + 1);
    buf[0] = (uint8_t)reg;
    memcpy(buf + 1, RSTRING_PTR(data), len);
  }
  else if (mrb_array_p(data)) {
    len = RARRAY_LEN(data);
    buf = mrb_malloc(mrb, len + 1);
    buf[0] = (uint8_t)reg;
    for (i=0; i<len; i++) {
      buf[i + 1] = mrb_fixnum(mrb_ary_ref(mrb, data, i));
    }
  }
  else if (mrb_fixnum_p(data)) {
    len = 1;
    buf = mrb_malloc(mrb, len + 1);
    buf[0] = (uint8_t)reg;
    buf[1] = mrb_fixnum(data);
  }
  else {
    v = mrb_obj_as_string(mrb, data);
    len = RSTRING_LEN(v);
    buf = mrb_malloc(mrb, len + 1);
    buf[0] = (uint8_t)reg;
    memcpy(buf + 1, RSTRING_PTR(v), len);
  }

#ifndef NO_MBED
  /* write data to I2C */
  mbedI2CWrite(i2c->i2c, i2c->addr, (const char*)buf, len + 1, (uint8_t)rep);
#endif

  mrb_free(mrb, buf);

  return mrb_nil_value();
}

static mrb_value
mrb_i2c_start(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_i2c *i2c = DATA_PTR(self);
#ifndef NO_MBED
  mbedI2CStart(i2c->i2c);
#endif
  return mrb_nil_value();
}

static mrb_value
mrb_i2c_end(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_i2c *i2c = DATA_PTR(self);
#ifndef NO_MBED
  mbedI2CStop(i2c->i2c);
#endif
  return mrb_nil_value();
}

void
mrb_mruby_plato_i2c_grpeach_gem_init(mrb_state *mrb)
{
  struct RClass *mod  = mrb_define_module(mrb, "PlatoPeach");
  struct RClass *i2c  = mrb_define_class_under(mrb, mod, "I2C", mrb->object_class);

  mrb_define_method(mrb, i2c, "initialize", mrb_i2c_init,     MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, i2c, "read",       mrb_i2c_read,     MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, i2c, "write",      mrb_i2c_write,    MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, i2c, "_start",     mrb_i2c_start,    MRB_ARGS_NONE());
  mrb_define_method(mrb, i2c, "_end",       mrb_i2c_end,      MRB_ARGS_NONE());
}

void
mrb_mruby_plato_i2c_grpeach_gem_final(mrb_state *mrb)
{
}
