/**
 * @file seg.c
 * @author Lubrin, Clarence, U.
 * @details Implements the segment-cache loading extension point.
 */
#include "cpu/cpu.h"
bool cpu_load_seg(CPU *cpu, unsigned index, u16 selector) { if (!cpu || index >= 6) return false; cpu->seg[index].sel = selector; return true; }
