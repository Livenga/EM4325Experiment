/** 9 System configuration controller RM0451 p.208 */

#ifndef _SYSCFG_H
#define _SYSCFG_H

#include <stdint.h>
#include "io.h"

#define SYSCFG_ADDRESS (0x00000000)
#define SYSCFG ((syscfg_t *)SYSCFG_ADDRESS)

typedef volatile struct syscfg_t syscfg_t;

struct syscfg_t {
  _IO uint32_t CFGR1;
  _IO uint32_t CFGR2;
  _IO uint32_t EXTICR1;
  _IO uint32_t EXTICR2;
  _IO uint32_t EXTICR3;
  _IO uint32_t EXTICR4;

  _RO uint32_t _reserved0[2];

  _IO uint32_t CFGR3;
};

/** SYSCFG memory remap register (SYSCFG_CFGR1)
 * Address offset: 0x00
 * Reset value: 0x0000 0000
*/
#define SYSCFG_CFGR1_BOOT_MODE (0x00000300)
#define SYSCFG_CFGR1_MEM_MODE  (0x00000003)

#define SYSCFG_CFGR1_BOOT_MODE_MAIN_FLASH    (0x00000000)
#define SYSCFG_CFGR1_BOOT_MODE_SYSTEM_FLASH  (0x00000100)
#define SYSCFG_CFGR1_BOOT_MODE_RESERVED      (0x00000200)
#define SYSCFG_CFGR1_BOOT_MODE_EMBEDDED_SRAM (0x00000300)

#define SYSCFG_CFGR1_MEM_MODE_MAIN_FLASH    (0x00000000)
#define SYSCFG_CFGR1_MEM_MODE_SYSTEM_FLASH  (0x00000001)
#define SYSCFG_CFGR1_MEM_MODE_RESERVED      (0x00000002)
#define SYSCFG_CFGR1_MEM_MODE_EMBEDDED_SRAM (0x00000003)


/** SYSCFG peripheral mode configuration register (SYSCFG_CFGR2)
 * Address offset: 0x04
 * Reset value: 0x0000 0001
 */
#define SYSCFG_CFGR2_FWDIS (0x00000001)


/** Reference control and status register (SYSCFG_CFGR3)
 * Address offset: 0x20
 * Reset value: 0x0000 0000
 */
#define SYSCFG_CFGR3_REF_LOCK          (0x80000000)
#define SYSCFG_CFGR3_VREFINT_RDYF      (0x40000000)
#define SYSCFG_CFGR3_ENBUF_VREFINT_ADC (0x00000100)
#define SYSCFG_CFGR3_SEL_VREF_OUT      (0x00000030)
#define SYSCFG_CFGR3_EN_VREFINT        (0x00000001)

#define SYSCFG_CFGR3_SEL_VREF_OUT_NO_PAD_CONNECTED (0x00000000)
#define SYSCFG_CFGR3_SEL_VREF_OUT_PB0_CONNECTED    (0x00000010)
#define SYSCFG_CFGR3_SEL_VREF_OUT_PB1_CONNECTED    (0x00000020)
#define SYSCFG_CFGR3_SEL_VREF_OUT_PB2_CONNECTED    (0x00000030)


/** SYSCFG external interrupt configuration register 1 (SYSCFG_EXTICR1)
 * Address offset: 0x08
 * Reset value: 0x0000 0000
 */
#define SYSCFG_EXTICR1_EXTI3 (0x0000f000)
#define SYSCFG_EXTICR1_EXTI2 (0x00000f00)
#define SYSCFG_EXTICR1_EXTI1 (0x000000f0)
#define SYSCFG_EXTICR1_EXTI0 (0x0000000f)


/** SYSCFG external interrupt configuration register 2
 * Address offset: 0x0c
 * Reset value: 0x0000 0000
 */
#define SYSCFG_EXTICR3_EXTI7 (0x0000f000)
#define SYSCFG_EXTICR3_EXTI6 (0x00000f00)
#define SYSCFG_EXTICR3_EXTI5 (0x000000f0)
#define SYSCFG_EXTICR3_EXTI4 (0x0000000f)


/** SYSCFG external interrupt configuration register 3
 * Address offset: 0x10
 * Reset value: 0x0000 0000
 */
#define SYSCFG_EXTICR4_EXTI15 (0x0000f000)
#define SYSCFG_EXTICR4_EXTI14 (0x00000f00)
#define SYSCFG_EXTICR4_EXTI13 (0x000000f0)
#define SYSCFG_EXTICR4_EXTI12 (0x0000000f)

#endif
