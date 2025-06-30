#ifndef RIF_HELPER_H_
#define RIF_HELPER_H_

#include <stdint.h>

#include "pfs_helper.h"
#include "sparse.h"

#define RIF_DIGEST_SIZE 0x10
#define RIF_DATA_SIZE 0x90
#define RIF_KEY_TABLE_SIZE 0x230
#define RIF_MAX_KEY_SIZE 0x20
#define RIF_PAYLOAD_SIZE (RIF_DIGEST_SIZE + RIF_DATA_SIZE)
#define SIZEOF_ACTDAT 0x200
#define SIZEOF_RSA_KEY 0x48
#define SIZEOF_RIF 0x400

struct rif_key_blob {
  struct ekc eekc;
  uint8_t entitlement_key[0x10];
};

union keymgr_response {
  struct {
    uint32_t type;
    uint8_t key[RIF_MAX_KEY_SIZE];
    uint8_t data[RIF_DIGEST_SIZE + RIF_DATA_SIZE];
  } decrypt_rif;
  struct {
    uint8_t raw[SIZEOF_RIF];
  } decrypt_entire_rif;
};

union keymgr_payload {
  struct {
    uint32_t cmd;
    uint32_t status;
    uint64_t data;
  };
  uint8_t buf[0x80];
};

TYPE_BEGIN(struct rsa_key, SIZEOF_RSA_KEY);
TYPE_FIELD(uint8_t *p, 0x20);
TYPE_FIELD(uint8_t *q, 0x28);
TYPE_FIELD(uint8_t *dmp1, 0x30);
TYPE_FIELD(uint8_t *dmq1, 0x38);
TYPE_FIELD(uint8_t *iqmp, 0x40);
TYPE_END();

TYPE_BEGIN(struct actdat, SIZEOF_ACTDAT);
TYPE_FIELD(uint32_t magic, 0x00);
TYPE_FIELD(uint16_t version_major, 0x04);
TYPE_FIELD(uint16_t version_minor, 0x06);
TYPE_FIELD(uint64_t account_id, 0x08);
TYPE_FIELD(uint64_t start_time, 0x10);
TYPE_FIELD(uint64_t end_time, 0x18);
TYPE_FIELD(uint64_t flags, 0x20);
TYPE_FIELD(uint32_t unk3, 0x28);
TYPE_FIELD(uint32_t unk4, 0x2C);
TYPE_FIELD(uint8_t open_psid_hash[0x20], 0x60);
TYPE_FIELD(uint8_t static_per_console_data_1[0x20], 0x80);
TYPE_FIELD(uint8_t digest[0x10], 0xA0);
TYPE_FIELD(uint8_t key_table[0x20], 0xB0);
TYPE_FIELD(uint8_t static_per_console_data_2[0x10], 0xD0);
TYPE_FIELD(uint8_t static_per_console_data_3[0x20], 0xE0);
TYPE_FIELD(uint8_t signature[0x100], 0x100);
TYPE_END();

TYPE_BEGIN(struct rif, SIZEOF_RIF);
TYPE_FIELD(uint32_t magic, 0x00);
TYPE_FIELD(uint16_t version_major, 0x04);
TYPE_FIELD(uint16_t version_minor, 0x06);
TYPE_FIELD(uint64_t account_id, 0x08);
TYPE_FIELD(uint64_t start_time, 0x10);
TYPE_FIELD(uint64_t end_time, 0x18);
TYPE_FIELD(char content_id[0x30], 0x20);
TYPE_FIELD(uint16_t format, 0x50);
TYPE_FIELD(uint16_t drm_type, 0x52);
TYPE_FIELD(uint16_t content_type, 0x54);
TYPE_FIELD(uint16_t sku_flag, 0x56);
TYPE_FIELD(uint64_t content_flags, 0x58);
TYPE_FIELD(uint32_t iro_tag, 0x60);
TYPE_FIELD(uint32_t ekc_version, 0x64);
TYPE_FIELD(uint16_t unk3, 0x6A);
TYPE_FIELD(uint16_t unk4, 0x6C);
TYPE_FIELD(uint8_t digest[0x10], 0x260);
TYPE_FIELD(uint8_t data[RIF_DATA_SIZE], 0x270);
TYPE_FIELD(uint8_t signature[0x100], 0x300);
TYPE_END();

union keymgr_request {
  struct {
    uint32_t type;
    uint8_t key[RIF_MAX_KEY_SIZE];
    uint8_t data[RIF_DIGEST_SIZE + RIF_DATA_SIZE];
  } decrypt_rif;
  struct {
    struct rif rif;
    uint8_t key_table[RIF_KEY_TABLE_SIZE];
    uint64_t timestamp;
    int status;
  } decrypt_entire_rif;
};

#endif
