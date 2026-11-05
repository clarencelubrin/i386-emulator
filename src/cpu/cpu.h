/**
 * @file cpu.h
 * @author Lubrin, Clarence, U.
 * @details Defines CPU struct, Segment struct, Register union, and public execution APIs.
 */
#ifndef EMU_CPU_CPU_H
#define EMU_CPU_CPU_H
#include "common/types.h"
#include "mem/mem.h"
#include "io/io.h"

typedef union { 
    u32 r32;                    // 32-bits register
    u16 r16;                    // 16-bits register
    struct { u8 r8l, r8h; };    // 8-bits lower/upper register
} Register;

typedef struct { 
    // 16-bit visible selector
    u16 selector;               // holds the location of the segment descriptor
    // Hidden descriptors
    u32 base, limit;            // base and limit of the segment descriptor table
    u8 type, dpl, present, db, g;
} Segment;

typedef struct CPU {
    Register r[8];              // General-purpose registers
    u32 eip, eip_start;         // Instruction register
    u32 eflags;                 // Flag register
    u32 cr0, cr2, cr3, cr4;     // Control register
    Segment seg[6];             // Segment registers
    struct { u32 base; u16 limit; } gdtr, idtr; // (Global/local) Descriptor registers
    Segment ldtr, tr; u8 cpl; 
    bool halted, irq_inhibit;
    PhysicalMemory *memory; 
    IoBus *io;
} CPU;

void cpu_reset(CPU *cpu);
bool cpu_step(CPU *cpu);
#endif
