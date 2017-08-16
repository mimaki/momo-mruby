#include "mbed.h"
#include "SDFileSystem.h"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/irep.h"
#include "mruby/variable.h"
#include "mruby/dump.h"
#include "mruby/_string.h"
#include "mruby/hash.h"
#include "mbedapi.h"

#include <stdio.h>
#include <string.h>

#define SD_ROOT "/sd/"
#define PRELOAD "preload"
#define AUTORUN "autorun.mrb"
#define LOW   0
#define HIGH  1

#define KEY_IPADDR  "ipaddr"
#define KEY_SUBNET  "subnet"
#define KEY_GATEWAY "gatewauy"
#define KEY_DHCP    "DHCP"
#define KEY_MIRB    "mirb"
#define KEY_MRDB    "mrdb"

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

  if (sd.disk_status()) return NULL;  /* SD not initialized */

  if ((fp = fopen(SD_ROOT PRELOAD, "rb")) != NULL) {
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
  char path[PATH_MAX] = SD_ROOT;
  FILE *fp;
  mrb_value v, s;

  if (sd.disk_status()) return 0; /* SD not initialized */

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
get_fixnum(mrb_state *mrb, mrb_value cfg, const char *key)
{
  mrb_value v = mrb_hash_get(mrb, cfg, mrb_symbol_value(mrb_intern_cstr(mrb, key)));
  if (mrb_fixnum_p(v))  return mrb_fixnum(v);
  if (!mrb_string_p(v)) v = mrb_obj_as_string(mrb, v);
  return (mrb_int)atoi(mrb_str_to_cstr(mrb, v));
}

static char *
get_string(mrb_state *mrb, mrb_value cfg, const char *key)
{
  mrb_value v = mrb_hash_get(mrb, cfg, mrb_symbol_value(mrb_intern_cstr(mrb, key)));
  if (!mrb_string_p(v)) v = mrb_obj_as_string(mrb, v);
  return mrb_str_to_cstr(mrb, v);
}

static Config*
configure(mrb_state *mrb, bool menu)
{
  extern const uint8_t cfgmenu[];
  static Config config = {
    "0.0.0.0",  // IP address
    "0.0.0.0",  // Subnet mask
    "0.0.0.0",  // Default gateway
    1,          // DHCP
    1,          // mirb
    0           // mrdb
  };
  mrb_value cfg;

  mrb_gv_set(mrb, mrb_intern_lit(mrb, "$menu"), mrb_bool_value(menu));
  mrb_load_irep(mrb, cfgmenu);
  cfg = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$appcfg"));

  config.mirb = get_fixnum(mrb, cfg, "mirb");
  config.mrdb = get_fixnum(mrb, cfg, "mrdb");
  config.dhcp = get_fixnum(mrb, cfg, "lan_dhcp");
  strcpy(config.ipaddr, get_string(mrb, cfg, "lan_ipaddr"));
  strcpy(config.subnet, get_string(mrb, cfg, "lan_subnet"));
  strcpy(config.gateway, get_string(mrb, cfg, "lan_gateway"));

  return &config;
}

int main(void)
{
  mrb_state *mrb;
  char *mrblist, *fn;
  bool menu = false;
  Config *cfg;

  while (1) {
    ledr = 1;
    mrb = mrb_open();
    ledr = 0;

    ledb = 1;
    if (button == LOW) {
      mbedPrintf("Enter mbed-mruby configuration mode\n");
      menu = true;
    }
    cfg = configure(mrb, menu);
    menu = 0;
    ledb = 0;

    if (cfg->mrdb) {
      mrb_debugger(mrb, SD_ROOT AUTORUN);
      /* mrb was closed */
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

    /* launch mirb */
    if (cfg->mirb) {
      mirb(mrb);
    }

    mrb_close(mrb);
    /* restart mruby */
  }

  return 0;
}
