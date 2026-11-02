/**
 * @file pci.h
 * @author Lubrin, Clarence, U.
 * @details Declares the PCI bus device.
 */
#ifndef EMU_DEV_PCI_H
#define EMU_DEV_PCI_H
typedef struct { unsigned device_count; } Pci;
void pci_init(Pci *);
#endif
