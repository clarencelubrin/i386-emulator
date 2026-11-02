/**
 * @file flags.h
 * @author Lubrin, Clarence, U.
 * @details Declares arithmetic flag calculation helpers.
 */
#ifndef EMU_CPU_FLAGS_H
#define EMU_CPU_FLAGS_H
#include "common/types.h"
enum { FLAG_CF = BIT(0), FLAG_PF = BIT(2), FLAG_AF = BIT(4), FLAG_ZF = BIT(6), FLAG_SF = BIT(7), FLAG_OF = BIT(11), FLAG_IF = BIT(9) };
u32 flags_add(u32 a, u32 b, u32 result, unsigned bits);
u32 flags_sub(u32 a, u32 b, u32 result, unsigned bits);
#endif
