#include <ps4.h>

#include "common.h"

#define PS4UPDATE_FILE "/update/PS4UPDATE.PUP"
#define PS4UPDATE_TEMP_FILE "/update/PS4UPDATE.PUP.net.temp"

void write_blob(const char *path, const void *blob, const size_t blobsz) {
  if (!path || !blob || blobsz == 0) {
    printf_notification("Invalid parameters for write_blob");
    return;
  }

  if (file_exists(path)) {
    unlink(path);
  }
  int fd = open(path, O_CREAT | O_RDWR, 0777);
  printf_debug("fd %s %d\n", path, fd);
  if (fd > 0) {
    ssize_t written = write(fd, blob, blobsz);
    if (written != (ssize_t)blobsz) {
      printf_notification("Partial write to %s: %zd/%zu bytes", path, written, blobsz);
    }
    close(fd);
  } else {
    printf_notification("Failed to write %s!\nFile descriptor %d", path, fd);
  }
}

const unsigned char *decompress_zlib(const unsigned char *zlib_data, size_t zlib_len, size_t *out_size) {
  int r = sceZlibInitialize(NULL, 0);
  if (r < 0) {
    printf_debug("sceZlibInitialize failed 0x%08x\n", r);
    return NULL;
  }

  size_t decompressed_max_size = 64 * 1024;
  uint8_t *dst = malloc(decompressed_max_size);
  if (!dst) {
    printf_debug("dst == NULL\n");
    sceZlibFinalize();
    return NULL;
  }

  uint64_t req_id;
  r = sceZlibInflate(zlib_data, zlib_len, dst, decompressed_max_size, &req_id);
  if (r < 0) {
    printf_debug("sceZlibInflate failed 0x%08x\n", r);
    free(dst);
    sceZlibFinalize();
    return NULL;
  }

  uint64_t done_id;
  r = sceZlibWaitForDone(&done_id, NULL);
  if (r < 0) {
    printf_debug("sceZlibWaitForDone failed 0x%08x\n", r);
    free(dst);
    sceZlibFinalize();
    return NULL;
  }

  int status;
  uint32_t destination_len;
  r = sceZlibGetResult(done_id, &destination_len, &status);
  if (r < 0) {
    printf_debug("sceZlibGetResult failed 0x%08x\n", r);
    free(dst);
    sceZlibFinalize();
    return NULL;
  }

  r = sceZlibFinalize();
  if (r < 0) {
    printf_debug("sceZlibFinalize failed 0x%08x\n", r);
    free(dst);
    return NULL;
  }

  if (out_size) {
    *out_size = destination_len;
  }
  return (const unsigned char *)dst;
}

const unsigned char *decompress_chunked_zlib(const unsigned char **chunk_ptrs, const size_t *chunk_lens, const size_t num_chunks, const size_t expected_decompressed_len) {
  size_t total_decompressed = 0;
  unsigned char *all_decompressed = malloc(expected_decompressed_len);
  printf_debug("all_decompressed: 0x%p\n", all_decompressed);
  if (!all_decompressed) {
    return NULL;
  }

  printf_debug("num_chunks: %lu\n", num_chunks);
  for (size_t i = 0; i < num_chunks; ++i) {
    size_t chunk_decompressed_len = 0;
    const unsigned char *chunk_decompressed = decompress_zlib(chunk_ptrs[i], chunk_lens[i], &chunk_decompressed_len);
    printf_debug("chunk_decompressed[%lu]\n", i);
    printf_debug("chunk_decompressed_len: %lu\n", chunk_decompressed_len);
    if (!chunk_decompressed || total_decompressed + chunk_decompressed_len > expected_decompressed_len) {
      printf_debug("if (!chunk_decompressed || total_decompressed + chunk_decompressed_len > expected_decompressed_len)\n");
      // handle error: decompression failed or overflow
      free((void *)chunk_decompressed);
      free(all_decompressed);
      return NULL;
    }
    memcpy(all_decompressed + total_decompressed, chunk_decompressed, chunk_decompressed_len);
    total_decompressed += chunk_decompressed_len;
    free((void *)chunk_decompressed);
  }

  if (total_decompressed == expected_decompressed_len) {
    return all_decompressed;
  } else {
    // handle error: decompressed size mismatch
    free(all_decompressed);
    return NULL;
  }
}

int unchunk_decompress_and_write(const unsigned char **chunk_ptrs, const size_t *chunk_lens, const size_t num_chunks, const size_t expected_decompressed_len, const char *out_path) {
  const unsigned char *all_decompressed = decompress_chunked_zlib(chunk_ptrs, chunk_lens, num_chunks, expected_decompressed_len);
  if (all_decompressed) {
    write_blob(out_path, all_decompressed, expected_decompressed_len);
    free((void *)all_decompressed);
  } else {
    printf_debug("failed to decompress %s\n", out_path);
    return 1;
  }
  return 0;
}

void kill_proc(const char *proc) {
  if (!proc) {
    return;
  }
  const int party = findProcess(proc);
  printf_debug("%s %d\n", proc, party);
  if (party > 0) {
    const int k = kill(party, SIGKILL);
    printf_debug("sent SIGKILL(%d) to %s(%d)\n", k, proc, party);
  }
}

void block_updates(void) {
  // Delete existing updates/blocker and recreate
  unlink(PS4UPDATE_FILE);
  rmdir(PS4UPDATE_FILE);
  mkdir(PS4UPDATE_FILE, 777);

  unlink(PS4UPDATE_TEMP_FILE);
  rmdir(PS4UPDATE_TEMP_FILE);
  mkdir(PS4UPDATE_TEMP_FILE, 777);

  // Unmount update directory. From etaHEN
  if ((int)unmount("/update", 0x80000LL) < 0) {
    unmount("/update", 0);
  }
}
