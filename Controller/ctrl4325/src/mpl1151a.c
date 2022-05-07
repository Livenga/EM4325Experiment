#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/spi_ex.h"
#include "../include/mpl1151a.h"
#include "../include/digit_util.h"
#include "../include/lpuart_ex.h"

#define __DEBUG__


extern void mdelay16(uint16_t msec);

extern uint16_t spi_communicate(spi_t *spi, uint16_t data);
extern uint16_t spi_writeonly(spi_t *spi, uint16_t data);

static int8_t _is_initialized = 0;
static struct mpl1151_coefficient_t _coefficient;

static struct gpio_t *_gpio = NULL;
static uint8_t _cs_number = 0;


/**
*/
const struct mpl1151_coefficient_t *mpl1151a_init(
    struct gpio_t *gpio,
    uint8_t cs_number) {
  _gpio = gpio,
  _cs_number = cs_number;

  if(_is_initialized) {
    return &_coefficient;
  }

  memset((void *)&_coefficient, 0, sizeof(struct mpl1151_coefficient_t));

  CS_OFF(_gpio, _cs_number);

  // 計数の読み出し
  uint16_t a0_msb, a0_lsb;
  spi_communicate(SPI1, MPL1151A_A0_MSB_COMMAND);
  a0_msb = spi_communicate(SPI1, 0);
  spi_communicate(SPI1, MPL1151A_A0_LSB_COMMAND);
  a0_lsb = spi_communicate(SPI1, 0);


  uint16_t b1_msb, b1_lsb;
  spi_communicate(SPI1, MPL1151A_B1_MSB_COMMAND);
  b1_msb = spi_communicate(SPI1, 0);
  spi_communicate(SPI1, MPL1151A_B1_LSB_COMMAND);
  b1_lsb = spi_communicate(SPI1, 0);


  uint16_t b2_msb, b2_lsb;
  spi_communicate(SPI1, MPL1151A_B2_MSB_COMMAND);
  b2_msb = spi_communicate(SPI1, 0);
  spi_communicate(SPI1, MPL1151A_B2_LSB_COMMAND);
  b2_lsb = spi_communicate(SPI1, 0);

  uint16_t c12_msb, c12_lsb;
  spi_communicate(SPI1, MPL1151A_C12_MSB_COMMAND);
  c12_msb = spi_communicate(SPI1, 0);
  spi_communicate(SPI1, MPL1151A_C12_LSB_COMMAND);
  c12_lsb = spi_communicate(SPI1, 0);

  spi_communicate(SPI1, 0);

  CS_ON(_gpio, _cs_number);


  int16_t a0  = (a0_msb << 8) | a0_lsb,
          b1  = (b1_msb << 8) | b1_lsb,
          b2  = (b2_msb << 8) | b2_lsb,
          c12 = (c12_msb << 8) | c12_lsb;

#ifdef __DEBUG__
  lpuart_println((struct lpuart_t *)LPUART1, "# MPL1151A Coefficient...");
  lpuart_print((struct lpuart_t *)LPUART1, "\ta0  = ");
  print_to_hex(a0, sizeof(uint16_t));

  lpuart_print((struct lpuart_t *)LPUART1, "\tb1  = ");
  print_to_hex(b1, sizeof(uint16_t));

  lpuart_print((struct lpuart_t *)LPUART1, "\tb2  = ");
  print_to_hex(b2, sizeof(uint16_t));

  lpuart_print((struct lpuart_t *)LPUART1, "\tc12 = ");
  print_to_hex(c12, sizeof(uint16_t));
  lpuart_println((struct lpuart_t *)LPUART1, NULL);
#endif

  _coefficient.a0  = (float)a0 / 8.f;
  _coefficient.b1  = (float)b1 / 8192.f;
  _coefficient.b2  = (float)b2 / 16384.f;

  int16_t _c12 = (c12 & (1 << 15)) | ((c12 >> 2) & (~(1 << 13)));
  _coefficient.c12 = (float)_c12 / (1 << 22);

  _is_initialized = 1;

  return &_coefficient;
}


float mpl1151a_get_pressure(void) {
  if(! _is_initialized) {
    return .0f;
  }

  CS_OFF(_gpio, _cs_number);

  spi_communicate(SPI1, MPL1151A_CONVERT);
  spi_communicate(SPI1, 0);

  CS_ON(_gpio, _cs_number);
  mdelay16(10);


  CS_OFF(_gpio, _cs_number);

  uint16_t padc_msb, padc_lsb;
  spi_communicate(SPI1, MPL1151A_PADC_MSB_COMMAND);
  padc_msb = spi_communicate(SPI1, 0);
  spi_communicate(SPI1, MPL1151A_PADC_LSB_COMMAND);
  padc_lsb = spi_communicate(SPI1, 0);

  uint16_t tadc_msb, tadc_lsb;
  spi_communicate(SPI1, MPL1151A_TADC_MSB_COMMAND);
  tadc_msb = spi_communicate(SPI1, 0);
  spi_communicate(SPI1, MPL1151A_TADC_LSB_COMMAND);
  tadc_lsb = spi_communicate(SPI1, 0);

  spi_communicate(SPI1, 0x00);

  CS_ON(_gpio, _cs_number);


  uint16_t padc = ((padc_msb << 8) | padc_lsb) >> 6,
           tadc = ((tadc_msb << 8) | tadc_lsb) >> 6;

  float pcomp = _coefficient.a0
    + (_coefficient.b1 + _coefficient.c12 * tadc) * padc
    + _coefficient.b2 * tadc;

  float pressure = pcomp * ((115.f - 50.f) / 1023.f) + 50.f;

  return pressure;
}
