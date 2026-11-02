/**
 * @file fdc.c
 * @author Lubrin, Clarence, U.
 * @details Implements the floppy disk controller scaffold.
 */
#include "dev/fdc.h"
void fdc_init(Fdc *f) { f->attached = 0; }
