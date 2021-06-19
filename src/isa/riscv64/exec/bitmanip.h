#include "rvintrin.h"

#define IS_BWORD ((s->isa.instr.bi.opcode6_2 >> 1) & 0x1)

#define BUILD_EXEC_B1(x) \
  static inline make_EHelper(x) { \
    *ddest = concat(_rv_, x)(*dsrc1); \
    print_asm_template2(x); \
  }

BUILD_EXEC_B1(clz)
BUILD_EXEC_B1(ctz)
BUILD_EXEC_B1(cpop)
BUILD_EXEC_B1(sextb)
BUILD_EXEC_B1(sexth)
BUILD_EXEC_B1(zexth)

#define BUILD_EXEC_B1W(x) \
  static inline make_EHelper(x ## w) { \
    *ddest = concat(_rv32_, x)(*dsrc1); \
    print_asm_template2(x ## w); \
  }

BUILD_EXEC_B1W(clz)
BUILD_EXEC_B1W(ctz)
BUILD_EXEC_B1W(cpop)


#define BUILD_EXEC_B2(x) \
  static inline make_EHelper(x) { \
    *ddest = concat(_rv_, x)(*dsrc1, *dsrc2); \
    print_asm_template3(x); \
  }

BUILD_EXEC_B2(andn)
BUILD_EXEC_B2(orn)
BUILD_EXEC_B2(xnor)
BUILD_EXEC_B2(rol)
BUILD_EXEC_B2(ror)
BUILD_EXEC_B2(bclr)
BUILD_EXEC_B2(bset)
BUILD_EXEC_B2(binv)
BUILD_EXEC_B2(bext)
BUILD_EXEC_B2(clmul)
BUILD_EXEC_B2(clmulr)
BUILD_EXEC_B2(clmulh)
BUILD_EXEC_B2(min)
BUILD_EXEC_B2(max)
BUILD_EXEC_B2(minu)
BUILD_EXEC_B2(maxu)

#define BUILD_EXEC_B2W(x) \
  static inline make_EHelper(x ## w) { \
    *ddest = concat(_rv32_, x)(*dsrc1, *dsrc2); \
    print_asm_template3(x ## w); \
  }

BUILD_EXEC_B2W(rol)
BUILD_EXEC_B2W(ror)

#define BUILD_EXEC_BI2(x) \
  static inline make_EHelper(x ## i) { \
    *ddest = concat(_rv_, x)(*dsrc1, id_src2->imm); \
    print_asm_template3(x); \
  }

BUILD_EXEC_BI2(ror)
BUILD_EXEC_BI2(bclr)
BUILD_EXEC_BI2(binv)
BUILD_EXEC_BI2(bext)
BUILD_EXEC_BI2(bset)

#define BUILD_EXEC_BI2W(x) \
  static inline make_EHelper(x ## i ## w) { \
    *ddest = concat(_rv32_, x)(*dsrc1, id_src2->imm); \
    print_asm_template3(x); \
  }

BUILD_EXEC_BI2W(ror)


make_EHelper(adduw) { *ddest = *dsrc1 + (uint32_t)*dsrc2; print_asm_template3(adduw); }
make_EHelper(slliuw) { *ddest = (uint32_t)*dsrc1 << id_src2->imm; print_asm_template3(slliuw); }

make_EHelper(sh1add) { *ddest = (*dsrc1 << 1) + *dsrc2; print_asm_template3(sh1add); }
make_EHelper(sh2add) { *ddest = (*dsrc1 << 2) + *dsrc2; print_asm_template3(sh2add); }
make_EHelper(sh3add) { *ddest = (*dsrc1 << 3) + *dsrc2; print_asm_template3(sh3add); }
make_EHelper(sh1adduw) { *ddest = ((uint32_t)*dsrc1 << 1) + *dsrc2; print_asm_template3(sh1adduw); }
make_EHelper(sh2adduw) { *ddest = ((uint32_t)*dsrc1 << 2) + *dsrc2; print_asm_template3(sh2adduw); }
make_EHelper(sh3adduw) { *ddest = ((uint32_t)*dsrc1 << 3) + *dsrc2; print_asm_template3(sh3adduw); }