/**
 * @file flags.c
 * @author Lubrin, Clarence, U.
 * @details Implements arithmetic flag calculation helpers.
 */
#include "cpu/flags.h"
u32 flags_add(u32 a, u32 b, u32 r, unsigned bits) {
    u32 mask = bits == 32 ? UINT32_MAX : ((UINT32_C(1) << bits) - 1), f = 0;
    if ((u64)a + b > mask) f |= FLAG_CF; if (!r) f |= FLAG_ZF; if (r & (UINT32_C(1) << (bits - 1))) f |= FLAG_SF;
    if ((~(a ^ b) & (a ^ r)) & (UINT32_C(1) << (bits - 1))) f |= FLAG_OF; return f;
}
u32 flags_sub(u32 a, u32 b, u32 r, unsigned bits) {
    u32 f = 0, sign = UINT32_C(1) << (bits - 1); if (a < b) f |= FLAG_CF;
    if (!r) f |= FLAG_ZF; if (r & sign) f |= FLAG_SF; if (((a ^ b) & (a ^ r)) & sign) f |= FLAG_OF; return f;
}
