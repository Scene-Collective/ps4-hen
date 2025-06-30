#include "sections.h"

#include "offsets/1202.h"

// clang-format off

const struct kpayload_offsets offsets_1202 PAYLOAD_RDATA = {
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
  .memcmp_addr                     = 0x003942A0,
  ._sx_xlock_addr                  = 0x000A3840,
  ._sx_xunlock_addr                = 0x000A3A00,
  .malloc_addr                     = 0x00009520,
  .free_addr                       = 0x000096E0,
  .strstr_addr                     = 0x0021CC50,
  .fpu_kern_enter_addr             = 0x001DFFE0,
  .fpu_kern_leave_addr             = 0x001E00A0,
  .memcpy_addr                     = 0x002BD480,
  .memset_addr                     = 0x001FA140,
  .strlen_addr                     = 0x0036AB30,
  .printf_addr                     = 0x002E03E0,
  .eventhandler_register_addr      = 0x00224110,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x003B2D80,
  .sceSblServiceMailbox_addr       = 0x0062F960,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0063C770,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0063CFB0,
  ._sceSblAuthMgrSmStart_addr      = 0x0063DB40,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0063C7D0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x0021BC00,
  .Sha256Hmac_addr                 = 0x001F8D40,
  .AesCbcCfb128Encrypt_addr        = 0x00340E30,
  .AesCbcCfb128Decrypt_addr        = 0x00341060,
  .sceSblDriverSendMsg_0_addr      = 0x0061BFA0,
  .sceSblPfsSetKeys_addr           = 0x006266E0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00624740,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0062B030,
  .sceSblKeymgrCleartKey_addr      = 0x0062B370,
  .sceSblKeymgrSmCallfunc_addr     = 0x0062AC00,

  // Patch
  .vmspace_acquire_ref_addr        = 0x002F6F20,
  .vmspace_free_addr               = 0x002F6D50,
  .vm_map_lock_read_addr           = 0x002F70B0,
  .vm_map_unlock_read_addr         = 0x002F7100,
  .vm_map_lookup_entry_addr        = 0x002F76F0,
  .proc_rwmem_addr                 = 0x00365FA0,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x00641F8C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x006420DE,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00642876,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00643559,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0063FF8D,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00640BC8,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x006247E5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0062C1ED,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C4E0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064D2AE,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006A2D99,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006A2FCA,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D100,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D460,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x0018B310, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC7012, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000ED1F5,
  .SceRemotePlay_patch2                                      = 0x000ED210,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016F5A4,
  .sceKernelIsGenuineCEX_patch2    = 0x00873754,
  .sceKernelIsGenuineCEX_patch3    = 0x008C3A52,
  .sceKernelIsGenuineCEX_patch4    = 0x00A27304,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016F5D2,
  .nidf_libSceDipsw_patch2         = 0x0024E14C,
  .nidf_libSceDipsw_patch3         = 0x00873782,
  .nidf_libSceDipsw_patch4         = 0x00A27332,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0xDEADC0DE,
  .app_installer_patch             = 0x001389A0,
  .check_system_version            = 0x003CA567,
  .check_title_system_update_patch = 0x003CD7B0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x003233B0,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DAE610,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003DE23F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FCFDF9,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x00A10851,
  .ext_hdd_patch                   = 0x0061475D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0074CCC9,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D2216,
};

// clang-format on
