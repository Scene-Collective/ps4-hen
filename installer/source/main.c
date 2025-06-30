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

  if (spoof_target_id(hex) != 0) {
    printf_notification("ERROR: Unable to spoof target ID");
    return;
  }

  printf_notification("Spoofing: %s", buffer);
}

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

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

  // Apply all HEN kernel patches
  install_patches();

  // Initialize config
  struct configuration config;
  init_config(&config);

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
    printf_notification("NoBD patches enabled");
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
    upload_prx_to_disk();
  }

  printf_notification("Welcome to HEN %s", VERSION);

  // for future use
  const bool kill_ui = false;
  const int sleep_sec = kill_ui ? 4 : 1;
  const int u_to_sec = 1000 * 1000;
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
