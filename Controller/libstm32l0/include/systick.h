/**
 * Cortex-M0+ core peripherals PM0223 95 / 110
 * SysTick timer(STK)
 */
#ifndef _SYSTICK_H
#define _SYSTICK_H

#include <stdint.h>
#include "io.h"

#define STK_ADDR (0xe000e010)
#define STK ((volatile struct stk_t *)STK_ADDR)

struct stk_t {
  _IO uint32_t CSR;
  _IO uint32_t RVR;
  _IO uint32_t CVR;
  _RO uint32_t CALIB;
};


/** SysTick Control and Status Register(STK_CSR)
 */
#define STK_CSR_COUNTFLAG (0x00010000)
#define STK_CSR_CLKSOURCE (0x00000004)
#define STK_CSR_TICKINT   (0x00000002)
#define STK_CSR_ENABLE    (0x00000001)

/** SysTick Reload Value Register(STK_RVR)
 */
#define STK_RVR_RELOAD (0x00ffffff)

/** SysTick Current Value Register(STK_CVR)
 */
#define STK_CVR_CURRENT (0x00ffffff)

/** SysTick Calibration value Register(STK_CALIB)
 */
#define STK_CALIB_OREF  (0x80000000)
#define STK_CALIB_SKEW  (0x40000000)
#define STK_CALIB_TENMS (0x00ffffff)

#endif
