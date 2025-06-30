#include "sections.h"

#include "offsets/960.h"

// clang-format off

const struct kpayload_offsets offsets_960 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01A4ECB0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01542948,
  .ALLPROC_addr                    = 0x0221D2A0,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x0263A6D0,
  .SBL_PFS_SX_addr                 = 0x02658650,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02648B78,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02648B88,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0264C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0264C808,
  .FPU_CTX_addr                    = 0x0263AEC0,
  .SYSENT_addr                     = 0x010F92F0,

  // common
  .memcmp_addr                     = 0x0047CB80,
  ._sx_xlock_addr                  = 0x0042BB40,
  ._sx_xunlock_addr                = 0x0042BD00,
  .malloc_addr                     = 0x0029D330,
  .free_addr                       = 0x0029D4F0,
  .strstr_addr                     = 0x00248480,
  .fpu_kern_enter_addr             = 0x002BDDA0,
  .fpu_kern_leave_addr             = 0x002BDE60,
  .memcpy_addr                     = 0x00201CC0,
  .memset_addr                     = 0x000C1720,
  .strlen_addr                     = 0x003F1980,
  .printf_addr                     = 0x00205470,
  .eventhandler_register_addr      = 0x00285720,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x00032640,
  .sceSblServiceMailbox_addr       = 0x006276E0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0063A970,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0063B1B0,
  ._sceSblAuthMgrSmStart_addr      = 0x00633FA0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0063A9D0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x0005F060,
  .Sha256Hmac_addr                 = 0x0021B230,
  .AesCbcCfb128Encrypt_addr        = 0x003681A0,
  .AesCbcCfb128Decrypt_addr        = 0x003683D0,
  .sceSblDriverSendMsg_0_addr      = 0x00613C30,
  .sceSblPfsSetKeys_addr           = 0x0061F6D0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x0061F3F0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00619DF0,
  .sceSblKeymgrCleartKey_addr      = 0x0061A130,
  .sceSblKeymgrSmCallfunc_addr     = 0x006199C0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x00191BA0,
  .vmspace_free_addr               = 0x001919D0,
  .vm_map_lock_read_addr           = 0x00191D30,
  .vm_map_unlock_read_addr         = 0x00191D80,
  .vm_map_lookup_entry_addr        = 0x00192370,
  .proc_rwmem_addr                 = 0x00479620,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x006390EC,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0063923E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x006399D6,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0063A6B9,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x006363ED,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00637028,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x0061F495,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0061AFAD,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x00645DD0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x00646B9E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006A69E9,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006A6C1A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001CE50,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D1B0,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00185160, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EEFF41, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000EA0B5,
  .SceRemotePlay_patch2                                      = 0x000EA0D0,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016CD64,
  .sceKernelIsGenuineCEX_patch2    = 0x008630A4,
  .sceKernelIsGenuineCEX_patch3    = 0x008B1CA2,
  .sceKernelIsGenuineCEX_patch4    = 0x00A122C4,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016CD92,
  .nidf_libSceDipsw_patch2         = 0x0024A35C,
  .nidf_libSceDipsw_patch3         = 0x008630D2,
  .nidf_libSceDipsw_patch4         = 0x00A122F2,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0xDEADC0DE,
  .app_installer_patch             = 0x00136160,
  .check_system_version            = 0x003C1F97,
  .check_title_system_update_patch = 0x003C51E0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0031D651,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00D99B00,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003D4E9F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FBD319,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009FB811,
  .ext_hdd_patch                   = 0x00610AED,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x00741E09,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CF776,
};

// clang-format on
