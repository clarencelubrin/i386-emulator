/**
 * @file dump.c
 * @author Lubrin, Clarence, U.
 * @details Provides CPU state dump support.
 */
#include "cpu/cpu.h"
#include <stdio.h>
void cpu_dump(const CPU *cpu) { if (cpu) printf("EIP=%08x EFLAGS=%08x\n", cpu->eip, cpu->eflags); }
