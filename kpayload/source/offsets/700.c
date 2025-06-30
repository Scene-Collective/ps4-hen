#include "sections.h"

#include "offsets/700.h"

// clang-format off

const struct kpayload_offsets offsets_700 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .M_TEMP_addr                     = 0x01A7AE50,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x01555BD8,
  .ALLPROC_addr                    = 0x01B48318,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02669E48,
  .SBL_PFS_SX_addr                 = 0x026945C0,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02698848,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02698858,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0269C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0269C808,
  .FPU_CTX_addr                    = 0x02688400,
  .SYSENT_addr                     = 0x01125660,

  // common
  .memcmp_addr                     = 0x00207500,
  ._sx_xlock_addr                  = 0x001AE030,
  ._sx_xunlock_addr                = 0x001AE1F0,
  .malloc_addr                     = 0x00301840,
  .free_addr                       = 0x00301A40,
  .strstr_addr                     = 0x00005740,
  .fpu_kern_enter_addr             = 0x002CEBF0,
  .fpu_kern_leave_addr             = 0x002CECE0,
  .memcpy_addr                     = 0x0002F040,
  .memset_addr                     = 0x002DFC20,
  .strlen_addr                     = 0x00093FF0,
  .printf_addr                     = 0x000BC730,
  .eventhandler_register_addr      = 0x00483810,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x001CB930,
  .sceSblServiceMailbox_addr       = 0x0064C110,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00660210,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x00660A90,
  ._sceSblAuthMgrSmStart_addr      = 0x0065A560,
  .sceSblAuthMgrVerifyHeader_addr  = 0x00660270,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x001DD540,
  .Sha256Hmac_addr                 = 0x00205F50,
  .AesCbcCfb128Encrypt_addr        = 0x001DA410,
  .AesCbcCfb128Decrypt_addr        = 0x001DA640,
  .sceSblDriverSendMsg_0_addr      = 0x006376A0,
  .sceSblPfsSetKeys_addr           = 0x00647000,
  .sceSblKeymgrSetKeyStorage_addr  = 0x0063E230,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00648650,
  .sceSblKeymgrCleartKey_addr      = 0x006489D0,
  .sceSblKeymgrSmCallfunc_addr     = 0x00648220,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0025F9F0,
  .vmspace_free_addr               = 0x0025F820,
  .vm_map_lock_read_addr           = 0x0025FB90,
  .vm_map_unlock_read_addr         = 0x0025FBE0,
  .vm_map_lookup_entry_addr        = 0x00260190,
  .proc_rwmem_addr                 = 0x00043E80,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0065E97C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x0065EACF,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x0065F256,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0065FEF8,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0065CA0D,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x0065D669,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x0063E2D5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0064989D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x00668A50,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0066985E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006B534B,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006B557C,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D240,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D5A0,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x00191220, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00ECC9A1, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010B343,
  .SceRemotePlay_patch2                                      = 0x0010B35E,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x00174260,
  .sceKernelIsGenuineCEX_patch2    = 0x007F5D00,
  .sceKernelIsGenuineCEX_patch3    = 0x00840132,
  .sceKernelIsGenuineCEX_patch4    = 0x009CE100,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0017428A,
  .nidf_libSceDipsw_patch2         = 0x0023A6FC,
  .nidf_libSceDipsw_patch3         = 0x007F5D2A,
  .nidf_libSceDipsw_patch4         = 0x009CE12A,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x0013CE3D,
  .app_installer_patch             = 0x0013CF20,
  .check_system_version            = 0x003B3B38,
  .check_title_system_update_patch = 0x003B6270,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00318FE1,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00D629A0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003C5900,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00F5E9B1,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009B6C41,
  .ext_hdd_patch                   = 0x005C6AAD,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x006E85A9,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D61F6,
};

// clang-format on
