/**
 * @file io.h
 * @author Lubrin, Clarence, U.
 * @details Declares the x86 port I/O bus.
 */
#ifndef EMU_IO_IO_H
#define EMU_IO_IO_H
#include "common/types.h"
typedef u8 (*IoRead)(void *opaque, u16 port);
typedef void (*IoWrite)(void *opaque, u16 port, u8 value);
typedef struct { u16 first, last; IoRead read; IoWrite write; void *opaque; } IoDevice;
typedef struct { IoDevice *devices; size_t count; } IoBus;
void io_init(IoBus *bus);
void io_destroy(IoBus *bus);
bool io_register(IoBus *bus, IoDevice device);
u8 io_read8(IoBus *bus, u16 port);
void io_write8(IoBus *bus, u16 port, u8 value);
#endif
