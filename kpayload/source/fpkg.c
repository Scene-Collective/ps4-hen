#include <stddef.h>
#include <stdint.h>

#include "amd_helper.h"
#include "ccp_helper.h"
#include "freebsd_helper.h"
#include "offsets.h"
#include "pfs_helper.h"
#include "rif_helper.h"
#include "sbl_helper.h"
#include "sections.h"
#include "sparse.h"

extern const struct kpayload_offsets *fw_offsets PAYLOAD_BSS;

extern int (*_sx_xlock)(struct sx *sx, int opts, const char *file, int line) PAYLOAD_BSS;
extern int (*_sx_xunlock)(struct sx *sx) PAYLOAD_BSS;
extern int (*fpu_kern_enter)(struct thread *td, struct fpu_kern_ctx *ctx, uint32_t flags) PAYLOAD_BSS;
extern int (*fpu_kern_leave)(struct thread *td, struct fpu_kern_ctx *ctx) PAYLOAD_BSS;
extern void *(*memcpy)(void *dst, const void *src, size_t len)PAYLOAD_BSS;
extern void *(*memset)(void *s, int c, size_t n)PAYLOAD_BSS;

extern struct sbl_map_list_entry **SBL_DRIVER_MAPPED_PAGES PAYLOAD_BSS;
extern struct sx *SBL_PFS_SX PAYLOAD_BSS;
extern struct sbl_key_slot_queue *SBL_KEYMGR_KEY_SLOTS PAYLOAD_BSS;
extern struct sbl_key_rbtree_entry **SBL_KEYMGR_KEY_RBTREE PAYLOAD_BSS;
extern uint8_t *SBL_KEYMGR_BUF_VA PAYLOAD_BSS;
extern uint64_t *SBL_KEYMGR_BUF_GVA PAYLOAD_BSS;
extern void *FPU_CTX PAYLOAD_BSS;

extern int (*RsaesPkcs1v15Dec2048CRT)(struct rsa_buffer *out, struct rsa_buffer *in, struct rsa_key *key) PAYLOAD_BSS;
extern void (*Sha256Hmac)(uint8_t hash[0x20], const uint8_t *data, size_t data_size, const uint8_t *key, int key_size) PAYLOAD_BSS;
extern int (*AesCbcCfb128Encrypt)(uint8_t *out, const uint8_t *in, size_t data_size, const uint8_t *key, int key_size, uint8_t *iv) PAYLOAD_BSS;
extern int (*AesCbcCfb128Decrypt)(uint8_t *out, const uint8_t *in, size_t data_size, const uint8_t *key, int key_size, uint8_t *iv) PAYLOAD_BSS;
extern int (*sceSblDriverSendMsg_0)(struct sbl_msg *msg, size_t size) PAYLOAD_BSS;
extern int (*sceSblPfsSetKeys)(uint32_t *ekh, uint32_t *skh, uint8_t *eekpfs, struct ekc *eekc, unsigned int pubkey_ver, unsigned int key_ver, struct pfs_header *hdr, size_t hdr_size, unsigned int type, unsigned int finalized, unsigned int is_disc) PAYLOAD_BSS;
extern int (*sceSblKeymgrSetKeyStorage)(uint64_t key_gpu_va, unsigned int key_size, uint32_t key_id, uint32_t key_handle) PAYLOAD_BSS;
extern int (*sceSblKeymgrSetKeyForPfs)(union sbl_key_desc *key, unsigned int *handle) PAYLOAD_BSS;
extern int (*sceSblKeymgrCleartKey)(uint32_t kh) PAYLOAD_BSS;
extern int (*sceSblKeymgrSmCallfunc)(union keymgr_payload *payload) PAYLOAD_BSS;

extern int my_sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif(union keymgr_payload *payload) PAYLOAD_CODE;
extern int my_sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new(union keymgr_payload *payload) PAYLOAD_CODE;
extern int my_sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg(struct sbl_msg *msg, size_t size) PAYLOAD_CODE;
extern int my_mountpfs__sceSblPfsSetKeys(uint32_t *ekh, uint32_t *skh, uint8_t *eekpfs, struct ekc *eekc, unsigned int pubkey_ver, unsigned int key_ver, struct pfs_header *hdr, size_t hdr_size, unsigned int type, unsigned int finalized, unsigned int is_disc) PAYLOAD_CODE;

// clang-format off

static const uint8_t s_ypkg_p[0x80] PAYLOAD_RDATA = {
  0x2D, 0xE8, 0xB4, 0x65, 0xBE, 0x05, 0x78, 0x6A, 0x89, 0x31, 0xC9, 0x5A, 0x44, 0xDE, 0x50, 0xC1,
  0xC7, 0xFD, 0x9D, 0x3E, 0x21, 0x42, 0x17, 0x40, 0x79, 0xF9, 0xC9, 0x41, 0xC1, 0xFC, 0xD7, 0x0F,
  0x34, 0x76, 0xA3, 0xE2, 0xC0, 0x1B, 0x5A, 0x20, 0x0F, 0xAF, 0x2F, 0x52, 0xCD, 0x83, 0x34, 0x72,
  0xAF, 0xB3, 0x12, 0x33, 0x21, 0x2C, 0x20, 0xB0, 0xC6, 0xA0, 0x2D, 0xB1, 0x59, 0xE3, 0xA7, 0xB0,
  0x4E, 0x1C, 0x4C, 0x5B, 0x5F, 0x10, 0x9A, 0x50, 0x18, 0xCC, 0x86, 0x79, 0x25, 0xFF, 0x10, 0x02,
  0x8F, 0x90, 0x03, 0xA9, 0x37, 0xBA, 0xF2, 0x1C, 0x13, 0xCC, 0x09, 0x45, 0x15, 0xB8, 0x55, 0x74,
  0x0A, 0x28, 0x24, 0x04, 0xD1, 0x19, 0xAB, 0xB3, 0xCA, 0x44, 0xB6, 0xF8, 0x3D, 0xB1, 0x2A, 0x72,
  0x88, 0x35, 0xE4, 0x86, 0x6B, 0x55, 0x47, 0x08, 0x25, 0x16, 0xAB, 0x69, 0x1D, 0xBF, 0xF6, 0xFE,
};

static const uint8_t s_ypkg_q[0x80] PAYLOAD_RDATA = {
  0x23, 0x80, 0x77, 0x84, 0x4D, 0x6F, 0x9B, 0x24, 0x51, 0xFE, 0x2A, 0x6B, 0x28, 0x80, 0xA1, 0x9E,
  0xBD, 0x6D, 0x18, 0xCA, 0x8D, 0x7D, 0x9E, 0x79, 0x5A, 0xE0, 0xB8, 0xEB, 0xD1, 0x3D, 0xF3, 0xD9,
  0x02, 0x90, 0x2A, 0xA7, 0xB5, 0x7E, 0x9A, 0xA2, 0xD7, 0x2F, 0x21, 0xA8, 0x50, 0x7D, 0x8C, 0xA1,
  0x91, 0x2F, 0xBF, 0x97, 0xBE, 0x92, 0xC2, 0xC1, 0x0D, 0x8C, 0x0C, 0x1F, 0xDE, 0x31, 0x35, 0x15,
  0x39, 0x90, 0xCC, 0x97, 0x47, 0x2E, 0x7F, 0x09, 0xE9, 0xC3, 0x9C, 0xCE, 0x91, 0xB2, 0xC8, 0x58,
  0x76, 0xE8, 0x70, 0x1D, 0x72, 0x5F, 0x4A, 0xE6, 0xAA, 0x36, 0x22, 0x94, 0xC6, 0x52, 0x90, 0xB3,
  0x9F, 0x9B, 0xF0, 0xEF, 0x57, 0x8E, 0x53, 0xC3, 0xE3, 0x30, 0xC9, 0xD7, 0xB0, 0x3A, 0x0C, 0x79,
  0x1B, 0x97, 0xA8, 0xD4, 0x81, 0x22, 0xD2, 0xB0, 0x82, 0x62, 0x7D, 0x00, 0x58, 0x47, 0x9E, 0xC7,
};

static const uint8_t s_ypkg_dmp1[0x80] PAYLOAD_RDATA = {
  0x25, 0x54, 0xDB, 0xFD, 0x86, 0x45, 0x97, 0x9A, 0x1E, 0x17, 0xF0, 0xE3, 0xA5, 0x92, 0x0F, 0x12,
  0x2A, 0x5C, 0x4C, 0xA6, 0xA5, 0xCF, 0x7F, 0xE8, 0x5B, 0xF3, 0x65, 0x1A, 0xC8, 0xCF, 0x9B, 0xB9,
  0x2A, 0xC9, 0x90, 0x5D, 0xD4, 0x08, 0xCF, 0xF6, 0x03, 0x5A, 0x5A, 0xFC, 0x9E, 0xB6, 0xDB, 0x11,
  0xED, 0xE2, 0x3D, 0x62, 0xC1, 0xFC, 0x88, 0x5D, 0x97, 0xAC, 0x31, 0x2D, 0xC3, 0x15, 0xAD, 0x70,
  0x05, 0xBE, 0xA0, 0x5A, 0xE6, 0x34, 0x9C, 0x44, 0x78, 0x2B, 0xE5, 0xFE, 0x38, 0x56, 0xD4, 0x68,
  0x83, 0x13, 0xA4, 0xE6, 0xFA, 0xD2, 0x9C, 0xAB, 0xAC, 0x89, 0x5F, 0x10, 0x8F, 0x75, 0x6F, 0x04,
  0xBC, 0xAE, 0xB9, 0xBC, 0xB7, 0x1D, 0x42, 0xFA, 0x4E, 0x94, 0x1F, 0xB4, 0x0A, 0x27, 0x9C, 0x6B,
  0xAB, 0xC7, 0xD2, 0xEB, 0x27, 0x42, 0x52, 0x29, 0x41, 0xC8, 0x25, 0x40, 0x54, 0xE0, 0x48, 0x6D,
};

static const uint8_t s_ypkg_dmq1[0x80] PAYLOAD_RDATA = {
  0x4D, 0x35, 0x67, 0x38, 0xBC, 0x90, 0x3E, 0x3B, 0xAA, 0x6C, 0xBC, 0xF2, 0xEB, 0x9E, 0x45, 0xD2,
  0x09, 0x2F, 0xCA, 0x3A, 0x9C, 0x02, 0x36, 0xAD, 0x2E, 0xC1, 0xB1, 0xB2, 0x6D, 0x7C, 0x1F, 0x6B,
  0xA1, 0x8F, 0x62, 0x20, 0x8C, 0xD6, 0x6C, 0x36, 0xD6, 0x5A, 0x54, 0x9E, 0x30, 0xA9, 0xA8, 0x25,
  0x3D, 0x94, 0x12, 0x3E, 0x0D, 0x16, 0x1B, 0xF0, 0x86, 0x42, 0x72, 0xE0, 0xD6, 0x9C, 0x39, 0x68,
  0xDB, 0x11, 0x80, 0x96, 0x18, 0x2B, 0x71, 0x41, 0x48, 0x78, 0xE8, 0x17, 0x8B, 0x7D, 0x00, 0x1F,
  0x16, 0x68, 0xD2, 0x75, 0x97, 0xB5, 0xE0, 0xF2, 0x6D, 0x0C, 0x75, 0xAC, 0x16, 0xD9, 0xD5, 0xB1,
  0xB5, 0x8B, 0xE8, 0xD0, 0xBF, 0xA7, 0x1F, 0x61, 0x5B, 0x08, 0xF8, 0x68, 0xE7, 0xF0, 0xD1, 0xBC,
  0x39, 0x60, 0xBF, 0x55, 0x9C, 0x7C, 0x20, 0x30, 0xE8, 0x50, 0x28, 0x44, 0x02, 0xCE, 0x51, 0x2A,
};

static const uint8_t s_ypkg_iqmp[0x80] PAYLOAD_RDATA = {
  0xF5, 0x73, 0xB8, 0x7E, 0x5C, 0x98, 0x7C, 0x87, 0x67, 0xF1, 0xDA, 0xAE, 0xA0, 0xF9, 0x4B, 0xAB,
  0x77, 0xD8, 0xCE, 0x64, 0x6A, 0xC1, 0x4F, 0xA6, 0x9B, 0xB9, 0xAA, 0xCC, 0x76, 0x09, 0xA4, 0x3F,
  0xB9, 0xFA, 0xF5, 0x62, 0x84, 0x0A, 0xB8, 0x49, 0x02, 0xDF, 0x9E, 0xC4, 0x1A, 0x37, 0xD3, 0x56,
  0x0D, 0xA4, 0x6E, 0x15, 0x07, 0x15, 0xA0, 0x8D, 0x97, 0x9D, 0x92, 0x20, 0x43, 0x52, 0xC3, 0xB2,
  0xFD, 0xF7, 0xD3, 0xF3, 0x69, 0xA2, 0x28, 0x4F, 0x62, 0x6F, 0x80, 0x40, 0x5F, 0x3B, 0x80, 0x1E,
  0x5E, 0x38, 0x0D, 0x8B, 0x56, 0xA8, 0x56, 0x58, 0xD8, 0xD9, 0x6F, 0xEA, 0x12, 0x2A, 0x40, 0x16,
  0xC1, 0xED, 0x3D, 0x27, 0x16, 0xA0, 0x63, 0x97, 0x61, 0x39, 0x55, 0xCC, 0x8A, 0x05, 0xFA, 0x08,
  0x28, 0xFD, 0x55, 0x56, 0x31, 0x94, 0x65, 0x05, 0xE7, 0xD3, 0x57, 0x6C, 0x0D, 0x1C, 0x67, 0x0B,
};

static const uint8_t rif_debug_key[0x10] PAYLOAD_RDATA = {
  0x96, 0xC2, 0x26, 0x8D, 0x69, 0x26, 0x1C, 0x8B, 0x1E, 0x3B, 0x6B, 0xFF, 0x2F, 0xE0, 0x4E, 0x12
};

// we mark our key using some pattern that we can check later
static const uint8_t s_fake_key_seed[0x10] PAYLOAD_RDATA = {
  0x46, 0x41, 0x4B, 0x45, 0x46, 0x41, 0x4B, 0x45, 0x46, 0x41, 0x4B, 0x45, 0x46, 0x41, 0x4B, 0x45,
};

// clang-format on

// a common function to generate a final key for PFS
PAYLOAD_CODE static inline void pfs_gen_crypto_key(uint8_t *ekpfs, uint8_t seed[PFS_SEED_SIZE], unsigned int index, uint8_t key[PFS_FINAL_KEY_SIZE]) {
  struct thread *td = curthread();
  struct fake_key_d d;

  memset(&d, '\0', sizeof(d));
  {
    d.index = index;
    memcpy(d.seed, seed, PFS_SEED_SIZE);
  }

  fpu_kern_enter(td, FPU_CTX, 0);
  Sha256Hmac(key, (uint8_t *)&d, sizeof(d), ekpfs, EKPFS_SIZE);

  fpu_kern_leave(td, FPU_CTX);
}

// an encryption key generator based on EKPFS and PFS header seed
PAYLOAD_CODE static inline void pfs_generate_enc_key(uint8_t *ekpfs, uint8_t seed[PFS_SEED_SIZE], uint8_t key[PFS_FINAL_KEY_SIZE]) {
  pfs_gen_crypto_key(ekpfs, seed, 1, key);
}

// assigning key generator based on EKPFS and PFS header seed
PAYLOAD_CODE static inline void pfs_generate_sign_key(uint8_t *ekpfs, uint8_t seed[PFS_SEED_SIZE], uint8_t key[PFS_FINAL_KEY_SIZE]) {
  pfs_gen_crypto_key(ekpfs, seed, 2, key);
}

PAYLOAD_CODE static inline int npdrm_decrypt_debug_rif(unsigned int type, uint8_t *data) {
  (void)(type); // UNUSED(type);
  struct thread *td = curthread();
  int ret;

  fpu_kern_enter(td, FPU_CTX, 0);
  {
    // decrypt fake rif manually using a key from publishing tools
    ret = AesCbcCfb128Decrypt(data + RIF_DIGEST_SIZE, data + RIF_DIGEST_SIZE, RIF_DATA_SIZE, rif_debug_key, sizeof(rif_debug_key) * 8, data);
    if (ret) {
      ret = SCE_SBL_ERROR_NPDRM_ENOTSUP;
    }
  }
  fpu_kern_leave(td, FPU_CTX);

  return ret;
}

PAYLOAD_CODE static inline struct sbl_map_list_entry *sceSblDriverFindMappedPageListByGpuVa(vm_offset_t gpu_va) {
  struct sbl_map_list_entry *entry;
  if (!gpu_va) {
    return NULL;
  }

  entry = *SBL_DRIVER_MAPPED_PAGES;
  while (entry) {
    if (entry->gpu_va == gpu_va) {
      return entry;
    }
    entry = entry->next;
  }
  return NULL;
}

PAYLOAD_CODE static inline vm_offset_t sceSblDriverGpuVaToCpuVa(vm_offset_t gpu_va, size_t *num_page_groups) {
  struct sbl_map_list_entry *entry = sceSblDriverFindMappedPageListByGpuVa(gpu_va);
  if (!entry) {
    return 0;
  }

  if (num_page_groups) {
    *num_page_groups = entry->num_page_groups;
  }

  return entry->cpu_va;
}

PAYLOAD_CODE int my_sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg(struct sbl_msg *msg, size_t size) {
  union ccp_op *op;
  unsigned int cmd_mask;
  size_t key_len;
  size_t i;
  int ret;

  if (msg->hdr.cmd != SBL_MSG_CCP) {
    goto done;
  }

  op = &msg->service.ccp.op;
  if (CCP_OP(op->common.cmd) != CCP_OP_AES) {
    goto done;
  }

  cmd_mask = CCP_USE_KEY_FROM_SLOT | CCP_GENERATE_KEY_AT_SLOT;
  if ((op->aes.cmd & cmd_mask) != cmd_mask || (op->aes.key_index != PFS_FAKE_OBF_KEY_ID)) {
    goto done;
  }

  op->aes.cmd &= ~CCP_USE_KEY_FROM_SLOT;

  key_len = 16;

  // reverse key bytes
  for (i = 0; i < key_len; ++i) {
    op->aes.key[i] = s_fake_key_seed[key_len - i - 1];
  }

done:
  ret = sceSblDriverSendMsg_0(msg, size);

  return ret;
}

PAYLOAD_CODE int my_mountpfs__sceSblPfsSetKeys(uint32_t *ekh, uint32_t *skh, uint8_t *eekpfs, struct ekc *eekc, unsigned int pubkey_ver, unsigned int key_ver, struct pfs_header *hdr, size_t hdr_size, unsigned int type, unsigned int finalized, unsigned int is_disc) {
  struct thread *td;
  struct rsa_buffer in_data;
  struct rsa_buffer out_data;
  struct rsa_key key;
  uint8_t ekpfs[EKPFS_SIZE];
  uint8_t iv[16];
  union sbl_key_desc enc_key_desc;
  union sbl_key_desc sign_key_desc;
  int orig_ret, ret;

  ret = orig_ret = sceSblPfsSetKeys(ekh, skh, eekpfs, eekc, pubkey_ver, key_ver, hdr, hdr_size, type, finalized, is_disc);

  if (ret) {
    if (!finalized) {
      memset(&in_data, '\0', sizeof(in_data));
      in_data.ptr = eekpfs;
      in_data.size = EEKPFS_SIZE;

      memset(&out_data, '\0', sizeof(out_data));
      out_data.ptr = ekpfs;
      out_data.size = EKPFS_SIZE;

      memset(&key, '\0', sizeof(key));
      key.p = (uint8_t *)s_ypkg_p;
      key.q = (uint8_t *)s_ypkg_q;
      key.dmp1 = (uint8_t *)s_ypkg_dmp1;
      key.dmq1 = (uint8_t *)s_ypkg_dmq1;
      key.iqmp = (uint8_t *)s_ypkg_iqmp;

      td = curthread();

      fpu_kern_enter(td, FPU_CTX, 0);
      ret = RsaesPkcs1v15Dec2048CRT(&out_data, &in_data, &key);

      fpu_kern_leave(td, FPU_CTX);

      if (ret) {
        ret = orig_ret;
        goto err;
      }

      _sx_xlock(SBL_PFS_SX, 0, 0, 0);
      {
        memset(&enc_key_desc, '\0', sizeof(enc_key_desc));
        {
          enc_key_desc.pfs.obf_key_id = PFS_FAKE_OBF_KEY_ID;
          enc_key_desc.pfs.key_size = sizeof(enc_key_desc.pfs.escrowed_key);

          pfs_generate_enc_key(ekpfs, hdr->crypt_seed, enc_key_desc.pfs.escrowed_key);

          fpu_kern_enter(td, FPU_CTX, 0);
          {
            memset(iv, '\0', sizeof(iv));
            ret = AesCbcCfb128Encrypt(enc_key_desc.pfs.escrowed_key, enc_key_desc.pfs.escrowed_key, sizeof(enc_key_desc.pfs.escrowed_key), s_fake_key_seed, sizeof(s_fake_key_seed) * 8, iv);
          }
          fpu_kern_leave(td, FPU_CTX);
        }
        if (ret) {
          _sx_xunlock(SBL_PFS_SX);
          ret = orig_ret;
          goto err;
        }

        memset(&sign_key_desc, '\0', sizeof(sign_key_desc));
        {
          sign_key_desc.pfs.obf_key_id = PFS_FAKE_OBF_KEY_ID;
          sign_key_desc.pfs.key_size = sizeof(sign_key_desc.pfs.escrowed_key);

          pfs_generate_sign_key(ekpfs, hdr->crypt_seed, sign_key_desc.pfs.escrowed_key);

          fpu_kern_enter(td, FPU_CTX, 0);
          {
            memset(iv, '\0', sizeof(iv));
            ret = AesCbcCfb128Encrypt(sign_key_desc.pfs.escrowed_key, sign_key_desc.pfs.escrowed_key, sizeof(sign_key_desc.pfs.escrowed_key), s_fake_key_seed, sizeof(s_fake_key_seed) * 8, iv);
          }
          fpu_kern_leave(td, FPU_CTX);
        }
        if (ret) {
          _sx_xunlock(SBL_PFS_SX);
          ret = orig_ret;
          goto err;
        }

        ret = sceSblKeymgrSetKeyForPfs(&enc_key_desc, ekh);
        if (ret) {
          if (*ekh != -1) {
            sceSblKeymgrCleartKey(*ekh);
          }
          _sx_xunlock(SBL_PFS_SX);
          ret = orig_ret;
          goto err;
        }

        ret = sceSblKeymgrSetKeyForPfs(&sign_key_desc, skh);
        if (ret) {
          if (*skh != -1) {
            sceSblKeymgrCleartKey(*skh);
          }
          _sx_xunlock(SBL_PFS_SX);
          ret = orig_ret;
          goto err;
        }
      }
      _sx_xunlock(SBL_PFS_SX);

      ret = 0;
    }
  }
err:
  return ret;
}

PAYLOAD_CODE int my_sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif(union keymgr_payload *payload) {
  // it's SM request, thus we have the GPU address here, so we need to convert it to the CPU address
  union keymgr_request *request = (union keymgr_request *)sceSblDriverGpuVaToCpuVa(payload->data, NULL);
  int ret;

  // try to decrypt rif normally
  ret = sceSblKeymgrSmCallfunc(payload);

  // and if it fails then we check if it's fake rif and try to decrypt it by ourselves
  if ((ret != 0 || payload->status != 0) && request) {
    if (request->decrypt_rif.type == 0x200) { // fake?
      ret = npdrm_decrypt_debug_rif(request->decrypt_rif.type, request->decrypt_rif.data);
      payload->status = ret;
      ret = 0;
    }
  }
  return ret;
}

PAYLOAD_CODE int my_sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new(union keymgr_payload *payload) {
  uint64_t buf_gpu_va = payload->data;

  // it's SM request, thus we have the GPU address here, so we need to convert it to the CPU address
  union keymgr_request *request = (union keymgr_request *)sceSblDriverGpuVaToCpuVa(buf_gpu_va, NULL);
  union keymgr_response *response = (union keymgr_response *)request;
  int orig_ret, ret;

  // try to decrypt rif normally
  ret = orig_ret = sceSblKeymgrSmCallfunc(payload);

  // and if it fails then we check if it's fake rif and try to decrypt it by ourselves
  if ((ret != 0 || payload->status != 0) && request) {
    if (request->decrypt_entire_rif.rif.format != 2) { // not fake?
      ret = orig_ret;
      goto err;
    }

    ret = npdrm_decrypt_debug_rif(request->decrypt_entire_rif.rif.format, request->decrypt_entire_rif.rif.digest);

    if (ret) {
      ret = orig_ret;
      goto err;
    }

    // XXX: Sorry, I'm lazy to refactor this crappy code :D basically, we're copying decrypted data to proper place,
    // consult with kernel code if offsets needs to be changed
    memcpy(response->decrypt_entire_rif.raw, request->decrypt_entire_rif.rif.digest, sizeof(request->decrypt_entire_rif.rif.digest) + sizeof(request->decrypt_entire_rif.rif.data));
    memset(response->decrypt_entire_rif.raw + sizeof(request->decrypt_entire_rif.rif.digest) + sizeof(request->decrypt_entire_rif.rif.data), '\0', sizeof(response->decrypt_entire_rif.raw) - (sizeof(request->decrypt_entire_rif.rif.digest) + sizeof(request->decrypt_entire_rif.rif.data)));

    payload->status = ret;
    ret = 0;
  }

err:
  return ret;
}

PAYLOAD_CODE static inline struct sbl_key_rbtree_entry *sceSblKeymgrGetKey(unsigned int handle) {
  struct sbl_key_rbtree_entry *entry = *SBL_KEYMGR_KEY_RBTREE;

  while (entry) {
    if (entry->handle < handle) {
      entry = entry->right;
    } else if (entry->handle > handle) {
      entry = entry->left;
    } else if (entry->handle == handle) {
      return entry;
    }
  }

  return NULL;
}

PAYLOAD_CODE static int my_sceSblKeymgrInvalidateKey__sx_xlock(struct sx *sx, int opts, const char *file, int line) {
  struct sbl_key_rbtree_entry *key_desc;
  struct sbl_key_slot_desc *key_slot_desc;
  unsigned key_handle;
  int ret, ret2;

  ret = _sx_xlock(sx, opts, file, line);

  if (TAILQ_EMPTY(SBL_KEYMGR_KEY_SLOTS)) {
    goto done;
  }

  TAILQ_FOREACH(key_slot_desc, SBL_KEYMGR_KEY_SLOTS, list) {
    key_handle = key_slot_desc->key_handle;
    if (key_handle == (unsigned int)-1) {
      // unbounded
      continue;
    }
    key_desc = sceSblKeymgrGetKey(key_handle);
    if (!key_desc) {
      // shouldn't happen in normal situations
      continue;
    }
    if (!key_desc->occupied) {
      continue;
    }
    if (key_desc->desc.pfs.obf_key_id != PFS_FAKE_OBF_KEY_ID) {
      // not our key, just skip, so it will be handled by original code
      continue;
    }
    if (key_desc->desc.pfs.key_size != sizeof(key_desc->desc.pfs.escrowed_key)) {
      // something weird with key params, just ignore and app will just crash...
      continue;
    }
    memcpy(SBL_KEYMGR_BUF_VA, key_desc->desc.pfs.escrowed_key, key_desc->desc.pfs.key_size);
    ret2 = sceSblKeymgrSetKeyStorage(*SBL_KEYMGR_BUF_GVA, key_desc->desc.pfs.key_size, key_desc->desc.pfs.obf_key_id, key_slot_desc->key_id);
    if (ret2) {
      // wtf?
      continue;
    }
  }

done:
  // XXX: no need to call SX unlock because we'll jump to original code which expects SX is already locked
  return ret;
}

PAYLOAD_CODE void install_fpkg_hooks() {
  uint64_t flags, cr0;
  uint64_t kernbase = getkernbase(fw_offsets->XFAST_SYSCALL_addr);

  cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);
  flags = intr_disable();

  KCALL_REL32(kernbase, fw_offsets->sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook, (uint64_t)my_sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif);
  KCALL_REL32(kernbase, fw_offsets->sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook, (uint64_t)my_sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new);
  KCALL_REL32(kernbase, fw_offsets->sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook, (uint64_t)my_sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg);
  KCALL_REL32(kernbase, fw_offsets->sceSblKeymgrInvalidateKey__sx_xlock_hook, (uint64_t)my_sceSblKeymgrInvalidateKey__sx_xlock);
  KCALL_REL32(kernbase, fw_offsets->mountpfs__sceSblPfsSetKeys_hook1, (uint64_t)my_mountpfs__sceSblPfsSetKeys);
  KCALL_REL32(kernbase, fw_offsets->mountpfs__sceSblPfsSetKeys_hook2, (uint64_t)my_mountpfs__sceSblPfsSetKeys);

  intr_restore(flags);
  writeCr0(cr0);
}
