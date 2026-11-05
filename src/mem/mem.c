/**
 * @file mem.c
 * @author Lubrin, Clarence, U.
 * @details Implements physical memory access and region mapping.
 */
#include "mem/mem.h"
#include <stdlib.h>
#include <string.h>

/**
 * ============================================ Memory Organization ============================================
 * @author Lubrin, Clarence, U.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 * 
 *                      Memory Regions
 * 0x00000000 - RAM
 * 0x000A0000 - VGA window (stub unless graphics is needed)
 * 0x000B8000 - VGA text (4000 bytes used)
 * 0x000C0000 - option ROM area
 * 0x000E0000 - BIOS shadow
 * 0xFFFC0000 - BIOS ROM at top of 4 GB
 * 
 * Physical Memory: 
 * - 64MiB RAM by default (configurable), little-endian accessors read8/16/32 and write8/16/32.
 * 
 * ============================================ Address Translation ============================================
 * Logical Address  31                    0
 * ( SELECTOR )     [        OFFSET       ]
 * - The segment selector (from the segment register) points to the segment descriptor from the descriptor table
 * - The offset is added to the base address from the segment descriptor entry to get the LINEAR ADDRESS.
 * 
 * Linear Address   31  22 21  12 11      0
 *                  [ DIR | PAGE | OFFSET ]
 * - Refers indirectly to physical address by specifying a page table (DIR), page within the table (PAGE), offset within the page (OFFSET).
 * DIR - address of page directory entry
 * PAGE - address of page table entry
 * OFFSET - offset within the page
 * CR3 - base address of the page directory
 *  
 * Physical Address 31                    0
 *                  [    PHYSICAL ADDR.   ]
 * 
 * "FLAT" Architecture
 * - Perform flat architecture by initially loading the segment registers with selectors for descriptors that encompass the entire 32-bit linear address space
 * - Once loaded, the segment registers don't need to be changed
 * - 32-bit offsets used by 80386 instructions are adequate to address the entire linear-address space
 */


/* Initialize the physical memory for the machine */
bool mem_init(PhysicalMemory *mem, u32 size) {
    if (!mem || !size) return false;    // mem and size must not be NULL
    mem->data = calloc(1, size);        // Initialize data
    mem->size = mem->data ? size : 0;   // Initialize size
    mem->regions = NULL;                // Set initial regions to NULL and region_count to 0
    mem->region_count = 0; 
    return mem->data != NULL;           // Return if mem->data is initialized successfully
}
/* Cleanup for the dynamically allocated physical memory */
void mem_destroy(PhysicalMemory *mem) {
    if (!mem) return;
    free(mem->data); free(mem->regions);        // Clean mem->data and mem->regions
    memset(mem, 0, sizeof(*mem));               // Deallocate the physical memory
}
/* Create a Memory Region for the Physical Memory */
bool mem_map_region(PhysicalMemory *mem, MemRegion region) {
    if (!mem || !region.size || region.base > mem->size || region.size > mem->size - region.base) return false;
    MemRegion *next = realloc(mem->regions, (mem->region_count + 1) * sizeof(*next));
    if (!next) return false;                    // Return false if it did not allocate successfully
    mem->regions = next;                        // set mem->region to point to the newly resized memory region
    mem->regions[mem->region_count++] = region; // Increment region_count then set the newly allocated region to that index
    return true;
}
/* Read from physical memory using the physical address */
bool mem_read(const PhysicalMemory *mem, u32 address, void *out, size_t size) {
    if (!mem || !out || address > mem->size || size > mem->size - address) return false;
    memcpy(out, mem->data + address, size);     // Copy the memory from mem->data + address (src) to out (dest)
    return true;
}
/* Write to physical memory using the physical address */
bool mem_write(PhysicalMemory *mem, u32 address, const void *in, size_t size) {
    if (!mem || !in || address > mem->size || size > mem->size - address) return false;
    memcpy(mem->data + address, in, size);      // Copy the memory from in (src) to mem->data + address (dest)
    return true;
}
/* Read memory with 8 bit value */
u8 mem_read8(const PhysicalMemory *mem, u32 address) { 
    u8 v = 0; 
    (void)mem_read(mem, address, &v, 1); 
    return v; 
}
/* Read memory with 16 bit value */
u16 mem_read16(const PhysicalMemory *mem, u32 address) { 
    u16 v = 0; 
    (void)mem_read(mem, address, &v, 2); 
    return v; 
}
/* Read memory with 32 bit value */
u32 mem_read32(const PhysicalMemory *mem, u32 address) { 
    u32 v = 0; 
    (void)mem_read(mem, address, &v, 4); 
    return v; 
}
/* Write memory with 8 bit value */
void mem_write8(PhysicalMemory *mem, u32 address, u8 value) { 
    (void)mem_write(mem, address, &value, 1); 
}
/* Write memory with 16 bit value */
void mem_write16(PhysicalMemory *mem, u32 address, u16 value) { 
    (void)mem_write(mem, address, &value, 2); 
}
/* Write memory with 32 bit value */
void mem_write32(PhysicalMemory *mem, u32 address, u32 value) { 
    (void)mem_write(mem, address, &value, 4); 
}






