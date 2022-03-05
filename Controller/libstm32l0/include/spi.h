/** 23 Serial peripheral interface (SPI) RM0451 p.684
 */

#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>
#include "io.h"

#define SPI1_ADDR (0x40013000)
#define SPI1 ((volatile spi_t *)SPI1_ADDR)


struct spi_t {
  _IO uint32_t CR1;
  _IO uint32_t CR2;
  _IO uint32_t SR;
  _IO uint32_t DR;
  _IO uint32_t CRCPR;
  _RO uint32_t RXCRCR;
  _RO uint32_t TXCRCR;
};


/** SPI control register 1 (SPI_CR1)
 * Offset: 0x0000
 * Reset value: 0x0000 0000
 */
#define SPI_CR1_BIDIMODE (0x00008000)
#define SPI_CR1_BIDIOE   (0x00004000)
#define SPI_CR1_CRCEN    (0x00002000)
#define SPI_CR1_CRCNEXT  (0x00001000)
#define SPI_CR1_DFF      (0x00000800)
#define SPI_CR1_RXONLY   (0x00000400)
#define SPI_CR1_SSM      (0x00000200)
#define SPI_CR1_SSI      (0x00000100)
#define SPI_CR1_LSBFIRST (0x00000080)
#define SPI_CR1_SPE      (0x00000040)
#define SPI_CR1_BR       (0x00000038)
#define SPI_CR1_MSTR     (0x00000004)
#define SPI_CR1_CPOL     (0x00000002)
#define SPI_CR1_CPHA     (0x00000001)

/** SPI control register 2 (SPI_CR2)
 * Offset: 0x0004
 * Reset value: 0x0000 0000
 */
#define SPI_CR2_TXEIE   (0x00000080)
#define SPI_CR2_RXNEIE  (0x00000040)
#define SPI_CR2_ERRIE   (0x00000020)
#define SPI_CR2_FRF     (0x00000010)
#define SPI_CR2_SSOE    (0x00000004)
#define SPI_CR2_TXDMAEN (0x00000002)
#define SPI_CR2_RXDMAEN (0x00000001)

/** SPI status register (SPI_SR)
 * Offset: 0x0008
 * Reset value: 0x0000 0002
 */
#define SPI_SR_FRF    (0x00000100)
#define SPI_SR_BSY    (0x00000080)
#define SPI_SR_OVR    (0x00000040)
#define SPI_SR_MODF   (0x00000020)
#define SPI_SR_CRCERR (0x00000010)
#define SPI_SR_TXF    (0x00000002)
#define SPI_SR_RXNF   (0x00000001)

/** SPI data register (SPI_DR)
 * Offset: 0x000c
 * Reset value: 0x0000 0000
 */
#define SPI_DR_DR (0x0000ffff)

/** SPI CRC polynomial register (SPI_CRCPR)
 * Offset: 0x0010
 * Reset value: 0x0000 0007
 */
#define SPI_CRCPR_CRCPOLY (0x0000ffff)

/** SPI RX CRC register (SPI_RXCRCR)
 * Offset: 0x0014
 * Reset value: 0x0000 0000
 */
#define SPI_RXCRCR_RXCRC (0x0000ffff)

/** SPI TX CRC register (SPI_TXCRCR)
 * Offset: 0x0018
 * Reset value: 0x0000 0000
 */
#define SPI_TXCRCR_TXCRC (0x0000ffff)
#endif
