/** 10 Direct memory access controller (DMA) RM0451 p.216
 */
#ifndef _DMA_H
#define _DMA_H

#include <stdint.h>
#include "io.h"


#define DMA1_ADDR (0x40020000)
#define DMA1 ((dma_t *)DMA1_ADDR)

typedef volatile struct dma_t dma_t;

struct dma_t {
  _RO uint32_t ISR;
  _IO uint32_t IFCR;
  _IO uint32_t CCR1;
  _IO uint32_t CNDTR1;
  _IO uint32_t CPAR1;
  _IO uint32_t CMAR1;

  _RO uint32_t reserved0;

  _IO uint32_t CCR2;
  _IO uint32_t CNDTR2;
  _IO uint32_t CPAR2;
  _IO uint32_t CMAR2;

  _RO uint32_t reserved1;

  _IO uint32_t CCR3;
  _IO uint32_t CNDTR3;
  _IO uint32_t CPAR3;
  _IO uint32_t CMAR3;

  _RO uint32_t reserved2;

  _IO uint32_t CCR4;
  _IO uint32_t CNDTR4;
  _IO uint32_t CPAR4;
  _IO uint32_t CMAR4;

  _RO uint32_t reserved3;

  _IO uint32_t CCR5;
  _IO uint32_t CNDTR5;
  _IO uint32_t CPAR5;
  _IO uint32_t CMAR5;

  _RO uint32_t reserved4;

  _IO uint32_t CCR6;
  _IO uint32_t CNDTR6;
  _IO uint32_t CPAR6;
  _IO uint32_t CMAR6;

  _RO uint32_t reserved5;

  _IO uint32_t CCR7;
  _IO uint32_t CNDTR7;
  _IO uint32_t CPAR7;
  _IO uint32_t CMAR7;

  _RO uint32_t reserved6[6];

  _IO uint32_t CSELR;
};

#endif
