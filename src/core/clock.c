/**
 * @file clock.c
 * @author Lubrin, Clarence, U.
 * @details Implements virtual time and one-shot event dispatch.
 */
#include "core/clock.h"
#include <stdlib.h>
void clock_init(VirtualClock *c) { c->now = 0; c->events = NULL; c->count = 0; }
void clock_destroy(VirtualClock *c) { free(c->events); clock_init(c); }
bool clock_schedule(VirtualClock *c, u64 delay, ClockCallback cb, void *opaque) {
    ClockEvent *n = realloc(c->events, (c->count + 1) * sizeof(*n)); if (!n) return false;
    c->events = n; c->events[c->count++] = (ClockEvent){c->now + delay, cb, opaque}; return true;
}
void clock_advance(VirtualClock *c, u64 ticks) {
    c->now += ticks;
    for (size_t i = 0; i < c->count;) {
        if (c->events[i].due > c->now) { ++i; continue; }
        ClockEvent e = c->events[i]; c->events[i] = c->events[--c->count]; if (e.callback) e.callback(e.opaque);
    }
}
