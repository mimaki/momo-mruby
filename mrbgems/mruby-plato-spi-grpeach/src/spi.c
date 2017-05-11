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

typedef struct mrb_mbed_spi {
  void *spi;      /* SPI object */
  mrb_int sspin;  /* SS pin */
} mrb_mbed_spi;

static void
mrb_mbed_spi_free(mrb_state *mrb, void *ptr)
{
  mrb_mbed_spi *spi = (mrb_mbed_spi*)ptr;
  if (spi->spi) {
#ifndef NO_MBED
    mbedSPIClose(spi->spi);
#endif
  }
  mrb_free(mrb, ptr);
}

static const struct mrb_data_type mrb_spi_type = { "mbedSPI", mrb_mbed_spi_free };

static mrb_value
mrb_spi_init(mrb_state *mrb, mrb_value self)
{
  mrb_int mode;
  mrb_value vclk = mrb_nil_value();
  mrb_sym sb = mrb_intern_lit(mrb, "msbfirst"); /* not work in mbed */
#ifdef NO_MBED
  mrb_value vss = mrb_nil_value();
#else /* MBED */
  mrb_value vss = mrb_fixnum_value(MBED_D10);
#endif
  mrb_int clk = 1000000;
  mrb_mbed_spi *spi;

  mrb_get_args(mrb, "i|ono", &mode, &vclk, &sb, &vss);
  if (mode < 0 || mode > 3) {
    mrb_raise(mrb, E_RANGE_ERROR, "Specify mode value of 0..3");
  }
  if (!mrb_nil_p(vclk)) {
    clk = mrb_fixnum(vclk);
  }

  spi = (mrb_mbed_spi*)mrb_malloc(mrb, sizeof(mrb_mbed_spi));
  spi->sspin = mrb_fixnum_p(vss) ? mrb_fixnum(vss) : -1;

  /* initialize SPI object */
#ifdef NO_MBED
  spi->spi = NULL;
#else
  spi->spi = mbedSPIInit(mode, clk);
#endif
  mrb_data_init(self, spi, &mrb_spi_type);
  return self;
}

static mrb_value
mrb_spi_transfer(mrb_state *mrb, mrb_value self)
{
  mrb_int sd, rd = 0;
  mrb_mbed_spi *spi = DATA_PTR(self);

  if (!spi->spi) mrb_raise(mrb, E_RUNTIME_ERROR, "SPI device is already closed.");

  mrb_get_args(mrb, "i", &sd);

  /* transfer data to SPI */
#ifdef NO_MBED
#else /* MBED */
  rd = mbedSPITransfer(spi->spi, sd);
#endif

  return mrb_fixnum_value(rd);
}

static mrb_value
mrb_spi_start(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_spi *spi = DATA_PTR(self);
  if (!spi->spi) mrb_raise(mrb, E_RUNTIME_ERROR, "SPI device is already closed.");
#ifdef NO_MBED
#else
  if (spi->sspin >= 0) {
    mbedDigitalWrite(spi->sspin, 0);
  }
#endif
  return mrb_nil_value();
}

static mrb_value
mrb_spi_stop(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_spi *spi = DATA_PTR(self);
  if (!spi->spi) mrb_raise(mrb, E_RUNTIME_ERROR, "SPI device is already closed.");
#ifdef NO_MBED
#else
  if (spi->sspin >= 0) {
    mbedDigitalWrite(spi->sspin, 1);
  }
#endif
  return mrb_nil_value();
}

static mrb_value
mrb_spi_close(mrb_state *mrb, mrb_value self)
{
  mrb_mbed_spi *spi = DATA_PTR(self);
  if (spi->spi) {
#ifdef NO_MBED
#else
    mbedSPIClose(spi->spi);
    spi->spi = NULL;
#endif
  }
  return mrb_nil_value();
}

void
mrb_mruby_plato_spi_grpeach_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb_define_module(mrb, "PlatoPeach");
  struct RClass *spi = mrb_define_class_under(mrb, mod, "SPI", mrb->object_class);
  MRB_SET_INSTANCE_TT(spi, MRB_TT_DATA);

  mrb_define_method(mrb, spi, "initialize", mrb_spi_init,     MRB_ARGS_ARG(1, 3));
  mrb_define_method(mrb, spi, "transfer",   mrb_spi_transfer, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, spi, "_start",     mrb_spi_start,    MRB_ARGS_NONE());
  mrb_define_method(mrb, spi, "_end",       mrb_spi_stop,     MRB_ARGS_NONE());
  mrb_define_method(mrb, spi, "close",      mrb_spi_close,    MRB_ARGS_NONE());
}

void
mrb_mruby_plato_spi_grpeach_gem_final(mrb_state *mrb)
{
}
