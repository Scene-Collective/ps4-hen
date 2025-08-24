#include "sections.h"

#include "offsets/620.h"

// clang-format off

const struct kpayload_offsets offsets_620 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .PRISON0_addr                    = 0x0113D458,
  .ROOTVNODE_addr                  = 0x021C3AC0,
  .M_TEMP_addr                     = 0x0155D070,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0157F648,
  .ALLPROC_addr                    = 0x022FBCD0,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02659E58,
  .SBL_PFS_SX_addr                 = 0x02677290,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02684A78,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02684A88,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02688000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02688808,
  .FPU_CTX_addr                    = 0x026846C0,
  .SYSENT_addr                     = 0x0111F540,

  // common
  .memcmp_addr                     = 0x004A1740,
  ._sx_xlock_addr                  = 0x00083F00,
  ._sx_xunlock_addr                = 0x000840C0,
  .malloc_addr                     = 0x001D9060,
  .free_addr                       = 0x001D9260,
  .strstr_addr                     = 0x004247F0,
  .fpu_kern_enter_addr             = 0x001E3990,
  .fpu_kern_leave_addr             = 0x001E3A90,
  .memcpy_addr                     = 0x00114700,
  .memset_addr                     = 0x00394C60,
  .strlen_addr                     = 0x000D5AA0,
  .printf_addr                     = 0x00307E10,
  .eventhandler_register_addr      = 0x00180F80,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x004594E0,
  .sceSblServiceMailbox_addr       = 0x0064B480,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x00656D20,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x006575B0,
  ._sceSblAuthMgrSmStart_addr      = 0x0065B070,
  .sceSblAuthMgrVerifyHeader_addr  = 0x00656D80,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x002209B0,
  .Sha256Hmac_addr                 = 0x00165D80,
  .AesCbcCfb128Encrypt_addr        = 0x002D40F0,
  .AesCbcCfb128Decrypt_addr        = 0x002D4320,
  .sceSblDriverSendMsg_0_addr      = 0x006378E0,
  .sceSblPfsSetKeys_addr           = 0x00640C90,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00646050,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00648EF0,
  .sceSblKeymgrCleartKey_addr      = 0x00649280,
  .sceSblKeymgrSmCallfunc_addr     = 0x00648AC0,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0034D0B0,
  .vmspace_free_addr               = 0x0034CEE0,
  .vm_map_lock_read_addr           = 0x0034D260,
  .vm_map_unlock_read_addr         = 0x0034D2B0,
  .vm_map_lookup_entry_addr        = 0x0034D860,
  .proc_rwmem_addr                 = 0x0013E7A0,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x00658D2C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x00658E7F,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00659636,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x0065A2D8,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0065D29A,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x0065DEE1,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x006460F5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0064A11D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x006685C0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x006693D3,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x0069FABA,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x0069FCE6,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D6D0,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001DA30,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001A0510, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00E9F7B1, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

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
  .enable_psvr_patch               = 0x00DBABB0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003F7222,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00F9FB11,

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
