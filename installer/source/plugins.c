#include "common.h"
#include "path.h"

#include "plugins.h"

// will force rebuild because its translation unit to be built first
// static won't redefine these symbols here
#include "plugin_bootloader.prx.inc.c"
#include "plugin_loader.prx.inc.c"
#include "plugin_server.prx.inc.c"
#include "plugin_mono.prx.inc.c"
#include "plugin_shellcore.prx.inc.c"

int upload_prx_to_disk(void) {
  int r = 0;
  r |= unchunk_decompress_and_write(plugin_bootloader_prx_chunks, plugin_bootloader_prx_chunk_lens, plugin_bootloader_prx_chunk_count, plugin_bootloader_prx_total_size, PRX_BOOTLOADER_PATH);
  r |= unchunk_decompress_and_write(plugin_loader_prx_chunks, plugin_loader_prx_chunk_lens, plugin_loader_prx_chunk_count, plugin_loader_prx_total_size, PRX_LOADER_PATH);
  r |= unchunk_decompress_and_write(plugin_mono_prx_chunks, plugin_mono_prx_chunk_lens, plugin_mono_prx_chunk_count, plugin_mono_prx_total_size, PRX_MONO_PATH);
  r |= unchunk_decompress_and_write(plugin_server_prx_chunks, plugin_server_prx_chunk_lens, plugin_server_prx_chunk_count, plugin_server_prx_total_size, PRX_SERVER_PATH);
  r |= unchunk_decompress_and_write(plugin_shellcore_prx_chunks, plugin_shellcore_prx_chunk_lens, plugin_shellcore_prx_chunk_count, plugin_shellcore_prx_total_size, PRX_SHELLCORE_PATH);
  return r;
}
