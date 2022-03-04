/** Low-power universal asynchronous receiver transmitter
 * PM0451 p.683
 */

#ifndef _LPUART_H
#define _LPUART_H

#include <stdint.h>
#include "io.h"

#define LPUART_ADDR (0x40004800)
#define LPUART1 ((volatile struct lpuart_t *)LPUART_ADDR)

struct lpuart_t {
  _IO uint32_t CR1;
  _IO uint32_t CR2;
  _IO uint32_t CR3;
  _IO uint32_t BRR;

  _RO uint32_t reserved0[2];

  _IO uint32_t RQR;
  _RO uint32_t ISR;
  _IO uint32_t ICR;
  _RO uint32_t RDR;
  _IO uint32_t TDR;
};

/** Control register 1 (CR1)
 * Offset: 0x0000 0000
 * Reset value: 0x0000 0000
 */
#define LPUART_CR1_M1     (0x10000000)
#define LPUART_CR1_DEAT   (0x03e00000)
#define LPUART_CR1_DEDT   (0x001f0000)
#define LPUART_CR1_CMIE   (0x00004000)
#define LPUART_CR1_MME    (0x00002000)
#define LPUART_CR1_M0     (0x00001000)
#define LPUART_CR1_WAKE   (0x00000800)
#define LPUART_CR1_PCE    (0x00000400)
#define LPUART_CR1_PS     (0x00000200)
#define LPUART_CR1_PEIE   (0x00000100)
#define LPUART_CR1_TXEIE  (0x00000080)
#define LPUART_CR1_TCIE   (0x00000040)
#define LPUART_CR1_RXNEIE (0x00000020)
#define LPUART_CR1_IDLEIE (0x00000010)
#define LPUART_CR1_TE     (0x00000008)
#define LPUART_CR1_RE     (0x00000004)
#define LPUART_CR1_UESM   (0x00000002)
#define LPUART_CR1_UE     (0x00000001)

/** Control register 2 (CR2)
 * Offset: 0x0004
 * Reset value: 0x0000 0000
 */
#define LPUART_CR2_ADD      (0xff000000)
#define LPUART_CR2_MSBFIRST (0x00080000)
#define LPUART_CR2_DATAINV  (0x00040000)
#define LPUART_CR2_TXINV    (0x00020000)
#define LPUART_CR2_RXINV    (0x00010000)
#define LPUART_CR2_SWAP     (0x00008000)
#define LPUART_CR2_STOP     (0x00003000)
#define LPUART_CR2_ADDM7    (0x00000010)

/** Control register 3 (CR3)
 * Offset: 0x0008
 * Reset value: 0x0000 0000
 */
#define LPUART_CR3_UCESM  (0x00800000)
#define LPUART_CR3_WUFIE  (0x00400000)
#define LPUART_CR3_WUS    (0x00300000)
#define LPUART_CR3_DEP    (0x00008000)
#define LPUART_CR3_DEM    (0x00004000)
#define LPUART_CR3_DDRE   (0x00002000)
#define LPUART_CR3_OVRDIS (0x00001000)
#define LPUART_CR3_CTSIE  (0x00000400)
#define LPUART_CR3_CTSE   (0x00000200)
#define LPUART_CR3_RTSE   (0x00000100)
#define LPUART_CR3_DMAT   (0x00000080)
#define LPUART_CR3_DMAR   (0x00000040)
#define LPUART_CR3_HDSEL  (0x00000008)
#define LPUART_CR3_EIE    (0x00000001)

/** Baud rate register (BRR)
 * Offset: 0x000c
 * Reset value: 0x0000 0000
 */
#define LPUART_BRR_BRR (0x000fffff)

/** Request register (RQR)
 * Offset: 0x0018
 * Reset value: 0x0000 0000
 */
#define LPUART_RQR_RXFRQ (0x00000008)
#define LPUART_RQR_MMRQ  (0x00000004)
#define LPUART_RQR_SBKRQ (0x00000002)

/** Interrupt & status register (ISR)
 * Offset: 0x001c
 * Reset value: 0x0000 00c0
 */
#define LPUART_ISR_REACK (0x00400000)
#define LPUART_ISR_TEACK (0x00200000)
#define LPUART_ISR_WUF   (0x00100000)
#define LPUART_ISR_RWU   (0x00080000)
#define LPUART_ISR_SBKF  (0x00040000)
#define LPUART_ISR_CMF   (0x00020000)
#define LPUART_ISR_BUSY  (0x00010000)
#define LPUART_ISR_CTS   (0x00000400)
#define LPUART_ISR_CTSIF (0x00000200)
#define LPUART_ISR_TXE   (0x00000080)
#define LPUART_ISR_TC    (0x00000040)
#define LPUART_ISR_RXNE  (0x00000020)
#define LPUART_ISR_IDLE  (0x00000010)
#define LPUART_ISR_ORE   (0x00000008)
#define LPUART_ISR_NF    (0x00000004)
#define LPUART_ISR_FE    (0x00000002)
#define LPUART_ISR_PE    (0x00000001)


/** Interrupt flag clear register (ICR)
 * Offset: 0x0020
 * Reset value: 0x0000 0000
 */
#define LPUART_ICR_WUCF   (0x00100000)
#define LPUART_ICR_CMCF   (0x00020000)
#define LPUART_ICR_CTSCF  (0x00000200)
#define LPUART_ICR_TCCF   (0x00000040)
#define LPUART_ICR_IDLECF (0x00000010)
#define LPUART_ICR_ORECF  (0x00000008)
#define LPUART_ICR_NCF    (0x00000004)
#define LPUART_ICR_FECF   (0x00000002)
#define LPUART_ICR_PECF   (0x00000001)

/** Receive data register (RDR)
 * Offset: 0x0024
 * Reset value: Undefined
 */
#define LPUART_RDR_RDR (0x000000ff)

/** Transmit data register (TDR)
 * Offset: 0x0028
 * Reset value: Undefined
 */
#define LPUART_TDR_TDR (0x000000ff)
#endif
