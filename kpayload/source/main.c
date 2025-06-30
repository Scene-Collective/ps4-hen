#include <stddef.h>
#include <stdint.h>

#include "amd_helper.h"
#include "ccp_helper.h"
#include "elf_helper.h"
#include "freebsd_helper.h"
#include "offsets.h"
#include "pfs_helper.h"
#include "rif_helper.h"
#include "sbl_helper.h"
#include "sections.h"
#include "self_helper.h"
#include "sparse.h"

#include "../../installer/include/config_struct.h"

uint16_t fw_version PAYLOAD_BSS = 0;
const struct kpayload_offsets *fw_offsets PAYLOAD_BSS = NULL;
struct configuration config PAYLOAD_BSS = {0};

int (*memcmp)(const void *ptr1, const void *ptr2, size_t num) PAYLOAD_BSS;
int (*_sx_xlock)(struct sx *sx, int opts, const char *file, int line) PAYLOAD_BSS;
int (*_sx_xunlock)(struct sx *sx) PAYLOAD_BSS;
void *(*malloc)(unsigned long size, void *type, int flags)PAYLOAD_BSS;
void (*free)(void *addr, void *type) PAYLOAD_BSS;
char *(*strstr)(const char *haystack, const char *needle)PAYLOAD_BSS;
int (*fpu_kern_enter)(struct thread *td, struct fpu_kern_ctx *ctx, uint32_t flags) PAYLOAD_BSS;
int (*fpu_kern_leave)(struct thread *td, struct fpu_kern_ctx *ctx) PAYLOAD_BSS;
void *(*memcpy)(void *dst, const void *src, size_t len)PAYLOAD_BSS;
void *(*memset)(void *s, int c, size_t n)PAYLOAD_BSS;
size_t (*strlen)(const char *str) PAYLOAD_BSS;
int (*printf)(const char *fmt, ...) PAYLOAD_BSS;
// Varies per FW
void (*eventhandler_register_old)(void *list, const char *name, void *func, void *arg, int priority) PAYLOAD_BSS; // < 5.50
void (*eventhandler_register)(void *list, const char *name, void *func, void *key, void *arg, int priority) PAYLOAD_BSS; // 5.50+ (Any changes after 6.72?)

void *M_TEMP PAYLOAD_BSS;
uint8_t *MINI_SYSCORE_SELF_BINARY PAYLOAD_BSS;
struct proc **ALLPROC PAYLOAD_BSS;
struct sbl_map_list_entry **SBL_DRIVER_MAPPED_PAGES PAYLOAD_BSS;
struct sx *SBL_PFS_SX PAYLOAD_BSS;
struct sbl_key_slot_queue *SBL_KEYMGR_KEY_SLOTS PAYLOAD_BSS;
struct sbl_key_rbtree_entry **SBL_KEYMGR_KEY_RBTREE PAYLOAD_BSS;
uint8_t *SBL_KEYMGR_BUF_VA PAYLOAD_BSS;
uint64_t *SBL_KEYMGR_BUF_GVA PAYLOAD_BSS;
void *FPU_CTX PAYLOAD_BSS;
struct sysent *SYSENT PAYLOAD_BSS;

// Fself
int (*sceSblACMgrGetPathId)(const char *path) PAYLOAD_BSS;
int (*sceSblServiceMailbox)(unsigned long service_id, uint8_t request[SBL_MSG_SERVICE_MAILBOX_MAX_SIZE], void *response) PAYLOAD_BSS;
int (*sceSblAuthMgrSmIsLoadable2)(struct self_context *ctx, struct self_auth_info *old_auth_info, int path_id, struct self_auth_info *new_auth_info) PAYLOAD_BSS;
int (*_sceSblAuthMgrGetSelfInfo)(struct self_context *ctx, struct self_ex_info **info) PAYLOAD_BSS;
void (*_sceSblAuthMgrSmStart)(void **) PAYLOAD_BSS;
int (*sceSblAuthMgrVerifyHeader)(struct self_context *ctx) PAYLOAD_BSS;

extern int my_sceSblAuthMgrIsLoadable2(struct self_context *ctx, struct self_auth_info *old_auth_info, int path_id, struct self_auth_info *new_auth_info) PAYLOAD_CODE;
extern int my_sceSblAuthMgrVerifyHeader(struct self_context *ctx) PAYLOAD_CODE;
extern int my_sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox(unsigned long service_id, uint8_t *request, void *response) PAYLOAD_CODE;
extern int my_sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox(unsigned long service_id, uint8_t *request, void *response) PAYLOAD_CODE;
extern int my_sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId(const char *path) PAYLOAD_CODE;

// Fpkg
int (*RsaesPkcs1v15Dec2048CRT)(struct rsa_buffer *out, struct rsa_buffer *in, struct rsa_key *key) PAYLOAD_BSS;
void (*Sha256Hmac)(uint8_t hash[0x20], const uint8_t *data, size_t data_size, const uint8_t *key, int key_size) PAYLOAD_BSS;
int (*AesCbcCfb128Encrypt)(uint8_t *out, const uint8_t *in, size_t data_size, const uint8_t *key, int key_size, uint8_t *iv) PAYLOAD_BSS;
int (*AesCbcCfb128Decrypt)(uint8_t *out, const uint8_t *in, size_t data_size, const uint8_t *key, int key_size, uint8_t *iv) PAYLOAD_BSS;
int (*sceSblDriverSendMsg_0)(struct sbl_msg *msg, size_t size) PAYLOAD_BSS;
int (*sceSblPfsSetKeys)(uint32_t *ekh, uint32_t *skh, uint8_t *eekpfs, struct ekc *eekc, unsigned int pubkey_ver, unsigned int key_ver, struct pfs_header *hdr, size_t hdr_size, unsigned int type, unsigned int finalized, unsigned int is_disc) PAYLOAD_BSS;
int (*sceSblKeymgrSetKeyStorage)(uint64_t key_gpu_va, unsigned int key_size, uint32_t key_id, uint32_t key_handle) PAYLOAD_BSS;
int (*sceSblKeymgrSetKeyForPfs)(union sbl_key_desc *key, unsigned int *handle) PAYLOAD_BSS;
int (*sceSblKeymgrCleartKey)(uint32_t kh) PAYLOAD_BSS;
int (*sceSblKeymgrSmCallfunc)(union keymgr_payload *payload) PAYLOAD_BSS;

extern int my_sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif(union keymgr_payload *payload) PAYLOAD_CODE;
extern int my_sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new(union keymgr_payload *payload) PAYLOAD_CODE;
extern int my_sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg(struct sbl_msg *msg, size_t size) PAYLOAD_CODE;
extern int my_mountpfs__sceSblPfsSetKeys(uint32_t *ekh, uint32_t *skh, uint8_t *eekpfs, struct ekc *eekc, unsigned int pubkey_ver, unsigned int key_ver, struct pfs_header *hdr, size_t hdr_size, unsigned int type, unsigned int finalized, unsigned int is_disc) PAYLOAD_CODE;

// Patch
struct vmspace *(*vmspace_acquire_ref)(struct proc *p)PAYLOAD_BSS;
void (*vmspace_free)(struct vmspace *vm) PAYLOAD_BSS;
void (*vm_map_lock_read)(struct vm_map *map) PAYLOAD_BSS;
void (*vm_map_unlock_read)(struct vm_map *map) PAYLOAD_BSS;
int (*vm_map_lookup_entry)(struct vm_map *map, uint64_t address, struct vm_map_entry **entries) PAYLOAD_BSS;
int (*proc_rwmem)(struct proc *p, struct uio *uio) PAYLOAD_BSS;

int (*sys_dynlib_load_prx)(void *param_1, void *param_2) PAYLOAD_BSS;
int (*sys_dynlib_dlsym)(void *param_1, void *param_2) PAYLOAD_BSS;

// initialization, etc
extern void install_fself_hooks(void) PAYLOAD_CODE;
extern void install_fpkg_hooks(void) PAYLOAD_CODE;
extern void install_patches(void) PAYLOAD_CODE;
extern void install_syscall_hooks(void) PAYLOAD_CODE;
extern void *get_syscall(uint64_t n) PAYLOAD_CODE;

#define resolve(name) name = (void *)(kernbase + fw_offsets->name##_addr)

PAYLOAD_CODE void resolve_kdlsym() {
  uint64_t kernbase = getkernbase(fw_offsets->XFAST_SYSCALL_addr);

  // data
  resolve(M_TEMP);
  resolve(MINI_SYSCORE_SELF_BINARY);
  resolve(ALLPROC);
  resolve(SBL_DRIVER_MAPPED_PAGES);
  resolve(SBL_PFS_SX);
  resolve(SBL_KEYMGR_KEY_SLOTS);
  resolve(SBL_KEYMGR_KEY_RBTREE);
  resolve(SBL_KEYMGR_BUF_VA);
  resolve(SBL_KEYMGR_BUF_GVA);
  resolve(FPU_CTX);
  resolve(SYSENT);

  // common
  resolve(memcmp);
  resolve(_sx_xlock);
  resolve(_sx_xunlock);
  resolve(malloc);
  resolve(free);
  resolve(strstr);
  resolve(fpu_kern_enter);
  resolve(fpu_kern_leave);
  resolve(memcpy);
  resolve(memset);
  resolve(strlen);
  resolve(printf);
  resolve(eventhandler_register);
  eventhandler_register_old = (void *)eventhandler_register;

  // Fself
  resolve(sceSblACMgrGetPathId);
  resolve(sceSblServiceMailbox);
  resolve(sceSblAuthMgrSmIsLoadable2);
  resolve(_sceSblAuthMgrGetSelfInfo);
  resolve(_sceSblAuthMgrSmStart);
  resolve(sceSblAuthMgrVerifyHeader);

  // Fpkg
  resolve(sceSblPfsSetKeys);
  resolve(sceSblKeymgrCleartKey);
  resolve(sceSblKeymgrSetKeyForPfs);
  resolve(sceSblKeymgrSetKeyStorage);
  resolve(sceSblKeymgrSmCallfunc);
  resolve(sceSblDriverSendMsg_0);
  resolve(RsaesPkcs1v15Dec2048CRT);
  resolve(AesCbcCfb128Encrypt);
  resolve(AesCbcCfb128Decrypt);
  resolve(Sha256Hmac);

  // Patch
  resolve(proc_rwmem);
  resolve(vmspace_acquire_ref);
  resolve(vmspace_free);
  resolve(vm_map_lock_read);
  resolve(vm_map_unlock_read);
  resolve(vm_map_lookup_entry);
}

PAYLOAD_CODE int my_hex_to_int(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  }
  if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  }
  return -1;
}

PAYLOAD_CODE int my_is_space(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

PAYLOAD_CODE int my_strlen(const char *str) {
  int len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

PAYLOAD_CODE uintptr_t pattern_scan(const uintptr_t base, const uintptr_t base_size, const char *pattern) {
  if (!base || !base_size || !pattern) {
    return 0;
  }

  const uint8_t *memory = (const uint8_t *)base;
  const int pattern_len = my_strlen(pattern);

  int byte_count = 0;
  for (int i = 0; i < pattern_len; i++) {
    if (!my_is_space(pattern[i])) {
      if (pattern[i] == '?') {
        byte_count++;
        if (i + 1 < pattern_len && pattern[i + 1] == '?') {
          i++;
        }
      } else if (my_hex_to_int(pattern[i]) >= 0) {
        if (i + 1 < pattern_len && my_hex_to_int(pattern[i + 1]) >= 0) {
          i++;
        }
        byte_count++;
      }
    }
  }

  if (byte_count == 0 || (uintptr_t)byte_count > base_size) {
    return 0;
  }

  for (uintptr_t mem_offset = 0; mem_offset <= base_size - byte_count; mem_offset++) {
    int pattern_pos = 0;
    int byte_pos = 0;
    int match = 1;

    while (pattern_pos < pattern_len && byte_pos < byte_count && match) {
      while (pattern_pos < pattern_len && my_is_space(pattern[pattern_pos])) {
        pattern_pos++;
      }

      if (pattern_pos >= pattern_len) {
        break;
      }

      if (pattern[pattern_pos] == '?') {
        pattern_pos++;
        if (pattern_pos < pattern_len && pattern[pattern_pos] == '?') {
          pattern_pos++;
        }
        byte_pos++;
      } else if (my_hex_to_int(pattern[pattern_pos]) >= 0) {
        int high = my_hex_to_int(pattern[pattern_pos]);
        int low = 0;

        pattern_pos++;
        if (pattern_pos < pattern_len && my_hex_to_int(pattern[pattern_pos]) >= 0) {
          low = my_hex_to_int(pattern[pattern_pos]);
          pattern_pos++;
        } else {
          low = high;
          high = 0;
        }

        uint8_t expected_byte = (uint8_t)((high << 4) | low);
        if (memory[mem_offset + byte_pos] != expected_byte) {
          match = 0;
        }
        byte_pos++;
      } else {
        pattern_pos++;
      }
    }

    if (match && byte_pos == byte_count) {
      return base + mem_offset;
    }
  }

  return 0;
}

PAYLOAD_CODE uintptr_t pattern_scan_offset(const uintptr_t base, const uintptr_t base_size, const char *pattern, const size_t ret_offset) {
  const uintptr_t r = pattern_scan(base, base_size, pattern);
  return r ? r + ret_offset : 0;
}

static PAYLOAD_CODE void get_memory_dump(uintptr_t addr, void *out, uint64_t outsz) {
  uint8_t *pout = (uint8_t *)out;
  uint8_t *paddr = (uint8_t *)addr;
  for (uint64_t o = 0; o < outsz; o++) {
    pout[o] = paddr[o];
  }
}

static PAYLOAD_CODE uint64_t get_kernel_size(uint64_t kernel_base) {
  if (!kernel_base) {
    return 0;
  }
  uint16_t elf_header_size;       // ELF header size
  uint16_t elf_header_entry_size; // ELF header entry size
  uint16_t num_of_elf_entries;    // Number of entries in the ELF header

  get_memory_dump(kernel_base + 0x34, &elf_header_size, sizeof(uint16_t));
  get_memory_dump(kernel_base + 0x34 + sizeof(uint16_t), &elf_header_entry_size, sizeof(uint16_t));
  get_memory_dump(kernel_base + 0x34 + (sizeof(uint16_t) * 2), &num_of_elf_entries, sizeof(uint16_t));

  // printf_debug("elf_header_size: %u bytes\n", elf_header_size);
  // printf_debug("elf_header_entry_size: %u bytes\n", elf_header_entry_size);
  // printf_debug("num_of_elf_entries: %u\n", num_of_elf_entries);

  uint64_t max = 0;
  for (int i = 0; i < num_of_elf_entries; i++) {
    uint64_t temp_memsz;
    uint64_t temp_vaddr;
    uint64_t temp_align;
    uint64_t temp_max;

    uint64_t memsz_offset = elf_header_size + (i * elf_header_entry_size) + 0x28;
    uint64_t vaddr_offset = elf_header_size + (i * elf_header_entry_size) + 0x10;
    uint64_t align_offset = elf_header_size + (i * elf_header_entry_size) + 0x30;
    get_memory_dump(kernel_base + memsz_offset, &temp_memsz, sizeof(uint64_t));
    get_memory_dump(kernel_base + vaddr_offset, &temp_vaddr, sizeof(uint64_t));
    get_memory_dump(kernel_base + align_offset, &temp_align, sizeof(uint64_t));

    temp_vaddr -= kernel_base;
    temp_vaddr += 0xFFFFFFFF82200000;

    temp_max = (temp_vaddr + temp_memsz + (temp_align - 1)) & ~(temp_align - 1);

    if (temp_max > max) {
      max = temp_max;
    }
  }

  return max - 0xFFFFFFFF82200000;
}

PAYLOAD_CODE static void resolve_syscall(void) {
  sys_dynlib_load_prx = get_syscall(594);
  sys_dynlib_dlsym = get_syscall(591);
}

PAYLOAD_CODE static void resolve_patterns(void) {
  return;
  uint64_t flags, cr0;
  cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);
  flags = intr_disable();

  const uint64_t kernbase = getkernbase(fw_offsets->XFAST_SYSCALL_addr);
  const uint64_t kernsize = get_kernel_size(kernbase);

  if (kernbase && kernsize) {
    // only stack size difference
    sys_dynlib_load_prx = (void *)pattern_scan(kernbase, kernsize, "55 48 89 e5 41 57 41 56 41 55 41 54 53 48 81 ec 88 05 00 00 48 8d 1d ? ? ? ? 48 8b 03 48 89 45 d0 48 8b 47 08 4c 8b b8 40 03 00 00");
    sys_dynlib_dlsym = (void *)pattern_scan(kernbase, kernsize, "55 48 89 e5 41 57 41 56 41 55 41 54 53 48 81 ec d8 0a 00 00 48 8d 1d ? ? ? ? 48 8b 03 48 89 45 d0 48 8b 47 08 4c 8b a0 40 03 00 00");
  }

  intr_restore(flags);
  writeCr0(cr0);
}

PAYLOAD_CODE int my_entrypoint(uint16_t fw_version_arg, struct configuration config_arg) {
  fw_version = fw_version_arg;
  fw_offsets = get_offsets_for_fw(fw_version);
  if (!fw_offsets) {
    return -1;
  }
  resolve_kdlsym();
  memcpy(&config, &config_arg, sizeof(struct configuration));
  printf("Hello from KPayload: %i\n", fw_version);
  install_fself_hooks();
  install_fpkg_hooks();
  if (!config.skip_patches) {
    install_patches();
  }
  if (config.enable_plugins) {
    resolve_patterns();
    resolve_syscall();
    install_syscall_hooks();
  }

  return 0;
}

struct {
  uint64_t signature;
  void *entrypoint;
} payload_header PAYLOAD_HEADER = {
    0x5041594C4F414458ull, // `payloadx`
    &my_entrypoint,
};

int _start() {
  return 0;
}
