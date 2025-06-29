#include "sections.h"

#include "offsets/750.h"

// clang-format off

const struct kpayload_offsets offsets_750 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01556DA0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x015A8FC8,
  .ALLPROC_addr                    = 0x0213C828,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02662648,
  .SBL_PFS_SX_addr                 = 0x0267C040,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02684238,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02684248,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02688000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02688808,
  .FPU_CTX_addr                    = 0x02680900,
  .SYSENT_addr                     = 0x01122340,

  // common
  .memcmp_addr                     = 0x0031D250,
  ._sx_xlock_addr                  = 0x000D1600,
  ._sx_xunlock_addr                = 0x000D17C0,
  .malloc_addr                     = 0x001D6680,
  .free_addr                       = 0x001D6870,
  .strstr_addr                     = 0x003B0250,
  .fpu_kern_enter_addr             = 0x004A5260,
  .fpu_kern_leave_addr             = 0x004A5350,
  .memcpy_addr                     = 0x0028F800,
  .memset_addr                     = 0x0008D6F0,
  .strlen_addr                     = 0x002E8BC0,
  .printf_addr                     = 0x0026F740,
  .eventhandler_register_addr      = 0x000D3670,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x00364D80,
  .sceSblServiceMailbox_addr       = 0x0064A1A0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0065C090,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0065C8E0,
  ._sceSblAuthMgrSmStart_addr      = 0x00655C50,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0065C0F0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x001517F0,
  .Sha256Hmac_addr                 = 0x00274740,
  .AesCbcCfb128Encrypt_addr        = 0x0021F810,
  .AesCbcCfb128Decrypt_addr        = 0x0021FA40,
  .sceSblDriverSendMsg_0_addr      = 0x00634A40,
  .sceSblPfsSetKeys_addr           = 0x0063F100,
  .sceSblKeymgrSetKeyStorage_addr  = 0x0063E3E0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00643B20,
  .sceSblKeymgrCleartKey_addr      = 0x00643E80,
  .sceSblKeymgrSmCallfunc_addr     = 0x006436F0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x002FC290,
  .vmspace_free_addr               = 0x002FC0C0,
  .vm_map_lock_read_addr           = 0x002FC430,
  .vm_map_unlock_read_addr         = 0x002FC480,
  .vm_map_lookup_entry_addr        = 0x002FCA70,
  .proc_rwmem_addr                 = 0x00361310,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0065A51C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0065A66E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x0065AE06,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0065BAE9,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x006580FD,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00658D48,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x0063E485,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x00644CFD,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x006667D0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0066759E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006D9727,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006D9958,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D140,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D4A0,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x0018E120, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC6491, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010A13A,
  .SceRemotePlay_patch2                                      = 0x0010A155,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x00168A90,
  .sceKernelIsGenuineCEX_patch2    = 0x007FBF70,
  .sceKernelIsGenuineCEX_patch3    = 0x0084AFB2,
  .sceKernelIsGenuineCEX_patch4    = 0x009D31D0,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x00168ABA,
  .nidf_libSceDipsw_patch2         = 0x0023CE48,
  .nidf_libSceDipsw_patch3         = 0x007FBF9A,
  .nidf_libSceDipsw_patch4         = 0x009D31FA,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00132F9D,
  .app_installer_patch             = 0x00133080,
  .check_system_version            = 0x003B0B47,
  .check_title_system_update_patch = 0x003B3200,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00316BC3,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00D57EE0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003C244F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00F66891,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009BC1C1,
  .ext_hdd_patch                   = 0x005BCF2D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x006E7D29,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CD6B6,
};

// clang-format on
