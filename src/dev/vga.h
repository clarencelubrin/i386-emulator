/**
 * @file vga.h
 * @author Lubrin, Clarence, U.
 * @details Declares the VGA device.
 */
#ifndef EMU_DEV_VGA_H
#define EMU_DEV_VGA_H
typedef struct { unsigned width, height; } Vga;
void vga_init(Vga *);
#endif
