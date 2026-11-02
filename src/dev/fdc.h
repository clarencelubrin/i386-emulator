/**
 * @file fdc.h
 * @author Lubrin, Clarence, U.
 * @details Declares the floppy disk controller device.
 */
#ifndef EMU_DEV_FDC_H
#define EMU_DEV_FDC_H
typedef struct { int attached; } Fdc;
void fdc_init(Fdc *);
#endif
