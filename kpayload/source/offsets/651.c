#include "sections.h"

#include "offsets/651.h"

// clang-format off

const struct kpayload_offsets offsets_651 PAYLOAD_RDATA = {
  // data
  .XFAST_SYSCALL_addr              = 0x000001C0,
  .PRISON0_addr                    = 0x0113D4F8,
  .ROOTVNODE_addr                  = 0x02300320,
  .M_TEMP_addr                     = 0x01540EB0,
  .MINI_SYSCORE_SELF_BINARY_addr   = 0x0156A588,
  .ALLPROC_addr                    = 0x022BBE80,
  .SBL_DRIVER_MAPPED_PAGES_addr    = 0x0266AC68,
  .SBL_PFS_SX_addr                 = 0x02679040,
  .SBL_KEYMGR_KEY_SLOTS_addr       = 0x02694570,
  .SBL_KEYMGR_KEY_RBTREE_addr      = 0x02694580,
  .SBL_KEYMGR_BUF_VA_addr          = 0x02698000,
  .SBL_KEYMGR_BUF_GVA_addr         = 0x02698808,
  .FPU_CTX_addr                    = 0x02694080,
  .SYSENT_addr                     = 0x0111D000,

  // common
  .memcmp_addr                     = 0x00207A90,
  ._sx_xlock_addr                  = 0x000426C0,
  ._sx_xunlock_addr                = 0x00042880,
  .malloc_addr                     = 0x0000D7A0,
  .free_addr                       = 0x0000D9A0,
  .strstr_addr                     = 0x00481440,
  .fpu_kern_enter_addr             = 0x0036B330,
  .fpu_kern_leave_addr             = 0x0036B420,
  .memcpy_addr                     = 0x003C1200,
  .memset_addr                     = 0x00168420,
  .strlen_addr                     = 0x00243030,
  .printf_addr                     = 0x00122ED0,
  .eventhandler_register_addr      = 0x00402AD0,

  // Fself
  .sceSblACMgrGetPathId_addr       = 0x002338C0,
  .sceSblServiceMailbox_addr       = 0x0064C860,
  .sceSblAuthMgrSmIsLoadable2_addr = 0x0065C400,
  ._sceSblAuthMgrGetSelfInfo_addr  = 0x0065CC70,
  ._sceSblAuthMgrSmStart_addr      = 0x0065D0F0,
  .sceSblAuthMgrVerifyHeader_addr  = 0x0065C460,

  // Fpkg
  .RsaesPkcs1v15Dec2048CRT_addr    = 0x001D5CA0,
  .Sha256Hmac_addr                 = 0x003357C0,
  .AesCbcCfb128Encrypt_addr        = 0x003BFF70,
  .AesCbcCfb128Decrypt_addr        = 0x003C01A0,
  .sceSblDriverSendMsg_0_addr      = 0x00637720,
  .sceSblPfsSetKeys_addr           = 0x00641160,
  .sceSblKeymgrSetKeyStorage_addr  = 0x00646A40,
  .sceSblKeymgrSetKeyForPfs_addr   = 0x00649440,
  .sceSblKeymgrCleartKey_addr      = 0x006497C0,
  .sceSblKeymgrSmCallfunc_addr     = 0x00649010,

  // Patch
  .vmspace_acquire_ref_addr        = 0x0044C7E0,
  .vmspace_free_addr               = 0x0044C610,
  .vm_map_lock_read_addr           = 0x0044C990,
  .vm_map_unlock_read_addr         = 0x0044C9E0,
  .vm_map_lookup_entry_addr        = 0x0044CF80,
  .proc_rwmem_addr                 = 0x0010EA60,

  // Fself hooks
  .sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook        = 0x002338C0,
  .sceSblAuthMgrIsLoadable2_hook                             = 0x006582CF,
  .sceSblAuthMgrVerifyHeader_hook1                           = 0x00658A86,
  .sceSblAuthMgrVerifyHeader_hook2                           = 0x00659718,
  .sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook = 0x0065F31A,
  .sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook   = 0x0065FF61,

  // Fpkg hooks
  .sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook       = 0x00646AE5,
  .sceSblKeymgrInvalidateKey__sx_xlock_hook                  = 0x0064A67D,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook    = 0x00667F00,
  .sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook         = 0x00668D13,
  .mountpfs__sceSblPfsSetKeys_hook1                          = 0x006CC865,
  .mountpfs__sceSblPfsSetKeys_hook2                          = 0x006CCA91,

  // SceShellUI patches - debug patches - libkernel_sys.sprx
  .sceSblRcMgrIsAllowDebugMenuForSettings_patch              = 0x0001D670,
  .sceSblRcMgrIsStoreMode_patch                              = 0x0001D9D0,

  // SceShellUI patches - remote play patches
  .CreateUserForIDU_patch                                    = 0x001A08B0, // system_ex\app\NPXS20001\eboot.bin
  .remote_play_menu_patch                                    = 0x00EC6801, // system_ex\app\NPXS20001\psm\Application\app.exe.sprx

  // SceRemotePlay patches - remote play patches - system\vsh\app\NPXS21006
  .SceRemotePlay_patch1                                      = 0x0010C6D4,
  .SceRemotePlay_patch2                                      = 0x0010C6EF,

  // SceShellCore patches - call sceKernelIsGenuineCEX
  .sceKernelIsGenuineCEX_patch1    = 0x001898A2,
  .sceKernelIsGenuineCEX_patch2    = 0x008294A2,
  .sceKernelIsGenuineCEX_patch3    = 0x00874052,
  .sceKernelIsGenuineCEX_patch4    = 0x00A04BD2,

  // SceShellCore patches - call nidf_libSceDipsw
  .nidf_libSceDipsw_patch1         = 0x001898D0,
  .nidf_libSceDipsw_patch2         = 0x002543F7,
  .nidf_libSceDipsw_patch3         = 0x008294D0,
  .nidf_libSceDipsw_patch4         = 0x00A04C00,

  // SceShellCore patches - bypass firmware checks
  .check_disc_root_param_patch     = 0x00149D9D,
  .app_installer_patch             = 0x00149E90,
  .check_system_version            = 0x003DB768,
  .check_title_system_update_patch = 0x003DED30,

  // SceShellCore patches - enable remote pkg installer
  .enable_data_mount_patch         = 0x0033904E,

  // SceShellCore patches - enable VR without spoof
  .enable_psvr_patch               = 0x00DCFAD0,

  // SceShellCore patches - enable fpkg
  .enable_fpkg_patch               = 0x003EFB00,

  // SceShellCore patches - use `free` prefix instead `fake`
  .fake_free_patch                 = 0x00FC40D1,

  // SceShellCore patches - enable official external HDD support
  .pkg_installer_patch             = 0x009ED351,
  .ext_hdd_patch                   = 0x00604F3D,

  // SceShellCore patches - enable debug trophies
  .debug_trophies_patch            = 0x0071F249,

  // SceShellCore patches - disable screenshot block
  .disable_screenshot_patch        = 0x000DD176,

  // Process structure offsets
  .proc_p_comm_offset = 0x454,
  .proc_path_offset   = 0x474,
};

// clang-format on
