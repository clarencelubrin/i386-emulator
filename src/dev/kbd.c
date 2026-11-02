/**
 * @file kbd.c
 * @author Lubrin, Clarence, U.
 * @details Implements the keyboard controller scaffold.
 */
#include "dev/kbd.h"
#include <string.h>
void kbd_init(Keyboard *k) { memset(k, 0, sizeof(*k)); }
