/**
 * @file dma.c
 * @author Lubrin, Clarence, U.
 * @details Implements the DMA controller scaffold.
 */
#include "dev/dma.h"
#include <string.h>
void dma_init(Dma *d) { memset(d, 0, sizeof(*d)); }
