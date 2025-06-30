#ifndef PFS_HELPER_H_
#define PFS_HELPER_H_

#include <stdint.h>

#include "sparse.h"

#define EKPFS_SIZE 0x20
#define EEKPFS_SIZE 0x100
#define PFS_SEED_SIZE 0x10
#define PFS_FINAL_KEY_SIZE 0x20
#define SIZEOF_PFS_KEY_BLOB 0x140
#define CONTENT_KEY_SEED_SIZE 0x10
#define SELF_KEY_SEED_SIZE 0x10
#define EEKC_SIZE 0x20
#define MAX_FAKE_KEYS 32
#define SIZEOF_RSA_KEY 0x48
#define PFS_FAKE_OBF_KEY_ID 0x1337
#define SIZEOF_PFS_HEADER 0x5A0

struct fake_key_desc {
  uint8_t key[0x20];
  int occupied;
};

struct fake_key_d {
  uint32_t index;
  uint8_t seed[PFS_SEED_SIZE];
};

struct ekc {
  uint8_t content_key_seed[CONTENT_KEY_SEED_SIZE];
  uint8_t self_key_seed[SELF_KEY_SEED_SIZE];
};

union pfs_key_blob {
  struct {
    uint8_t eekpfs[EEKPFS_SIZE];
    struct ekc eekc;
    uint32_t pubkey_ver; // 0x1/0x80000001/0xC0000001
    uint32_t key_ver;    // 1 (if (rif_ver_major & 0x1) != 0, then pfs_key_ver=1, otherwise pfs_key_ver=0)
    uint64_t header_gva;
    uint32_t header_size;
    uint32_t type;
    uint32_t finalized;
    uint32_t is_disc;
  } in;
  struct {
    uint8_t escrowed_keys[0x40];
  } out;
};

typedef union pfs_key_blob pfs_key_blob_t;
TYPE_CHECK_SIZE(pfs_key_blob_t, SIZEOF_PFS_KEY_BLOB);

struct rsa_buffer {
  uint8_t *ptr;
  size_t size;
};

TYPE_BEGIN(struct pfs_header, SIZEOF_PFS_HEADER);
TYPE_FIELD(uint8_t crypt_seed[0x10], 0x370);
TYPE_END();

#endif
