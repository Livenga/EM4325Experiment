#include <stdio.h>
#include <stdint.h>
#include "../include/asm.h"
#include "../../libstm32l0/include/libstm32l0.h"


extern void NVIC_enable_IRQ(
    struct nvic_t *nvic,
    irq_type_t n);

extern void NVIC_set_priority(
    struct nvic_t *nvic,
    irq_type_t    n,
    uint32_t      priority);

extern void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c);

extern void gpio_set_mode(
    struct  gpio_t *gpio,
    uint8_t n,
    uint8_t mode);


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
  // LPUART1 有効化
  RCC->APB1ENR |= RCC_APB1ENR_LPUART1EN;
  RCC->CCIPR = (RCC->CCIPR & ~RCC_CCIPR_LPUART1SEL) | (0b01 << 10);

  // GPIO A, B, H 有効化
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN | RCC_IOPENR_IOPHEN;


  // LPUART 設定
  // GPIO A 2,3, LPUART1 Tx, LPUART1 Rx
  gpio_set_mode((struct gpio_t *)GPIOA, 2, GPIO_MODER_MODE_ALTERNATE_FUNCTION);
  gpio_set_mode((struct gpio_t *)GPIOA, 3, GPIO_MODER_MODE_ALTERNATE_FUNCTION);

  LPUART1->CR1 = LPUART_CR1_RXNEIE
    | LPUART_CR1_TE | LPUART_CR1_RE;

  //LPUART1->BRR = 9160; // 115200
  LPUART1->BRR = 109440; // 9600

  LPUART1->CR1 |= LPUART_CR1_UE;

  lpuart_putchar((struct lpuart_t *)LPUART1, 'H');
  lpuart_putchar((struct lpuart_t *)LPUART1, 'e');
  lpuart_putchar((struct lpuart_t *)LPUART1, 'l');
  lpuart_putchar((struct lpuart_t *)LPUART1, 'l');
  lpuart_putchar((struct lpuart_t *)LPUART1, 'o');

  //
  STK->RVR = 4104000;
  STK->CVR = 0;
  STK->CSR = STK_CSR_CLKSOURCE
    | STK_CSR_ENABLE;


  while(1) {
    NOP();
  }

  return 0;
}
