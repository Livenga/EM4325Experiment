#ifndef _EM4325_H
#define _EM4325_H

#include <stdint.h>

struct em4325_sensor_data_t {
  uint8_t status;
  uint32_t sensor;
  uint32_t utc;
};


extern uint16_t em4325_request_status(void);

extern int8_t em4325_get_sensordata(
    uint8_t required_new_sample,
    struct em4325_sensor_data_t *p);

extern void em4325_read_word(
    spi_t *spi,
    uint8_t address);
#endif
