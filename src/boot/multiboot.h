/**
 * @file multiboot.h
 * @author Lubrin, Clarence, U.
 * @details Declares Multiboot image loading.
 */
#ifndef EMU_BOOT_MULTIBOOT_H
#define EMU_BOOT_MULTIBOOT_H
#include "machine.h"
bool multiboot_load(Machine *machine, const char *path);
#endif
