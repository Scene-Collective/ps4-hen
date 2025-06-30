#ifndef AMD_HELPER_H_
#define AMD_HELPER_H_

#include <stdint.h>

#include "sections.h"

PAYLOAD_CODE static inline __attribute__((always_inline)) uint64_t __readmsr(unsigned long __register) {
  unsigned long __edx;
  unsigned long __eax;
  __asm__("rdmsr" : "=d"(__edx), "=a"(__eax) : "c"(__register));
  return (((uint64_t)__edx) << 32) | (uint64_t)__eax;
}

#define X86_CR0_WP (1 << 16)

PAYLOAD_CODE static inline __attribute__((always_inline)) uint64_t readCr0(void) {
  uint64_t cr0;
  __asm__ volatile("movq %0, %%cr0" : "=r"(cr0) : : "memory");
  return cr0;
}

PAYLOAD_CODE static inline __attribute__((always_inline)) void writeCr0(uint64_t cr0) {
  __asm__ volatile("movq %%cr0, %0" : : "r"(cr0) : "memory");
}

PAYLOAD_CODE static inline __attribute__((always_inline)) void disable_interrupts(void) {
  __asm__ volatile("cli");
}

PAYLOAD_CODE static inline __attribute__((always_inline)) void enable_interrupts(void) {
  __asm__ volatile("sti");
}

PAYLOAD_CODE static inline __attribute__((always_inline)) uint64_t read_flags(void) {
  uint64_t flags;
  __asm__ volatile("pushf; pop %0;" : "=r"(flags));
  return flags;
}

PAYLOAD_CODE static inline __attribute__((always_inline)) uint64_t intr_disable(void) {
  uint64_t flags = read_flags();
  disable_interrupts();
  return flags;
}

PAYLOAD_CODE static inline __attribute__((always_inline)) void intr_restore(uint64_t flags) {
  __asm__ volatile("push %0; popf;" : : "rm"(flags) : "memory");
}

PAYLOAD_CODE static inline __attribute__((always_inline)) uint64_t getkernbase(uint64_t xfast_syscall_offset) {
  return (__readmsr(0xC0000082) - xfast_syscall_offset);
}

#endif
