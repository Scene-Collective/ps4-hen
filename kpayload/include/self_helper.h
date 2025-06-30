#ifndef SELF_HELPER_H_
#define SELF_HELPER_H_

#include <stdint.h>

#include "freebsd_helper.h"

#define SELF_DIGEST_SIZE 0x20
#define SELF_CONTENT_ID_SIZE 0x13
#define SELF_RANDOM_PAD_SIZE 0x0D
#define SELF_MAX_HEADER_SIZE 0x4000

enum self_format { SELF_FORMAT_NONE, SELF_FORMAT_ELF, SELF_FORMAT_SELF };

#define SIZEOF_SELF_CONTEXT 0x60 // sceSblAuthMgrAuthHeader:bzero(sbl_authmgr_context, 0x60)

TYPE_BEGIN(struct self_context, SIZEOF_SELF_CONTEXT);
TYPE_FIELD(enum self_format format, 0x00);
TYPE_FIELD(int elf_auth_type, 0x04); // auth id is based on that
TYPE_FIELD(unsigned int total_header_size, 0x08);
TYPE_FIELD(int ctx_id, 0x1C);
TYPE_FIELD(uint64_t svc_id, 0x20);
TYPE_FIELD(int buf_id, 0x30);
TYPE_FIELD(uint8_t *header, 0x38);
TYPE_FIELD(struct mtx lock, 0x40);
TYPE_END();

#define SIZEOF_SELF_HEADER 0x20

TYPE_BEGIN(struct self_header, SIZEOF_SELF_HEADER);
TYPE_FIELD(uint32_t magic, 0x00);
#define SELF_MAGIC 0x1D3D154F
#define ELF_MAGIC 0x464C457F
TYPE_FIELD(uint8_t version, 0x04);
TYPE_FIELD(uint8_t mode, 0x05);
TYPE_FIELD(uint8_t endian, 0x06);
TYPE_FIELD(uint8_t attr, 0x07);
TYPE_FIELD(uint32_t key_type, 0x08);
TYPE_FIELD(uint16_t header_size, 0x0C);
TYPE_FIELD(uint16_t meta_size, 0x0E);
TYPE_FIELD(uint64_t file_size, 0x10);
TYPE_FIELD(uint16_t num_entries, 0x18);
TYPE_FIELD(uint16_t flags, 0x1A);
TYPE_END();

#define SIZEOF_SELF_ENTRY 0x20

TYPE_BEGIN(struct self_entry, SIZEOF_SELF_ENTRY);
TYPE_FIELD(uint64_t props, 0x00);
TYPE_FIELD(uint64_t offset, 0x08);
TYPE_FIELD(uint64_t file_size, 0x10);
TYPE_FIELD(uint64_t memory_size, 0x18);
TYPE_END();

#define SIZEOF_SELF_EX_INFO 0x40

TYPE_BEGIN(struct self_ex_info, SIZEOF_SELF_EX_INFO);
TYPE_FIELD(uint64_t paid, 0x00);
TYPE_FIELD(uint64_t ptype, 0x08);
#define SELF_PTYPE_FAKE 0x1
TYPE_FIELD(uint64_t app_version, 0x10);
TYPE_FIELD(uint64_t fw_version, 0x18);
TYPE_FIELD(uint8_t digest[SELF_DIGEST_SIZE], 0x20);
TYPE_END();

#define SIZEOF_SELF_AUTH_INFO 0x88 // sceSblAuthMgrIsLoadable2:bzero(auth_info, 0x88)

TYPE_BEGIN(struct self_auth_info, SIZEOF_SELF_AUTH_INFO);
TYPE_FIELD(uint64_t paid, 0x00);
TYPE_FIELD(uint64_t caps[4], 0x08);
TYPE_FIELD(uint64_t attrs[4], 0x28);
TYPE_FIELD(uint8_t unk[0x40], 0x48);
TYPE_END();

#define SIZEOF_SELF_FAKE_AUTH_INFO (sizeof(uint64_t) + SIZEOF_SELF_AUTH_INFO)

TYPE_BEGIN(struct self_fake_auth_info, SIZEOF_SELF_FAKE_AUTH_INFO);
TYPE_FIELD(uint64_t size, 0x00);
TYPE_FIELD(struct self_auth_info info, 0x08);
TYPE_END();

#endif
