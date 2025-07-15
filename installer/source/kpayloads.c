#include <ps4.h>

#include "config_struct.h"
#include "offsets.h"

#include "kpayloads.h"

#include "kpayload.inc.c"

#define KERNEL_BASE_FILE 0xFFFFFFFF82200000

#define patch_macro(x)                                                                           \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL];                      \
  kernel_ptr = (uint8_t *)kernel_base;                                                           \
  uart_patch = &kernel_ptr[K##x##_UART_PATCH];                                                   \
  /* is_diag_process_patch = &kernel_ptr[K##x##_IS_DIAG_PROCESS_PATCH]; */                       \
  /* allow_system_level_logging_patch = &kernel_ptr[K##x##_ALLOW_SYSTEM_LEVEL_LOGGING_PATCH]; */ \
  /* allow_coredump_patch = &kernel_ptr[K##x##_ALLOW_COREDUMP_PATCH]; */                         \
  copyin_patch_1 = &kernel_ptr[K##x##_COPYIN_PATCH_1];                                           \
  copyin_patch_2 = &kernel_ptr[K##x##_COPYIN_PATCH_2];                                           \
  copyout_patch_1 = &kernel_ptr[K##x##_COPYOUT_PATCH_1];                                         \
  copyout_patch_2 = &kernel_ptr[K##x##_COPYOUT_PATCH_2];                                         \
  copyinstr_patch_1 = &kernel_ptr[K##x##_COPYINSTR_PATCH_1];                                     \
  copyinstr_patch_2 = &kernel_ptr[K##x##_COPYINSTR_PATCH_2];                                     \
  copyinstr_patch_3 = &kernel_ptr[K##x##_COPYINSTR_PATCH_3];                                     \
  setlogin_patch = &kernel_ptr[K##x##_SETLOGIN_PATCH];                                           \
  pfs_signature_check_patch = &kernel_ptr[K##x##_PFS_SIGNATURE_CHECK_PATCH];                     \
  debug_rif_patch_1 = &kernel_ptr[K##x##_DEBUG_RIF_PATCH_1];                                     \
  debug_rif_patch_2 = &kernel_ptr[K##x##_DEBUG_RIF_PATCH_2];                                     \
  debug_settings_error_patch_1 = &kernel_ptr[K##x##_DEBUG_SETTINGS_ERROR_PATCH_1];               \
  debug_settings_error_patch_2 = &kernel_ptr[K##x##_DEBUG_SETTINGS_ERROR_PATCH_2];               \
  /* mount_patch = &kernel_ptr[K##x##_MOUNT_PATCH]; */                                           \
  depth_limit_patch = &kernel_ptr[K##x##_DEPTH_LIMIT_PATCH];

#define install_macro(x)                                                    \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  kernel_pmap_store = &kernel_ptr[K##x##_PMAP_STORE];                       \
  pmap_protect_p_patch = &kernel_ptr[K##x##_PMAP_PROTECT_P];                \
  pmap_protect = (void *)(kernel_base + K##x##_PMAP_PROTECT);

struct kpayload_payload_header {
  uint64_t signature;
  size_t entrypoint_offset;
};

struct kpayload_payload_info {
  uint16_t fw_version;
  struct configuration config;
  uint8_t *buffer;
  size_t size;
};

struct kpayload_install_payload_args {
  void *syscall_handler;
  struct kpayload_payload_info *kpayload_payload_info;
};

// Return 0 on success
// Return -1 on unsupported firmware error
// Can also just give a memory error in the browser or panic the console on failure
static int kpayload_patches(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  // Use "kmem" for all patches
  uint8_t *kmem;

  // Pointers to be assigned in build_kpayload macro
  uint8_t *uart_patch;
  // uint8_t *is_diag_process_patch;
  // uint8_t *allow_system_level_logging_patch;
  // uint8_t *allow_coredump_patch;
  uint8_t *copyin_patch_1;
  uint8_t *copyin_patch_2;
  uint8_t *copyout_patch_1;
  uint8_t *copyout_patch_2;
  uint8_t *copyinstr_patch_1;
  uint8_t *copyinstr_patch_2;
  uint8_t *copyinstr_patch_3;
  uint8_t *setlogin_patch;
  uint8_t *pfs_signature_check_patch;
  uint8_t *debug_rif_patch_1;
  uint8_t *debug_rif_patch_2;
  uint8_t *debug_settings_error_patch_1;
  uint8_t *debug_settings_error_patch_2;
  // uint8_t *mount_patch;
  uint8_t *depth_limit_patch;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, patch_macro);

  // Disable write protection
  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  // Enable UART
  kmem = (uint8_t *)uart_patch;
  kmem[0] = 0x00;

  // sceSblACMgrIsDiagProcess
  // kmem = (uint8_t *)is_diag_process_patch;
  // kmem[0] = 0xB8;
  // kmem[1] = 0x01;
  // kmem[2] = 0x00;
  // kmem[3] = 0x00;
  // kmem[4] = 0x00;
  // kmem[5] = 0xC3;

  // sceSblACMgrIsAllowedSystemLevelDebugging
  // kmem = (uint8_t *)allow_system_level_logging_patch;
  // kmem[0] = 0xB8;
  // kmem[1] = 0x01;
  // kmem[2] = 0x00;
  // kmem[3] = 0x00;
  // kmem[4] = 0x00;
  // kmem[5] = 0xC3;

  // sceSblACMgrIsAllowedCoredump
  // kmem = (uint8_t *)allow_coredump_patch;
  // kmem[0] = 0xB8;
  // kmem[1] = 0x01;
  // kmem[2] = 0x00;
  // kmem[3] = 0x00;
  // kmem[4] = 0x00;
  // kmem[5] = 0xC3;

  // Patch copyin/copyout/copyinstr to allow userland + kernel addresses in both params
  // copyin
  kmem = (uint8_t *)copyin_patch_1;
  kmem[0] = 0xEB;
  kmem[1] = 0x00;

  if (fw_version >= 550) {
    kmem = (uint8_t *)copyin_patch_2;
    kmem[0] = 0xEB;
    kmem[1] = 0x01;
  }

  kmem = (uint8_t *)copyout_patch_1;
  kmem[0] = 0xEB;
  kmem[1] = 0x00;

  if (fw_version >= 550) {
    kmem = (uint8_t *)copyout_patch_2;
    kmem[0] = 0xEB;
    kmem[1] = 0x01;
  }

  // copyinstr
  kmem = (uint8_t *)copyinstr_patch_1;
  kmem[0] = 0xEB;
  kmem[1] = 0x00;

  if (fw_version >= 550) {
    kmem = (uint8_t *)copyinstr_patch_2;
    kmem[0] = 0xEB;
    kmem[1] = 0x01;
  }

  kmem = (uint8_t *)copyinstr_patch_3;
  kmem[0] = 0xEB;
  kmem[1] = 0x00;

  // setlogin patch (for autolaunch check)
  kmem = (uint8_t *)setlogin_patch;
  kmem[0] = 0x48;
  kmem[1] = 0x31;
  kmem[2] = 0xC0;
  kmem[3] = 0xEB;
  kmem[4] = 0x00;

  // Disable PFS signature check
  kmem = (uint8_t *)pfs_signature_check_patch;
  kmem[0] = 0x31;
  kmem[1] = 0xC0;
  kmem[2] = 0xC3;

  // Enable debug RIFs
  kmem = (uint8_t *)debug_rif_patch_1;
  kmem[0] = 0xB0;
  kmem[1] = 0x01;
  kmem[2] = 0xC3;

  kmem = (uint8_t *)debug_rif_patch_2;
  kmem[0] = 0xB0;
  kmem[1] = 0x01;
  kmem[2] = 0xC3;

  // Patch debug setting errors
  kmem = (uint8_t *)debug_settings_error_patch_1;
  kmem[0] = 0x00;
  kmem[1] = 0x00;
  kmem[2] = 0x00;
  kmem[3] = 0x00;

  kmem = (uint8_t *)debug_settings_error_patch_2;
  kmem[0] = 0x00;
  kmem[1] = 0x00;
  kmem[2] = 0x00;
  kmem[3] = 0x00;

  // Enable mount for unprivileged user
  // kmem = (uint8_t *)mount_patch;
  // kmem[0] = 0xEB;
  // kmem[1] = 0x04;

  // Change directory depth limit from 9 to 64
  kmem = (uint8_t *)depth_limit_patch;
  kmem[0] = 0x40;

  // Restore write protection
  writeCr0(cr0);

  return 0;
}

static void get_memory_dump2(uintptr_t addr, void *out, uint64_t outsz) {
  uint8_t *pout = (uint8_t *)out;
  uint8_t *paddr = (uint8_t *)addr;
  for (uint64_t o = 0; o < outsz; o++) {
    pout[o] = paddr[o];
  }
}

static uint64_t get_kernel_size(uint64_t kernel_base) {
  uint16_t elf_header_size;       // ELF header size
  uint16_t elf_header_entry_size; // ELF header entry size
  uint16_t num_of_elf_entries;    // Number of entries in the ELF header

  get_memory_dump2(kernel_base + 0x34, &elf_header_size, sizeof(uint16_t));
  get_memory_dump2(kernel_base + 0x34 + sizeof(uint16_t), &elf_header_entry_size, sizeof(uint16_t));
  get_memory_dump2(kernel_base + 0x34 + (sizeof(uint16_t) * 2), &num_of_elf_entries, sizeof(uint16_t));

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
    get_memory_dump2(kernel_base + memsz_offset, &temp_memsz, sizeof(uint64_t));
    get_memory_dump2(kernel_base + vaddr_offset, &temp_vaddr, sizeof(uint64_t));
    get_memory_dump2(kernel_base + align_offset, &temp_align, sizeof(uint64_t));

    temp_vaddr -= kernel_base;
    temp_vaddr += KERNEL_BASE_FILE;

    temp_max = (temp_vaddr + temp_memsz + (temp_align - 1)) & ~(temp_align - 1);

    if (temp_max > max) {
      max = temp_max;
    }
  }

  return max - KERNEL_BASE_FILE;
}

static uint64_t *u64_Scan(const void *module, uint64_t size_of_image, uint64_t value) {
  uint8_t *scanBytes = (uint8_t *)module;
  for (size_t i = 0; i < size_of_image; ++i) {
    uint64_t currentValue = *(uint64_t *)&scanBytes[i];
    if (currentValue == value) {
      return (uint64_t *)&scanBytes[i];
    }
  }
  return 0;
}

// Return 0 on success
// Return -1 on memory allocation error or unsupported firmware error
// Can also just give a memory error in the browser or panic the console on failure
static int kpayload_install_payload(struct thread *td, struct kpayload_install_payload_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  // Use "kmem" for all patches
  uint8_t *kmem;

  // Pointers to be assigned in build_kpayload macro
  void *kernel_pmap_store;
  uint8_t *pmap_protect_p_patch;
  uint8_t *payload_buffer;

  void (*pmap_protect)(void *pmap, uint64_t sva, uint64_t eva, uint8_t pr);

  uint16_t fw_version = args->kpayload_payload_info->fw_version;
  struct configuration config = args->kpayload_payload_info->config;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, install_macro);

  const uint64_t kptr = (uint64_t)kernel_ptr;
  const uint64_t kernelsz = get_kernel_size(kptr);
  if (!kptr || !kernelsz) {
    return -1;
  }
  const uint64_t SCE_RELA_tag = 0x6100002F;
  const uintptr_t *sce_reloc = u64_Scan(kernel_base, kernelsz, SCE_RELA_tag);
  // discard old value
  payload_buffer = 0;
  if (sce_reloc) {
    payload_buffer = (uint8_t *)(kptr + (sce_reloc[1] - KERNEL_BASE_FILE));
  } else {
    return -1;
  }
  if (!payload_buffer) {
    return -1;
  }

  uint8_t *payload_data = args->kpayload_payload_info->buffer;
  size_t payload_size = args->kpayload_payload_info->size;

  struct kpayload_payload_header *payload_header = (struct kpayload_payload_header *)payload_data;

  if (!payload_data || payload_size < sizeof(payload_header) || payload_header->signature != 0x5041594C4F414458ull) { // `payloadx`
    return -1;
  }

  // Disable write protection
  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  memset(payload_buffer, '\0', PAGE_SIZE);
  memcpy(payload_buffer, payload_data, payload_size);

  uint64_t sss = ((uint64_t)payload_buffer) & ~(uint64_t)(PAGE_SIZE - 1);
  uint64_t eee = ((uint64_t)payload_buffer + payload_size + PAGE_SIZE - 1) & ~(uint64_t)(PAGE_SIZE - 1);

  kmem = (uint8_t *)pmap_protect_p_patch;
  kmem[0] = 0xEB;
  pmap_protect(kernel_pmap_store, sss, eee, 7);
  kmem[0] = 0x75;

  // Restore write protection
  writeCr0(cr0);

  int (*payload_entrypoint)(uint16_t, struct configuration);
  *((void **)&payload_entrypoint) = (void *)(&payload_buffer[payload_header->entrypoint_offset]);

  return payload_entrypoint(fw_version, config);
}

// HACK: Fix missing/bad/conflicting exploit patches for supported FWs
// Lua+Lapse and PSFree+Lapse have the correct patch from 7.00-12.02, every FW *should* match these
// Try to get these patches fixed/added upstream if possible
// It's hard to tell with some of them because so many people forked/tweaked it
// These fixes can be opinionated/pedantic, but the goal is to have every kernel looking the same post exploit
static int kpayload_exploit_fixes(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  // Use "kmem" for all patches
  uint8_t *kmem;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, kernel_ptr_macro);

  // Disable write protection
  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  // TODO:
  // 6.00, 6.02, 6.20, 6.50, 6.51 // ps4-ipv6-uaf
  // 6.70, 6.71                   // ps4jb2, ps4-ipv6-uaf
  if (fw_version == 474) {
    // Fixes
    //   - [X] PS4-5.05-Kernel-Exploit
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x0073A6A0];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00149CCD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00149C0D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00149C51]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00149D4D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00149D91]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00149F2D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0014A39D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0014A45D]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x003DD4B3];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x003DD4E5];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003DD4DC];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x003DD4D1];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x00113B73];
    kmem[0] = 0xE8;
    kmem[1] = 0xB8;
    kmem[2] = 0x65;
    kmem[3] = 0x13;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00113B7E];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00397876];
    kmem[0] = 0x38;
    kmem[1] = 0xEA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x003D05AE];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0x51;
    kmem[3] = 0x03;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x000686A0];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x001413A4];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x001413A7];
    kmem[0] = 0x37;
  } else if (fw_version == 500 || fw_version == 501) {
    // Fixes
    //   - [X] PS4-5.05-Kernel-Exploit
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x00766FE0];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000ABD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA36D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA3B1]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA42D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA471]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA60D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EAA3D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EAAFD]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000493];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C5];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004BC];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B1];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x00054A72];
    kmem[0] = 0xE8;
    kmem[1] = 0xA9;
    kmem[2] = 0xAD;
    kmem[3] = 0x2A;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00054A7D];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x001A3AF6];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00237E2A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC0;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x002B2350];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0013D510];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x0013D513];
    kmem[0] = 0x37;
  } else if (fw_version == 503) {
    // Fixes
    //   - [X] PS4-5.05-Kernel-Exploit
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x007673A0];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000ABD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA47D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA4C1]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA53D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA581]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA71D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EAB4D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EAC0D]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000493];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C5];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004BC];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B1];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x00054A72];
    kmem[0] = 0xE8;
    kmem[1] = 0x39;
    kmem[2] = 0xB1;
    kmem[3] = 0x2A;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00054A7D];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x001A3C06];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00237F3A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC0;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x002B2620];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0013D620];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x0013D623];
    kmem[0] = 0x37;
  } else if (fw_version == 505 || fw_version == 507) {
    // Fixes
    //   - [X] PS4-5.05-Kernel-Exploit
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x007673E0];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000ABD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA47D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA4C1]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA53D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA581]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EA71D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EAB4D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001EAC0D]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000493];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C5];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004BC];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B1];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x00054A72];
    kmem[0] = 0xE8;
    kmem[1] = 0x39;
    kmem[2] = 0xB1;
    kmem[3] = 0x2A;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00054A7D];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x001A3C06];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00237F3A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC0;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x002B2620];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0013D620];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x0013D623];
    kmem[0] = 0x37;
  } else if (fw_version == 550) {
    // Fixes
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x0077F860];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000AED]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0040590D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405951]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x004059CD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405A11]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405BBD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0040606D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0040613D]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x000107C2];
    kmem[0] = 0xE8;
    kmem[1] = 0x79;
    kmem[2] = 0x62;
    kmem[3] = 0x3C;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x000107CD];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0002EE96];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0006390A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC3;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x00400130];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x003C25D9];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x003C25DC];
    kmem[0] = 0x37;
  } else if (fw_version == 553) {
    // Fixes
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x0077F760];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000AED]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0040580D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405851]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x004058CD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405911]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405ABD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405F6D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0040603D]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x000107C2];
    kmem[0] = 0xE8;
    kmem[1] = 0x79;
    kmem[2] = 0x61;
    kmem[3] = 0x3C;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x000107CD];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0002EE96];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0006390A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC3;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x00400030];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x003C24D9];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x003C24DC];
    kmem[0] = 0x37;
  } else if (fw_version == 555) {
    // Fixes
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x0077FDE0];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000AED]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405BCD]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405C11]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405C8D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405CD1]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00405E7D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0040632D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x004063FD]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x000107C2];
    kmem[0] = 0xE8;
    kmem[1] = 0x39;
    kmem[2] = 0x65;
    kmem[3] = 0x3C;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x000107CD];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0002EE96];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0006390A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC3;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x004003F0];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x003C2899];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x003C289C];
    kmem[0] = 0x37;
  } else if (fw_version == 556) {
    // Fixes
    //   - [X] ps4-ipv6-uaf

    // Remove extra patch from ps4-ipv-uaf that provides more crash info
    // TODO: We need to double check this and make sure we don't clobber a
    // patch we make in `install_patches()`
    kmem = (uint8_t *)&kernel_ptr[0x00788780];
    kmem[0] = 0x55;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00000ADD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0011464D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00114680]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0011470D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00114751]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001148FD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00114DAD]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00114E7D]; // copystr
    kmem[0] = 0xEB;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE0;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // repair sys_setuid() from exploit
    kmem = (uint8_t *)&kernel_ptr[0x000290E2];
    kmem[0] = 0xE8;
    kmem[1] = 0x69;
    kmem[2] = 0x2B;
    kmem[3] = 0x27;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x000290ED];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00352256];
    kmem[0] = 0x38;
    kmem[1] = 0xFA;
    kmem[2] = 0x0F;
    kmem[3] = 0x85;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0027F65A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC3;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x48;
    kmem[7] = 0x8B;

    kmem = (uint8_t *)&kernel_ptr[0x0001A810];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;
    kmem[4] = 0x25;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0x00;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0024026D];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x00240270];
    kmem[0] = 0x37;
  } else if (fw_version == 672) {
    // Fixes
    //   - [X] ps4jb2
    //   - [X] ps4-ipv6-uaf

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x0063C8CE]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C14FD]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C1541]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C15BD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C1601]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C17AD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C1C5D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003C1D2D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0063D1CF];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE8;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x0010BED0];
    kmem[0] = 0xE8;
    kmem[1] = 0xBB;
    kmem[2] = 0x1B;
    kmem[3] = 0xFC;
    kmem[4] = 0xFF;
    kmem[5] = 0x85;
    kmem[6] = 0xC0;
    kmem[7] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00451DB8];
    kmem[0] = 0x0F;
    kmem[1] = 0x85;
    kmem[2] = 0x00;
    kmem[3] = 0x00;
    kmem[4] = 0x00;
    kmem[5] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x001D83CE];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x001D895A];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC6;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x0041A2D0];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x000AB57A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x000AB57D];
    kmem[0] = 0x37;
  } else if (fw_version >= 700 && fw_version <= 702) {
    // Fixes
    //   - [X] ps4jb2
    //   - [X] ps4-ipv6-uaf
    //   - [X] pppwn

    // Unpatch SysVeri
    kmem = (uint8_t *)&kernel_ptr[0x0063A160];
    kmem[0] = 0x55;

    kmem = (uint8_t *)&kernel_ptr[0x0063ACC0];
    kmem[0] = 0x8B;
    kmem[1] = 0x05;
    kmem[2] = 0x32;
    kmem[3] = 0x09;

    kmem = (uint8_t *)&kernel_ptr[0x00639F10];
    kmem[0] = 0x55;
    kmem[1] = 0x48;
    kmem[2] = 0x89;
    kmem[3] = 0xE5;

    kmem = (uint8_t *)&kernel_ptr[0x0063A6E0];
    kmem[0] = 0x55;
    kmem[1] = 0x48;
    kmem[2] = 0x89;
    kmem[3] = 0xE5;

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x0002F295];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x0002F1A0];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x0002F741];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x0063ACCE]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002EF8D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002EFD1]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002F04D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002F091]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002F23D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002F6ED]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0002F7BD]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0063B5EF];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE8;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00087B70];
    kmem[0] = 0xE8;
    kmem[1] = 0x7B;
    kmem[2] = 0x12;
    kmem[3] = 0x03;
    kmem[4] = 0x00;
    kmem[5] = 0x85;
    kmem[6] = 0xC0;
    kmem[7] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00264C08];
    kmem[0] = 0x0F;
    kmem[1] = 0x85;
    kmem[2] = 0x00;
    kmem[3] = 0x00;
    kmem[4] = 0x00;
    kmem[5] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x00094EC1];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0009547B];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xBC;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x002F2C20];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x001D2336];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x001D2339];
    kmem[0] = 0x37;
  } else if (fw_version >= 750 && fw_version <= 755) {
    // Fixes
    //   - [X] ps4jb2
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x0028FA55];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x0028F960];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x0028FF01];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00637394]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ADD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028F74D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028F791]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028F80D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028F851]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028F9FD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028FEAD]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0028FF7D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x00637CCF];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C6];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    kmem = (uint8_t *)&kernel_ptr[0x000004BD];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B2];
    kmem[0] = 0x48;
    kmem[1] = 0x3B;
    kmem[2] = 0x90;
    kmem[3] = 0xE8;
    kmem[4] = 0x00;
    kmem[5] = 0x00;
    kmem[6] = 0x00;
    kmem[7] = 0xEB;
    kmem[8] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x0037A320];
    kmem[0] = 0xE8;
    kmem[1] = 0x8B;
    kmem[2] = 0x49;
    kmem[3] = 0x06;
    kmem[4] = 0x00;
    kmem[5] = 0x85;
    kmem[6] = 0xC0;
    kmem[7] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x003014C8];
    kmem[0] = 0x0F;
    kmem[1] = 0x85;
    kmem[2] = 0x00;
    kmem[3] = 0x00;
    kmem[4] = 0x00;
    kmem[5] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x00451E04];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x004523C4];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0xC7;
    kmem[3] = 0x01;
    kmem[4] = 0x00;
    kmem[5] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00029A30];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x000DB17D];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x000DB180];
    kmem[0] = 0x37;
  } else if (fw_version >= 800 && fw_version <= 803) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x0025E415];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x0025E320];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x0025E8C1];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x0062D254]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E10D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E151]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E1CD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E211]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E3BD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E86D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0025E93D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0062DB3F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x0034D696];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x003EC68D];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x00318D84];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0031953F];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000951C0];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x000FD03A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x000FD03D];
    kmem[0] = 0x37;
  } else if (fw_version == 850 || fw_version == 852) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x003A4345];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x003A4250];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x003A47F1];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00624674]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A403D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A4081]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A40FD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A4141]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A42ED]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A479D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003A486D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x00624F5F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x0022F3D6];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0014D6DD];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x00017474];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00017C2F];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x003AD040];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x000826EA];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x000826ED];
    kmem[0] = 0x37;
  } else if (fw_version == 900) {
    // Fixes
    //   - [X] pOOBs4
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x00271705];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x00271610];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x00271BB1];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00626874]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002713FD]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00271441]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002714BD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00271501]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002716AD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00271B5D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00271C2D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0062715F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00001A06];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00080B8D];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x0023AEC4];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0023B67F];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00221B40];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0016632A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x0016632D];
    kmem[0] = 0x37;
  } else if (fw_version == 903 || fw_version == 904) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x00271385];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x00271290];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x00271831];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00624834]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0027107D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002710C1]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0027113D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00271181]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0027132D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002717DD]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002718AD]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0062511F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00001A06];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00080B8D];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x0023AB94];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0023B34F];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00221810];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x001662DA];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x001662DD];
    kmem[0] = 0x37;
  } else if (fw_version >= 950 && fw_version <= 960) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x00201F15];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x00201E20];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x002023C1];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00624AE4]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00201C0D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00201C51]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00201CCD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00201D11]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00201EBD]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0020236D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0020243D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x006253CF];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x001FA536];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00196D3D];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x0019F724];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0019FEDF];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00011960];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x00122D7A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x00122D7D];
    kmem[0] = 0x37;
  } else if (fw_version == 1000 || fw_version == 1001) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x00472F75];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x00472E80];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x00473421];
    kmem[0] = 0xCE;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x0061E864]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00472C6D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00472CB1]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00472D2D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00472D71]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x00472F1D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x004733CD]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x0047349D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0061F14F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00267756];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0392070D];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x0018FAA4];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x0019025F];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x001BEA40];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x000ED59A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x000ED59D];
    kmem[0] = 0x37;
  } else if (fw_version >= 1050 && fw_version <= 1071) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x000D75C5];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x000D74D0];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x000D7A71];
    kmem[0] = 0xCE;

    // LightningMods's additional dlsym patches
    kmem = (uint8_t *)&kernel_ptr[0x00213013]; // skip check 1
    kmem[0] = 0xEB;
    kmem[1] = 0x04;

    kmem = (uint8_t *)&kernel_ptr[0x00213023]; // skip check 2
    kmem[0] = 0xEB;
    kmem[1] = 0x04;

    kmem = (uint8_t *)&kernel_ptr[0x00213043]; // nop + jmp
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00627DB4]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D72BD]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D7301]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D737D]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D73C1]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D756D]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D7A1D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000D7AED]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0062869F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x0008C1C6];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0047B2EE];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x00212AD4];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00213088];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0x3C;
    kmem[3] = 0x01;

    kmem = (uint8_t *)&kernel_ptr[0x002DAB60];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0019C42A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x0019C42D];
    kmem[0] = 0x37;
  } else if (fw_version == 1100) {
    // Fixes
    //   - [X] pppwn

    // Unpatch extra bytes from copyin, copyout, and copinstr (pppwn)
    kmem = (uint8_t *)&kernel_ptr[0x002DE045];
    kmem[0] = 0xC7;

    kmem = (uint8_t *)&kernel_ptr[0x002DDF50];
    kmem[0] = 0xC6;

    kmem = (uint8_t *)&kernel_ptr[0x002DE4F1];
    kmem[0] = 0xCE;

    // LightningMods's additional dlsym patches
    kmem = (uint8_t *)&kernel_ptr[0x001E4C33]; // skip check 1
    kmem[0] = 0xEB;
    kmem[1] = 0x04;

    kmem = (uint8_t *)&kernel_ptr[0x001E4C43]; // skip check 2
    kmem[0] = 0xEB;
    kmem[1] = 0x04;

    kmem = (uint8_t *)&kernel_ptr[0x001E4C63]; // nop + jmp
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // ChendoChap's patches from pOOBs4
    kmem = (uint8_t *)&kernel_ptr[0x00623F64]; // veriPatch
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x00000ACD]; // bcopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DDD3D]; // bzero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DDD81]; // pagezero
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DDDFD]; // memcpy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DDE41]; // pagecopy
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DDFED]; // copyin
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DE49D]; // copyinstr
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x002DE56D]; // copystr
    kmem[0] = 0xEB;

    // stop sysVeri from causing a delayed panic on suspend
    kmem = (uint8_t *)&kernel_ptr[0x0062484F];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch amd64_syscall() to allow calling syscalls everywhere
    kmem = (uint8_t *)&kernel_ptr[0x00000490];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004C2];
    kmem[0] = 0xEB;

    kmem = (uint8_t *)&kernel_ptr[0x000004B9];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    kmem = (uint8_t *)&kernel_ptr[0x000004B5];
    kmem[0] = 0xEB;
    kmem[1] = 0x00;

    // patch sys_setuid() to allow freely changing the effective user ID
    kmem = (uint8_t *)&kernel_ptr[0x00431526];
    kmem[0] = 0xEB;

    // patch vm_map_protect() (called by sys_mprotect()) to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0035C8EE];
    kmem[0] = 0x00;
    kmem[1] = 0x00;
    kmem[2] = 0x00;
    kmem[3] = 0x00;

    // TODO: Description of this patch. patch sys_dynlib_load_prx()
    kmem = (uint8_t *)&kernel_ptr[0x001E46F4];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;

    // patch sys_dynlib_dlsym() to allow dynamic symbol resolution everywhere
    kmem = (uint8_t *)&kernel_ptr[0x001E4CA8];
    kmem[0] = 0x90;
    kmem[1] = 0xE9;
    kmem[2] = 0x3C;
    kmem[3] = 0x01;

    kmem = (uint8_t *)&kernel_ptr[0x00088CE0];
    kmem[0] = 0x48;
    kmem[1] = 0x31;
    kmem[2] = 0xC0;
    kmem[3] = 0xC3;

    // patch sys_mmap() to allow rwx mappings
    kmem = (uint8_t *)&kernel_ptr[0x0015626A];
    kmem[0] = 0x37;

    kmem = (uint8_t *)&kernel_ptr[0x0015626D];
    kmem[0] = 0x37;
  }

  // Restore write protection
  writeCr0(cr0);

  return 0;
}

// Passes on the result of kpayload_patches
int install_patches() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_patches, &kpayload_firmware_info);
}

// Passes on the result of kpayload_install_payload
int install_payload(struct configuration *config) {
  struct kpayload_payload_info kpayload_payload_info;
  kpayload_payload_info.fw_version = get_firmware();
  kpayload_payload_info.config = *config;
  kpayload_payload_info.buffer = (uint8_t *)kpayload_bin;
  kpayload_payload_info.size = (size_t)kpayload_bin_len;

  return kexec(&kpayload_install_payload, &kpayload_payload_info);
}

// Passes on the result of kpayload_exploit_fixes
int exploit_fixes() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_exploit_fixes, &kpayload_firmware_info);
}
