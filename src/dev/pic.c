/**
 * @file pic.c
 * @author Lubrin, Clarence, U.
 * @details Implements the programmable interrupt controller scaffold.
 */
#include "dev/pic.h"
void pic_init(Pic *p, IrqController *i) { p->irq = i; }
