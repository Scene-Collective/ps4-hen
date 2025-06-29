#include <ps4.h>

#include "common.h"

void write_blob(const char *path, const void *blob, const size_t blobsz) {
  int fd = open(path, O_CREAT | O_RDWR, 0777);
  printf_debug("fd %s %d\n", path, fd);
  if (fd > 0) {
    write(fd, blob, blobsz);
    close(fd);
  } else {
    printf_notification("Failed to write %s!\nFile descriptor %d", path, fd);
  }
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
  // Delete existing updates
  unlink("/update/PS4UPDATE.PUP");
  unlink("/update/PS4UPDATE.PUP.net.temp");

  // Unmount update directory. From etaHEN
  if ((int)unmount("/update", 0x80000LL) < 0) {
    unmount("/update", 0);
  }
}
