#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/asm.h"

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

uint16_t spi_writeonly(spi_t *spi, uint16_t data) {
  while((spi->SR & SPI_SR_TXE) == 0) { NOP(); }
  spi->DR = data;

  while((spi->SR & SPI_SR_RXNE) == 0) { NOP(); }
  return spi->DR & 0xff;
}
