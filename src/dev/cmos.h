/**
 * @file cmos.h
 * @author Lubrin, Clarence, U.
 * @details Declares the CMOS/RTC device.
 */
#ifndef EMU_DEV_CMOS_H
#define EMU_DEV_CMOS_H
#include "common/types.h"
typedef struct { u8 registers[128]; } Cmos;
void cmos_init(Cmos *);
#endif
