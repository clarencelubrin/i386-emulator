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
typedef union { u32 r32; u16 r16; struct { u8 r8l, r8h; }; } Register;
typedef struct { u16 sel; u32 base, limit; u8 type, dpl, present, db, g; } Segment;
typedef struct CPU {
    Register r[8]; u32 eip, eip_start, eflags, cr0, cr2, cr3, cr4;
    Segment seg[6]; struct { u32 base; u16 limit; } gdtr, idtr;
    Segment ldtr, tr; u8 cpl; bool halted, irq_inhibit;
    PhysicalMemory *memory; IoBus *io;
} CPU;
void cpu_reset(CPU *cpu);
bool cpu_step(CPU *cpu);
#endif
