#ifndef _MPL115A1_H
#define _MPL115A1_H

#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"

#define MPL115A1_CONVERT (0x24)

#define MPL115A1_PADC_MSB_COMMAND (0x80)
#define MPL115A1_PADC_LSB_COMMAND (0x82)
#define MPL115A1_TADC_MSB_COMMAND (0x84)
#define MPL115A1_TADC_LSB_COMMAND (0x86)

#define MPL115A1_A0_MSB_COMMAND (0x88)
#define MPL115A1_A0_LSB_COMMAND (0x8a)
#define MPL115A1_B1_MSB_COMMAND (0x8c)
#define MPL115A1_B1_LSB_COMMAND (0x8e)
#define MPL115A1_B2_MSB_COMMAND (0x90)
#define MPL115A1_B2_LSB_COMMAND (0x92)
#define MPL115A1_C12_MSB_COMMAND (0x94)
#define MPL115A1_C12_LSB_COMMAND (0x96)


struct mpl115a1_coefficient_t {
  float a0;
  float b1;
  float b2;
  float c12;
};


extern const struct mpl115a1_coefficient_t *mpl115a1_init(struct gpio_t *gpio, uint8_t cs_number);
extern float mpl115a1_get_pressure(void);

#endif
