/**
 * @file dma.h
 * @author Lubrin, Clarence, U.
 * @details Declares the DMA controller device.
 */
#ifndef EMU_DEV_DMA_H
#define EMU_DEV_DMA_H
#include "common/types.h"
typedef struct { u32 address[4], count[4]; } Dma;
void dma_init(Dma *);
#endif
