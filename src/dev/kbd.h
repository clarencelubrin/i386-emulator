/**
 * @file kbd.h
 * @author Lubrin, Clarence, U.
 * @details Declares the keyboard controller device.
 */
#ifndef EMU_DEV_KBD_H
#define EMU_DEV_KBD_H
#include "common/types.h"
typedef struct { u8 status, data; } Keyboard;
void kbd_init(Keyboard *);
#endif
