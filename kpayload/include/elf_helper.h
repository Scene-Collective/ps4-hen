#ifndef ELF_HELPER_H_
#define ELF_HELPER_H_

#include <stdint.h>

#define ELF_IDENT_SIZE 0x10
#define ELF_EHDR_EXT_SIZE 0x1000

#define ELF_IDENT_MAG0 0
#define ELF_IDENT_MAG1 1
#define ELF_IDENT_MAG2 2
#define ELF_IDENT_MAG3 3
#define ELF_IDENT_CLASS 4
#define ELF_IDENT_DATA 5

#define ELF_CLASS_64 2
#define ELF_DATA_LSB 1

#define ELF_TYPE_NONE 0
#define ELF_TYPE_EXEC 2

#define ELF_MACHINE_X86_64 0x3E

#define ELF_PHDR_TYPE_NULL 0x0
#define ELF_PHDR_TYPE_LOAD 0x1
#define ELF_PHDR_TYPE_SCE_DYNLIBDATA 0x61000000
#define ELF_PHDR_TYPE_SCE_RELRO 0x61000010
#define ELF_PHDR_TYPE_SCE_COMMENT 0x6FFFFF00
#define ELF_PHDR_TYPE_SCE_VERSION 0x6FFFFF01

#define ELF_PHDR_FLAG_X 0x1
#define ELF_PHDR_FLAG_W 0x2
#define ELF_PHDR_FLAG_R 0x4

#define ELF_ET_EXEC 0x2
#define ELF_ET_SCE_EXEC 0xFE00
#define ELF_ET_SCE_EXEC_ASLR 0xFE10
#define ELF_ET_SCE_DYNAMIC 0xFE18

typedef uint16_t elf64_half_t;
typedef uint32_t elf64_word_t;
typedef uint64_t elf64_xword_t;
typedef uint64_t elf64_off_t;
typedef uint64_t elf64_addr_t;

struct elf64_ehdr {
  uint8_t ident[ELF_IDENT_SIZE];
  elf64_half_t type;
  elf64_half_t machine;
  elf64_word_t version;
  elf64_addr_t entry;
  elf64_off_t phoff;
  elf64_off_t shoff;
  elf64_word_t flags;
  elf64_half_t ehsize;
  elf64_half_t phentsize;
  elf64_half_t phnum;
  elf64_half_t shentsize;
  elf64_half_t shnum;
  elf64_half_t shstrndx;
};

struct elf64_phdr {
  elf64_word_t type;
  elf64_word_t flags;
  elf64_off_t offset;
  elf64_addr_t vaddr;
  elf64_addr_t paddr;
  elf64_xword_t filesz;
  elf64_xword_t memsz;
  elf64_xword_t align;
};

struct elf64_shdr {
  elf64_word_t name;
  elf64_word_t type;
  elf64_xword_t flags;
  elf64_addr_t addr;
  elf64_off_t offset;
  elf64_xword_t size;
  elf64_word_t link;
  elf64_word_t info;
  elf64_xword_t addralign;
  elf64_xword_t entsize;
};

#endif
