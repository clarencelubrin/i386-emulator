/**
 * @file seg.c
 * @author Lubrin, Clarence, U.
 * @details Implements the segment-cache loading extension point.
 */

/**
 * ============================================ Segmentation ============================================
 * @author Lubrin, Clarence, U.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 * 
 * General Segment-Descriptor Format for CODE AND DATA SEGMENT
 * 31               23              15              7               0
 * [      Base      |G|X|O|A|  LIM  |P|DPL |1|TYPE|D|      BASE     ]
 *      31..24                19..16                      23...16
 * [           Segment Base         |        Segment Limit          ]
 *               15..0                           15..0
 * D - Accessed
 * A - Available for use by systems programmers
 * DPL - Descriptor privilege level
 * G - Granularity
 * P - Segment Present
 */
#include "cpu/cpu.h"
bool cpu_load_seg(CPU *cpu, unsigned index, u16 selector) { 
    if (!cpu || index >= 6) return false; 
    cpu->seg[index].selector = selector; 
    return true; 
}

/* Translate logical address to linear address */
bool mem_logical_to_linear_addr(PhysicalMemory *mem, u16 selector, u32 dt_base, u32 logical, u32 *linear) {
    if (!mem) return false;
    u64 seg_descriptor = mem_read32(mem, dt_base + selector) | (u64) mem_read32(mem, dt_base + selector + 32) << 32;
    u32 seg_base = ((seg_descriptor & 0xFF00000000000000) | (seg_descriptor & 0x000000FF00000000) << 8 | (seg_descriptor & 0x00000000FFFF0000) << 16) >> 16;
    u32 seg_lim = ((seg_descriptor >> 32) | seg_descriptor) & 0x0000000000FFFFFF;
    if (seg_base + logical > seg_lim) return false;
    *linear = seg_base + logical;
    return true;
}