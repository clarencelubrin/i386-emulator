/**
 * @file trace.c
 * @author Lubrin, Clarence, U.
 * @details Implements instruction tracing.
 */
#include "dbg/trace.h"
#include <stdio.h>
void trace_cpu(const CPU *cpu) { 
    if (cpu) fprintf(stderr, "eip=%08x eflags=%08x\n", cpu->eip, cpu->eflags); 
}
