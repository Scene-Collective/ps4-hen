#include "sections.h"

#include "offsets/900.h"

// clang-format off

const struct kpayload_offsets offsets_900 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x015621E0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01579DF8,
  .ALLPROC_addr                    = 0x01B946E0,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02646CA8,
  .SBL_PFS_SX_addr                 = 0x0264DB40,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02648238,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02648248,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0264C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0264C808,
  .FPU_CTX_addr                    = 0x026541C0,
  .SYSENT_addr                     = 0x01100310,

  // common
  .memcmp_addr                     = 0x00271E20,
  ._sx_xlock_addr                  = 0x0043E610,
  ._sx_xunlock_addr                = 0x0043E7D0,
  .malloc_addr                     = 0x00301B20,
  .free_addr                       = 0x00301CE0,
  .strstr_addr                     = 0x00487AB0,
  .fpu_kern_enter_addr             = 0x002196D0,
  .fpu_kern_leave_addr             = 0x00219790,
  .memcpy_addr                     = 0x002714B0,
  .memset_addr                     = 0x001496C0,
  .strlen_addr                     = 0x0030F450,
  .printf_addr                     = 0x000B7A30,
  .eventhandler_register_addr      = 0x000F8370,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x0008BCD0,
  .sceSblServiceMailbox_addr       = 0x00630C40,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x006439A0,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x006441E0,
  ._sceSblAuthMgrSmStart_addr      = 0x0063FEE0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x00643A00,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x004628B0,
  .Sha256Hmac_addr                 = 0x00445060,
  .AesCbcCfb128Encrypt_addr        = 0x001FF2D0,
  .AesCbcCfb128Decrypt_addr        = 0x001FF500,
  .sceSblDriverSendMsg_0_addr      = 0x0061CED0,
  .sceSblPfsSetKeys_addr           = 0x006252D0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00624970,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0061F690,
  .sceSblKeymgrCleartKey_addr      = 0x0061F9D0,
  .sceSblKeymgrSmCallfunc_addr     = 0x0061F260,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0007B9E0,
  .vmspace_free_addr               = 0x0007B810,
  .vm_map_lock_read_addr           = 0x0007BB80,
  .vm_map_unlock_read_addr         = 0x0007BBD0,
  .vm_map_lookup_entry_addr        = 0x0007C1C0,
  .proc_rwmem_addr                 = 0x0041EB00,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0064473C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0064488E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00645026,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00645D09,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0064232D,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00642F68,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00624A15,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0062084D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064E070,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064EE3E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006C3EF9,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006C412A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D1C0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D520,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00188C10, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EE55C1, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010039B,
  .SceRemotePlay_patch2                                      = 0x001003B6,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016EAA4,
  .sceKernelIsGenuineCEX_patch2    = 0x008621D4,
  .sceKernelIsGenuineCEX_patch3    = 0x008AFBC2,
  .sceKernelIsGenuineCEX_patch4    = 0x00A27BD4,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016EAD2,
  .nidf_libSceDipsw_patch2         = 0x00249F7B,
  .nidf_libSceDipsw_patch3         = 0x00862202,
  .nidf_libSceDipsw_patch4         = 0x00A27C02,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00138DA0,
  .app_installer_patch             = 0x00138E90,
  .check_system_version            = 0x003C5EA7,
  .check_title_system_update_patch = 0x003C8540,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0032079B,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DB0B60,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003D7AFF,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FD3211,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x00A10A81,
  .ext_hdd_patch                   = 0x006180FD,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x00743299,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D1866,
};

// clang-format on
