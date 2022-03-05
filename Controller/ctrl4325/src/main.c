#include <stdio.h>
#include <stdint.h>
#include "../include/asm.h"
#include "../../libstm32l0/include/libstm32l0.h"

#define __DEBUG__ 1


extern void NVIC_enable_IRQ(irq_type_t n);
extern void NVIC_set_priority(
    irq_type_t    n,
    uint32_t      priority);

extern void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c);

extern void lpuart_print(
    struct lpuart_t *lpuart,
    const char *str);

extern void lpuart_println(
    struct lpuart_t *lpuart,
    const char *str);

extern void gpio_set_mode(
    struct  gpio_t *gpio,
    uint8_t n,
    uint8_t mode);

extern void gpio_set_alternate_function(
    struct gpio_t *gpio,
    uint8_t n,
    gpio_afsel_t afsel);


int main(void) {
  // System Clock MSI 4.2[MHz]
  RCC->ICSCR = (RCC->ICSCR & ~RCC_ICSCR_MSIRANGE) | RCC_ICSCR_MSIRANGE_4_2MHZ;

  if((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI) {
    FLASH->ARC |= FLASH_ACR_LATENCY;
    while((FLASH->ARC & FLASH_ACR_LATENCY) == 0);

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_MSI;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI);
  }

  // SPI1, TIM21, System Config 有効化
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_TIM21EN | RCC_APB2ENR_SYSCFEN;
  // LPUART1, TIM2 有効化
  RCC->APB1ENR |= RCC_APB1ENR_LPUART1EN
    | RCC_APB1ENR_TIM2EN;
  RCC->CCIPR = (RCC->CCIPR & ~RCC_CCIPR_LPUART1SEL) | (0b01 << 10);

  // GPIO A, B, H 有効化
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN | RCC_IOPENR_IOPHEN;


  // LPUART 設定
  // GPIO A 2,3, LPUART1 Tx, LPUART1 Rx
  gpio_set_mode((struct gpio_t *)GPIOA, 2, GPIO_MODER_MODE_ALTERNATE_FUNCTION);
  gpio_set_mode((struct gpio_t *)GPIOA, 3, GPIO_MODER_MODE_ALTERNATE_FUNCTION);

  gpio_set_alternate_function((struct gpio_t *)GPIOA, 2, 6);
  gpio_set_alternate_function((struct gpio_t *)GPIOA, 3, 6);


  // GPIO A 10 Output
  gpio_set_mode((struct gpio_t *)GPIOA, 10, GPIO_MODER_MODE_GPO);

  //
  LPUART1->CR1 = LPUART_CR1_TE | LPUART_CR1_RE
    | LPUART_CR1_RXNEIE;

  LPUART1->BRR = 9320; // 115200
  //LPUART1->BRR = 111840; // 9600
  LPUART1->CR1 |= LPUART_CR1_UE;

#ifdef __DEBUG__
  lpuart_println((struct lpuart_t *)LPUART1, "Hello, World");
#endif


  NVIC_set_priority(LPUART1_IRQn, 1);
  NVIC_set_priority(TIM2_IRQn, 0);
  NVIC_set_priority(SysTick_IRQn, 3);

  NVIC_enable_IRQ(LPUART1_IRQn);
  NVIC_enable_IRQ(TIM2_IRQn);

  //
  STK->RVR = 2052000;
  STK->CVR = 0;
  STK->CSR = STK_CSR_TICKINT
    | STK_CSR_CLKSOURCE
    | STK_CSR_ENABLE;

  while(1) {
    NOP();
  }

  return 0;
}
