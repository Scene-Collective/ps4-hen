#include "sections.h"

#include "offsets/1000.h"

// clang-format off

const struct kpayload_offsets offsets_1000 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01532C00,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0155EC48,
  .ALLPROC_addr                    = 0x022D9B40,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02646258,
  .SBL_PFS_SX_addr                 = 0x0267C088,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x026583B8,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x026583C8,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0265C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0265C808,
  .FPU_CTX_addr                    = 0x02660040,
  .SYSENT_addr                     = 0x01102D90,

  // common
  .memcmp_addr                     = 0x00109940,
  ._sx_xlock_addr                  = 0x000A9A80,
  ._sx_xunlock_addr                = 0x000A9C40,
  .malloc_addr                     = 0x00109A60,
  .free_addr                       = 0x00109C20,
  .strstr_addr                     = 0x003F7490,
  .fpu_kern_enter_addr             = 0x0026C7D0,
  .fpu_kern_leave_addr             = 0x0026C890,
  .memcpy_addr                     = 0x00472D20,
  .memset_addr                     = 0x0003E6F0,
  .strlen_addr                     = 0x002E0340,
  .printf_addr                     = 0x000C50F0,
  .eventhandler_register_addr      = 0x002269A0,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x000A5D10,
  .sceSblServiceMailbox_addr       = 0x0062DBE0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x006415F0,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x00641E30,
  ._sceSblAuthMgrSmStart_addr      = 0x0063D790,
  .sceSblAuthMgrVerifyHeader_addr  = 0x00641650,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x0006CA20,
  .Sha256Hmac_addr                 = 0x0013A3D0,
  .AesCbcCfb128Encrypt_addr        = 0x003B9E00,
  .AesCbcCfb128Decrypt_addr        = 0x003BA030,
  .sceSblDriverSendMsg_0_addr      = 0x006194A0,
  .sceSblPfsSetKeys_addr           = 0x0062CB00,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00624CA0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00621220,
  .sceSblKeymgrCleartKey_addr      = 0x00621560,
  .sceSblKeymgrSmCallfunc_addr     = 0x00620DF0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0038CEE0,
  .vmspace_free_addr               = 0x0038CD10,
  .vm_map_lock_read_addr           = 0x0038D070,
  .vm_map_unlock_read_addr         = 0x0038D0C0,
  .vm_map_lookup_entry_addr        = 0x0038D6B0,
  .proc_rwmem_addr                 = 0x0044DC40,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0063A7FC,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0063A94E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x0063B0E6,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0063BDC9,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0063FBDD,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00640818,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00624D45,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x006223DD,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064AD10,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064BADE,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x0068E4C9,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x0068E6FA,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001CE50,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D1B0,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00185E90, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC2282, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000ECB55,
  .SceRemotePlay_patch2                                      = 0x000ECB70,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016B694,
  .sceKernelIsGenuineCEX_patch2    = 0x008594B4,
  .sceKernelIsGenuineCEX_patch3    = 0x008A85F2,
  .sceKernelIsGenuineCEX_patch4    = 0x00A08094,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016B6C2,
  .nidf_libSceDipsw_patch2         = 0x00247E4C,
  .nidf_libSceDipsw_patch3         = 0x008594E2,
  .nidf_libSceDipsw_patch4         = 0x00A080C2,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0xDEADC0DE,
  .app_installer_patch             = 0x00134A90,
  .check_system_version            = 0x003BF7A7,
  .check_title_system_update_patch = 0x003C29F0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0031B310,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00D919E0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003D26AF,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FB08B9,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009F15E1,
  .ext_hdd_patch                   = 0x00604FFD,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x00738319,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CF8B6,
};

// clang-format on
