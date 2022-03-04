#ifndef _MPU_H
#define _MPU_H

#include <stdint.h>
#include "io.h"

#define MPU_ADDR (0xe000ed90)
#define MPU ((volatile struct mpu_t *)MPU_ADDR)

struct mpu_t {
  _RO uint32_t TYPE;
  _IO uint32_t CTRL;
  _IO uint32_t RNR;
  _IO uint32_t RBAR;
  _IO uint32_t RASR;
};

#endif
