#include <stdint.h>
#include "../include/asm.h"
#include "../../libstm32l0/include/libstm32l0.h"

#if 0
///
/// 割り込みによる制御
///

static uint8_t _is_timeout = 0;

void TIM2_handler(void) {
  uint32_t sr = TIM2->SR;

  if(sr & TIM2_SR_UIF) {
    _is_timeout = 1;
  }

  TIM2->SR = 0;
}

void mdelay16(uint16_t msec) {
  if(msec == 0)
    return;

  _is_timeout = 0;

  TIM2->CR1 = TIM2_CR1_OPM;
  //TIM2->CR2 = (TIM2->CR2 & ~(TIM2_CR2_MMS)) | (0b001 << 4);
  TIM2->CR2 = 0;
  TIM2->SMCR = 0x00000000;
  TIM2->DIER = TIM2_DIER_UIE;
  TIM2->ARR  = msec;
  TIM2->PSC  = 4193;
  TIM2->CNT  = 0;
  TIM2->CR1  |= TIM2_CR1_CEN;

  while(! _is_timeout) { NOP(); }

  TIM2->DIER = 0;
}

#else
///
/// カウンタのポーリング
///

void mdelay16(uint16_t msec) {
  if(msec == 0)
    return;

  TIM2->CR1 = TIM2_CR1_OPM;
  //TIM2->CR2 = (TIM2->CR2 & ~(TIM2_CR2_MMS)) | (0b001 << 4);

  TIM2->SMCR = 0x00000000;
  TIM2->DIER = 0x00000000;

  TIM2->ARR  = msec;
  TIM2->PSC  = 4193;
  TIM2->CNT  = 0;
  TIM2->CR1  |= TIM2_CR1_CEN;

  while((TIM2->SR & TIM2_SR_UIF) == 0) { NOP(); }

  TIM2->SR   = 0;
  TIM2->DIER = 0;
  TIM2->CR1  &= ~TIM2_CR1_CEN;
}


#endif
