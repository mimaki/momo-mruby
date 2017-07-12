#include "mbed.h"
#include "SDFileSystem.h"

#include "mruby.h"
#include "mruby/irep.h"
#include "mruby/dump.h"
#include "mruby/_string.h"
#include "mbedapi.h"

/* mount microSD */
SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");

DigitalOut ledr(LED1);
DigitalOut ledg(LED2);
DigitalOut ledb(LED3);

extern "C" int mirb(mrb_state *mrb);

int main(void)
{
  extern const uint8_t appbin[];
  mrb_value v, s;
  mrb_state *mrb;
  FILE *fp;

  while (1) {
    ledr = 1;
    mrb = mrb_open();

    wait(0.1);
    ledg = 1;

    if ((fp = fopen("/sd/app.mrb", "rb")) != NULL) {
      /* launch mruby application (MRB file) */
      v = mrb_load_irep_file(mrb, fp);
      fclose(fp);
    }
    else {
      /* launch mruby application (on memory) */
      v = mrb_load_irep(mrb, appbin);
    }
    s = mrb_obj_as_string(mrb, v);
    mbedPrintf(mrb_str_to_cstr(mrb, s));
    mbedPrintf("\n");

    wait(0.1);
    ledb = 1;

    wait(0.3);
    ledr = 0; ledg = 0; ledb = 0;

    /* lauch mirb */
    mirb(mrb);

    mrb_close(mrb);
  }

  return 0;
}
