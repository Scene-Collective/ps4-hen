#include "sections.h"

#include "offsets/672.h"

// clang-format off

const struct kpayload_offsets offsets_672 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01540EB0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0156A588,
  .ALLPROC_addr                    = 0x022BBE80,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x0266AC68,
  .SBL_PFS_SX_addr                 = 0x02679040,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02694570,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02694580,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02698000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02698808,
  .FPU_CTX_addr                    = 0x02694080,
  .SYSENT_addr                     = 0x0111E000,

  // common
  .memcmp_addr                     = 0x00207E40,
  ._sx_xlock_addr                  = 0x000426C0,
  ._sx_xunlock_addr                = 0x00042880,
  .malloc_addr                     = 0x0000D7A0,
  .free_addr                       = 0x0000D9A0,
  .strstr_addr                     = 0x004817F0,
  .fpu_kern_enter_addr             = 0x0036B6E0,
  .fpu_kern_leave_addr             = 0x0036B7D0,
  .memcpy_addr                     = 0x003C15B0,
  .memset_addr                     = 0x001687D0,
  .strlen_addr                     = 0x002433E0,
  .printf_addr                     = 0x00123280,
  .eventhandler_register_addr      = 0x00402E80,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x00233C70,
  .sceSblServiceMailbox_addr       = 0x0064CC20,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0065D7A0,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0065E010,
  ._sceSblAuthMgrSmStart_addr      = 0x0065E490,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0065D800,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x001D6050,
  .Sha256Hmac_addr                 = 0x00335B70,
  .AesCbcCfb128Encrypt_addr        = 0x003C0320,
  .AesCbcCfb128Decrypt_addr        = 0x003C0550,
  .sceSblDriverSendMsg_0_addr      = 0x00637AE0,
  .sceSblPfsSetKeys_addr           = 0x00641520,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00646E00,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00649800,
  .sceSblKeymgrCleartKey_addr      = 0x00649B80,
  .sceSblKeymgrSmCallfunc_addr     = 0x006493D0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0044CB90,
  .vmspace_free_addr               = 0x0044C9C0,
  .vm_map_lock_read_addr           = 0x0044CD40,
  .vm_map_unlock_read_addr         = 0x0044CD90,
  .vm_map_lookup_entry_addr        = 0x0044D330,
  .proc_rwmem_addr                 = 0x0010EE10,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x006591BC,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0065930F,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00659AC6,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0065A758,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0066092A,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00661571,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00646EA5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0064AA3D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x00669500,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0066A313,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006CDF15,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006CE141,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D670,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D9D0,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001A0900, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC8291, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010C6D4,
  .SceRemotePlay_patch2                                      = 0x0010C6EF,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x00189602,
  .sceKernelIsGenuineCEX_patch2    = 0x00835642,
  .sceKernelIsGenuineCEX_patch3    = 0x00880492,
  .sceKernelIsGenuineCEX_patch4    = 0x00A12B92,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x00189630,
  .nidf_libSceDipsw_patch2         = 0x00254107,
  .nidf_libSceDipsw_patch3         = 0x00835670,
  .nidf_libSceDipsw_patch4         = 0x00A12BC0,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00149AFD,
  .app_installer_patch             = 0x00149BF0,
  .check_system_version            = 0x003DB6F8,
  .check_title_system_update_patch = 0x003DECC0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0033943E,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DDDD50,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003EFCF0,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FD2BF1,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009FB311,
  .ext_hdd_patch                   = 0x00606A0D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x007268C9,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000DD2A6,
};

// clang-format on
