#include <stddef.h>
#include <stdint.h>

#include "amd_helper.h"
#include "freebsd_helper.h"
#include "offsets.h"
#include "sections.h"
#include "sparse.h"

extern uint16_t fw_version PAYLOAD_BSS;
extern const struct kpayload_offsets *fw_offsets PAYLOAD_BSS;

extern int (*proc_rwmem)(struct proc *p, struct uio *uio) PAYLOAD_BSS;
extern struct vmspace *(*vmspace_acquire_ref)(struct proc *p)PAYLOAD_BSS;
extern void (*vmspace_free)(struct vmspace *vm) PAYLOAD_BSS;
extern void (*vm_map_lock_read)(struct vm_map *map) PAYLOAD_BSS;
extern void (*vm_map_unlock_read)(struct vm_map *map) PAYLOAD_BSS;
extern int (*vm_map_lookup_entry)(struct vm_map *map, uint64_t address, struct vm_map_entry **entries) PAYLOAD_BSS;

extern size_t (*strlen)(const char *str) PAYLOAD_BSS;
extern void *(*malloc)(unsigned long size, void *type, int flags)PAYLOAD_BSS;
extern void (*free)(void *addr, void *type) PAYLOAD_BSS;
extern void *(*memcpy)(void *dst, const void *src, size_t len)PAYLOAD_BSS;
extern void *(*memset)(void *s, int c, size_t n)PAYLOAD_BSS;
extern int (*memcmp)(const void *ptr1, const void *ptr2, size_t num) PAYLOAD_BSS;
// Varies per FW
extern void (*eventhandler_register_old)(void *list, const char *name, void *func, void *arg, int priority) PAYLOAD_BSS; // < 5.50
extern void (*eventhandler_register)(void *list, const char *name, void *func, void *key, void *arg, int priority) PAYLOAD_BSS; // 5.50+ (Any changes after 6.72?)

extern void *M_TEMP PAYLOAD_BSS;
extern struct proc **ALLPROC PAYLOAD_BSS;

PAYLOAD_CODE static inline void *alloc(uint32_t size) {
  return malloc(size, M_TEMP, 2);
}

PAYLOAD_CODE static inline void dealloc(void *addr) {
  free(addr, M_TEMP);
}

PAYLOAD_CODE static struct proc *proc_find_by_name(const char *name) {
  struct proc *p;

  if (!name) {
    return NULL;
  }

  p = *ALLPROC;

  do {
    if (!memcmp(p->p_comm, name, strlen(name))) {
      return p;
    }
  } while ((p = p->p_forw));

  return NULL;
}

PAYLOAD_CODE static int proc_get_vm_map(struct proc *p, struct proc_vm_map_entry **entries, size_t *num_entries) {
  struct proc_vm_map_entry *info = NULL;
  struct vm_map_entry *entry = NULL;

  struct vmspace *vm = vmspace_acquire_ref(p);
  if (!vm) {
    return -1;
  }

  struct vm_map *map = &vm->vm_map;

  int num = map->nentries;
  if (!num) {
    vmspace_free(vm);
    return 0;
  }

  vm_map_lock_read(map);

  if (vm_map_lookup_entry(map, 0, &entry)) {
    vm_map_unlock_read(map);
    vmspace_free(vm);
    return -1;
  }

  info = (struct proc_vm_map_entry *)alloc(num * sizeof(struct proc_vm_map_entry));
  if (!info) {
    vm_map_unlock_read(map);
    vmspace_free(vm);
    return -1;
  }

  for (int i = 0; i < num; i++) {
    info[i].start = entry->start;
    info[i].end = entry->end;
    info[i].offset = entry->offset;
    info[i].prot = entry->prot & (entry->prot >> 8);
    memcpy(info[i].name, entry->name, sizeof(info[i].name));

    if (!(entry = entry->next)) {
      break;
    }
  }

  vm_map_unlock_read(map);
  vmspace_free(vm);

  if (entries) {
    *entries = info;
  }

  if (num_entries) {
    *num_entries = num;
  }

  return 0;
}

PAYLOAD_CODE static int proc_rw_mem(struct proc *p, void *ptr, size_t size, void *data, size_t *n, int write) {
  struct thread *td = curthread();
  struct iovec iov;
  struct uio uio;
  int r = 0;

  if (!p) {
    return -1;
  }

  if (size == 0) {
    if (n) {
      *n = 0;
    }

    return 0;
  }

  memset(&iov, 0, sizeof(iov));
  iov.iov_base = (uint64_t)data;
  iov.iov_len = size;

  memset(&uio, 0, sizeof(uio));
  uio.uio_iov = (uint64_t)&iov;
  uio.uio_iovcnt = 1;
  uio.uio_offset = (uint64_t)ptr;
  uio.uio_resid = (uint64_t)size;
  uio.uio_segflg = UIO_SYSSPACE;
  uio.uio_rw = write ? UIO_WRITE : UIO_READ;
  uio.uio_td = td;

  r = proc_rwmem(p, &uio);

  if (n) {
    *n = (size_t)((uint64_t)size - uio.uio_resid);
  }

  return r;
}

PAYLOAD_CODE static inline int proc_write_mem(struct proc *p, void *ptr, size_t size, void *data, size_t *n) {
  return proc_rw_mem(p, ptr, size, data, n, 1);
}

PAYLOAD_CODE int shellcore_patch(void) {
  uint8_t *text_seg_base = NULL;
  size_t n;

  struct proc_vm_map_entry *entries = NULL;
  size_t num_entries = 0;

  int ret = 0;

  // clang-format off
  uint32_t call_ofs_for__xor__eax_eax__jmp[] = {
    // call sceKernelIsGenuineCEX
    fw_offsets->sceKernelIsGenuineCEX_patch1,
    fw_offsets->sceKernelIsGenuineCEX_patch2,
    fw_offsets->sceKernelIsGenuineCEX_patch3,
    fw_offsets->sceKernelIsGenuineCEX_patch4,
    // call nidf_libSceDipsw
    fw_offsets->nidf_libSceDipsw_patch1,
    fw_offsets->nidf_libSceDipsw_patch2,
    fw_offsets->nidf_libSceDipsw_patch3,
    fw_offsets->nidf_libSceDipsw_patch4,
  };
  // clang-format on

  struct proc *ssc = proc_find_by_name("SceShellCore");

  if (!ssc) {
    ret = -1;
    goto error;
  }

  ret = proc_get_vm_map(ssc, &entries, &num_entries);
  if (ret) {
    goto error;
  }

  for (size_t i = 0; i < num_entries; i++) {
    if (entries[i].prot == (PROT_READ | PROT_EXEC)) {
      text_seg_base = (uint8_t *)entries[i].start;
      break;
    }
  }

  if (!text_seg_base) {
    ret = -1;
    goto error;
  }

  // enable installing of debug packages
  for (size_t i = 0; i < COUNT_OF(call_ofs_for__xor__eax_eax__jmp); i++) {
    ret = proc_write_mem(ssc, (void *)(text_seg_base + call_ofs_for__xor__eax_eax__jmp[i]), 4, "\x31\xC0\xEB\x01", &n);
    if (ret) {
      goto error;
    }
  }

  // check_disc_root_param_patch
  // Varies per FW
  if (fw_version <= 904) {
    ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->check_disc_root_param_patch), 2, "\x90\xE9", &n);
    if (ret) {
      goto error;
    }
  }

  // app_installer_patch
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->app_installer_patch), 1, "\xEB", &n);
  if (ret) {
    goto error;
  }

  // check_system_version
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->check_system_version), 1, "\xEB", &n);
  if (ret) {
    goto error;
  }

  // check_title_system_update_patch
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->check_title_system_update_patch), 4, "\x48\x31\xC0\xC3", &n);
  if (ret) {
    goto error;
  }

  // allow SceShellCore to mount /data into an app's sandbox
  ret = proc_write_mem(ssc, text_seg_base + fw_offsets->enable_data_mount_patch, 5, "\x31\xC0\xFF\xC0\x90", &n);
  if (ret) {
    goto error;
  }

  // enable ps vr without spoofer
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->enable_psvr_patch), 3, "\x31\xC0\xC3", &n);
  if (ret) {
    goto error;
  }

  // enable fpkg for patches
  // Varies per FW
  const char *enable_fpkg_patch_data;
  if (fw_version >= 500 && fw_version <= 620) {
    enable_fpkg_patch_data = "\xE9\x96\x00\x00\x00";
  } else if (fw_version >= 650 && fw_version <= 1202) {
    enable_fpkg_patch_data = "\xE9\x98\x00\x00\x00";
  } else {
    enable_fpkg_patch_data = "\xE9\x98\x00\x00\x00";
  }
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->enable_fpkg_patch), 5, (void *)enable_fpkg_patch_data, &n);
  if (ret) {
    goto error;
  }

  // this offset corresponds to "fake" string in the SceShellCore's memory
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->fake_free_patch), 4, "free", &n);
  if (ret) {
    goto error;
  }

  // make pkgs installer working with external hdd
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->pkg_installer_patch), 1, "\x00", &n);
  if (ret) {
    goto error;
  }

  // enable support with 6.xx external hdd
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->ext_hdd_patch), 1, "\xEB", &n);
  if (ret) {
    goto error;
  }

  // enable debug trophies on retail
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->debug_trophies_patch), 4, "\x31\xC0\xEB\x01", &n);
  if (ret) {
    goto error;
  }

  // never disable screenshot
  ret = proc_write_mem(ssc, (void *)(text_seg_base + fw_offsets->disable_screenshot_patch), 2, "\xEB\x03", &n);
  if (ret) {
    goto error;
  }

error:
  if (entries) {
    dealloc(entries);
  }

  return ret;
}

PAYLOAD_CODE int shellui_patch(void) {
  uint8_t *libkernel_sys_base = NULL;
  uint8_t *executable_base = NULL;
  uint8_t *app_base = NULL;
  size_t n;

  struct proc_vm_map_entry *entries = NULL;
  size_t num_entries = 0;

  int ret = 0;

  struct proc *ssu = proc_find_by_name("SceShellUI");

  if (!ssu) {
    ret = -1;
    goto error;
  }

  ret = proc_get_vm_map(ssu, &entries, &num_entries);
  if (ret) {
    goto error;
  }

  for (size_t i = 0; i < num_entries; i++) {
    if (!memcmp(entries[i].name, "executable", 10) && (entries[i].prot >= (PROT_READ | PROT_EXEC))) {
      executable_base = (uint8_t *)entries[i].start;
      break;
    }
  }

  if (!executable_base) {
    ret = 1;
    goto error;
  }

  // disable CreateUserForIDU
  ret = proc_write_mem(ssu, (void *)(executable_base + fw_offsets->CreateUserForIDU_patch), 4, "\x48\x31\xC0\xC3", &n);
  if (ret) {
    goto error;
  }

  for (size_t i = 0; i < num_entries; i++) {
    if (!memcmp(entries[i].name, "app.exe.sprx", 12) && (entries[i].prot >= (PROT_READ | PROT_EXEC))) {
      app_base = (uint8_t *)entries[i].start;
      break;
    }
  }

  if (!app_base) {
    ret = 1;
    goto error;
  }

  // enable remote play menu - credits to Aida
  // Varies per FW
  const char *remote_play_patch_data;
  if (fw_version >= 500 && fw_version <= 507) {
    remote_play_patch_data = "\xE9\x82\x02\x00\x00";
  } else if (fw_version >= 550 && fw_version <= 620) {
    remote_play_patch_data = "\xE9\xB8\x02\x00\x00";
  } else if (fw_version >= 650 && fw_version <= 904) {
    remote_play_patch_data = "\xE9\xBA\x02\x00\x00";
  } else if (fw_version >= 950 && fw_version <= 960) {
    remote_play_patch_data = "\xE9\xA2\x02\x00\x00";
  } else if (fw_version >= 1000 && fw_version <= 1202) {
    remote_play_patch_data = "\xE9\x5C\x02\x00\x00";
  } else {
    remote_play_patch_data = "\xE9\x5C\x02\x00\x00";
  }
  ret = proc_write_mem(ssu, (void *)(app_base + fw_offsets->remote_play_menu_patch), 5, (void *)remote_play_patch_data, &n);
  if (ret) {
    goto error;
  }

  for (size_t i = 0; i < num_entries; i++) {
    if (!memcmp(entries[i].name, "libkernel_sys.sprx", 18) && (entries[i].prot >= (PROT_READ | PROT_EXEC))) {
      libkernel_sys_base = (uint8_t *)entries[i].start;
      break;
    }
  }

  if (!libkernel_sys_base) {
    ret = -1;
    goto error;
  }

  // enable debug settings menu
  ret = proc_write_mem(ssu, (void *)(libkernel_sys_base + fw_offsets->sceSblRcMgrIsAllowDebugMenuForSettings_patch), 6, "\xB8\x01\x00\x00\x00\xC3", &n);
  if (ret) {
    goto error;
  }

  ret = proc_write_mem(ssu, (void *)(libkernel_sys_base + fw_offsets->sceSblRcMgrIsStoreMode_patch), 6, "\xB8\x01\x00\x00\x00\xC3", &n);
  if (ret) {
    goto error;
  }

error:
  if (entries) {
    dealloc(entries);
  }

  return ret;
}

PAYLOAD_CODE int remoteplay_patch(void) {
  uint8_t *executable_base = NULL;

  struct proc_vm_map_entry *entries = NULL;
  size_t num_entries;
  size_t n;

  int ret = 0;

  struct proc *srp = proc_find_by_name("SceRemotePlay");

  if (!srp) {
    ret = 1;
    goto error;
  }

  if (proc_get_vm_map(srp, &entries, &num_entries)) {
    ret = 1;
    goto error;
  }

  for (size_t i = 0; i < num_entries; i++) {
    if (!memcmp(entries[i].name, "executable", 10) && (entries[i].prot == (PROT_READ | PROT_EXEC))) {
      executable_base = (uint8_t *)entries[i].start;
      break;
    }
  }

  if (!executable_base) {
    ret = 1;
    goto error;
  }

  // patch SceRemotePlay process
  ret = proc_write_mem(srp, (void *)(executable_base + fw_offsets->SceRemotePlay_patch1), 1, "\x01", &n);
  if (ret) {
    goto error;
  }

  ret = proc_write_mem(srp, (void *)(executable_base + fw_offsets->SceRemotePlay_patch2), 2, "\xEB\x1E", &n);
  if (ret) {
    goto error;
  }

error:
  if (entries) {
    dealloc(entries);
  }

  return ret;
}

PAYLOAD_CODE void apply_patches() {
  shellui_patch();
  remoteplay_patch();
  shellcore_patch();
}

PAYLOAD_CODE void install_patches() {
  apply_patches();

  // Varies per FW
  if (fw_version <= 550) {
    // eventhandler_register_old(NULL, "system_suspend_phase3", &function_name, NULL, EVENTHANDLER_PRI_PRE_FIRST); // < 5.50
    eventhandler_register_old(NULL, "system_resume_phase4", &apply_patches, NULL, EVENTHANDLER_PRI_LAST); // < 5.50
  } else {
    // eventhandler_register(NULL, "system_suspend_phase3", &function_name, "hen_resume_patches", NULL, EVENTHANDLER_PRI_PRE_FIRST); // 5.50+ (Any changes after 6.72?)
    eventhandler_register(NULL, "system_resume_phase4", &apply_patches, "hen_resume_patches", NULL, EVENTHANDLER_PRI_LAST); // 5.50+ (Any changes after 6.72?)
  }
}
