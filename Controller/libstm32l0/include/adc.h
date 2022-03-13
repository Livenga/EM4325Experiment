/** 13 Analog-to-digital converter (ADC) RM0451 p.252
 */


#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>
#include "io.h"

#define ADC1_ADDR (0x40012400)
#define ADC1 ((adc_t *)ADC1_ADDR)

typedef volatile struct adc_t adc_t;
struct adc_t {
  _IO uint32_t ISR;
  _IO uint32_t IER;
  _IO uint32_t CR;
  _IO uint32_t CFGR1;
  _IO uint32_t CFGR2;
  _IO uint32_t SMPR;

  _RO uint32_t reserved0[2];

  _IO uint32_t TR;

  _RO uint32_t reserved1;

  _IO uint32_t CHSELR;

  _RO uint32_t reserved2[5];

  _IO uint32_t DR;

  _RO uint32_t reserved3[28];

  _IO uint32_t CALFACT;

  _RO uint32_t reserved4[148];

  _IO uint32_t CCR;
};

#endif
