/**
 * @file paging.c
 * @author Lubrin, Clarence, U.
 * @details Implements the paging and TLB extension point.
 */
#include "cpu/cpu.h"
bool cpu_translate_page(CPU *cpu, u32 linear, u32 *physical) { 
    if (!cpu || !physical) return false; 
    *physical = linear; 
    return true; 
}
