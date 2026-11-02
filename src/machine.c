/**
 * @file machine.c
 * @author Lubrin, Clarence, U.
 * @details Wires memory, I/O, clock, IRQ, and CPU together.
 */
#include "machine.h"
#include <string.h>
bool machine_init(Machine *m, u32 size) {
    memset(m, 0, sizeof(*m)); if (!mem_init(&m->memory, size)) return false;
    io_init(&m->io); clock_init(&m->clock); irq_init(&m->irq); m->cpu.memory = &m->memory; m->cpu.io = &m->io; cpu_reset(&m->cpu); return true;
}
void machine_destroy(Machine *m) { io_destroy(&m->io); clock_destroy(&m->clock); mem_destroy(&m->memory); }
bool machine_step(Machine *m) { bool running = cpu_step(&m->cpu); clock_advance(&m->clock, 1); return running; }
