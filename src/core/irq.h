/**
 * @file irq.h
 * @author Lubrin, Clarence, U.
 * @details Declares the interrupt-source interface.
 */
#ifndef EMU_CORE_IRQ_H
#define EMU_CORE_IRQ_H
#include "common/types.h"
typedef struct { bool pending[16]; } IrqController;
void irq_init(IrqController *irq);
void irq_raise(IrqController *irq, unsigned line);
void irq_clear(IrqController *irq, unsigned line);
int irq_next(const IrqController *irq);
#endif
