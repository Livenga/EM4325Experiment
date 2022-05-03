#ifndef _MPL1151A_H
#define _MPL1151A_H

#include <stdint.h>

#define MPL1151A_CONVERT (0x24)

#define MPL1151A_PADC_MSB_COMMAND (0x80)
#define MPL1151A_PADC_LSB_COMMAND (0x82)
#define MPL1151A_TADC_MSB_COMMAND (0x84)
#define MPL1151A_TADC_LSB_COMMAND (0x86)

#define MPL1151A_A0_MSB_COMMAND (0x88)
#define MPL1151A_A0_LSB_COMMAND (0x8a)
#define MPL1151A_B1_MSB_COMMAND (0x8c)
#define MPL1151A_B1_LSB_COMMAND (0x8e)
#define MPL1151A_B2_MSB_COMMAND (0x90)
#define MPL1151A_B2_LSB_COMMAND (0x92)
#define MPL1151A_C12_MSB_COMMAND (0x94)
#define MPL1151A_C12_LSB_COMMAND (0x96)


struct mpl1151_coefficient_t {
  float a0;
  float b1;
  float b2;
  float c12;
};


extern const struct mpl1151_coefficient_t *mpl1151a_init(void);
extern float mpl1151a_get_pressure(void);

#endif
