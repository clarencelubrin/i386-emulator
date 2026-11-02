/**
 * @file rtl8139.c
 * @author Lubrin, Clarence, U.
 * @details Implements the RTL8139 network device scaffold.
 */
#include "dev/rtl8139.h"
void rtl8139_init(Rtl8139 *n) { n->link_up = 0; }
