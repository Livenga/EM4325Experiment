/** 6 Power control (PWR) RM0451 p.117 */

#ifndef _PWR_H
#define _PWR_H

#include <stdint.h>
#include "io.h"


#define PWR_ADDR (0x40007000)
#define PWR ((pwr_t *)PWR_ADDR)

typedef volatile struct pwr_t pwr_t;

struct pwr_t {
  _IO uint32_t CR;
  _IO uint32_t CSR;
};


/** PWR power control register (PWR_CR)
 * Offset: 0x0000
 * Reset value: 0x0000 1000
 */
#define PWR_CR_LPDS       (0x00010000)
#define PWR_CR_LPRUN      (0x00004000)
#define PWR_CR_DS_EE_KOFF (0x00002000)
#define PWR_CR_VOS        (0x00001800)
#define PWR_CR_FWU        (0x00000400)
#define PWR_CR_ULP        (0x00000200)
#define PWR_CR_DBP        (0x00000100)
#define PWR_CR_CSBF       (0x00000008)
#define PWR_CR_CWUF       (0x00000004)
#define PWR_CR_PDDS       (0x00000002)
#define PWR_CR_LPSDSR     (0x00000001)

#define PWR_CR_VOS_FORBIDDEN (0x00000000) // forbidden
#define PWR_CR_VOS_1_8V (0x00000800) // 1.8[V] (range 1)
#define PWR_CR_VOS_1_5V (0x00001000) // 1.5[V] (range 2)
#define PWR_CR_VOS_1_2V (0x00001800) // 1.2[V] (range 3)


/** PWR power control/status register (PWR_CSR)
 * Offset: 0x0004
 * Reset value: 0x0000 0008
 */
#define PWR_CSR_EWUP3       (0x00000400)
#define PWR_CSR_EWUP2       (0x00000200)
#define PWR_CSR_EWUP1       (0x00000100)
#define PWR_CSR_REGLPF      (0x00000020)
#define PWR_CSR_VOSF        (0x00000010)
#define PWR_CSR_VREFINTRDYF (0x00000008)
#define PWR_CSR_SBF         (0x00000002)
#define PWR_CSR_WUF         (0x00000001)

#endif
