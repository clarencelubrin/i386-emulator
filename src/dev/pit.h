/**
 * @file pit.h
 * @author Lubrin, Clarence, U.
 * @details Declares the programmable interval timer device.
 */
#ifndef EMU_DEV_PIT_H
#define EMU_DEV_PIT_H
#include "core/clock.h"
typedef struct { VirtualClock *clock; } Pit;
void pit_init(Pit *, VirtualClock *);
#endif
