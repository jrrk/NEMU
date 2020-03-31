#include <isa.h>
#include <memory/paddr.h>
#include <memory/vaddr.h>
#include <device/map.h>
#include <stdlib.h>
#include <time.h>

static uint8_t pmem[PMEM_SIZE] PG_ALIGN = {};

void* guest_to_host(paddr_t addr) { return &pmem[addr]; }
paddr_t host_to_guest(void *addr) { return (void *)pmem - addr; }

static IOMap pmem_map = {
  .name = "pmem",
  .space = pmem,
  .low = PMEM_BASE,
  .high = PMEM_BASE + PMEM_SIZE - 1,
  .callback = NULL
};

IOMap* fetch_mmio_map(paddr_t addr);

void init_mem() {
#ifndef DIFF_TEST
  srand(time(0));
  uint32_t *p = (uint32_t *)pmem;
  int i;
  for (i = 0; i < PMEM_SIZE / sizeof(p[0]); i ++) {
    p[i] = rand();
  }
#endif
}

/* Memory accessing interfaces */

#define make_paddr_access_template(bits) \
uint_type(bits) concat(paddr_read, bits)(paddr_t addr) { \
  if (map_inside(&pmem_map, addr)) { \
    paddr_t offset = addr - pmem_map.low; \
    return *(uint_type(bits) *)(pmem + offset); \
  } else return map_read(addr, bits / 8, fetch_mmio_map(addr)); \
} \
void concat(paddr_write, bits) (paddr_t addr, uint_type(bits) data) { \
  if (map_inside(&pmem_map, addr)) { \
    paddr_t offset = addr - pmem_map.low; \
    *(uint_type(bits) *)(pmem + offset) = data; \
  } else return map_write(addr, data, bits / 8, fetch_mmio_map(addr)); \
} \
uint_type(bits) concat(paddr_ifetch, bits)(paddr_t addr) { \
  return paddr_read(addr, bits / 8); \
}

make_paddr_access_template(8)
make_paddr_access_template(16)
make_paddr_access_template(32)
#ifdef ISA64
make_paddr_access_template(64)
#endif