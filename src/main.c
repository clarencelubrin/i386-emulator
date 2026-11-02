/**
 * @file main.c
 * @author Lubrin, Clarence, U.
 * @details Provides the emulator command-line entry point.
 */
#include "machine.h"
#include <stdio.h>
int main(void) {
    Machine machine;
    if (!machine_init(&machine, UINT32_C(1024 * 1024))) return 1;
    printf("i386 emulator scaffold initialized\n");
    machine_destroy(&machine);
    return 0;
}
