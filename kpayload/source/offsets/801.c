#include "sections.h"

#include "offsets/801.h"

// clang-format off

const struct kpayload_offsets offsets_801 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01A77E10,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01577F28,
  .ALLPROC_addr                    = 0x01B244E0,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x0263FAE8,
  .SBL_PFS_SX_addr                 = 0x02644008,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02648848,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02648858,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0264C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0264C808,
  .FPU_CTX_addr                    = 0x0266C500,
  .SYSENT_addr                     = 0x010FC4D0,

  // common
  .memcmp_addr                     = 0x00195A90,
  ._sx_xlock_addr                  = 0x0043A340,
  ._sx_xunlock_addr                = 0x0043A500,
  .malloc_addr                     = 0x0046F7F0,
  .free_addr                       = 0x0046F9B0,
  .strstr_addr                     = 0x00439C10,
  .fpu_kern_enter_addr             = 0x001714B0,
  .fpu_kern_leave_addr             = 0x00171570,
  .memcpy_addr                     = 0x0025E1C0,
  .memset_addr                     = 0x000F6C60,
  .strlen_addr                     = 0x002F6090,
  .printf_addr                     = 0x00430AE0,
  .eventhandler_register_addr      = 0x0026E270,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x001D57C0,
  .sceSblServiceMailbox_addr       = 0x0062F6E0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00641F40,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x00642780,
  ._sceSblAuthMgrSmStart_addr      = 0x0063D140,
  .sceSblAuthMgrVerifyHeader_addr  = 0x00641FA0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x0038F5A0,
  .Sha256Hmac_addr                 = 0x00126B90,
  .AesCbcCfb128Encrypt_addr        = 0x001665B0,
  .AesCbcCfb128Decrypt_addr        = 0x001667E0,
  .sceSblDriverSendMsg_0_addr      = 0x00619BE0,
  .sceSblPfsSetKeys_addr           = 0x0061CBA0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00627FB0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0061E250,
  .sceSblKeymgrCleartKey_addr      = 0x0061E590,
  .sceSblKeymgrSmCallfunc_addr     = 0x0061DE20,

  // Patch
  .vmspace_acquire_ref_addr        = 0x003E74E0,
  .vmspace_free_addr               = 0x003E7310,
  .vm_map_lock_read_addr           = 0x003E7680,
  .vm_map_unlock_read_addr         = 0x003E76D0,
  .vm_map_lookup_entry_addr        = 0x003E7CC0,
  .proc_rwmem_addr                 = 0x00173770,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0063B8BC,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0063BA0E,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x0063C1A6,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0063CE89,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0063F59D,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x006401D8,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00628055,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0061F40D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C590,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064D35E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x0068D509,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x0068D73A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D130,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D490,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00187300, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EDB1B1, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010C4CB,
  .SceRemotePlay_patch2                                      = 0x0010C4E6,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x00168D20,
  .sceKernelIsGenuineCEX_patch2    = 0x0084CFD0,
  .sceKernelIsGenuineCEX_patch3    = 0x0089C132,
  .sceKernelIsGenuineCEX_patch4    = 0x00A235E0,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x00168D4A,
  .nidf_libSceDipsw_patch2         = 0x00242978,
  .nidf_libSceDipsw_patch3         = 0x0084CFFA,
  .nidf_libSceDipsw_patch4         = 0x00A2360A,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00133480,
  .app_installer_patch             = 0x00133570,
  .check_system_version            = 0x003C02E7,
  .check_title_system_update_patch = 0x003C2970,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0031C503,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DA7480,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003D1A2F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FC61F1,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x00A0C5C1,
  .ext_hdd_patch                   = 0x0060756D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0072D5B9,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000CF3F6,
};

// clang-format on
