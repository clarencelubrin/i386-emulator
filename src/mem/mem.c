/**
 * @file mem.c
 * @author Lubrin, Clarence, U.
 * @details Implements physical memory access and region mapping.
 * 
 * Physical Memory: 
 * - 64MiB RAM by default (configurable), little-endian accessors read8/16/32 and write8/16/32.
 * Port bus: 
 * - io_read8/16/32(port) and io_write8/16/32(port, v) dispatching to registered handlers.
 * 
 * Regions:
 * 0x00000000 - RAM
 * 0x000A0000 - VGA window (stub unless graphics is needed)
 * 0x000B8000 - VGA text (4000 bytes used)
 * 0x000C0000 - option ROM area (later)
 * 0x000E0000 - BIOS shadow (later)
 * 0xFFFC0000 - BIOS ROM at top of 4 GB (later)
 */
#include "mem/mem.h"
#include <stdlib.h>
#include <string.h>

bool mem_init(PhysicalMemory *mem, u32 size) {
    if (!mem || !size) return false;
    mem->data = calloc(1, size); mem->size = mem->data ? size : 0;
    mem->regions = NULL; mem->region_count = 0; return mem->data != NULL;
}
void mem_destroy(PhysicalMemory *mem) {
    if (!mem) return; free(mem->data); free(mem->regions);
    memset(mem, 0, sizeof(*mem));
}
bool mem_map_region(PhysicalMemory *mem, MemRegion region) {
    if (!mem || !region.size || region.base > mem->size || region.size > mem->size - region.base) return false;
    MemRegion *next = realloc(mem->regions, (mem->region_count + 1) * sizeof(*next));
    if (!next) return false; mem->regions = next; mem->regions[mem->region_count++] = region; return true;
}
bool mem_read(const PhysicalMemory *mem, u32 address, void *out, size_t size) {
    if (!mem || !out || address > mem->size || size > mem->size - address) return false;
    memcpy(out, mem->data + address, size); return true;
}
bool mem_write(PhysicalMemory *mem, u32 address, const void *in, size_t size) {
    if (!mem || !in || address > mem->size || size > mem->size - address) return false;
    memcpy(mem->data + address, in, size); return true;
}
u8 mem_read8(const PhysicalMemory *mem, u32 address) { 
    u8 v = 0; 
    (void)mem_read(mem, address, &v, 1); 
    return v; 
}
u16 mem_read16(const PhysicalMemory *mem, u32 address) { 
    u16 v = 0; 
    (void)mem_read(mem, address, &v, 2); 
    return v; 
}
u32 mem_read32(const PhysicalMemory *mem, u32 address) { 
    u32 v = 0; 
    (void)mem_read(mem, address, &v, 4); 
    return v; 
}
void mem_write8(PhysicalMemory *mem, u32 address, u8 value) { 
    (void)mem_write(mem, address, &value, 1); 
}
void mem_write16(PhysicalMemory *mem, u32 address, u8 value) { 
    (void)mem_write(mem, address, &value, 2); 
}
void mem_write32(PhysicalMemory *mem, u32 address, u8 value) { 
    (void)mem_write(mem, address, &value, 4); 
}

/*
    Memory-mapped I/O

    Ports to stub from the start
    Port	        Purpose	            Behavior
    0x80	        I/O delay	        ignore writes
    0x92	        A20 fast gate	    accept writes; A20 always on
    0x3D4/0x3D5	    VGA CRTC (cursor)	store registers, update cursor
    0x3F8-0x3FF	    COM1	            absent or log to stdout
    0xCF8/0xCFC	    PCI config	        ----
 */
u8 io_read8(u32 port);
void io_write8(u32 port, u32 value);