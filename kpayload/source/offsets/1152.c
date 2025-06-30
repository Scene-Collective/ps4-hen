#include "sections.h"

#include "offsets/1152.h"

// clang-format off

const struct kpayload_offsets offsets_1152 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01520D00,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0153D6C8,
  .ALLPROC_addr                    = 0x01B28538,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02647350,
  .SBL_PFS_SX_addr                 = 0x0265C080,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02668040,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02668050,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0266C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0266C808,
  .FPU_CTX_addr                    = 0x026542C0,
  .SYSENT_addr                     = 0x01102B70,

  // common
  .memcmp_addr                     = 0x00394060,
  ._sx_xlock_addr                  = 0x000A3840,
  ._sx_xunlock_addr                = 0x000A3A00,
  .malloc_addr                     = 0x00009520,
  .free_addr                       = 0x000096E0,
  .strstr_addr                     = 0x0021CB70,
  .fpu_kern_enter_addr             = 0x001DFFE0,
  .fpu_kern_leave_addr             = 0x001E00A0,
  .memcpy_addr                     = 0x002BD3A0,
  .memset_addr                     = 0x001FA060,
  .strlen_addr                     = 0x0036A8F0,
  .printf_addr                     = 0x002E01A0,
  .eventhandler_register_addr      = 0x00224030,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x003B2B40,
  .sceSblServiceMailbox_addr       = 0x0062F720,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0063C530,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0063CD70,
  ._sceSblAuthMgrSmStart_addr      = 0x0063D900,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0063C590,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x0021BB20,
  .Sha256Hmac_addr                 = 0x001F8C60,
  .AesCbcCfb128Encrypt_addr        = 0x00340BF0,
  .AesCbcCfb128Decrypt_addr        = 0x00340E20,
  .sceSblDriverSendMsg_0_addr      = 0x0061BD60,
  .sceSblPfsSetKeys_addr           = 0x006264A0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00624500,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0062ADF0,
  .sceSblKeymgrCleartKey_addr      = 0x0062B130,
  .sceSblKeymgrSmCallfunc_addr     = 0x0062A9C0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x002F6CE0,
  .vmspace_free_addr               = 0x002F6B10,
  .vm_map_lock_read_addr           = 0x002F6E70,
  .vm_map_unlock_read_addr         = 0x002F6EC0,
  .vm_map_lookup_entry_addr        = 0x002F74B0,
  .proc_rwmem_addr                 = 0x00365D60,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x00641D4C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x00641E9E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00642636,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00643319,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0063FD4D,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00640988,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x006245A5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0062BFAD,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C2A0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064D06E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006A2919,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006A2B4A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D100,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D460,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x0018B110, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC6F92, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000ED1D5,
  .SceRemotePlay_patch2                                      = 0x000ED1F0,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016E004,
  .sceKernelIsGenuineCEX_patch2    = 0x00870E44,
  .sceKernelIsGenuineCEX_patch3    = 0x008C1142,
  .sceKernelIsGenuineCEX_patch4    = 0x00A228B4,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016E032,
  .nidf_libSceDipsw_patch2         = 0x0024C72C,
  .nidf_libSceDipsw_patch3         = 0x00870E72,
  .nidf_libSceDipsw_patch4         = 0x00A228E2,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0xDEADC0DE,
  .app_installer_patch             = 0x001373F0,
  .check_system_version            = 0x003C8B47,
  .check_title_system_update_patch = 0x003CBD90,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00321990,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DAD2F0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003DC64F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FCE619,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x00A0BE01,
  .ext_hdd_patch                   = 0x00612B6D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0074AB39,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D2216,
};

// clang-format on
