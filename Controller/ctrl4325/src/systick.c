#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/mpl1151a.h"
#include "../include/em4325.h"

#define __DEBUG__
#define HEX2CHR(u8) \
  (((u8) >= 0x0a) ? (((u8) - 0x0a) + 'A') : ((u8) + '0'))

extern void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c);
extern void lpuart_print(
    struct lpuart_t *lpuart,
    const char *str);
extern void lpuart_println(
    struct lpuart_t *lpuart,
    const char *str);

extern void print_float_value(float value, size_t n);
extern void print_to_hex(uint32_t value, size_t size);

static uint8_t _is_bright = 0;
static uint8_t _is_em4325_ready = 0;


void SysTick_handler(void) {
#if 1
  if(_is_bright) {
    GPIOA->BSRR = (1 <<  26);
  } else {
    GPIOA->BSRR = (1 <<  10);
  }

  float pressure = mpl1151a_get_pressure();
  lpuart_print((struct lpuart_t *)LPUART1, "Pressure = ");
  print_float_value(pressure, 3);
  lpuart_println((struct lpuart_t *)LPUART1, "[kPa]");

  _is_bright ^= 1;
#endif

#if 1
  uint16_t em4325_status = em4325_request_status();

#ifdef __DEBUG__
  lpuart_print((struct lpuart_t *)LPUART1, "# EM4325 Current Status\t");
  print_to_hex(em4325_status, sizeof(uint16_t));
#endif

  if((em4325_status & 0x03) == 0
      && (em4325_status & 0x38) == 0x38) {
    uint16_t result_boot = em4325_boot();
#ifdef __DEBUG__
    lpuart_print((struct lpuart_t *)LPUART1, "\tExecute EM4325 Boot command\t");
    print_to_hex(result_boot, sizeof(uint16_t));
#endif
  }

  struct em4325_sensor_data_t sensor_data;
  memset((void *)&sensor_data, 0, sizeof(struct em4325_sensor_data_t));

  int8_t response = em4325_get_sensordata(1, &sensor_data);
  lpuart_print((struct lpuart_t *)LPUART1, "\tGet sensor data Status: 0x");
  print_to_hex(sensor_data.status, sizeof(uint16_t));

  lpuart_print((struct lpuart_t *)LPUART1, "\t\tSensor Data: ");
  float temp = ((((int16_t)(sensor_data.sensor >> 16) & 0x01ff) << 7) * .25f) / 128.f;
  print_float_value(temp, 2);
  lpuart_println((struct lpuart_t *)LPUART1, NULL);

  lpuart_print((struct lpuart_t *)LPUART1, "\t\tUTC Data: 0x");
  print_to_hex(sensor_data.utc, sizeof(uint32_t));
#endif
}
