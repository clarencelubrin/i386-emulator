/**
 * @file pic.h
 * @author Lubrin, Clarence, U.
 * @details Declares the programmable interrupt controller device.
 */
#ifndef EMU_DEV_PIC_H
#define EMU_DEV_PIC_H
#include "core/irq.h"
typedef struct { IrqController *irq; } Pic;
void pic_init(Pic *pic, IrqController *irq);
#endif
