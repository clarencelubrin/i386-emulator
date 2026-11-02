/**
 * @file task.c
 * @author Lubrin, Clarence, U.
 * @details Provides TSS and privilege-transition extension points.
 */
#include "cpu/cpu.h"
bool cpu_switch_task(CPU *cpu, u16 selector) { (void)cpu; (void)selector; return false; }
