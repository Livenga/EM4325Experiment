#include <stdio.h>
#include <stdint.h>

#include "../include/asm.h"
#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/nvic_ex.h"
#include "../include/lpuart_ex.h"
#include "../include/em4325.h"
#include "../include/mpl115a1.h"

#define __DEBUG__ 1

extern void mdelay16(uint16_t msec);

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

  // LSI 有効化 (37 [kHz])
  if((RCC->CSR & RCC_CSR_LSIRDY) == 0) {
    RCC->CSR |= RCC_CSR_LSION;
    while((RCC->CSR & RCC_CSR_LSIRDY) == 0) { NOP(); }
  }


  // SPI1, TIM21, System Config 有効化
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_TIM21EN | RCC_APB2ENR_SYSCFGEN;
  // LPTIM1, LPUART1, TIM2 有効化
  RCC->APB1ENR |= RCC_APB1ENR_LPTIM1EN
    | RCC_APB1ENR_LPUART1EN
    | RCC_APB1ENR_TIM2EN;

  // LPUART1 のクロック供給元をSystem Clock(MSI: 4.2MHz) に変更.
  // LPTIM1 クロック供給源を LSI に変更.
  RCC->CCIPR = (RCC->CCIPR & ~(RCC_CCIPR_LPUART1SEL | RCC_CCIPR_LPTIM1SEL))
    | RCC_CCIPR_LPUART1SEL_SYSTEM
    | RCC_CCIPR_LPTIM1SEL_LSI;


  // GPIO A, B, H 有効化
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN | RCC_IOPENR_IOPHEN;

  gpio_set_mode((struct gpio_t *)GPIOA, 0, GPIO_MODER_MODE_GPO);
  gpio_set_mode((struct gpio_t *)GPIOA, 4, GPIO_MODER_MODE_INPUT);


  // LPUART 設定
  // GPIO A 2,3, LPUART1 Tx, LPUART1 Rx
  gpio_set_mode((struct gpio_t *)GPIOA, 2, GPIO_MODER_MODE_ALTERNATE_FUNCTION);
  gpio_set_mode((struct gpio_t *)GPIOA, 3, GPIO_MODER_MODE_ALTERNATE_FUNCTION);

  gpio_set_alternate_function((struct gpio_t *)GPIOA, 2, AF6);
  gpio_set_alternate_function((struct gpio_t *)GPIOA, 3, AF6);


  // SPI 設定
  // GPIO A 5, 6, 7 SCK, MISO, MOSI
  gpio_set_mode((struct gpio_t *)GPIOA, 5, GPIO_MODER_MODE_ALTERNATE_FUNCTION);
  gpio_set_mode((struct gpio_t *)GPIOA, 6, GPIO_MODER_MODE_ALTERNATE_FUNCTION);
  gpio_set_mode((struct gpio_t *)GPIOA, 7, GPIO_MODER_MODE_ALTERNATE_FUNCTION);

  gpio_set_alternate_function((struct gpio_t *)GPIOA, 5, AF0); // SCK
  gpio_set_alternate_function((struct gpio_t *)GPIOA, 6, AF0); // MISO
  gpio_set_alternate_function((struct gpio_t *)GPIOA, 7, AF0); // MOSI

  // GPIO B 1 CS
  GPIOB->BSRR |= (1 << 1);
  gpio_set_mode((struct gpio_t *)GPIOB, 1, GPIO_MODER_MODE_GPO);

  // GPIO A 1 CS
  gpio_set_mode((struct gpio_t *)GPIOA, 1, GPIO_MODER_MODE_GPO);
  GPIOA->BSRR |= (1 << 1);

  SPI1->CR1 =  SPI_CR1_CRCEN | SPI_CR1_BR_FPCLK_4 | SPI_CR1_MSTR;
  //SPI1->CR1 |= SPI_CR1_LSBFIRST;
#if 0
  SPI1->CR1 |= SPI_CR1_CPOL;
  SPI1->CR1 |= SPI_CR1_CPHA;
#endif
  SPI1->CR2 = SPI_CR2_SSOE;
  //SPI1->CR2 |= SPI_CR2_TXEIE | SPI_CR2_RXNEIE;
    SPI1->CR1 |= SPI_CR1_SPE;


  // LED 点滅確認用
  // GPIO A 10 Output
  gpio_set_mode((struct gpio_t *)GPIOA, 10, GPIO_MODER_MODE_GPO);

  //
  LPUART1->CR1 = LPUART_CR1_TE | LPUART_CR1_RE
    | LPUART_CR1_RXNEIE;

  LPUART1->BRR = 9320; // 115200
  //LPUART1->BRR = 111840; // 9600
  LPUART1->CR1 |= LPUART_CR1_UE;


  // EXTI4
  SYSCFG->EXTICR2 = (SYSCFG->EXTICR2 & ~SYSCFG_EXTICR2_EXTI4);
  EXTI->IMR  |= EXTI_IMR_IM4;
  EXTI->RTSR |= EXTI_RTSR_RT4;


  // SysTick 設定
  STK->RVR = 2052000;
  STK->CVR = 0;
  STK->CSR = STK_CSR_TICKINT
    | STK_CSR_CLKSOURCE
    | STK_CSR_ENABLE;


  /* 経過時間 (単位: 秒[s]) を余裕を持った形で計測するため,
   * LPTIM1 を 1[s]毎に割り込みを発生させ _ticks をカウントアップさせる.
   *
   * UHF RFID リーダから設定に応じた間隔で照射される電波にタグが応答するので
   * 必要以上に書き込みを実行させないため, 経過時間が必要.
   * 精度が要求されないため LPTIM1 のクロック源に LSI を採用.
   */
  // LPTIM1 設定とカウント開始
  LPTIM1->IER = LPTIM_IER_ARRMIE;
  // LSI の周波数は 37[kHz]. (fLSI / 8 = 4625) の周期で CNT レジスタを加算.
  LPTIM1->CFGR = LPTIM_CFGR_PRESC_PER_8
    | LPTIM_CFGR_PRELOAD;
  LPTIM1->CR   = LPTIM_CR_ENABLE;

  // 自動更新の値を LSI の周波数をプリスケーラで処理した値と同じに設定.
  LPTIM1->ARR  = 4625;
  LPTIM1->CR   |= LPTIM_CR_CNTSTRT | LPTIM_CR_ENABLE;


  // 割り込みの有効化と優先順位設定
  NVIC_enable_IRQ(LPUART1_IRQn);
  NVIC_enable_IRQ(EXTI15_4_IRQn);
  NVIC_set_priority(LPUART1_IRQn, 1);
  NVIC_set_priority(EXTI15_4_IRQn, 2);
  NVIC_set_priority(SysTick_IRQn, 3);

  // LPTIM1 の割り込み処理に多大な負荷はかからないので, 最も優先させる.
  // 異常が生じた場合は要修正.
  NVIC_enable_IRQ(LPTIM1_IRQn);
  NVIC_set_priority(LPTIM1_IRQn, 0);

#ifdef __DEBUG__
  lpuart_println((struct lpuart_t *)LPUART1, "Hello, World");
#endif
  // EM4325 初期設定
  em4325_init((struct gpio_t *)GPIOA, 1);

  // MPL1151A 初期設定
  GPIOA->BSRR = (1 << 0);
  mdelay16(1000);

  mpl115a1_init((struct gpio_t *)GPIOB, 1);
  mdelay16(3000);

  while(1) {
    NOP();
  }

  return 0;
}
