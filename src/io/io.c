/**
 * @file io.c
 * @author Lubrin, Clarence, U.
 * @details Implements the x86 port I/O bus.
 */
#include "io/io.h"
#include <stdlib.h>
void io_init(IoBus *bus) { bus->devices = NULL; bus->count = 0; }
void io_destroy(IoBus *bus) { free(bus->devices); io_init(bus); }
bool io_register(IoBus *bus, IoDevice device) {
    IoDevice *next = realloc(bus->devices, (bus->count + 1) * sizeof(*next));
    if (!next) return false; bus->devices = next; bus->devices[bus->count++] = device; return true;
}
static IoDevice *find(IoBus *bus, u16 port) {
    for (size_t i = 0; i < bus->count; ++i)
        if (port >= bus->devices[i].first && port <= bus->devices[i].last) return &bus->devices[i];
    return NULL;
}
u8 io_read8(IoBus *bus, u16 port) { IoDevice *d = find(bus, port); return d && d->read ? d->read(d->opaque, port) : 0xff; }
void io_write8(IoBus *bus, u16 port, u8 value) { IoDevice *d = find(bus, port); if (d && d->write) d->write(d->opaque, port, value); }
