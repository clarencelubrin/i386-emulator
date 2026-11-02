/**
 * @file rtl8139.h
 * @author Lubrin, Clarence, U.
 * @details Declares the RTL8139 network device.
 */
#ifndef EMU_DEV_RTL8139_H
#define EMU_DEV_RTL8139_H
typedef struct { int link_up; } Rtl8139;
void rtl8139_init(Rtl8139 *);
#endif
