/**
 * @file pit.c
 * @author Lubrin, Clarence, U.
 * @details Implements the programmable interval timer scaffold.
 */
#include "dev/pit.h"
void pit_init(Pit *p, VirtualClock *c) { p->clock = c; }
