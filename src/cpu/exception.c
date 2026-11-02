/**
 * @file exception.c
 * @author Lubrin, Clarence, U.
 * @details Declares exception and interrupt delivery extension points.
 */
#include "cpu/cpu.h"
void cpu_raise_exception(CPU *cpu, unsigned vector, u32 error_code) { (void)vector; (void)error_code; if (cpu) cpu->halted = true; }
