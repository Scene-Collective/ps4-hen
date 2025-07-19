#include "sections.h"

#include "offsets/555.h"

// clang-format off

const struct kpayload_offsets offsets_555 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .PRISON0_addr                    = 0x01139180,
  .ROOTVNODE_addr                  = 0x022F3570,
  .M_TEMP_addr                     = 0x01A92FF0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0156B618,
  .ALLPROC_addr                    = 0x021910E8,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x026536C8,
  .SBL_PFS_SX_addr                 = 0x02668080,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x0265B700,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x0265B710,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0265C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0265C808,
  .FPU_CTX_addr                    = 0x0266CD40,
  .SYSENT_addr                     = 0x0111ACC0,

  // common
  .memcmp_addr                     = 0x0005E270,
  ._sx_xlock_addr                  = 0x004828E0,
  ._sx_xunlock_addr                = 0x00482AA0,
  .malloc_addr                     = 0x00466DA0,
  .free_addr                       = 0x00466FA0,
  .strstr_addr                     = 0x000E4D90,
  .fpu_kern_enter_addr             = 0x0022CC00,
  .fpu_kern_leave_addr             = 0x0022CD00,
  .memcpy_addr                     = 0x00405C80,
  .memset_addr                     = 0x00108B50,
  .strlen_addr                     = 0x002A6F30,
  .printf_addr                     = 0x0011B150,
  .eventhandler_register_addr      = 0x0022D6A0,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x001B4C30,
  .sceSblServiceMailbox_addr       = 0x0064A6A0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0065C520,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0065CD80,
  ._sceSblAuthMgrSmStart_addr      = 0x00657120,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0065C580,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x002EA6B0,
  .Sha256Hmac_addr                 = 0x0031D470,
  .AesCbcCfb128Encrypt_addr        = 0x0045ACE0,
  .AesCbcCfb128Decrypt_addr        = 0x0045AF10,
  .sceSblDriverSendMsg_0_addr      = 0x00635EA0,
  .sceSblPfsSetKeys_addr           = 0x00641810,
  .sceSblKeymgrSetKeyStorage_addr  = 0x0063C7C0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0063ED00,
  .sceSblKeymgrCleartKey_addr      = 0x0063F080,
  .sceSblKeymgrSmCallfunc_addr     = 0x0063E8D0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x00029C90,
  .vmspace_free_addr               = 0x00029AC0,
  .vm_map_lock_read_addr           = 0x00029E40,
  .vm_map_unlock_read_addr         = 0x00029E90,
  .vm_map_lookup_entry_addr        = 0x0002A470,
  .proc_rwmem_addr                 = 0x00393470,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0065588D,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x006559D1,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x0065612C,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00656DD8,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x00658D13,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00659966,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x0063C865,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0063FF2A,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x00664130,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x00664F13,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006B1A68,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006B1C97,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D4D0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D830,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001A3350, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00E86151, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0003C0B6,
  .SceRemotePlay_patch2                                      = 0x0003C0D1,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x00177AFB,
  .sceKernelIsGenuineCEX_patch2    = 0x007BA80B,
  .sceKernelIsGenuineCEX_patch3    = 0x008052A3,
  .sceKernelIsGenuineCEX_patch4    = 0x0099520B,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x00177B27,
  .nidf_libSceDipsw_patch2         = 0x0024A9DD,
  .nidf_libSceDipsw_patch3         = 0x007BA837,
  .nidf_libSceDipsw_patch4         = 0x00995237,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00139017,
  .app_installer_patch             = 0x00139111,
  .check_system_version            = 0x003CB269,
  .check_title_system_update_patch = 0x003CDFC0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00327C8A,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00CE7790,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003DE982,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00F196B0,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x0097DB91,
  .ext_hdd_patch                   = 0x0059CB5D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x006B9529,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D47D6,

  // Process structure offsets
  .proc_p_comm_offset = 0x454,
  .proc_path_offset   = 0x474,
};

// clang-format on
