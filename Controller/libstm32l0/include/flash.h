#ifndef _FLASH_H
#define _FLASH_H

#define FLASH_ADDR (0x40022000)
#define FLASH ((volatile struct flash_t *)FLASH_ADDR)

#include <stdint.h>
#include "io.h"


struct flash_t {
  _IO uint32_t ARC;
  _IO uint32_t PECR;
  _IO uint32_t PDKEYR;
  _IO uint32_t PKEYR;
  _IO uint32_t PRGKEYR;
  _IO uint32_t OPTKEYR;
  _IO uint32_t SR;
  _RO uint32_t OPTR;
  _RO uint32_t WRPROT1;
  _RO uint32_t WRPROT2;
};


/** Access control register (ACR)
 * Offset; 0x0000
 * Reset value: 0x0000 0000
 */
#define FLASH_ACR_PRE_READ  (0x00000040)
#define FLASH_ACR_DISAB_BUF (0x00000020)
#define FLASH_ACR_RUN_PD    (0x00000010)
#define FLASH_ACR_SLEEP_PD  (0x00000008)
#define FLASH_ACR_PRFTEN    (0x00000002)
#define FLASH_ACR_LATENCY   (0x00000001)


/** Program and erase control register (PECR)
 * Offset: 0x0004
 * Reset value: 0x0000 0007
 */
#define FLASH_PECR_NZDISABLE  (0x00800000)
#define FLASH_PECR_OBL_LAUNCH (0x00040000)
#define FLASH_PECR_FRRIF      (0x00020000)
#define FLASH_PECR_EOPIE      (0x00010000)
#define FLASH_PECR_FPRG       (0x00000400)
#define FLASH_PECR_ERASE      (0x00000200)
#define FLASH_PECR_FIX        (0x00000100)
#define FLASH_PECR_DATA       (0x00000010)
#define FLASH_PECR_PROG       (0x00000008)
#define FLASH_PECR_OPT_LOCK   (0x00000004)
#define FLASH_PECR_PRG_LOCK   (0x00000002)
#define FLASH_PECR_PE_LOCK    (0x00000001)

/** Power-down key register (PDKEYR)
 * Offset: 0x0008
 * Reset value: 0x0000 0000
 */
#define FLASH_PDKEYR_FLASH_PDKEYR (0xffffffff)

/** PECR unlock key register (PEKEYR)
 * Offset: 0x000c
 * Reset value: 0x0000 0000
 */
#define FLASH_PEKEYR_FLASH_PEKEYR (0xffffffff)

/** Program and erase key register (PRGKEYR)
 * Offset: 0x0010
 * Reset value: 0x0000 0000
 */
#define FLASH_PRGKEYR_FLASH_PRGKEYR (0xffffffff)

/** Option bytes unlock key register (OPTKEYR)
 * Offset: 0x0014
 * Reset value: 0x0000 0000
 */
#define FLASH_OPTKEYR_FLASH_OPTKEYR (0xffffffff)

/** Status regsiter (SR)
 * Offset: 0x0018
 * Reset value: 0x0000 000c
 */
#define FLASH_SR_FWWERR     (0x00020000)
#define FLASH_SR_NOTZEROERR (0x00010000)
#define FLASH_SR_RDERR      (0x00002000)
#define FLASH_SR_OPTVERR    (0x00000800)
#define FLASH_SR_SIZER      (0x00000400)
#define FLASH_SR_PGAERR     (0x00000200)
#define FLASH_SR_WRPERR     (0x00000100)
#define FLASH_SR_READY      (0x00000008)
#define FLASH_SR_ENDHV      (0x00000004)
#define FLASH_SR_EOP        (0x00000002)
#define FLASH_SR_BSY        (0x00000001)

/** Option bytes register (OPTR)
 * Offset: 0x001c
 * Reset value: 0xX0XX 0XXX
 */
#define FLASH_OPTR_NBOOT1     (0x80000000)
#define FLASH_OPTR_NBOOT0     (0x40000000)
#define FLASH_OPTR_NBOOT_SEL  (0x20000000)
#define FLASH_OPTR_NRST_STDBY (0x00400000)
#define FLASH_OPTR_NRST_STOP  (0x00200000)
#define FLASH_OPTR_WDG_SW     (0x00100000)
#define FLASH_OPTR_BOR_LEV    (0x000f0000)
#define FLASH_OPTR_WPRMOD     (0x00000100)
#define FLASH_OPTR_RDPROT     (0x000000ff)

/** Write protection regsiter 1 (WRPROT1)
 * Offset: 0x0020
 * Reset value: 0xXXXX XXXX
 */
#define FLASH_WRPROT1_WRPROT1 (0xffffffff)

/** Write protection register 2 (WRPROT2)
 * Offset: 0x0080
 * Reset value: 0x0000 XXXX
 */
#define FLASH_WRPROT2_WRPROT2 (0x0000ffff)
#endif
