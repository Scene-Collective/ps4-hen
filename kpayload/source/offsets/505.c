#include "sections.h"

#include "offsets/505.h"

// clang-format off

const struct kpayload_offsets offsets_505 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x014B4110,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x014C9D48,
  .ALLPROC_addr                    = 0x02382FF8,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x0271E208,
  .SBL_PFS_SX_addr                 = 0x0271E5D8,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02744548,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02744558,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02748000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02748800,
  .FPU_CTX_addr                    = 0x0274C040,
  .SYSENT_addr                     = 0x0107C610,

  // common
  .memcmp_addr                     = 0x00050AC0,
  ._sx_xlock_addr                  = 0x000F5E10,
  ._sx_xunlock_addr                = 0x000F5FD0,
  .malloc_addr                     = 0x0010E250,
  .free_addr                       = 0x0010E460,
  .strstr_addr                     = 0x0017DFB0,
  .fpu_kern_enter_addr             = 0x001BFF90,
  .fpu_kern_leave_addr             = 0x001C0090,
  .memcpy_addr                     = 0x001EA530,
  .memset_addr                     = 0x003205C0,
  .strlen_addr                     = 0x003B71A0,
  .printf_addr                     = 0x00436040,
  .eventhandler_register_addr      = 0x001EC400,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x000117E0,
  .sceSblServiceMailbox_addr       = 0x00632540,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0063C4F0,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0063CD40,
  ._sceSblAuthMgrSmStart_addr      = 0x006418E0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0063C550,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x001FD7D0,
  .Sha256Hmac_addr                 = 0x002D55B0,
  .AesCbcCfb128Encrypt_addr        = 0x003A2BD0,
  .AesCbcCfb128Decrypt_addr        = 0x003A2E00,
  .sceSblDriverSendMsg_0_addr      = 0x0061D7F0,
  .sceSblPfsSetKeys_addr           = 0x0061EFA0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00623FC0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0062D780,
  .sceSblKeymgrCleartKey_addr      = 0x0062DB10,
  .sceSblKeymgrSmCallfunc_addr     = 0x0062E2A0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0019EF90,
  .vmspace_free_addr               = 0x0019EDC0,
  .vm_map_lock_read_addr           = 0x0019F140,
  .vm_map_unlock_read_addr         = 0x0019F190,
  .vm_map_lookup_entry_addr        = 0x0019F760,
  .proc_rwmem_addr                 = 0x0030D150,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0063E25D,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0063E3A1,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x0063EAFC,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0063F718,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0064318B,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00643DA2,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00624065,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0062E96D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C720,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064D4FF,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006AAAD5,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006AAD04,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001BD90,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001C090,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001A8FA0, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EE638E, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0003C33F,
  .SceRemotePlay_patch2                                      = 0x0003C35A,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016D05B,
  .sceKernelIsGenuineCEX_patch2    = 0x0079980B,
  .sceKernelIsGenuineCEX_patch3    = 0x007E5A13,
  .sceKernelIsGenuineCEX_patch4    = 0x0094715B,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016D087,
  .nidf_libSceDipsw_patch2         = 0x0023747B,
  .nidf_libSceDipsw_patch3         = 0x00799837,
  .nidf_libSceDipsw_patch4         = 0x00947187,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x0013097F,
  .app_installer_patch             = 0x00130A71,
  .check_system_version            = 0x003CCB79,
  .check_title_system_update_patch = 0x003CF8D0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00319A53,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00C791A0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003E0602,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00EA96A7,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009312A1,
  .ext_hdd_patch                   = 0x00593C7D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x006ABE39,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CB8C6,
};

// clang-format on
