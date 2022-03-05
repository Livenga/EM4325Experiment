/** 14 General-purpose timer (TIM2) RM0451 p.302 */


#ifndef _TIM2_H
#define _TIM2_H

#include <stdint.h>
#include "io.h"

#define TIM2_ADD (0x40000000)
#define TIM2 ((volatile struct tim2_t *)TIM2_ADD)

struct tim2_t {
  _IO uint32_t CR1;
  _IO uint32_t CR2;
  _IO uint32_t SMCR;
  _IO uint32_t DIER;
  _IO uint32_t SR;
  _IO uint32_t EGR;
  _IO uint32_t CCMR1;
  _IO uint32_t CCMR2;
  _IO uint32_t CCER;
  _IO uint32_t CNT;
  _IO uint32_t PSC;
  _IO uint32_t ARR;

  _RO uint32_t _reserved0;

  _IO uint32_t CCR1;
  _IO uint32_t CCR2;
  _IO uint32_t CCR3;
  _IO uint32_t CCR4;

  _RO uint32_t _reserved1;

  _IO uint32_t DCR;
  _IO uint32_t DMAR;
  _IO uint32_t OR;
};


/** TIMx control register (CR1)
 * Offset: 0x0000
 * Reset value: 0x0000 0000
 */
#define TIM2_CR1_CKD  (0x00000300)
#define TIM2_CR1_ARPE (0x00000080)
#define TIM2_CR1_CMS  (0x00000060)
#define TIM2_CR1_DIR  (0x00000010)
#define TIM2_CR1_OPM  (0x00000008)
#define TIM2_CR1_URS  (0x00000004)
#define TIM2_CR1_UDIS (0x00000002)
#define TIM2_CR1_CEN  (0x00000001)


/** TIMx Control register 2 (TIMx_CR2)
 * Offset: 0x0004
 * Reset value: 0x0000 0000
 */
#define TIM2_CR2_TI1S (0x00000080)
#define TIM2_CR2_MMS  (0x00000070)
#define TIM2_CR2_CCDS (0x00000008)

/** TIMx slave mode control register (TIMx_SMCR)
 * Offset: 0x0008
 * Reset value: 0x0000 0000
 */
#define TIM2_SMCR_ETP  (0x00008000)
#define TIM2_SMCR_ECE  (0x00004000)
#define TIM2_SMCR_ETPS (0x00003000)
#define TIM2_SMCR_ETF  (0x00000f00)
#define TIM2_SMCR_MSM  (0x00000080)
#define TIM2_SMCR_TS   (0x00000070)
#define TIM2_SMCR_SMS  (0x00000007)

/** TIMx DMA/Interrupt enable register (TIMx_DIER)
 * Offset: 0x000c
 * Reset value: 0x0000 0000
 */
#define TIM2_DIER_TDE   (0x00004000)
#define TIM2_DIER_CC4DE (0x00001000)
#define TIM2_DIER_CC3DE (0x00000800)
#define TIM2_DIER_CC2DE (0x00000400)
#define TIM2_DIER_CC1DE (0x00000200)
#define TIM2_DIER_UDE   (0x00000100)
#define TIM2_DIER_TIE   (0x00000040)
#define TIM2_DIER_CC4IE (0x00000010)
#define TIM2_DIER_CC3IE (0x00000008)
#define TIM2_DIER_CC2IE (0x00000004)
#define TIM2_DIER_CC1IE (0x00000002)
#define TIM2_DIER_UIE   (0x00000001)

/** TIMx status register (TIMx_SR)
 * Offset: 0x0010
 * Reset value: 0x0000 0000
 */
#define TIM2_SR_CC4OF (0x00001000)
#define TIM2_SR_CC3OF (0x00000800)
#define TIM2_SR_CC2OF (0x00000400)
#define TIM2_SR_CC1OF (0x00000200)
#define TIM2_SR_TIF   (0x00000040)
#define TIM2_SR_CC4IF (0x00000010)
#define TIM2_SR_CC3IF (0x00000008)
#define TIM2_SR_CC2IF (0x00000004)
#define TIM2_SR_CC1IF (0x00000002)
#define TIM2_SR_UIF   (0x00000001)

/** TIMx event generate register (TIMx_EGR)
 * Offset: 0x0014
 * Reset value: 0x0000 0000
 */
#define TIM2_EGR_TG   (0x00000100)
#define TIM2_EGR_CC4G (0x00000010)
#define TIM2_EGR_CC3G (0x00000008)
#define TIM2_EGR_CC2G (0x00000004)
#define TIM2_EGR_CC1G (0x00000002)
#define TIM2_EGR_UG   (0x00000001)

/** TIMx capture/compare mode register 1 (TIMx_CCMR1)
 * Offset: 0x0018
 * Reset value: 0x0000 0000
 */

// TODO
// Output compare mode
// Input capture mode

/** TIMx capture/compare mode register 2 (TIMx_CCMR2)
 * Offset: 0x001c
 * Reset value: 0x0000 0000
 */

// TODO

/** TIMx capture/compare enable register (TIMx_CCER)
 * Offset: 0x0020
 * Reset value: 0x0000 0000
 */
#define TIM2_CCER_CC4NP (0x00008000)
#define TIM2_CCER_CC4P  (0x00002000)
#define TIM2_CCER_CC4E  (0x00001000)
#define TIM2_CCER_CC3NP (0x00000800)
#define TIM2_CCER_CC3P  (0x00000200)
#define TIM2_CCER_CC3E  (0x00000100)
#define TIM2_CCER_CC2NP (0x00000080)
#define TIM2_CCER_CC2P  (0x00000020)
#define TIM2_CCER_CC2E  (0x00000010)
#define TIM2_CCER_CC1NP (0x00000008)
#define TIM2_CCER_CC1P  (0x00000002)
#define TIM2_CCER_CC1E  (0x00000001)

/** TIMx counter (TIMx_CNT)
 * Offset: 0x0024
 * Reset value: 0x0000 0000
 */
#define TIM2_CNT_CNT (0x0000ffff)

/** TIMx prescaler (TIMx_PSC)
 * Offset: 0x0028
 * Reset value: 0x0000 0000
 */
#define TIM2_PSC_PSC (0x0000ffff)

/** TIMx auto-reload register (TIMx_ARR)
 * Offset: 0x002c
 * Reset value: 0x0000 0000
 */
#define TIM2_ARR_ARR (0x0000ffff)

/** TIMx capture/compare register 1 (TIMx_CCR1)
 * Offset: 0x0034
 * Reset value: 0x0000 0000
 */
#define TIM2_CCR1_CCR1 (0x0000ffff)

/** TIMx capture/compare register 2 (TIMx_CCR2)
 * Offset: 0x0038
 * Reset value: 0x0000 0000
 */
#define TIM2_CCR2_CCR2 (0x0000ffff)

/** TIMx capture/compare register 3 (TIMx_CCR3)
 * Offset: 0x003c
 * Reset value: 0x0000 0000
 */
#define TIM2_CCR3_CCR3 (0x0000ffff)

/** TIMx capture/compare register 4 (TIMx_CCR4)
 * Offset: 0x0040
 * Reset value: 0x0000 0000
 */
#define TIM2_CCR4_CCR4 (0x0000ffff)

/** TIMx DMA control register (TIMx_DCR)
 * Offset: 0x0048
 * Reset value: 0x0000 0000
 */
#define TIM2_DCR_DBL (0x00001f00)
#define TIM2_DCR_DBA (0x0000001f)

/** TIMx DMA address for full transfer (TIMx_DMAR)
 * Offset: 0x004c
 * Reset value: 0x0000 0000
 */
#define TIM2_DMAR_DMAB (0x0000ffff)

/** TIM2 option register (TIM2_OR)
 * Offset: 0x0050
 * Reset value: 0x0000 0000
 */
#define TIM2_OR_RMP     (0x00000018)
#define TIM2_OR_ETR_RMP (0x00000007)

#endif
