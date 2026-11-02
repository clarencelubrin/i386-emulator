/**
 * @file access.c
 * @author Lubrin, Clarence, U.
 * @details Provides segmented and paged memory access extension points.
 */
#include "cpu/cpu.h"
bool cpu_access_read(CPU *cpu, u32 address, void *out, size_t size) { return cpu && cpu->memory && mem_read(cpu->memory, address, out, size); }
bool cpu_access_write(CPU *cpu, u32 address, const void *in, size_t size) { return cpu && cpu->memory && mem_write(cpu->memory, address, in, size); }
