/**
 * @file vga.c
 * @author Lubrin, Clarence, U.
 * @details Implements the VGA scaffold.
 */
#include "dev/vga.h"
void vga_init(Vga *v) { v->width = 320; v->height = 200; }
