#ifndef __RISCV64_REG_H__
#define __RISCV64_REG_H__

#include "common.h"
#include "memory.h"

#define PC_START (0x80000000u + IMAGE_START)

typedef struct {

  struct { // difftest regs 
    // the regs in this struct must keep their order becasue difftest use memcpy
    union {
      rtlreg_t _64;
      uint32_t _32[2];
      uint16_t _16[4];
      uint8_t _8[8];
    } gpr[32];

    union {
      rtlreg_t _64;
      uint32_t _32[2];
      uint16_t _16[4];
      uint8_t _8[8];
    } fpr[32];

    vaddr_t pc;

    vaddr_t mstatus, mcause, mepc;
    vaddr_t sstatus, scause, sepc;
  };

  uint8_t mode;

  bool fetching;
  bool amo;

  // for LR/SC
  vaddr_t lr_addr;

  bool INTR;
} CPU_state;

static inline int check_reg_index(int index) {
  assert(index >= 0 && index < 32);
  return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._64)

static inline const char* reg_name(int index, int width) {
  extern const char* regsl[];
  assert(index >= 0 && index < 32);
  return regsl[index];
}

#define fpreg_l(index) (cpu.fpr[check_reg_index(index)]._64)

static inline const char* fpreg_name(int index, int width) {
  extern const char* fpregsl[];
  assert(index >= 0 && index < 32);
  return fpregsl[index];
}

#endif