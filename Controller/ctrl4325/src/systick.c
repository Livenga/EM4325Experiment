#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/mpl1151a.h"
#include "../include/em4325.h"

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

#if 0
  struct em4325_sensor_data_t sensor_data;
  if(_is_em4325_ready == 0) {
    uint16_t status = em4325_request_status();

#if 1
    lpuart_print((struct lpuart_t *)LPUART1, "# Request status: 0x");
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((status >> 12) & 0xf));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((status >> 8) & 0xf));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((status >> 4) & 0xf));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((status >> 0) & 0xf));
    lpuart_println((struct lpuart_t *)LPUART1, NULL);
#endif

    if(status != 0 && (status & 0b11) == 0) {
      _is_em4325_ready = 1;
    }
  } else {
#if 1
    memset((void *)&sensor_data, 0, sizeof(struct em4325_sensor_data_t));

    int8_t response = em4325_get_sensordata(1, &sensor_data);
    lpuart_print((struct lpuart_t *)LPUART1, "# Get sensor data Status: 0x");
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((sensor_data.status >> 12) & 0xf));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((sensor_data.status >> 8) & 0xf));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((sensor_data.status >> 4) & 0xf));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((sensor_data.status >> 0) & 0xf));
    lpuart_println((struct lpuart_t *)LPUART1, NULL);

    lpuart_print((struct lpuart_t *)LPUART1, "# Sensor Data: 0x");

    int8_t i;
    for(i = 0; i < 4; ++i) {
      uint8_t _segment = (sensor_data.sensor >> (8 * (3 - i))) & 0xff;

      lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((_segment >> 4) & 0xf));
      lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((_segment >> 0) & 0xf));
    }
    lpuart_println((struct lpuart_t *)LPUART1, NULL);
#endif
  }
#endif
}
