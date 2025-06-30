#include "common.h"
#include "path.h"

#include "plugins.h"

// will force rebuild because its translation unit to be built first
// static won't redefine these symbols here
#include "plugin_bootloader.prx.inc.c"
#include "plugin_loader.prx.inc.c"
#include "plugin_server.prx.inc.c"

void upload_prx_to_disk(void) {
  write_blob(PRX_BOOTLOADER_PATH, plugin_bootloader_prx, plugin_bootloader_prx_len);
  write_blob(PRX_LOADER_PATH, plugin_loader_prx, plugin_loader_prx_len);
  write_blob(PRX_SERVER_PATH, plugin_server_prx, plugin_server_prx_len);
}
