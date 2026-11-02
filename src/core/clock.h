/**
 * @file clock.h
 * @author Lubrin, Clarence, U.
 * @details Declares the virtual clock and event scheduler.
 */
#ifndef EMU_CORE_CLOCK_H
#define EMU_CORE_CLOCK_H
#include "common/types.h"
typedef void (*ClockCallback)(void *opaque);
typedef struct { u64 due; ClockCallback callback; void *opaque; } ClockEvent;
typedef struct { u64 now; ClockEvent *events; size_t count; } VirtualClock;
void clock_init(VirtualClock *clock);
void clock_destroy(VirtualClock *clock);
bool clock_schedule(VirtualClock *clock, u64 delay, ClockCallback callback, void *opaque);
void clock_advance(VirtualClock *clock, u64 ticks);
#endif
