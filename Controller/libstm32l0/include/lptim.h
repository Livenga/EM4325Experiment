/** 16 Low-power timer (LPTIM) RM0451 p.423 */

#ifndef _LPTIM_H
#define _LPTIME_H

#include <stdint.h>
#include "io.h"

#define LPTIM1_ADDR (0x40007c00)
#define LPTIM1 ((lptim_t *)LPTIM1_ADDR)


typedef volatile struct lptim_t lptim_t;

struct lptim_t {
  _RO uint32_t ISR;
  _IO uint32_t ICR;
  _IO uint32_t IER;
  _IO uint32_t CFGR;
  _IO uint32_t CR;
  _IO uint32_t CMP;
  _IO uint32_t ARR;
  _RO uint32_t CNT;
};

/** LPTIM interrupt and status register (LPTIM_ISR)
 * Address offset: 0x00
 * Reset value: 0x0000 0000
 */
#define LPTIM_ISR_DOWN    (0x00000040)
#define LPTIM_ISR_UP      (0x00000020)
#define LPTIM_ISR_ARROK   (0x00000010)
#define LPTIM_ISR_CMPOK   (0x00000008)
#define LPTIM_ISR_EXTTRIG (0x00000004)
#define LPTIM_ISR_ARRM    (0x00000002)
#define LPTIM_ISR_CMPM    (0x00000001)


/** LPTIM interrupt clear register (LPTIM_ICR)
 * Address offset: 0x04
 * Reset value: 0x0000 0000
 */
#define LPTIM_ICR_DOWNCF    (0x00000040)
#define LPTIM_ICR_UPCF      (0x00000020)
#define LPTIM_ICR_ARROKCF   (0x00000010)
#define LPTIM_ICR_CMPOKCF   (0x00000008)
#define LPTIM_ICR_EXTTRIGCF (0x00000004)
#define LPTIM_ICR_ARRMCF    (0x00000002)
#define LPTIM_ICR_CMPMCF    (0x00000001)


/** LPTIM interupt enable register (LPTIM_IER)
 * Address offset: 0x08
 * Reset value: 0x0000 0000
 */
#define LPTIM_IER_DOWNIE    (0x00000040)
#define LPTIM_IER_UPIE      (0x00000020)
#define LPTIM_IER_ARROKIE   (0x00000010)
#define LPTIM_IER_CMPOKIE   (0x00000008)
#define LPTIM_IER_EXTTRIGIE (0x00000004)
#define LPTIM_IER_ARRMIE    (0x00000002)
#define LPTIM_IER_CMPMIE    (0x00000001)


/** LPTIM configuration register (LPTIM_CFGR)
 * Address offset: 0x0c
 * Reset value: 0x0000 0000
 */
#define LPTIM_CFGR_ENC       (0x01000000)
#define LPTIM_CFGR_COUNTMODE (0x00800000)
#define LPTIM_CFGR_PRELOAD   (0x00400000)
#define LPTIM_CFGR_WAVPOL    (0x00200000)
#define LPTIM_CFGR_WAVE      (0x00100000)
#define LPTIM_CFGR_TIMEOUT   (0x00080000)
#define LPTIM_CFGR_TRIGEN    (0x00060000)
#define LPTIM_CFGR_TRIGSEL   (0x0000e000)
#define LPTIM_CFGR_PRESC     (0x00000e00)
#define LPTIM_CFGR_TRGFLT    (0x000000c0)
#define LPTIM_CFGR_CKFLT     (0x00000018)
#define LPTIM_CFGR_CKPOL     (0x00000006)
#define LPTIM_CFGR_CKSEL     (0x00000001)

// Trigger enable and polarity
#define LPTIM_CFGR_TRIGEN_SOFTWARE_TRIGGER (0x00000000)
#define LPTIM_CFGR_TRIGEN_RISING_EDGE      (0x00020000)
#define LPTIM_CFGR_TRIGEN_FALLING_EDGE     (0x00040000)
#define LPTIM_CFGR_TRIGEN_BOTH_EDGES       (0x00060000)

// Trigger selector
#define LPTIM_CFGR_TRIGSEL_TRIG0 (0x00000000)
#define LPTIM_CFGR_TRIGSEL_TRIG1 (0x00002000)
#define LPTIM_CFGR_TRIGSEL_TRIG2 (0x00004000)
#define LPTIM_CFGR_TRIGSEL_TRIG3 (0x00006000)
#define LPTIM_CFGR_TRIGSEL_TRIG4 (0x00008000)
#define LPTIM_CFGR_TRIGSEL_TRIG5 (0x0000a000)
#define LPTIM_CFGR_TRIGSEL_TRIG6 (0x0000c000)
#define LPTIM_CFGR_TRIGSEL_TRIG7 (0x0000e000)

// Clock prescaler
#define LPTIM_CFGR_PRESC_PER_1   (0x00000000)
#define LPTIM_CFGR_PRESC_PER_2   (0x00000200)
#define LPTIM_CFGR_PRESC_PER_4   (0x00000400)
#define LPTIM_CFGR_PRESC_PER_8   (0x00000600)
#define LPTIM_CFGR_PRESC_PER_16  (0x00000800)
#define LPTIM_CFGR_PRESC_PER_32  (0x00000a00)
#define LPTIM_CFGR_PRESC_PER_64  (0x00000c00)
#define LPTIM_CFGR_PRESC_PER_128 (0x00000e00)

// Configuration digital filter for trigger
#define LPTIM_CFGR_TRGFLT_ANY_TRIGGER   (0x00000000)
#define LPTIM_CFGR_TRGFLT_LEAST_2_CLOCK (0x00000040)
#define LPTIM_CFGR_TRGFLT_LEAST_4_CLOCK (0x00000080)
#define LPTIM_CFGR_TRGFLT_LEAST_8_CLOCK (0x000000c0)

// Configuration digital filter for external clock
#define LPTIM_CFGR_CKFLT_ANY_TRIGGER   (0x00000000)
#define LPTIM_CFGR_CKFLT_LEAST_2_CLOCK (0x00000040)
#define LPTIM_CFGR_CKFLT_LEAST_4_CLOCK (0x00000080)
#define LPTIM_CFGR_CKFLT_LEAST_8_CLOCK (0x000000c0)

// Clock Polarity
#define LPTIM_CFGR_CKPOL_MODE1       (0x00000000)
#define LPTIM_CFGR_CKPOL_MODE2       (0x00000002)
#define LPTIM_CFGR_CKPOL_MODE3       (0x00000004)
#define LPTIM_CFGR_CKPOL_NOT_ALLOWED (0x00000006)


/** LPTIM control register (LPTIM_CR)
 * Address offset: 0x10
 * Reset value: 0x0000 0000
 */
#define LPTIM_CR_CNTSTRT (0x00000004)
#define LPTIM_CR_SNGSTRT (0x00000002)
#define LPTIM_CR_ENABLE  (0x00000001)


/** LPTIM compare register (LPTIM_CMP)
 * Address offset: 0x14
 * Reset value: 0x0000 0000
 */
#define LPTIM_CMP_CMP (0x0000ffff)


/** LPTIM autoreload register(LPTIM_ARR)
 * Address offset: 0x18
 * Reset value: 0x0000 0001
 */
#define LPTIM_ARR_ARR (0x0000ffff)


/** LPTIM counter register (LPTIM_CNT)
 * Address offset: 0x1c
 * Reset value: 0x0000 0000
 */
#define LPTIM_CNT_CNT (0x0000ffff)

#endif
