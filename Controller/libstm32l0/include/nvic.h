#ifndef _NVIC_H
#define _NVIC_H

#include <stdint.h>
#include "io.h"

#define NVIC_ADD (0xe000e100)
#define NVIC ((volatile struct nvic_t *)NVIC_ADD)

struct nvic_t {
  _IO uint32_t ISER;
  _RO uint32_t reserved0[31];

  _IO uint32_t ICER;
  _RO uint32_t reserved1[31];

  _IO uint32_t ISPR;
  _RO uint32_t reserved2[31];

  _IO uint32_t ICPR;
  _RO uint32_t reserved3[95];

  _IO uint32_t IPR[8];
};

/** Interrupt Set-enable Register */
#define NVIC_ISER_SETPENA (0xffffffff)

/** Interrupt Clear-eanble register */
#define NVIC_ICER_CLRENA (0xffffffff)

/** Interrupt Set-pending Register */
#define NVIC_ISPR_SETPEND (0xffffffff)

/** Interrupt Clear-pending Register */
#define NVIC_ICPR_CLRPEND (0xffffffff)

typedef enum irq_type_t irq_type_t;
enum irq_type_t {
  NMI_IRQn = -14,
  HardFault_IRQn = -13,
  SVCall_IRQn = -5,
  PendSV_IRQn = -2,
  SysTick_IRQn = -1,
  WWDG_IRQn = 0,
  RTC_IRQn = 2,
  FLASH_IRQn = 3,
  RCC_CRS_IRQn = 4,
  EXTI1_0_IRQn = 5,
  EXTI3_2_IRQn = 6,
  EXTI15_4_IRQn = 7,
  DMA1_Channel1_IRQn = 9,
  DMA1_Channel3_2_IRQn = 10,
  DMA1_Channel7_4_IRQn = 11,
  ADC_IRQn = 12,
  LPTIM1_IRQn = 13,
  TIM2_IRQn = 15,
  TIM21_IRQn = 20,
  TIM22_IRQn = 22,
  I2C1_IRQn = 23,
  SPI1_IRQn = 25,
  USART2_IRQn = 28,
  LPUART1_IRQn = 29,
};

#endif
