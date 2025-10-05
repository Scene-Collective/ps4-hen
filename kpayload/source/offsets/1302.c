#include "sections.h"

#include "offsets/1302.h"

// clang-format off

const struct kpayload_offsets offsets_1302 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .PRISON0_addr                    = 0x0111FA18,
  .ROOTVNODE_addr                  = 0x02136E90,
  .M_TEMP_addr                     = 0x01520D00,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0153D6C8,
  .ALLPROC_addr                    = 0x01B28538,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x02647350,
  .SBL_PFS_SX_addr                 = 0x0265C080,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02668040,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02668050,
  .SBL_KEYMGR_BUF_VA_addr          = 0x0266C000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x0266C808,
  .FPU_CTX_addr                    = 0x026542C0,
  .SYSENT_addr                     = 0x01102B70,

  // common
  .memcmp_addr                     = 0x00394310,
  ._sx_xlock_addr                  = 0x000A3840,
  ._sx_xunlock_addr                = 0x000A3A00,
  .malloc_addr                     = 0x00009520,
  .free_addr                       = 0x000096E0,
  .strstr_addr                     = 0x0021CCC0,
  .fpu_kern_enter_addr             = 0x001E0050,
  .fpu_kern_leave_addr             = 0x001E0110,
  .memcpy_addr                     = 0x002BD4F0,
  .memset_addr                     = 0x001FA1B0,
  .strlen_addr                     = 0x0036ABA0,
  .printf_addr                     = 0x002E0450,
  .eventhandler_register_addr      = 0x00224180,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x003B2DF0,
  .sceSblServiceMailbox_addr       = 0x0062F9F0,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0063C860,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0063D0A0,
  ._sceSblAuthMgrSmStart_addr      = 0x0063DC30,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0063C8C0,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x0021BC70,
  .Sha256Hmac_addr                 = 0x001F8DB0,
  .AesCbcCfb128Encrypt_addr        = 0x00340EA0,
  .AesCbcCfb128Decrypt_addr        = 0x003410D0,
  .sceSblDriverSendMsg_0_addr      = 0x0061C030,
  .sceSblPfsSetKeys_addr           = 0x00626770,
  .sceSblKeymgrSetKeyStorage_addr  = 0x006247D0,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x0062B0C0,
  .sceSblKeymgrCleartKey_addr      = 0x0062B400,
  .sceSblKeymgrSmCallfunc_addr     = 0x0062AC90,

  // Patch
  .vmspace_acquire_ref_addr        = 0x002F6F90,
  .vmspace_free_addr               = 0x002F6DC0,
  .vm_map_lock_read_addr           = 0x002F7120,
  .vm_map_unlock_read_addr         = 0x002F7170,
  .vm_map_lookup_entry_addr        = 0x002F7760,
  .proc_rwmem_addr                 = 0x00366010,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x0064207C,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x006421CE,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00642966,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00643649,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0064007D,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x00640CB8,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00624875,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0062C27D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x0064C5D0,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x0064D39E,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006A2EF9,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006A312A,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D100,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D460,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x0018B3B0, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC8902, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x000ED1F5,
  .SceRemotePlay_patch2                                      = 0x000ED210,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x0016F5A4,
  .sceKernelIsGenuineCEX_patch2    = 0x00874674,
  .sceKernelIsGenuineCEX_patch3    = 0x008C4992,
  .sceKernelIsGenuineCEX_patch4    = 0x00A28244,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x0016F5D2,
  .nidf_libSceDipsw_patch2         = 0x0024E11C,
  .nidf_libSceDipsw_patch3         = 0x008746A2,
  .nidf_libSceDipsw_patch4         = 0x00A28272,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0xDEADC0DE,
  .app_installer_patch             = 0x001389A0,
  .check_system_version            = 0x003CA3A7,
  .check_title_system_update_patch = 0x003CD5F0,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x00323380,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DAF5E0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003DE07F,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FD0E59,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x00A11791,
  .ext_hdd_patch                   = 0x0061465D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0074D0C9,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000D2216,

  // Process structure offsets
  .proc_p_comm_offset = 0x454,
  .proc_path_offset   = 0x474,
};

// clang-format on
