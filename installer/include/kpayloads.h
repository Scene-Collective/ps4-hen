#ifndef KPAYLOADS_H_
#define KPAYLOADS_H_

#define patch_macro(x)                                                                     \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL];                \
  kernel_ptr = (uint8_t *)kernel_base;                                                     \
  uart_patch = &kernel_ptr[K##x##_UART_PATCH];                                             \
  /* is_diag_process_patch = &kernel_ptr[K##x##_IS_DIAG_PROCESS_PATCH]; */                       \
  /* allow_system_level_logging_patch = &kernel_ptr[K##x##_ALLOW_SYSTEM_LEVEL_LOGGING_PATCH]; */ \
  /* allow_coredump_patch = &kernel_ptr[K##x##_ALLOW_COREDUMP_PATCH]; */                         \
  copyin_patch_1 = &kernel_ptr[K##x##_COPYIN_PATCH_1];                                     \
  copyin_patch_2 = &kernel_ptr[K##x##_COPYIN_PATCH_2];                                     \
  copyout_patch_1 = &kernel_ptr[K##x##_COPYOUT_PATCH_1];                                   \
  copyout_patch_2 = &kernel_ptr[K##x##_COPYOUT_PATCH_2];                                   \
  copyinstr_patch_1 = &kernel_ptr[K##x##_COPYINSTR_PATCH_1];                               \
  copyinstr_patch_2 = &kernel_ptr[K##x##_COPYINSTR_PATCH_2];                               \
  copyinstr_patch_3 = &kernel_ptr[K##x##_COPYINSTR_PATCH_3];                               \
  setlogin_patch = &kernel_ptr[K##x##_SETLOGIN_PATCH];                                     \
  pfs_signature_check_patch = &kernel_ptr[K##x##_PFS_SIGNATURE_CHECK_PATCH];               \
  debug_rif_patch_1 = &kernel_ptr[K##x##_DEBUG_RIF_PATCH_1];                               \
  debug_rif_patch_2 = &kernel_ptr[K##x##_DEBUG_RIF_PATCH_2];                               \
  debug_settings_error_patch_1 = &kernel_ptr[K##x##_DEBUG_SETTINGS_ERROR_PATCH_1];         \
  debug_settings_error_patch_2 = &kernel_ptr[K##x##_DEBUG_SETTINGS_ERROR_PATCH_2];         \
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
  uint8_t *buffer;
  size_t size;
};

struct kpayload_install_payload_args {
  void *syscall_handler;
  struct kpayload_payload_info *kpayload_payload_info;
};

int install_patches();
int install_payload();
int exploit_fixes();

#endif
