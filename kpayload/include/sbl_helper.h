#ifndef SBL_HELPER_H_
#define SBL_HELPER_H_

#include <stdint.h>

#include "freebsd_helper.h"

#define SCE_SBL_ERROR_NPDRM_ENOTSUP 0x800F0A25
#define SIZEOF_SBL_KEY_RBTREE_ENTRY 0xA8 // sceSblKeymgrSetKey
#define SIZEOF_SBL_MAP_LIST_ENTRY 0x50 // sceSblDriverMapPages
#define SIZEOF_SBL_KEY_DESC 0x7C // sceSblKeymgrSetKey
#define SIZEOF_SBL_KEY_SLOT_DESC 0x20
#define SBL_MSG_SERVICE_MAILBOX_MAX_SIZE 0x80
#define SBL_MSG_CCP 0x8

struct sbl_mapped_page_group;

union sbl_key_desc {
  struct {
    uint16_t obf_key_id;
    uint16_t key_size;
    uint8_t escrowed_key[0x20];
  } pfs;
  struct {
    uint16_t cmd;
    uint16_t pad;
    uint16_t key_id;
  } portability;
  uint8_t raw[SIZEOF_SBL_KEY_DESC];
};
TYPE_CHECK_SIZE(union sbl_key_desc, SIZEOF_SBL_KEY_DESC);

TYPE_BEGIN(struct sbl_key_slot_desc, SIZEOF_SBL_KEY_SLOT_DESC);
TYPE_FIELD(uint32_t key_id, 0x00);
TYPE_FIELD(uint32_t unk_0x04, 0x04);
TYPE_FIELD(uint32_t key_handle, 0x08); // or -1 if it's freed
TYPE_FIELD(uint32_t unk_0x0C, 0x0C);
TYPE_FIELD(TAILQ_ENTRY(sbl_key_slot_desc) list, 0x10);
TYPE_END();

TAILQ_HEAD(sbl_key_slot_queue, sbl_key_slot_desc);

TYPE_BEGIN(struct sbl_key_rbtree_entry, SIZEOF_SBL_KEY_RBTREE_ENTRY);
TYPE_FIELD(uint32_t handle, 0x00);
TYPE_FIELD(uint32_t occupied, 0x04);
TYPE_FIELD(union sbl_key_desc desc, 0x08);
TYPE_FIELD(uint32_t locked, 0x80);
TYPE_FIELD(struct sbl_key_rbtree_entry *left, 0x88);
TYPE_FIELD(struct sbl_key_rbtree_entry *right, 0x90);
TYPE_FIELD(struct sbl_key_rbtree_entry *parent, 0x98);
TYPE_FIELD(uint32_t set, 0xA0);
TYPE_END();

TYPE_BEGIN(struct sbl_map_list_entry, SIZEOF_SBL_MAP_LIST_ENTRY);
TYPE_FIELD(struct sbl_map_list_entry *next, 0x00);
TYPE_FIELD(struct sbl_map_list_entry *prev, 0x08);
TYPE_FIELD(unsigned long cpu_va, 0x10);
TYPE_FIELD(unsigned int num_page_groups, 0x18);
TYPE_FIELD(unsigned long gpu_va, 0x20);
TYPE_FIELD(struct sbl_mapped_page_group *page_groups, 0x28);
TYPE_FIELD(unsigned int num_pages, 0x30);
TYPE_FIELD(unsigned long flags, 0x38);
TYPE_FIELD(struct proc *proc, 0x40);
TYPE_FIELD(void *vm_page, 0x48);
TYPE_END();

#endif
