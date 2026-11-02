/**
 * @file irq.c
 * @author Lubrin, Clarence, U.
 * @details Implements interrupt-source bookkeeping.
 */
#include "core/irq.h"
#include <string.h>
void irq_init(IrqController *i) { memset(i, 0, sizeof(*i)); }
void irq_raise(IrqController *i, unsigned line) { if (line < 16) i->pending[line] = true; }
void irq_clear(IrqController *i, unsigned line) { if (line < 16) i->pending[line] = false; }
int irq_next(const IrqController *i) { for (unsigned n = 0; n < 16; ++n) if (i->pending[n]) return (int)n; return -1; }
