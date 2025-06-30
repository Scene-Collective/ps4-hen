#ifndef CCP_HELPER_H_
#define CCP_HELPER_H_

#include <stdint.h>

#include "freebsd_helper.h"

#define CCP_MAX_PAYLOAD_SIZE 0x88
#define CCP_OP(cmd) (cmd >> 24)
#define CCP_OP_AES 0
#define CCP_OP_XTS 2
#define CCP_OP_HMAC 9
#define CCP_USE_KEY_FROM_SLOT (1 << 18)
#define CCP_GENERATE_KEY_AT_SLOT (1 << 19)
#define CCP_USE_KEY_HANDLE (1 << 20)

struct ccp_link {
  void *p;
};

union ccp_op {
  struct {
    uint32_t cmd;
    uint32_t status;
  } common;
  struct {
    uint32_t cmd;
    uint32_t status;
    uint64_t data_size;
    uint64_t in_data;
    uint64_t out_data;
    union {
      uint32_t key_index;
      uint8_t key[0x20];
    };
    uint8_t iv[0x10];
  } aes;
  uint8_t buf[CCP_MAX_PAYLOAD_SIZE];
};

struct ccp_msg {
  union ccp_op op;
  uint32_t index;
  uint32_t result;
  TAILQ_ENTRY(ccp_msg) next;
  uint64_t message_id;
  LIST_ENTRY(ccp_link) links;
};

struct ccp_req {
  TAILQ_HEAD(, ccp_msg) msgs;
  void (*cb)(void *arg, int result);
  void *arg;
  uint64_t message_id;
  LIST_ENTRY(ccp_link) links;
};

union sbl_msg_service {
  struct {
    union ccp_op op;
  } ccp;
};

struct sbl_msg_hdr {
  uint32_t cmd;
  uint32_t status;
  uint64_t message_id;
  uint64_t extended_msgs;
};

struct sbl_msg {
  struct sbl_msg_hdr hdr;
  union {
    union sbl_msg_service service;
    uint8_t raw[0x1000];
  };
};

#endif
