// #define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include <ps4.h>
#include <stdbool.h>

#include "common.h"
#include "config.h"
#include "kpayloads.h"
#include "path.h"
#include "plugins.h"
#include "version.h"
#include "patch.h"

// TODO: Where should this go? `common.c` doesn't feel right
// Apply target ID spoofing if configured
static void set_target_id(char *tid) {
  // The function input is from a controlled source and is already checked
  int hex;
  sscanf(tid, "%x", &hex);

  // Longest string for this buffer is 23 chars + 1 null term
  char buffer[0x100] = {0};
  int buffer_size = sizeof(buffer);
  switch (hex) {
  case 0:
    break;
  case 0x80:
    snprintf(buffer, buffer_size, "Diagnostic");
    break;
  case 0x81:
    snprintf(buffer, buffer_size, "Devkit");
    break;
  case 0x82:
    snprintf(buffer, buffer_size, "Testkit");
    break;
  case 0x83:
    snprintf(buffer, buffer_size, "Japan");
    break;
  case 0x84:
    snprintf(buffer, buffer_size, "USA");
    break;
  case 0x85:
    snprintf(buffer, buffer_size, "Europe");
    break;
  case 0x86:
    snprintf(buffer, buffer_size, "Korea");
    break;
  case 0x87:
    snprintf(buffer, buffer_size, "United Kingdom");
    break;
  case 0x88:
    snprintf(buffer, buffer_size, "Mexico");
    break;
  case 0x89:
    snprintf(buffer, buffer_size, "Australia & New Zealand");
    break;
  case 0x8A:
    snprintf(buffer, buffer_size, "South Asia");
    break;
  case 0x8B:
    snprintf(buffer, buffer_size, "Taiwan");
    break;
  case 0x8C:
    snprintf(buffer, buffer_size, "Russia");
    break;
  case 0x8D:
    snprintf(buffer, buffer_size, "China");
    break;
  case 0x8E:
    snprintf(buffer, buffer_size, "Hong Kong");
    break;
  case 0x8F:
    snprintf(buffer, buffer_size, "Brazil");
    break;
  case 0xA0:
    snprintf(buffer, buffer_size, "Kratos");
    break;
  default:
    printf_notification("Spoofing: UNKNOWN...\nCheck your `" HEN_INI "` file");
    return;
  }

  if (hex > 0 && spoof_target_id(hex) != 0) {
    printf_notification("ERROR: Unable to spoof target ID");
    return;
  }
}

int _main(struct thread *td) {
  UNUSED(td);

  found_version = 0;
  const bool kill_ui = true;
  const int sleep_sec = kill_ui ? 5 : 1;
  const int u_to_sec = 1000 * 1000;
  initKernel();
  initLibc();
  initModule();
  const int ORBIS_SYSMODULE_ZLIB = 0x00C5;
  if (sceSysmoduleLoadModule(ORBIS_SYSMODULE_ZLIB) == 0) {
    initZlib();
  }

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  uint16_t fw_version = get_firmware();
  if (fw_version < MIN_FW || fw_version > MAX_FW) {
    printf_notification("Unsupported Firmware");
    return -1;
  }

  // Jailbreak the process
  jailbreak();

  // Use temp file to prevent re-running HEN
  if (file_exists(IS_INSTALLED_PATH)) {
    printf_notification("HEN is already installed. Skipping...");
    return 0;
  }
  touch_file(IS_INSTALLED_PATH);

  // Apply all HEN kernel patches
  install_patches();

  // Initialize config
  struct configuration config;
  init_config(&config);

  const bool ver_match = config.config_version != DEFAULT_CONFIG_VERSION;
  const bool found_ver = found_version == 0;
  if (file_exists(HDD_INI_PATH) && (ver_match || found_ver)) {
    const char *reason = " unknown!";
    if (ver_match) {
      reason = " out of date!";
    } else if (found_ver) {
      reason = " not found!";
    }
    printf_debug("config version not match\n");
    printf_debug("config.config_version: %d\n", config.config_version);
    printf_debug("found_version: %d\n", found_version);
    upload_ini(HDD_INI_PATH);
    bool found_usb = file_exists(USB_INI_PATH) == 1;
    if (found_usb) {
      upload_ini(USB_INI_PATH);
    }
    printf_notification("Config version (%d/%d)%s\n"
                        "Updating settings file on %s%s...", config.config_version, DEFAULT_CONFIG_VERSION, reason, "HDD", found_usb ? " and USB" : "");
    init_config(&config);
    // sleep so user can see welcome message before shellui restarts
    usleep(sleep_sec * u_to_sec);
  }

  if (config.exploit_fixes) {
    printf_debug("Applying exploit fixes...\n");
    exploit_fixes();
  }

  if (config.mmap_patches) {
    printf_debug("Applying mmap patches...\n");
    mmap_patch();
  }

  if (config.block_updates) {
    printf_debug("Blocking updates...\n");
    block_updates();
  }

  if (config.disable_aslr) {
    printf_debug("Disabling ASLR...\n");
    disable_aslr();
  }

  if (config.nobd_patches) {
    printf_debug("Installing NoBD patches...\n");
    no_bd_patch();
  }

  // Install and run kpayload
  install_payload(&config);

  // Do this after the kpayload so if the user spoofs it doesn't affect checks in the kpayload
  if (config.target_id[0] != '\0') {
    printf_debug("Setting new target ID...\n");
    set_target_id(config.target_id);
  }

  if (config.upload_prx) {
    printf_debug("Writing plugin PRXs to disk...\n");
    int r = upload_prx_to_disk();
    if (r)
    {
      printf_notification("failed to decompress bundled plugins to disk\n");
    }
  }

  if (!config.skip_patches) {
    InstallShellCoreCodeForAppinfo();
  }

  printf_notification("Welcome to HEN %s", VERSION);

  const char *proc = kill_ui ? "SceShellUI" : NULL;
  if (kill_ui) {
    usleep(sleep_sec * u_to_sec);
    printf_notification("HEN will restart %s\nin %d seconds...", proc, sleep_sec);
  }

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  usleep(sleep_sec * u_to_sec);
  // this was chosen because SceShellCore will try to restart this daemon if it crashes
  // or manually killed in this case
  kill_proc("ScePartyDaemon");
  kill_proc(proc);

  return 0;
}
