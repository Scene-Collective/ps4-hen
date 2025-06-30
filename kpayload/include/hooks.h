#ifndef HOOKS_H_
#define HOOKS_H_

// golden
// 6/12/2018

#include <elf.h>
#include <stdint.h>

#include "freebsd_helper.h"
// TODO: Where is `ucred` defined?

TYPE_BEGIN(struct thread, 0x800); // XXX: random, don't use directly without fixing it
TYPE_FIELD(struct mtx *volatile td_lock, 0);
TYPE_FIELD(struct proc *td_proc, 8);
TYPE_FIELD(TAILQ_ENTRY(thread) td_plist, 0x10);
TYPE_FIELD(int tid, 0x88);
TYPE_FIELD(int td_pinned, 0x12C);
TYPE_FIELD(struct ucred *td_ucred, 0x130);
TYPE_FIELD(char td_name[32], 0x284);
TYPE_FIELD(uint64_t td_retval[2], 0x398);
TYPE_FIELD(uint16_t td_priority, 0x380);
TYPE_END();

TYPE_BEGIN(struct sysent, 0x30);
TYPE_FIELD(uint32_t sy_narg, 0x00);
TYPE_FIELD(void *sy_call, 0x08);
TYPE_FIELD(uint16_t sy_auevent, 0x10);
TYPE_FIELD(uint64_t sy_systrace_args_func, 0x18);
TYPE_FIELD(uint32_t sy_entry, 0x20);
TYPE_FIELD(uint32_t sy_return, 0x24);
TYPE_FIELD(uint32_t sy_flags, 0x28);
TYPE_FIELD(uint32_t sy_thrcnt, 0x2C);
TYPE_END();

// custom syscall 107
struct proc_list_entry {
  char p_comm[32];
  int pid;
} __attribute__((packed));

struct sys_proc_list_args {
  struct proc_list_entry *procs;
  uint64_t *num;
} __attribute__((packed));
int sys_proc_list(struct thread *td, struct sys_proc_list_args *uap);

// custom syscall 108
struct sys_proc_rw_args {
  uint64_t pid;
  uint64_t address;
  void *data;
  uint64_t length;
  uint64_t write;
} __attribute__((packed));
int sys_proc_rw(struct thread *td, struct sys_proc_rw_args *uap);

// custom syscall 109
#define SYS_PROC_ALLOC 1
#define SYS_PROC_FREE 2
#define SYS_PROC_PROTECT 3
#define SYS_PROC_VM_MAP 4
#define SYS_PROC_INSTALL 5
#define SYS_PROC_CALL 6
#define SYS_PROC_ELF 7
#define SYS_PROC_INFO 8
#define SYS_PROC_THRINFO 9
struct sys_proc_alloc_args {
  uint64_t address;
  uint64_t length;
} __attribute__((packed));
struct sys_proc_free_args {
  uint64_t address;
  uint64_t length;
} __attribute__((packed));
struct sys_proc_protect_args {
  uint64_t address;
  uint64_t length;
  uint64_t prot;
} __attribute__((packed));
struct sys_proc_vm_map_args {
  struct proc_vm_map_entry *maps;
  uint64_t num;
} __attribute__((packed));
struct sys_proc_install_args {
  uint64_t stubentryaddr;
} __attribute__((packed));
struct sys_proc_call_args {
  uint32_t pid;
  uint64_t rpcstub;
  uint64_t rax;
  uint64_t rip;
  uint64_t rdi;
  uint64_t rsi;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t r8;
  uint64_t r9;
} __attribute__((packed));
struct sys_proc_elf_args {
  void *elf;
} __attribute__((packed));
struct sys_proc_info_args {
  int pid;
  char name[40];
  char path[64];
  char titleid[16];
  char contentid[64];
} __attribute__((packed));
struct sys_proc_thrinfo_args {
  uint32_t lwpid;
  uint32_t priority;
  char name[32];
} __attribute__((packed));
struct sys_proc_cmd_args {
  uint64_t pid;
  uint64_t cmd;
  void *data;
} __attribute__((packed));
int sys_proc_cmd(struct thread *td, struct sys_proc_cmd_args *uap);

// custom syscall 110
struct sys_kern_base_args {
  uint64_t *kbase;
} __attribute__((packed));
int sys_kern_base(struct thread *td, struct sys_kern_base_args *uap);

// custom syscall 111
struct sys_kern_rw_args {
  uint64_t address;
  void *data;
  uint64_t length;
  uint64_t write;
} __attribute__((packed));
int sys_kern_rw(struct thread *td, struct sys_kern_rw_args *uap);

// custom syscall 112
#define SYS_CONSOLE_CMD_REBOOT 1
#define SYS_CONSOLE_CMD_PRINT 2
#define SYS_CONSOLE_CMD_JAILBREAK 3
struct sys_console_cmd_args {
  uint64_t cmd;
  void *data;
} __attribute__((packed));
int sys_console_cmd(struct thread *td, struct sys_console_cmd_args *uap);

// void hook_trap_fatal(struct trapframe *tf);
void install_syscall(uint32_t n, void *func);
int install_hooks();

struct dynlib_load_prx_args {
  const char *prx_path;
  int flags;
  int *handle_out;
  uint64_t unk;
};

struct dynlib_dlsym_args {
  int module;
  const char *symbol;
  uintptr_t *symbol_ptr;
};

#endif
