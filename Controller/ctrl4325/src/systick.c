#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"

extern void mdelay16(uint16_t msec);

static uint8_t _is_bright = 0;


void SysTick_handler(void) {
  if(_is_bright) {
    GPIOA->BSRR = (1 <<  26);
  } else {
    GPIOA->BSRR = (1 <<  10);
  }
  _is_bright ^= 1;
}
