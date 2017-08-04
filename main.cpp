#include "mbed.h"
#include "SDFileSystem.h"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/irep.h"
#include "mruby/dump.h"
#include "mruby/_string.h"
#include "mbedapi.h"

#include <stdio.h>
#include <string.h>

#define PRELOAD "/sd/preload"
#define AUTORUN "autorun.mrb"
#define LOW   0
#define HIGH  1

typedef struct _Config {
  char ipaddr[16];    /* IP address */
  char subnet[16];    /* Subnet mask */
  char gateway[16];   /* Default gateway */
  uint8_t dhcp : 1;   /* Use DHCP */
  uint8_t mirb : 1;   /* Run interact mruby */
  uint8_t mrdb : 1;   /* Run mruby debugger */
} Config;

/* mount microSD */
SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");

DigitalOut ledr(LED1);
DigitalOut ledg(LED2);
DigitalOut ledb(LED3);
DigitalIn button(USER_BUTTON0);

// static Config config = {
//   "0.0.0.0",
//   "0.0.0.0",
//   "0.0.0.0",
//   1,
//   1,
//   0
// };

extern "C" int mirb(mrb_state*);
extern "C" int mrb_debugger(mrb_state*, const char*);

// Load pre-load MRB file list
// Args
//  mrb_state *mrb  mruby status
// Return
//  MRB file list (seperated by "\n")
static char *
getMRBFiles(mrb_state *mrb)
{
  char *list = NULL;
  long fsz;
  FILE *fp;

  if ((fp = fopen(PRELOAD, "rb")) != NULL) {
    fseek(fp, 0, SEEK_END);
    fsz = ftell(fp);
    list = (char*)mrb_malloc(mrb, fsz + 1);
    fseek(fp, 0, SEEK_SET);
    fread(list, fsz, 1, fp);
    list[fsz] = '\0';
  }
  return list;
}

// Launch mruby binary (MRB)
// Args
//  mrb_state *mrb  mruby status
//  const char *fn  MRB file name
// Ruturn
//  Result code
static int
launchMRBFile(mrb_state *mrb, const char *fn)
{
  char path[PATH_MAX] = "/sd/";
  FILE *fp;
  mrb_value v, s;

  strcat(path, fn);
  if ((fp = fopen(path, "r")) != NULL) {
    mbedPrintf("run \"%s\"\n", path);
    v = mrb_load_irep_file(mrb, fp);
    fclose(fp);
    s = mrb_obj_as_string(mrb, v);
    mbedPrintf(" => ");
    mbedPrintf(mrb_str_to_cstr(mrb, s));
    mbedPrintf("\n\n");
  }
  return 0;
}

static mrb_int
configure(mrb_state *mrb)
{
  extern const uint8_t cfgmenu[];
  mrb_value vcmd = mrb_load_irep(mrb, cfgmenu);
  return mrb_fixnum(vcmd);
}

int main(void)
{
  mrb_state *mrb;
  char *mrblist, *fn;

  while (1) {
    ledr = 1;
    mrb = mrb_open();
    ledr = 0;

    if (button == LOW) {
      ledb = 1;
      mbedPrintf("Enter mbed-mruby configuration mode\n");
      configure(mrb);
      ledb = 0;
    }

    if (mrb_debugger(mrb, "/sd/autorun.mrb") == 0) {
      continue;
    }

    /* Launch applications that listed in /sd/preload */
    mrblist = getMRBFiles(mrb);
    if (mrblist) {
      fn = strtok(mrblist, "\n");
      while (fn) {
        if (strlen(fn) > 0 && fn[0] != '#') {
          launchMRBFile(mrb, fn);
        }
        fn = strtok(NULL, "\n");
      }
      mrb_free(mrb, mrblist);
    }

    /* Launch autorun.mrb */
    launchMRBFile(mrb, AUTORUN);

    /* lauch mirb */
    mirb(mrb);

    mrb_close(mrb);
    /* restart mruby */
  }

  return 0;
}
