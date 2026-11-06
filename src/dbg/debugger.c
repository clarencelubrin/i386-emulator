/**
 * @file debugger.c
 * @author Lubrin, Clarence, U.
 * @details Implements debugger state and breakpoint hooks.
 */
#include "dbg/debugger.h"
void debugger_init(Debugger *d) { 
    d->stopped = false; 
    d->breakpoint = UINT32_MAX; 
}
bool debugger_check(const Debugger *d, const CPU *c) { 
    return d && c && c->eip == d->breakpoint; 
}
