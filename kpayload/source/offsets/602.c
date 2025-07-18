#include "sections.h"

#include "offsets/602.h"

// clang-format off

const struct kpayload_offsets offsets_602 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .PRISON0_addr                    = 0x01139458,
  .ROOTVNODE_addr                  = 0x021BFAC0,
  .M_TEMP_addr                     = 0x01559070,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0157B648,
  .ALLPROC_addr                    = 0x022F7CD0,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02655E58,
  .SBL_PFS_SX_addr                 = 0x02673290,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02680A78,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02680A88,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02684000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02684808,
  .FPU_CTX_addr                    = 0x026806C0,
  .SYSENT_addr                     = 0x0111B540,

  // common
  .memcmp_addr                     = 0x004A1720,
  ._sx_xlock_addr                  = 0x00083F00,
  ._sx_xunlock_addr                = 0x000840C0,
  .malloc_addr                     = 0x001D9060,
  .free_addr                       = 0x001D9260,
  .strstr_addr                     = 0x004247F0,
  .fpu_kern_enter_addr             = 0x001E3990,
  .fpu_kern_leave_addr             = 0x001E3A90,
  .memcpy_addr                     = 0x00114700,
  .memset_addr                     = 0x00394C40,
  .strlen_addr                     = 0x000D5AA0,
  .printf_addr                     = 0x00307DF0,
  .eventhandler_register_addr      = 0x00180F80,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x004594C0,
  .sceSblServiceMailbox_addr       = 0x0064AFC0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00656860,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x006570F0,
  ._sceSblAuthMgrSmStart_addr      = 0x0065ABB0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x006568C0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x002209B0,
  .Sha256Hmac_addr                 = 0x00165D80,
  .AesCbcCfb128Encrypt_addr        = 0x002D40D0,
  .AesCbcCfb128Decrypt_addr        = 0x002D4300,
  .sceSblDriverSendMsg_0_addr      = 0x00637420,
  .sceSblPfsSetKeys_addr           = 0x006407D0,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00645B90,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00648A30,
  .sceSblKeymgrCleartKey_addr      = 0x00648DC0,
  .sceSblKeymgrSmCallfunc_addr     = 0x00648600,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0034D090,
  .vmspace_free_addr               = 0x0034CEC0,
  .vm_map_lock_read_addr           = 0x0034D240,
  .vm_map_unlock_read_addr         = 0x0034D290,
  .vm_map_lookup_entry_addr        = 0x0034D840,
  .proc_rwmem_addr                 = 0x0013E7A0,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0065886C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x006589BF,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00659176,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00659E18,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0065CDDA,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x0065DA21,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00645C35,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x00649C5D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x00668100,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x00668F13,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x0069F5FA,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x0069F826,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D6D0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001DA30,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001A0510, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00E9F4F1, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0003CED6,
  .SceRemotePlay_patch2                                      = 0x0003CEF1,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x00186170,
  .sceKernelIsGenuineCEX_patch2    = 0x0081ED20,
  .sceKernelIsGenuineCEX_patch3    = 0x00869BA3,
  .sceKernelIsGenuineCEX_patch4    = 0x009F7550,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0018619A,
  .nidf_libSceDipsw_patch2         = 0x0025C923,
  .nidf_libSceDipsw_patch3         = 0x0081ED4A,
  .nidf_libSceDipsw_patch4         = 0x009F757A,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00146642,
  .app_installer_patch             = 0x00146731,
  .check_system_version            = 0x003E3029,
  .check_title_system_update_patch = 0x003E65D0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0033FF4C,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DBBD40,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003F7222,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FA0CB1,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009E0031,
  .ext_hdd_patch                   = 0x0060081D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0071CDD9,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000DACD6,

  // Process structure offsets
  .proc_p_comm_offset = 0x450,
  .proc_path_offset   = 0x470,
};

// clang-format on
