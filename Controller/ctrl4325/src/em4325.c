#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/asm.h"
#include "../include/em4325.h"

extern void mdelay16(uint16_t msec);
extern void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c);

extern void lpuart_print(
    struct lpuart_t *lpuart,
    const char *str);

extern void lpuart_println(
    struct lpuart_t *lpuart,
    const char *str);

#define HEX2CHR(u8) \
  (((u8) >= 0x0a) ? (((u8) - 0x0a) + 'A') : ((u8) + '0'))

/**
 */
uint16_t spi_communicate(
    spi_t *spi,
    uint16_t data) {
  while((spi->SR & SPI_SR_TXE) == 0) { NOP(); }
  spi->DR = data;

  while((spi->SR & SPI_SR_RXNE) == 0) { NOP(); }

  return spi->DR & 0xff;
}

/**
 */
uint16_t em4325_request_status(void) {
  uint32_t recv;
  GPIOB->BSRR |= (1 << 17);

  spi_communicate(SPI1, 0xe0);
  recv = spi_communicate(SPI1, 0x00);

  GPIOB->BSRR |= (1 << 1);

  return recv;
}

/**
 */
int8_t em4325_get_sensordata(
    uint8_t required_new_sample,
    struct em4325_sensor_data_t *p) {
  if(p == NULL)
    return -1;

  GPIOB->BSRR |= (1 << 17);

  spi_communicate(SPI1, (required_new_sample ? 0xe5 : 0xe4));

  mdelay16(20);

  uint8_t status = 0;
  int8_t response;
  uint8_t buffer[8];

  do {
    status = spi_communicate(SPI1, 0);
  } while(status == 0);
  response = status & 0b11;

  if(response == 0) {
    for(int8_t i = 0; i < 8; ++i) {
      uint16_t _recv = spi_communicate(SPI1, 0);
      *(buffer + (7 - i)) = (uint8_t)(_recv & 0xff);
    }
  }

  GPIOB->BSRR |= (1 << 1);

  p->status = status;

  if(response != 0)
    return response;

  memcpy((void *)&p->sensor, (const void *)(buffer + 4), sizeof(uint32_t));
  memcpy((void *)&p->utc, (const void *)(buffer + 0), sizeof(uint32_t));

  return 0;
}

void em4325_read_word(
    spi_t *spi,
    uint8_t address) {
  GPIOB->BSRR |= (1 << 17);

  spi_communicate(spi, 0xe7);
  spi_communicate(spi, address);

  mdelay16(1);

  uint8_t status;
  do {
    status = spi_communicate(spi, 0);
  } while(status == 0);

  uint8_t buffer[2];
  for(int8_t i = 0; i < 2; ++i) {
#if 0
    *(buffer + i) = spi_communicate(spi, 0);
#else
    *(buffer + (1 - i)) = spi_communicate(spi, 0);
#endif
  }

  GPIOB->BSRR |= (1 << 1);

  uint16_t data;
  memcpy((void *)&data, (const void *)buffer, sizeof(uint16_t));

  for(int8_t i = 0; i < 4; ++i) {
    int8_t shift_size = 12 - (i * 4);
    uint8_t segment = (data >> shift_size) & 0x0f;
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR(segment));
  }
}
