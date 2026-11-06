/**
 * @file paging.c
 * @author Lubrin, Clarence, U.
 * @details Implements the paging and TLB extension point.
 */
#include "cpu/cpu.h"

/**
 * ============================================ Paging ============================================
 * @author Lubrin, Clarence, U.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 * 
 * Page Tables
 * - Array of 32-bit page specifiers
 * - Page table is itself a page (4KB), up most of 1K 32-bit page entries
 * CR3 (PTBR) - holds the base address of the page table
 *
 * Page Table Entries
 *  31                                12 11                        0
 * [        Page Frame Address          | AVAIL |00|D|A|00|U/S|R/W|P]
 * 
 * (P) Present bit - indicates whether a PTE can be used in address translation. Set before a r/w operation to a page
 * (R/W) Read/write - set in second-level PT to one before write to an address covered by the PTE
 * (U/S) User/supervisor
 * (D) Dirty
 * (AVAIL) Available - available for system programmer use
 *
 * NOTE: 0 indicates Intel reserved. Do not use.
 * - Present and dirty bit is not cleared by the processor
 *
 * Page Directory Entries
 *  31                                12 11                        0
 * [     Page Table Base Address        |AVAIL|0|Z|0|A|C|W|U/S|R/W|P]
 * (Z) Page size - hardwired to 0 on 80386 (4KB pages only)
 * (C) Cache disabled - control caching. 1=do not cache this page table; 0=caching allowed
 * 
 * Page Frame Address
 * - Specifies the physical starting address of the page
 * - Low-order 12 bits are always zero
 * 
 * Page Translation Cache
 * - Processor stores the most recently used page-table data in the TLB.
 * - Can be flushed by either (1) reloading CR3 with MOV (2) performing task switch to a TSS that has different CR3 image
 */

bool cpu_translate_page(CPU *cpu, u32 linear, u32 *physical) { 
    if (!cpu || !physical) return false; 
    u16 offset = (linear & 0x00000FFF);        // 0-11  (12 bits)
    u16 page   = (linear & 0x003FF000) >> 12;  // 12-21 (10 bits)
    u16 dir    = (linear & 0xFFC00000) >> 22;  // 22-31 (10 bits)
    
    u32 pde_addr = (cpu->cr3 & 0xfffff000) + dir * 4;
    u32 pde;
    // Read memory from pde_addr
    if (!cpu->memory || !mem_read(cpu->memory, pde_addr, &pde, sizeof(pde))) return false;
    if (!(pde & 1)) return false;   // Check present bit
    /**
     * TODO: For PDE. 
     * - Check U/S againts CPL (ring 3=user)
     * - check R/W for writes (supervisor honors it only if CR0.WP=1)
     * - Set accessed (and Dirty on write)
     */

    u32 pte_addr = (pde & 0xfffff000) + page * 4;
    u32 pte;
    if (!mem_read(cpu->memory, pte_addr, &pte, sizeof(pte))) return false;
    if (!(pte & 1)) return false;   // Check present bit
    *physical = (pte & 0xfffff000) | offset;

    return true;
}