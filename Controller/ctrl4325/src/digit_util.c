#include <stdio.h>
#include <stdint.h>

#include "../../libstm32l0/include/libstm32l0.h"

extern void lpuart_putchar(struct lpuart_t *lpuart, const int8_t c);


/**
 */
void print_float_value(
    float value,
    size_t n) {
  size_t digit_count = 0;

  if(value < 0.f) {
    lpuart_putchar((struct lpuart_t *)LPUART1, '-');
    value = -value;
  }
  uint32_t u32_value = (uint32_t)value;
  while(u32_value > 0) {
    ++digit_count;
    u32_value /= 10;
  }

  u32_value = value;
  for(int i = 0; i < digit_count; ++i) {
    uint32_t div_value = 1;
    for(int j = 0; j < digit_count - (i + 1); ++j) {
      div_value *= 10;
    }

    int8_t n = (u32_value / div_value) % 10;
    lpuart_putchar((struct lpuart_t *)LPUART1, '0' + n);
  }
  lpuart_putchar((struct lpuart_t *)LPUART1, '.');

  float small_number = value - ((int32_t)value);
  for(int i = 0; i < n; ++i) {
    int32_t pow = 1;
    for(int j = 0; j < (i + 1); ++j) {
      pow *= 10;
    }

    int8_t n = (int32_t)(small_number * pow) % 10;
    lpuart_putchar((struct lpuart_t *)LPUART1, '0' + n);
  }
}
