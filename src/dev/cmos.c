/**
 * @file cmos.c
 * @author Lubrin, Clarence, U.
 * @details Implements the CMOS/RTC scaffold.
 */
#include "dev/cmos.h"
#include <string.h>
void cmos_init(Cmos *c) { memset(c, 0, sizeof(*c)); }
