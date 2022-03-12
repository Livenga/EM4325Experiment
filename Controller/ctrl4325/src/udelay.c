#include <stdint.h>
#include "../include/asm.h"
#include "../../libstm32l0/include/libstm32l0.h"


void udelay16(uint16_t usec) {
  if(usec == 0)
    return;

  TIM2->CR1 = TIM2_CR1_OPM;
  //TIM2->CR2 = (TIM2->CR2 & ~(TIM2_CR2_MMS)) | (0b001 << 4);

  TIM2->SMCR = 0x00000000;
  TIM2->DIER = 0x00000000;

  TIM2->ARR  = usec;
  //TIM2->PSC  = 4193;
  TIM2->PSC  = 3;
  TIM2->CNT  = 0;
  TIM2->CR1  |= TIM2_CR1_CEN;

  while((TIM2->SR & TIM2_SR_UIF) == 0) { NOP(); }

  TIM2->SR   = 0;
  TIM2->DIER = 0;
  TIM2->CR1  &= ~TIM2_CR1_CEN;
}
