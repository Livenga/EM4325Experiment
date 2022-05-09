#include <stdio.h>
#include <stdint.h>

#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/lpuart_ex.h"

#define HEX2CHR(u8) \
  (((u8) >= 0x0a) ? (((u8) - 0x0a) + 'A') : ((u8) + '0'))



/**
 */
void print_to_hex(
    uint32_t value,
    size_t size) {
  uint8_t display_count = size * 2;

  lpuart_print((struct lpuart_t *)LPUART1, "0x");
  for(int i = 0; i < display_count; ++i) {
    size_t offset = 4 * (display_count - (i + 1));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((value >> offset) & 0x0f));
  }
  lpuart_println((struct lpuart_t *)LPUART1, NULL);
}

/**
 */
void print_to_dec(int32_t value) {
  uint16_t digit_count = 0;

  if(value < 0) {
    value = -value;
    lpuart_putchar((struct lpuart_t *)LPUART1, '-');
  }

  int32_t u32 = value;
  while(u32 > 0) {
    ++digit_count;
    u32 /= 10;
  }

  for(int i = 0; i < digit_count; ++i) {
    uint16_t div = 1;
    for(int j = 0; j < digit_count - (i + 1); ++j) {
      div *= 10;
    }

    uint8_t d = (value / div) % 10;
    lpuart_putchar((struct lpuart_t *)LPUART1, '0' + d);
  }
}


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
