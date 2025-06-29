#ifndef SECTIONS_H_
#define SECTIONS_H_

#define PAYLOAD_DUMMY __attribute((section(".payload_dummy")))
#define PAYLOAD_HEADER __attribute__((section(".payload_header")))
#define PAYLOAD_CODE __attribute__((section(".payload_code")))
#define PAYLOAD_DATA __attribute__((section(".payload_data")))
#define PAYLOAD_RDATA __attribute__((section(".payload_rdata")))
#define PAYLOAD_BSS __attribute__((section(".payload_bss")))

#endif
