#include "sections.h"

#include "offsets/903.h"

// clang-format off

const struct kpayload_offsets offsets_903 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x0155E1E0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01575DF8,
  .ALLPROC_addr                    = 0x01B906E0,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02642CA8,
  .SBL_PFS_SX_addr                 = 0x02649B40,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02644238,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02644248,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02648000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02648808,
  .FPU_CTX_addr                    = 0x026501C0,
  .SYSENT_addr                     = 0x010FC310,

  // common
  .memcmp_addr                     = 0x00271AA0,
  ._sx_xlock_addr                  = 0x0043C530,
  ._sx_xunlock_addr                = 0x0043C6F0,
  .malloc_addr                     = 0x003017B0,
  .free_addr                       = 0x00301970,
  .strstr_addr                     = 0x004859B0,
  .fpu_kern_enter_addr             = 0x002193A0,
  .fpu_kern_leave_addr             = 0x00219460,
  .memcpy_addr                     = 0x00271130,
  .memset_addr                     = 0x00149670,
  .strlen_addr                     = 0x0030F0F0,
  .printf_addr                     = 0x000B79E0,
  .eventhandler_register_addr      = 0x000F8320,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x0008BCD0,
  .sceSblServiceMailbox_addr       = 0x0062EC00,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00641960,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x006421A0,
  ._sceSblAuthMgrSmStart_addr      = 0x0063DEA0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x006419C0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x004607B0,
  .Sha256Hmac_addr                 = 0x00442F80,
  .AesCbcCfb128Encrypt_addr        = 0x001FF000,
  .AesCbcCfb128Decrypt_addr        = 0x001FF230,
  .sceSblDriverSendMsg_0_addr      = 0x0061AE90,
  .sceSblPfsSetKeys_addr           = 0x00623290,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00622930,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0061D650,
  .sceSblKeymgrCleartKey_addr      = 0x0061D990,
  .sceSblKeymgrSmCallfunc_addr     = 0x0061D220,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0007B9E0,
  .vmspace_free_addr               = 0x0007B810,
  .vm_map_lock_read_addr           = 0x0007BB80,
  .vm_map_unlock_read_addr         = 0x0007BBD0,
  .vm_map_lookup_entry_addr        = 0x0007C1C0,
  .proc_rwmem_addr                 = 0x0041CA70,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x006426FC,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0064284E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00642FE6,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00643CC9,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x006402ED,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00640F28,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x006229D5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0061E80D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C030,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064CDFE,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006C1EB9,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006C20EA,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D1C0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D520,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00188C10, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EE5651, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010039B,
  .SceRemotePlay_patch2                                      = 0x001003B6,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016F014,
  .sceKernelIsGenuineCEX_patch2    = 0x00864744,
  .sceKernelIsGenuineCEX_patch3    = 0x008B2232,
  .sceKernelIsGenuineCEX_patch4    = 0x00A2A254,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016F042,
  .nidf_libSceDipsw_patch2         = 0x0024A4EB,
  .nidf_libSceDipsw_patch3         = 0x00864772,
  .nidf_libSceDipsw_patch4         = 0x00A2A282,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00139310,
  .app_installer_patch             = 0x00139400,
  .check_system_version            = 0x003C8417,
  .check_title_system_update_patch = 0x003CAAB0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00321F2B,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DB31E0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003DA06F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FD5BD1,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x00A13101,
  .ext_hdd_patch                   = 0x0061A66D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x00745809,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D1956,
};

// clang-format on
