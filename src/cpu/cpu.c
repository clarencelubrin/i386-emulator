/**
 * @file cpu.c
 * @author Lubrin, Clarence, U.
 * @details Implements CPU reset and the main instruction step loop.
 */
#include "cpu/cpu_internal.h"
#include "cpu/flags.h"
#include <string.h>
void cpu_reset(CPU *cpu) {
    PhysicalMemory *memory = cpu->memory; IoBus *io = cpu->io;
    memset(cpu, 0, sizeof(*cpu)); cpu->memory = memory; cpu->io = io;
    cpu->eflags = UINT32_C(0x2); cpu->seg[1].sel = UINT16_C(0xf000); cpu->seg[1].base = UINT32_C(0xffff0000); cpu->eip = UINT16_C(0xfff0);
}
u8 cpu_fetch8(CPU *cpu) { u8 value = cpu->memory ? mem_read8(cpu->memory, cpu->seg[1].base + cpu->eip) : 0xf4; ++cpu->eip; return value; }
bool cpu_step(CPU *cpu) { if (!cpu || cpu->halted) return false; if (cpu_fetch8(cpu) == 0xf4) cpu->halted = true; return !cpu->halted; }
