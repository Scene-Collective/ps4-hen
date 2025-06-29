#include "sections.h"

#include "offsets/850.h"

// clang-format off

const struct kpayload_offsets offsets_850 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01528FF0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01583618,
  .ALLPROC_addr                    = 0x01BD72D8,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02646238,
  .SBL_PFS_SX_addr                 = 0x0266CA40,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02650078,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02650088,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02654000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02654808,
  .FPU_CTX_addr                    = 0x0264C040,
  .SYSENT_addr                     = 0x010FC5C0,

  // common
  .memcmp_addr                     = 0x0020F280,
  ._sx_xlock_addr                  = 0x002BAF10,
  ._sx_xunlock_addr                = 0x002BB0D0,
  .malloc_addr                     = 0x000B5A40,
  .free_addr                       = 0x000B5C00,
  .strstr_addr                     = 0x00456420,
  .fpu_kern_enter_addr             = 0x00081D20,
  .fpu_kern_leave_addr             = 0x00081DE0,
  .memcpy_addr                     = 0x003A40F0,
  .memset_addr                     = 0x003D6710,
  .strlen_addr                     = 0x00270C40,
  .printf_addr                     = 0x0015D570,
  .eventhandler_register_addr      = 0x001ED3D0,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x00293690,
  .sceSblServiceMailbox_addr       = 0x0062F8E0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00641990,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x006421D0,
  ._sceSblAuthMgrSmStart_addr      = 0x0063E2B0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x006419F0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x00487240,
  .Sha256Hmac_addr                 = 0x00073D90,
  .AesCbcCfb128Encrypt_addr        = 0x002639A0,
  .AesCbcCfb128Decrypt_addr        = 0x00263BD0,
  .sceSblDriverSendMsg_0_addr      = 0x0061B030,
  .sceSblPfsSetKeys_addr           = 0x006295B0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x0062EE90,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00620D00,
  .sceSblKeymgrCleartKey_addr      = 0x00621040,
  .sceSblKeymgrSmCallfunc_addr     = 0x006208D0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x00148530,
  .vmspace_free_addr               = 0x00148360,
  .vm_map_lock_read_addr           = 0x001486D0,
  .vm_map_unlock_read_addr         = 0x00148720,
  .vm_map_lookup_entry_addr        = 0x00148D10,
  .proc_rwmem_addr                 = 0x00131B50,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0064243C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0064258E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00642D26,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00643A09,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x006406FD,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00641338,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x0062EF35,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x00621EBD,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C2F0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064D0BE,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006A0729,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006A095A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D1C0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D520,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001888C0, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EDA401, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000FC5CB,
  .SceRemotePlay_patch2                                      = 0x000FC5E6,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016C3D0,
  .sceKernelIsGenuineCEX_patch2    = 0x0084F5A0,
  .sceKernelIsGenuineCEX_patch3    = 0x0089E962,
  .sceKernelIsGenuineCEX_patch4    = 0x00A15C80,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016C3FA,
  .nidf_libSceDipsw_patch2         = 0x00247108,
  .nidf_libSceDipsw_patch3         = 0x0084F5CA,
  .nidf_libSceDipsw_patch4         = 0x00A15CAA,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00136E60,
  .app_installer_patch             = 0x00136F50,
  .check_system_version            = 0x003C1E57,
  .check_title_system_update_patch = 0x003C44C0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00320713,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00D9B890,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003D3ADF,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FBC331,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009FEB91,
  .ext_hdd_patch                   = 0x00607C8D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0072FA29,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CFCA6,
};

// clang-format on
