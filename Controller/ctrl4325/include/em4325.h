#ifndef _EM4325_H
#define _EM4325_H

#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"

#define EM4325_REQUEST_STATUS_COMMAND (0xe0)
#define EM4325_BOOT_COMMAND (0xe1)
#define EM4325_GET_SENSOR_DATA (0xe4)
#define EM4325_GET_SENSOR_DATA_AFTER_NEW_SAMPLE (0xe5)


struct em4325_sensor_data_t {
  uint8_t status;
  uint32_t sensor;
  uint32_t utc;
};


extern void em4325_init(struct gpio_t *gpio, uint8_t cs);

extern uint16_t em4325_request_status(void);
extern uint16_t em4325_boot(void);

extern int8_t em4325_get_sensordata(
    uint8_t required_new_sample,
    struct em4325_sensor_data_t *p);

extern uint16_t em4325_read_word(
    spi_t *spi,
    uint8_t address);

extern uint8_t em4325_write_word(
    spi_t    *spi,
    uint8_t  address,
    uint16_t data);

#endif
