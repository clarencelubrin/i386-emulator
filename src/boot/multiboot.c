/**
 * @file multiboot.c
 * @author Lubrin, Clarence, U.
 * @details Implements the initial Multiboot loading extension point.
 */
#include "boot/multiboot.h"
bool multiboot_load(Machine *machine, const char *path) { 
    (void)machine; 
    (void)path;
    return false; 
}
