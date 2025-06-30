#include <ps4.h>

#include "common.h"
#include "path.h"
#include "version.h"

#include "config.h"

#define DEFAULT_EXPLOIT_FIXES 0
#define DEFAULT_MMAP_PATCHES 1
#define DEFAULT_BLOCK_UPDATES 1
#define DEFAULT_DISABLE_ASLR 1
#define DEFAULT_NOBD_PATCHES 0
#define DEFAULT_SKIP_PATCHES 0
#define DEFAULT_UPLOAD_PRX 0
#define DEFAULT_ENABLE_PLUGINS 0

#define MATCH(n) strcmp(name, n) == 0

static void upload_ver(void) {
  write_blob(BASE_PATH "/" VERSION_TXT, VERSION, sizeof(VERSION) - 1);
}

// Helper function to set all configuration values to their defaults
static void set_config_defaults(struct configuration *config) {
  memset(config, '\0', sizeof(*config));
  config->exploit_fixes = DEFAULT_EXPLOIT_FIXES;
  config->mmap_patches = DEFAULT_MMAP_PATCHES;
  config->block_updates = DEFAULT_BLOCK_UPDATES;
  config->disable_aslr = DEFAULT_DISABLE_ASLR;
  config->nobd_patches = DEFAULT_NOBD_PATCHES;
  config->upload_prx = DEFAULT_UPLOAD_PRX;
  config->enable_plugins = DEFAULT_ENABLE_PLUGINS;
  // target_id is already zeroed by memset, which means no spoofing
}

// Helper function to validate and set boolean config values (0 or 1)
static int set_bool_config(const char *name, const char *value, int *config_field, int default_value) {
  if (strcmp(value, "0") == 0) {
    *config_field = 0;
    return 1;
  } else if (strcmp(value, "1") == 0) {
    *config_field = 1;
    return 1;
  } else {
    printf_notification("ERROR: Invalid %s:\n    Must be 0 or 1", name);
    *config_field = default_value;
    return 1;
  }
}

// The return values are flipped in this function compared to the rest of this
// file because the INI lib expects it that way
static int config_handler(void *config, const char *name, const char *value) {
  struct configuration *config_p = (struct configuration *)config;

  if (MATCH("exploit_fixes")) {
    return set_bool_config("exploit_fixes", value, &config_p->exploit_fixes, DEFAULT_EXPLOIT_FIXES);
  } else if (MATCH("mmap_patches")) {
    return set_bool_config("mmap_patches", value, &config_p->mmap_patches, DEFAULT_MMAP_PATCHES);
  } else if (MATCH("block_updates")) {
    return set_bool_config("block_updates", value, &config_p->block_updates, DEFAULT_BLOCK_UPDATES);
  } else if (MATCH("disable_aslr")) {
    return set_bool_config("disable_aslr", value, &config_p->disable_aslr, DEFAULT_DISABLE_ASLR);
  } else if (MATCH("nobd_patches")) {
    return set_bool_config("nobd_patches", value, &config_p->nobd_patches, DEFAULT_NOBD_PATCHES);
  } else if (MATCH("skip_patches")) {
    return set_bool_config("skip_patches", value, &config_p->skip_patches, DEFAULT_SKIP_PATCHES);
  } else if (MATCH("upload_prx")) {
    return set_bool_config("upload_prx", value, &config_p->upload_prx, DEFAULT_UPLOAD_PRX);
  } else if (MATCH("enable_plugins")) {
    return set_bool_config("enable_plugins", value, &config_p->enable_plugins, DEFAULT_ENABLE_PLUGINS);
  } else if (MATCH("target_id")) {
    if (strlen(value) == 1 && value[0] == '0') {
      memset(config_p->target_id, '\0', sizeof(config_p->target_id));
    } else if (strlen(value) != TARGET_ID_SIZE) {
      printf_notification("ERROR: Malformed target_id:\n    Must be %i bytes (e.g. 0x84)", TARGET_ID_SIZE);
      memset(config_p->target_id, '\0', sizeof(config_p->target_id));
    } else if (value[0] != '0' || value[1] != 'x' || !isxdigit(value[2]) || !isxdigit(value[3])) {
      printf_notification("ERROR: Malformed target_id:\n    Incorrect format, must be 0x?? (e.g. 0x84)");
      memset(config_p->target_id, '\0', sizeof(config_p->target_id));
    } else {
      int parsed_id;
      if (sscanf(value, "%x", &parsed_id) != 1) {
        printf_notification("ERROR: Failed to parse target_id:\n    Unable to convert hex value");
        memset(config_p->target_id, '\0', sizeof(config_p->target_id));
      } else if (!((parsed_id >= 0x80 && parsed_id <= 0x8F) || parsed_id == 0xA0)) {
        printf_notification("ERROR: Unknown target_id:\n    Only 0x80-0x8F and 0xA0 are valid");
        memset(config_p->target_id, '\0', sizeof(config_p->target_id));
      } else {
        memcpy(config_p->target_id, value, TARGET_ID_SIZE);
        config_p->target_id[TARGET_ID_SIZE] = '\0';
      }
    }
    return 1;
  } else {
    return 0;
  }
}

int init_config(struct configuration *config) {
  // Create HEN directory, if it doesn't already exist
  if (!dir_exists(BASE_PATH)) {
    mkdir(BASE_PATH, 0777);
  }

  upload_ver();

  int ret = -1;
  set_config_defaults(config);
  if (file_exists(USB_INI_PATH)) {
    if (cfg_parse(USB_INI_PATH, config_handler, config) < 0) {
      printf_notification("ERROR: Unable to load `" USB_INI_PATH "`");
      // Restore defaults in case parsing partially succeeded before failing
      set_config_defaults(config);
    } else {
      if (!file_compare(USB_INI_PATH, HDD_INI_PATH)) {
        unlink(HDD_INI_PATH);
        copy_file(USB_INI_PATH, HDD_INI_PATH);
      }
      ret = 0;
    }
  } else if (file_exists(HDD_INI_PATH)) {
    if (cfg_parse(HDD_INI_PATH, config_handler, config) < 0) {
      printf_notification("ERROR: Unable to load `" HDD_INI_PATH "`");
      // Restore defaults in case parsing partially succeeded before failing
      set_config_defaults(config);
    } else {
      ret = 0;
    }
  }

  return ret;
}
