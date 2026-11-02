/**
 * @file optable.c
 * @author Lubrin, Clarence, U.
 * @details Defines the opcode-handler table extension point.
 */
#include "cpu/cpu.h"
typedef void (*OpcodeHandler)(CPU *);
static void unimplemented(CPU *cpu) { cpu->halted = true; }
OpcodeHandler cpu_opcode_handler(u8 opcode) { (void)opcode; return unimplemented; }
