/**
 * @file debugger.h
 * @author Lubrin, Clarence, U.
 * @details Declares debugger state and breakpoint hooks.
 */
#ifndef EMU_DBG_DEBUGGER_H
#define EMU_DBG_DEBUGGER_H
#include "cpu/cpu.h"
typedef struct { bool stopped; u32 breakpoint; } Debugger;
void debugger_init(Debugger *);
bool debugger_check(const Debugger *, const CPU *);
#endif
