/**
 * @file types.h
 * @author Lubrin, Clarence, U.
 * @details Defines fixed-width aliases, boolean support, and helper macros.
 */
#ifndef EMU_COMMON_TYPES_H
#define EMU_COMMON_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))
#define UNUSED(x) ((void)(x))
#define BIT(n) (UINT32_C(1) << (n))

#endif
