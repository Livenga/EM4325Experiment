#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"


void gpio_set_mode(
    struct  gpio_t *gpio,
    uint8_t n,
    int8_t  mode) {
  if(n > 15)
    return;

  uint16_t shift_size = n * 2;
  mode &= 0b11;

  gpio->MODER = (gpio->MODER & ~(0b11 << shift_size)) | (mode << shift_size);
}

void gpio_set_alternate_function(
    struct gpio_t *gpio,
    uint8_t n,
    gpio_afsel_t afsel) {
  if(n > 15)
    return;

  afsel &= 0b111;
  uint8_t shift_size = 0;

  if(n > 7) {
    shift_size = (n - 8) * 4;
    gpio->AFRH = (gpio->AFRH & ~(0b111 << shift_size)) | (afsel << shift_size);
  } else {
    shift_size = n * 4;
    gpio->AFRL = (gpio->AFRL & ~(0b111 << shift_size)) | (afsel << shift_size);
  }
}
