#ifndef OFFSETS_H_
#define OFFSETS_H_

#include <stdint.h>

#include "sections.h"

// clang-format off

struct kpayload_offsets {
  // data
  uint32_t XFAST_SYSCALL_addr;
  uint32_t M_TEMP_addr;
  uint32_t MINI_SYSCORE_SELF_BINARY_addr;
  uint32_t ALLPROC_addr;
  uint32_t SBL_DRIVER_MAPPED_PAGES_addr;
  uint32_t SBL_PFS_SX_addr;
  uint32_t SBL_KEYMGR_KEY_SLOTS_addr;
  uint32_t SBL_KEYMGR_KEY_RBTREE_addr;
  uint32_t SBL_KEYMGR_BUF_VA_addr;
  uint32_t SBL_KEYMGR_BUF_GVA_addr;
  uint32_t FPU_CTX_addr;
  uint32_t SYSENT_addr;

  // common
  uint32_t memcmp_addr;
  uint32_t _sx_xlock_addr;
  uint32_t _sx_xunlock_addr;
  uint32_t malloc_addr;
  uint32_t free_addr;
  uint32_t strstr_addr;
  uint32_t fpu_kern_enter_addr;
  uint32_t fpu_kern_leave_addr;
  uint32_t memcpy_addr;
  uint32_t memset_addr;
  uint32_t strlen_addr;
  uint32_t printf_addr;
  uint32_t eventhandler_register_addr;

  // Fself
  uint32_t sceSblACMgrGetPathId_addr;
  uint32_t sceSblServiceMailbox_addr;
  uint32_t sceSblAuthMgrSmIsLoadable2_addr;
  uint32_t _sceSblAuthMgrGetSelfInfo_addr;
  uint32_t _sceSblAuthMgrSmStart_addr;
  uint32_t sceSblAuthMgrVerifyHeader_addr;

  // Fpkg
  uint32_t RsaesPkcs1v15Dec2048CRT_addr;
  uint32_t Sha256Hmac_addr;
  uint32_t AesCbcCfb128Encrypt_addr;
  uint32_t AesCbcCfb128Decrypt_addr;
  uint32_t sceSblDriverSendMsg_0_addr;
  uint32_t sceSblPfsSetKeys_addr;
  uint32_t sceSblKeymgrSetKeyStorage_addr;
  uint32_t sceSblKeymgrSetKeyForPfs_addr;
  uint32_t sceSblKeymgrCleartKey_addr;
  uint32_t sceSblKeymgrSmCallfunc_addr;

  // Patch
  uint32_t vmspace_acquire_ref_addr;
  uint32_t vmspace_free_addr;
  uint32_t vm_map_lock_read_addr;
  uint32_t vm_map_unlock_read_addr;
  uint32_t vm_map_lookup_entry_addr;
  uint32_t proc_rwmem_addr;

  // Fself hooks
  uint32_t sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook;
  uint32_t sceSblAuthMgrIsLoadable2_hook;
  uint32_t sceSblAuthMgrVerifyHeader_hook1;
  uint32_t sceSblAuthMgrVerifyHeader_hook2;
  uint32_t sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook;
  uint32_t sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook;

  // Fpkg hooks
  uint32_t sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook;
  uint32_t sceSblKeymgrInvalidateKey__sx_xlock_hook;
  uint32_t sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook;
  uint32_t sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook;
  uint32_t mountpfs__sceSblPfsSetKeys_hook1;
  uint32_t mountpfs__sceSblPfsSetKeys_hook2;

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  uint32_t sceSblRcMgrIsAllowDebugMenuForSettings_patch;
  uint32_t sceSblRcMgrIsStoreMode_patch;

  // SceShellUI patches - remote play patches
  uint32_t CreateUserForIDU_patch;
  uint32_t remote_play_menu_patch;

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  uint32_t SceRemotePlay_patch1;
  uint32_t SceRemotePlay_patch2;

  // SceShellCore patches - call sceKernelIsGenuineCEX
  uint32_t sceKernelIsGenuineCEX_patch1;
  uint32_t sceKernelIsGenuineCEX_patch2;
  uint32_t sceKernelIsGenuineCEX_patch3;
  uint32_t sceKernelIsGenuineCEX_patch4;

  // SceShellCore patches - call nidf_libSceDipsw
  uint32_t nidf_libSceDipsw_patch1;
  uint32_t nidf_libSceDipsw_patch2;
  uint32_t nidf_libSceDipsw_patch3;
  uint32_t nidf_libSceDipsw_patch4;

  // SceShellCore patches - bypass firmware checks
  uint32_t check_disc_root_param_patch;
  uint32_t app_installer_patch;
  uint32_t check_system_version;
  uint32_t check_title_system_update_patch;

  // SceShellCore patches - enable remote pkg installer
  uint32_t enable_data_mount_patch;

  // SceShellCore patches - enable VR without spoof
  uint32_t enable_psvr_patch;

  // SceShellCore patches - enable fpkg
  uint32_t enable_fpkg_patch;

  // SceShellCore patches - use `free` prefix instead `fake`
  uint32_t fake_free_patch;

  // SceShellCore patches - enable official external HDD support
  uint32_t pkg_installer_patch;
  uint32_t ext_hdd_patch;

  // SceShellCore patches - enable debug trophies
  uint32_t debug_trophies_patch;

  // SceShellCore patches - disable screenshot block
  uint32_t disable_screenshot_patch;
};

// Lookup function: implemented elsewhere
PAYLOAD_CODE const struct kpayload_offsets *get_offsets_for_fw(uint16_t fw_version);

// clang-format on

#endif
