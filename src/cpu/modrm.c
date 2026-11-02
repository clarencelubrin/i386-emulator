/**
 * @file modrm.c
 * @author Lubrin, Clarence, U.
 * @details Provides ModR/M and SIB effective-address extension points.
 */
#include "cpu/cpu.h"
u32 cpu_modrm_address(CPU *cpu, u8 modrm) { (void)cpu; return modrm; }
