/** System Control Block PM0223 p.88 */

#ifndef _SCB_H
#define _SCB_H

#include <stdint.h>
#include "io.h"

#define SCB_ADDR (0xe000ed00)
#define SCB ((volatile struct scb_t *)SCB_ADDR)

struct scb_t {
  _RO uint32_t CPUID;
  _IO uint32_t ICSR;
  _IO uint32_t VTOR;
  _IO uint32_t AIRCR;
  _IO uint32_t SCR;
  _RO uint32_t CCR;

  _RO uint32_t _reserved0;

  _IO uint32_t SHPR2;
  _IO uint32_t SHPR3;
};

/** CPUID Register (CPUID)
 * Offset: 0x0000
 * Reset value: 0410cc601
 */
#define SCB_CPUID_IMPLEMENTER  (0xff000000)
#define SCB_CPUID_VARIANT      (0x00f00000)
#define SCB_CPUID_ARCHITECTURE (0x000f0000)
#define SCB_CPUID_PART_NO      (0x0000fff0)
#define SCB_CPUID_REVISION     (0x0000000f)

/** Interrupt Control and State Register (ICSR)
 * Offset: 0x0004
 * Reset value: 0x0000 0000
 */
#define SCB_ICSR_NMIPENDSET  (0x80000000)
#define SCB_ICSR_PENDSVSET   (0x10000000)
#define SCB_ICSR_PENDSVCLR   (0x08000000)
#define SCB_ICSR_PENDSTSET   (0x04000000)
#define SCB_ICSR_PENDSTCLR   (0x02000000)
#define SCB_ICSR_ISRPENDING  (0x00400000)
#define SCB_ICSR_VECTPENDING (0x000ff000)
#define SCB_ICSR_RETOBASE    (0x00000800)
#define SCB_ICSR_VECTACTIVE  (0x000001ff)

/** Vector Table Offset Register (VTOR)
 * Offset: 0x0008
 * Reset value: 0x0000 0000
 */
#define SCB_VTOR_TBLOFF (0xffffff80)

/** Application Interrupt and Reset Control Register (AIRCR)
 * Offset: 0x000c
 * Reset value: 0x0000 0000
 */
#define SCB_AIRCR_VECTKEYSTAT   (0xffff0000)
#define SCB_AIRCR_ENDIANESS     (0x00008000)
#define SCB_AIRCR_SYSRESETREQ   (0x00000004)
#define SCB_AIRCR_VECTCLRACTIVE (0x00000002)

/** System Control Register (SCR)
 * Offset: 0x0010
 * Reset value: 0x0000 0000
 */
#define SCB_SCR_SEVONPEND   (0x00000010)
#define SCB_SCR_UNALIGN_TRP (0x00000008)
#define SCB_SCR_SLEEPDEEP   (0x00000004)
#define SCB_SCR_SLEEPONEXIT (0x00000002)

/** Configuration and Control Register (CCR)
 * Offset: 0x0014
 * Reset value: 0x0000 0204
 */

/** System Handler Priority Register 2 (SHPR2)
 * Offset: 0x001c
 * Reset value: 0x0000 0000
 */
#define SCB_SHPR2_PRI_11 (0xff000000)

/** System Handler Priority Register 3 (SHPR3)
 * Offset: 0x0020
 * Reset value: 0x0000 0000
 */
#define SCB_SHPR3_PRI_15 (0xff000000)
#define SCB_SHPR3_PRI_14 (0x00ff0000)

#endif
