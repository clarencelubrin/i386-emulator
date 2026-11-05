/**
 * @file mem.h
 * @author Lubrin, Clarence, U.
 * @details Declares physical memory and its region map.
 */
#ifndef EMU_MEM_MEM_H
#define EMU_MEM_MEM_H
#include "common/types.h"

typedef enum { MEM_RAM, MEM_ROM, MEM_MMIO } MemRegionType;

typedef struct { 
    u32 base, size; 
    MemRegionType type; 
} MemRegion;

typedef struct { 
    u8 *data; 
    u32 size; 
    MemRegion *regions; 
    size_t region_count; 
} PhysicalMemory;

bool mem_init(PhysicalMemory *mem, u32 size);
void mem_destroy(PhysicalMemory *mem);
bool mem_map_region(PhysicalMemory *mem, MemRegion region);
bool mem_read(const PhysicalMemory *mem, u32 address, void *out, size_t size);
bool mem_write(PhysicalMemory *mem, u32 address, const void *in, size_t size);
u8 mem_read8(const PhysicalMemory *mem, u32 address);
u16 mem_read16(const PhysicalMemory *mem, u32 address);
u32 mem_read32(const PhysicalMemory *mem, u32 address);
void mem_write8(PhysicalMemory *mem, u32 address, u8 value);
void mem_write16(PhysicalMemory *mem, u32 address, u16 value);
void mem_write32(PhysicalMemory *mem, u32 address, u32 value);
#endif
