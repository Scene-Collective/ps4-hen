#include "sections.h"

#include "offsets/1050.h"

// clang-format off

const struct kpayload_offsets offsets_1050 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01A5FE30,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01541E78,
  .ALLPROC_addr                    = 0x02269F30,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02646CA8,
  .SBL_PFS_SX_addr                 = 0x0265C310,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02660858,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02660868,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02664000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02664808,
  .FPU_CTX_addr                    = 0x026796C0,
  .SYSENT_addr                     = 0x011029C0,

  // common
  .memcmp_addr                     = 0x0002A020,
  ._sx_xlock_addr                  = 0x000977A0,
  ._sx_xunlock_addr                = 0x00097960,
  .malloc_addr                     = 0x0036E120,
  .free_addr                       = 0x0036E2E0,
  .strstr_addr                     = 0x002FDB20,
  .fpu_kern_enter_addr             = 0x00300A80,
  .fpu_kern_leave_addr             = 0x00300B40,
  .memcpy_addr                     = 0x000D7370,
  .memset_addr                     = 0x0000D090,
  .strlen_addr                     = 0x00160DA0,
  .printf_addr                     = 0x00450E80,
  .eventhandler_register_addr      = 0x000ED020,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x001F4520,
  .sceSblServiceMailbox_addr       = 0x00630550,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00643BF0,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x00644430,
  ._sceSblAuthMgrSmStart_addr      = 0x0063BEB0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x00643C50,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x00350360,
  .Sha256Hmac_addr                 = 0x00441BB0,
  .AesCbcCfb128Encrypt_addr        = 0x0033EE60,
  .AesCbcCfb128Decrypt_addr        = 0x0033F090,
  .sceSblDriverSendMsg_0_addr      = 0x0061B3C0,
  .sceSblPfsSetKeys_addr           = 0x00622F50,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00622910,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00625670,
  .sceSblKeymgrCleartKey_addr      = 0x006259B0,
  .sceSblKeymgrSmCallfunc_addr     = 0x00625240,

  // Patch
  .vmspace_acquire_ref_addr        = 0x00476140,
  .vmspace_free_addr               = 0x00475F70,
  .vm_map_lock_read_addr           = 0x004762D0,
  .vm_map_unlock_read_addr         = 0x00476320,
  .vm_map_lookup_entry_addr        = 0x00476910,
  .proc_rwmem_addr                 = 0x004244A0,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0064117C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x006412CE,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00641A66,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00642749,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0063E2FD,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x0063EF38,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x006229B5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0062682D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064B880,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064C64E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006B59F9,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006B5C2A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001CFC0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D320,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00188CB0, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC7B12, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000EC9F5,
  .SceRemotePlay_patch2                                      = 0x000ECA10,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016B664,
  .sceKernelIsGenuineCEX_patch2    = 0x0085BAB4,
  .sceKernelIsGenuineCEX_patch3    = 0x008ABCE2,
  .sceKernelIsGenuineCEX_patch4    = 0x00A0CA84,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016B692,
  .nidf_libSceDipsw_patch2         = 0x00249B0C,
  .nidf_libSceDipsw_patch3         = 0x0085BAE2,
  .nidf_libSceDipsw_patch4         = 0x00A0CAB2,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0xDEADC0DE,
  .app_installer_patch             = 0x00134A50,
  .check_system_version            = 0x003C1957,
  .check_title_system_update_patch = 0x003C4BA0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0031E890,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00D962D0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003D544F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FB5D59,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009F5FD1,
  .ext_hdd_patch                   = 0x00606B7D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0073A629,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CF876,
};

// clang-format on
