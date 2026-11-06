/**
 * @file seg.c
 * @author Lubrin, Clarence, U.
 * @details Implements the seg-cache loading extension point and logical to linear address translation.
 */

/**
 * ============================================ Segmentation ============================================
 * @author Lubrin, Clarence, U.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 * 
 * Segment Selector Format
 *  15                  3 2   1..0
 * [        INDEX        |TI| RPL ]
 *                         
 * (TI) Table Indicator                 - 0=GDTR; 1=LDTR
 * (RPL) Requestor's privilege level    - High bit: IDT (index refers to an IDT gate)
 *                                      - Low bit : EXT (event was external to a program (e.g. hardware interrupt))
 * 
 * Segment-Descriptor Format for DATA SEGMENT
 * 31               23              15               7               0
 * [      Base      |G|B|0|A|  LIM  |P|DPL |  TYPE   |      BASE     ]
 * [                | | | |V|       | |    |         |               ]
 * [                | | | |L|       | |    |1|0|E|W|A|               ]
 *      31..24                19..16       (S)            23...16
 * [           Segment Base         |         Segment Limit          ]
 *               15..0                           15..0
 *
 * Segment-Descriptor Format for EXECUTABLE SEGMENT
 * 31               23              15               7               0
 * [      Base      |G|D|0|A|  LIM  |P|DPL |  TYPE   |      BASE     ]
 * [                | | | |V|       | |    |         |               ]
 * [                | | | |L|       | |    |1|1|C|R|A|               ]
 *      31..24                19..16       (S)            23...16
 * [           Segment Base         |         Segment Limit          ]
 *               15..0                           15..0
 * 
 * Segment-Descriptor Format for SYSTEM SEGMENT
 * 31               23              15               7               0
 * [      Base      |G|X|0|A|  LIM  |P|DPL |  TYPE   |      BASE     ]
 * [                | | | |V|       | |    |         |               ]
 * [                | | | |L|       | |    |0|       |               ]
 *      31..24                19..16                      23...16
 * [           Segment Base         |         Segment Limit          ]
 *               15..0                           15..0
 * 
 * (A) Accessed     - set automatically by CPU when accessed
 * (AVL) Available for use by systems programmers
 * (B) Big          - 0=16-bit stack, use the 16-bit SP register; 
 *                    1=32-bit mode, use the 32-bit ESP register
 * (C) Conforming   - 0=Non-comforming (;
 *                    1=Conforming (may execute at a privilege level equal to or more privileged than DPL)
 * (D) Default      - 0=16-bit mode; 
 *                    1=32-bit mode
 * (DPL) Descriptor privilege level
 * (E) Expand-down  - 0=expand up (normal data); 
 *                    1=expand dorun only at privilege level of DPL unless transferred via a call gate)wn
 * (G) Granularity  - 0=limit is interpreted in units of one byte; 
 *                    1=limit is interpreted in units of 4 Kilobytes
 * (P) Segment Present
 * (R) Readable     - 0=Execute-only;   1=Read and executable
 * (W) Writable     - 0=Read-only data; 1=RW-data
 */
#include "cpu/cpu.h"
#include "cpu/seg.h"
#include "cpu/fault.h";

/* Fill segment content based from the selector and descriptor */
static void seg_cache_fill(Segment *seg, u16 s, u64 d) {
    u32 limit = (u32)((d & 0xFFFF) | ((d >> 32) & 0xF0000));
    seg->g       = (d >> 55) & 1;
    seg->selector = s;
    seg->base    = (u32)(((d >> 16) & 0xFFFFFF) | (((d >> 56) & 0xFF) << 24));
    seg->limit   = seg->g ? (limit << 12) | 0xFFF : limit;
    seg->type    = (d >> 40) & 0xF;
    seg->s       = (d >> 44) & 1;
    seg->dpl     = (d) & 3;
    seg->present = (d) & 1;
    seg->db      = (d) & 1;
}

/* Get the descriptor based from the segment selector */
static Fault fetch_descriptor(CPU *cpu, u16 selector, u64 *descriptor, u32 *addr) {
    u32 base, limit;
    if (selector & 4) {     // TI = 1: LDT
        // Check if ldtr selector has any value
        if (cpu->ldtr.selector == 0) return fault_gp(selector & 0xFFFC);
        base = cpu->ldtr.base;  limit = cpu->ldtr.limit;
    } else {                // TI = 0: GDT
        base = cpu->gdtr.base;  limit = cpu->gdtr.limit;
    }
    u32 offset = selector & 0xFFF8;    // Get the offset from the selector
    if ((u64)offset + 7 > limit) return fault_gp(selector & 0xFFFC);   // outside the table
    *addr = base + offset;             // Calculate for the address of the descriptor
    if (!mem_read(cpu->memory, *addr, descriptor, sizeof *descriptor)) return fault_gp(selector & 0xFFFC);
    return NO_FAULT;
}

Fault cpu_load_seg(CPU *cpu, SegmentIdx idx, u16 selector) {
    u32 err = selector & 0xFFFC;    // Get the error code from the selector
    // Null selector (index 0, TI = 0)
    if ((selector & 0xFFFC) == 0) {
        // If loads to CS or SS, raise a fault
        if (idx == SEG_REG_CS || idx == SEG_REG_SS) return fault_gp(0);
        cpu->seg[idx].selector = selector;  // set selector
        cpu->seg[idx].valid = 0;            // loadable, but faults when used
        return NO_FAULT;
    }

    // Fetch and parse the descriptor
    u64 descriptor; 
    u32 addr;
    Fault f = fetch_descriptor(cpu, selector, &descriptor, &addr);
    if (faulted(f)) return f;       // Check if faulted
    Segment new_seg;                // Get the new seg based from the selector and the descriptor
    seg_cache_fill(&new_seg, selector, descriptor);    // Fill the hidden data with the descriptor as cache

    // Perform type checks for protection
    if (!new_seg.s) return fault_gp(err);                        // must be code/data
    bool code = new_seg.type & 8;                                // Check if the segment is for code
    if (idx == SEG_REG_CS) {                                     // CS segment requires load only from code descriptor
        if (!code) return fault_gp(err);
    } else if (idx == SEG_REG_SS) {                              // Check for SS if selectors are writable data segments
        if (code || !(new_seg.type & 2)) return fault_gp(err);
    } else {                                                     // For DS ES FS GS data segments
        if (code && !(new_seg.type & 2)) return fault_gp(err);   // non-readable code
    }

    // Privilege checks for stack segment and data segment
    u8 rpl = selector & 3;          // Get the RPL from the selector
    if (idx == SEG_REG_SS) {        // Stack segment check
        // Check that the RPL and new_seg.dpl matches cpu->cpl privilege level
        if (rpl != cpu->cpl || new_seg.dpl != cpu->cpl) return fault_gp(err);
    } else if (idx != SEG_REG_CS) { // Data segment check
        bool conforming = code && (new_seg.type & 4);      // Get if new_seg is conforming (seg is type code segment and conforming bit)
        u8 eff = cpu->cpl > rpl ? cpu->cpl : rpl;          // Get the maximum privilege from cpl and rpl
        // conforming=0 -> raise fault when CPL/RPL is higher than new_seg.dpl (descriptor privilege level) 
        if (!conforming && eff > new_seg.dpl) return fault_gp(err);
    }

    // Check present bit from the seg
    if (!new_seg.present) return idx == SEG_REG_SS ? fault_ss(err) : fault_np(err);

    // Set the Accessed bit in memory (bit 40 = bit 8 of the high dword)
    if (!(new_seg.type & 1)) {                              // Set the accessed bit to on
        u32 hi = (u32)(descriptor >> 32) | (1u << 8);       
        mem_write(cpu->memory, addr + 4, &hi, sizeof hi);
        // Set the accessed bit from the new_seg.type to 1, 
        // retains the values from the higher bits of the new_seg.type
        new_seg.type |= 1;                                  
    }

    // Save the new seg to the cpu seg register
    cpu->seg[idx] = new_seg;
    return NO_FAULT;
}

Fault cpu_translate_seg(CPU *cpu, SegmentIdx idx, u32 offset, u32 size, Access acc, u32 *linear) {
    const Segment *s = &cpu->seg[idx];  // Get the segment from the cpu segment registers
    // fault_ss if SEG_RES_SS, else fault_gp
    Fault fault_code = (idx == SEG_REG_SS) ? fault_ss(0) : fault_gp(0);

    if (!s->valid) return fault_code;   // Raise a fault when segment invalid
    bool code = s->type & 8;            // Check if segment is a code segment
    if (acc == ACC_WRITE && (code || !(s->type & 2))) return fault_code;  // No writes to code / read-only data
    if (acc == ACC_READ  && code && !(s->type & 2))   return fault_code;  // Execute-only code
    if (acc == ACC_EXEC  && !code)                    return fault_code;  // Only execute from code segment

    u32 last = offset + (size - 1);             // Get the last address based on the offset + size-1
    if (last < offset) return fault_code;       // Raise a fault if last wraps
    bool expand_down = !code && (s->type & 4);  // Expansion direction
    if (!expand_down) {
        if (last > s->limit) return fault_code; // For grows upward, last must not exceed the segment limit
    } else {                                    // For grows downward, the upperbound is either 4KB or 4GB based on the db bit
        u32 upper = s->db ? 0xFFFFFFFFu : 0xFFFFu;
        if (offset <= s->limit || last > upper) return fault_code;
    }
    *linear = s->base + offset;                 // Set the calculated linear address
    return NO_FAULT;
}