#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define __DEBUG__ 1

#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/asm.h"
#include "../include/spi_ex.h"
#include "../include/em4325.h"
#include "../include/lpuart_ex.h"
#include "../include/digit_util.h"


extern uint16_t spi_communicate(spi_t *spi, uint16_t data);

extern void mdelay16(uint16_t msec);
extern void udelay16(uint16_t msec);


#define HEX2CHR(u8) \
  (((u8) >= 0x0a) ? (((u8) - 0x0a) + 'A') : ((u8) + '0'))


static struct gpio_t *_gpio = NULL;
static uint8_t _cs_number = 0;


/**
 */
void em4325_init(
    struct gpio_t *gpio,
    uint8_t cs) {
  _gpio      = gpio;
  _cs_number = cs;
}

/**
 */
uint16_t em4325_request_status(void) {
  uint32_t recv;
  CS_OFF(_gpio, _cs_number);

  spi_communicate(SPI1, EM4325_REQUEST_STATUS_COMMAND);
  do {
    recv = spi_communicate(SPI1, 0x00);
  } while(recv == 0);

  CS_ON(_gpio, _cs_number);

  return recv;
}

uint16_t em4325_boot(void) {
  uint32_t recv;
  CS_OFF(_gpio, _cs_number);

  spi_communicate(SPI1, EM4325_BOOT_COMMAND);
  do {
    recv = spi_communicate(SPI1, 0x00);
  }while(recv == 0);

  CS_ON(_gpio, _cs_number);

  return recv;
}

/**
 */
int8_t em4325_get_sensordata(
    uint8_t required_new_sample,
    struct em4325_sensor_data_t *p) {
  if(p == NULL)
    return -1;

  CS_OFF(_gpio, _cs_number);

  spi_communicate(
      SPI1,
      (required_new_sample
       ? EM4325_GET_SENSOR_DATA_AFTER_NEW_SAMPLE 
       : EM4325_GET_SENSOR_DATA));

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

  CS_ON(_gpio, _cs_number);

  p->status = status;
  if(response != 0)
    return response;

  memcpy((void *)&p->sensor, (const void *)(buffer + 4), sizeof(uint32_t));
  memcpy((void *)&p->utc, (const void *)(buffer + 0), sizeof(uint32_t));

  return 0;
}

uint16_t em4325_read_word(
    spi_t *spi,
    uint8_t address) {
  CS_OFF(_gpio, _cs_number);

  spi_communicate(spi, 0xe7);
  spi_communicate(spi, address);

  udelay16(25);

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

  CS_ON(_gpio, _cs_number);

  uint16_t data;
  memcpy((void *)&data, (const void *)buffer, sizeof(uint16_t));

  for(int8_t i = 0; i < 4; ++i) {
    int8_t shift_size = 12 - (i * 4);
    uint8_t segment = (data >> shift_size) & 0x0f;
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR(segment));
  }

  return data;
}

/**
 */
uint8_t em4325_write_word(
    spi_t    *spi,
    uint8_t  address,
    uint16_t data) {
  CS_OFF(_gpio, _cs_number);

  spi_communicate(spi, 0xe8);
  spi_communicate(spi, address);
  spi_communicate(spi, (data >> 8) & 0xff);
  spi_communicate(spi, (data >> 0) & 0xff);

  mdelay16(1);

  uint8_t status = 0;
  do {
    status = spi_communicate(spi, 0);
  } while(status == 0);

  CS_ON(_gpio, _cs_number);

#ifdef __DEBUG__
  lpuart_print((struct lpuart_t *)LPUART1, "# Write world response: ");
  print_to_hex(status, sizeof(int16_t));
#endif

  return status;
}
