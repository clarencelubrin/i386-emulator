/**
 * @file machine.h
 * @author Lubrin, Clarence, U.
 * @details Defines the top-level machine composition.
 */
#ifndef EMU_MACHINE_H
#define EMU_MACHINE_H
#include "cpu/cpu.h"
#include "core/clock.h"
#include "core/irq.h"
typedef struct { PhysicalMemory memory; IoBus io; VirtualClock clock; IrqController irq; CPU cpu; } Machine;
bool machine_init(Machine *machine, u32 memory_size);
void machine_destroy(Machine *machine);
bool machine_step(Machine *machine);
#endif
