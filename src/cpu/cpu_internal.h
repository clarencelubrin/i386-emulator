/**
 * @file cpu_internal.h
 * @author Lubrin, Clarence, U.
 * @details Private CPU accessors and operation helpers.
 */
#ifndef EMU_CPU_CPU_INTERNAL_H
#define EMU_CPU_CPU_INTERNAL_H
#include "cpu/cpu.h"
#define REG32(c, n) ((c)->r[(n)].r32)
#define FLAG(c, f) (((c)->eflags & (f)) != 0)
#define SET_FLAG(c, f, v) ((c)->eflags = (v) ? ((c)->eflags | (f)) : ((c)->eflags & ~(f)))
u8 cpu_fetch8(CPU *cpu);
#endif
