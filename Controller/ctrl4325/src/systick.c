#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"


static uint8_t _is_bright = 0;


void SysTick_handler(void) {
#if 1
  if(_is_bright) {
    GPIOA->BSRR = (1 <<  26);
  } else {
    GPIOA->BSRR = (1 <<  10);
  }
#endif

  _is_bright ^= 1;
}
