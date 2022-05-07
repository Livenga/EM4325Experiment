/** 7.3 RCC registers PM0451 p.158
 */

#ifndef _RCC_H
#define _RCC_H

#include <stdint.h>
#include "io.h"

#define RCC_ADDR (0x40021000)
#define RCC ((volatile struct rcc_t *)RCC_ADDR)

struct rcc_t {
  _IO uint32_t CR;
  _IO uint32_t ICSCR;
  _RO uint32_t reserved0;
  _IO uint32_t CFGR;

  _IO uint32_t CIER;
  _RO uint32_t CIFR;
  _IO uint32_t CICR;
  _IO uint32_t IOPRSTR;

  _IO uint32_t AHBRSTR;
  _IO uint32_t APB2RSTR;
  _IO uint32_t APB1RSTR;
  _IO uint32_t IOPENR;

  _IO uint32_t AHBENR;
  _IO uint32_t APB2ENR;
  _IO uint32_t APB1ENR;
  _IO uint32_t IOPSMEN;

  _IO uint32_t AHBSMENR;
  _IO uint32_t APB2SMENR;
  _IO uint32_t APB1SMENR;
  _IO uint32_t CCIPR;

  _IO uint32_t CSR;
};

/** Clock control register (CR)
 * Offset: 0x0000
 * Reset value: 0x0000 0300
 */
#define RCC_CR_PLLRDY     (0x02000000)
#define RCC_CR_PLLON      (0x01000000)
#define RCC_CR_RTCPRE     (0x00300000)
#define RCC_CR_CSSHSEON   (0x00080000)
#define RCC_CR_HSEBYP     (0x00040000)
#define RCC_CR_HSERDY     (0x00020000)
#define RCC_CR_HSEON      (0x00010000)
#define RCC_CR_MSIRDY     (0x00000200)
#define RCC_CR_MSION      (0x00000100)
#define RCC_CR_HSI16OUTEN (0x00000020)
#define RCC_CR_HSI16DIVF  (0x00000010)
#define RCC_CR_HSI16DIVEN (0x00000008)
#define RCC_CR_HSI16RDYF  (0x00000004)
#define RCC_CR_HSI16KERON (0x00000002)
#define RCC_CR_HSI16ON    (0x00000001)

/** internal clock sources calibration register (ICSCR)
 * Offset: 0x0004
 * Reset value: 0x00xx b0xx
 */
#define RCC_ICSCR_MSITRIM   (0xff000000)
#define RCC_ICSCR_MSICAL    (0x00ff0000)
#define RCC_ICSCR_MSIRANGE  (0x0000e000)
#define RCC_ICSCR_ISI16TRIM (0x00001f00)
#define RCC_ICSCR_HSI16CAL  (0x000000ff)

// 65.536 kHz
#define RCC_ICSCR_MSIRANGE_65_5KHZ  (0x00000000)
// 131.072 kHz
#define RCC_ICSCR_MSIRANGE_131KHZ   (0x00002000)
// 262.144 kHz
#define RCC_ICSCR_MSIRANGE_262_1KHZ (0x00004000)
// 524.288 kHz
#define RCC_ICSCR_MSIRANGE_524_3KHZ (0x00006000)
// 1.048 MHz
#define RCC_ICSCR_MSIRANGE_1MHZ     (0x00008000)
// 2.097 MHz
#define RCC_ICSCR_MSIRANGE_2MHZ     (0x0000a000)
// 4.194 MHz
#define RCC_ICSCR_MSIRANGE_4_2MHZ   (0x0000c000)


/** Clock configuration register (CFGR)
 * Offset: 0x000c
 * Reset value: 0x0000 0000
 */
#define RCC_CFGR_MCOPRE   (0x70000000)
#define RCC_CFGR_MCOSEL   (0x0f000000)
#define RCC_CFGR_PLLDIV   (0x00c00000)
#define RCC_CFGR_PLLMUL   (0x003c0000)
#define RCC_CFGR_PLLSRC   (0x00010000)
#define RCC_CFGR_STOPWUCK (0x00008000)
#define RCC_CFGR_PPRE2    (0x00003800)
#define RCC_CFGR_PPRE1    (0x00000700)
#define RCC_CFGR_HPRE     (0x000000f0)
#define RCC_CFGR_SWS      (0x0000000c)
#define RCC_CFGR_SW       (0x00000003)


#define RCC_CFGR_SWS_MSI   (0x00000000)
#define RCC_CFGR_SWS_HSI16 (0x00000004)
#define RCC_CFGR_SWS_HSE   (0x00000008)
#define RCC_CFGR_SWS_OLL   (0x0000000c)

#define RCC_CFGR_SW_MSI   (0x00000000)
#define RCC_CFGR_SW_HSI16 (0x00000001)
#define RCC_CFGR_SW_HSE   (0x00000002)
#define RCC_CFGR_SW_PLL   (0x00000003)


/** Clock interrupt enable register (CIER)
 * Offset: 0x0010
 * Reset value: 0x0000 0000
 */
#define RCC_CIER_CSSLSE     (0x00000080)
#define RCC_CIER_MSIRDYIE   (0x00000020)
#define RCC_CIER_PLLRDYIE   (0x00000010)
#define RCC_CIER_HSERDYIE   (0x00000008)
#define RCC_CIER_HSI16RDYIE (0x00000004)
#define RCC_CIER_LSERDYIE   (0x00000002)
#define RCC_CIER_LSIRDYIE   (0x00000001)

/** Clock interrupt flag register (CIFR)
 * Offset: 0x0014
 * Reset value: 0x0000 0000
 */
#define RCC_CIFR_CSSHSEF   (0x00000100)
#define RCC_CIFR_CSSLSEF   (0x00000080)
#define RCC_CIFR_MSIRDYF   (0x00000020)
#define RCC_CIFR_PLLRDYF   (0x00000010)
#define RCC_CIFR_HSERDYF   (0x00000008)
#define RCC_CIFR_HSI16RDYF (0x00000004)
#define RCC_CIFR_LSERDYF   (0x00000002)
#define RCC_CIFR_LSIRDYF   (0x00000001)

/** Clock interrupt clear register (CICR)
 * Offset: 0x0018
 * Reset value: 0x0000 0000
 */
#define RCC_CICR_CSSHSEC   (0x00000100)
#define RCC_CICR_CSSLSEC   (0x00000080)
#define RCC_CICR_MSIRDYC   (0x00000020)
#define RCC_CICR_PLLRDYC   (0x00000010)
#define RCC_CICR_HSERDYC   (0x00000008)
#define RCC_CICR_HSI16RDYC (0x00000004)
#define RCC_CICR_LSERDYC   (0x00000002)
#define RCC_CICR_LSIRDYC   (0x00000001)

/** GPIO reset register (IOPRSTR)
 * Offset: 0x001c
 * Reset value: 0x0000 0000
 */
#define RCC_IOPRSTR_IOPHRST (0x00000080)
#define RCC_IOPRSTR_IOPERST (0x00000010)
#define RCC_IOPRSTR_IOPDRST (0x00000008)
#define RCC_IOPRSTR_IOPCRST (0x00000004)
#define RCC_IOPRSTR_IOPBRST (0x00000002)
#define RCC_IOPRSTR_IOPARST (0x00000001)


/** AHB peripheral reset register(AHBRSTR)
 * Offset: 0x0020
 * Reset value: 0x0000 0000
 */
#define RCC_AHBRSTR_CRCRST (0x00001000)
#define RCC_AHBRSTR_MIFRST (0x00000100)
#define RCC_AHBRSTR_DMARST (0x00000001)

/** APB2 peripheral reset register (APB2RSTR)
 * Offset: 0x0024
 * Reset value: 0x0000 0000
 */
#define RCC_APB2RSTR_DGBRST    (0x00400000)
#define RCC_APB2RSTR_SPI1RST   (0x00001000)
#define RCC_APB2RSTR_ADCRST    (0x00000200)
#define RCC_APB2RSTR_TIM22RST  (0x00000020)
#define RCC_APB2RSTR_TIM21RST  (0x00000004)
#define RCC_APB2RSTR_SYSCFGRST (0x00000001)

/** APB1 peripheral reset register (APB1RSTR)
 * Offset: 0x0028
 * Rese tvalue: 0x0000 0000
 */
#define RCC_APB1RSTR_LPTIM1RST (0x80000000)
#define RCC_APB1RSTR_PWRRST    (0x10000000)
#define RCC_APB1RSTR_I2C1RST   (0x00200000)
#define RCC_APB1RSTR_LPUART1RST (0x00040000)
#define RCC_APB1RSTR_USART2RST (0x00020000)
#define RCC_APB1RSTR_WWDGRST   (0x00000800)
#define RCC_APB1RSTR_TIM2RST   (0x00000001)

/** GPIO clock enable register (IOPENR)
 * Offset: 0x002c
 * Reset value: 0x0000 0000
 */
#define RCC_IOPENR_IOPHEN (0x00000080)
#define RCC_IOPENR_IOPEEN (0x00000010)
#define RCC_IOPENR_IOPDEN (0x00000008)
#define RCC_IOPENR_IOPCEN (0x00000004)
#define RCC_IOPENR_IOPBEN (0x00000002)
#define RCC_IOPENR_IOPAEN (0x00000001)

/** AHB peripheral clock enable register (AHBENR)
 * Offset: 0x0030
 * Reset value: 0x0000 0100
 */
#define RCC_AHBENR_CRCEN (0x00001000)
#define RCC_AHBENR_MIFEN (0x00000100)
#define RCC_AHBENR_DMAEN (0x00000001)

/** APB2 peripheral clock enable register (APB2ENR)
 * Offset: 0x0034
 * Reset value: 0x0000 0000
 */
#define RCC_APB2ENR_DBGEN    (0x00400000)
#define RCC_APB2ENR_SPI1EN   (0x00001000)
#define RCC_APB2ENR_ADCEN    (0x00000200)
#define RCC_APB2ENR_FWEN     (0x00000080)
#define RCC_APB2ENR_TIM22EN  (0x00000020)
#define RCC_APB2ENR_TIM21EN  (0x00000004)
#define RCC_APB2ENR_SYSCFGEN (0x00000001)

/** APB1 peripheral clock enable register (APB1ENR)
 * Offset: 0x0038
 * Reset value: 0x0000 0000
 */
#define RCC_APB1ENR_LPTIM1EN  (0x80000000)
#define RCC_APB1ENR_PWREN     (0x10000000)
#define RCC_APB1ENR_I2C1EN    (0x00200000)
#define RCC_APB1ENR_LPUART1EN (0x00040000)
#define RCC_APB1ENR_USART2EN  (0x00020000)
#define RCC_APB1ENR_WWDGEN    (0x00000800)
#define RCC_APB1ENR_TIM2EN    (0x00000001)

/** GPIO clock enable in sleep mode register (IOPSMENR)
 * Offset: 0x003c
 * Reset value:
 */
#define RCC_IOPSMENR_IOPHSMEN (0x00000080)
#define RCC_IOPSMENR_IOPESMEN (0x00000010)
#define RCC_IOPSMENR_IOPDSMEN (0x00000008)
#define RCC_IOPSMENR_IOPCSMEN (0x00000004)
#define RCC_IOPSMENR_IOPBSMEN (0x00000002)
#define RCC_IOPSMENR_IOPASMEN (0x00000001)

/** AHB peripheral clock enable in Sleep mode register (AHBSMENR)
 * Offset: 0x0040
 * Reset value: 
 */
#define RCC_AHBSMENR_CRCSMEN  (0x00001000)
#define RCC_AHBSMENR_SRAMSMEN (0x00000200)
#define RCC_AHBSMENR_MIFSMEN  (0x00000100)
#define RCC_AHBSMENR_DMASMEN  (0x00000001)

/** APB2 peripheral clock enable in Sleep mode register (APB2SMENR)
 * Offset: 0x0044
 * Reset value:
 */
#define RCC_APB2SMENR_DBGSMEN    (0x00400000)
#define RCC_APB2SMENR_SPI1SMEN   (0x00001000)
#define RCC_APB2SMENR_ADCSMEN    (0x00000200)
#define RCC_APB2SMENR_TIM22SMEN  (0x00000020)
#define RCC_APB2SMENR_TIM21SMEN  (0x00000004)
#define RCC_APB2SMENR_SYSCFGSMEN (0x00000001)

/** APB1 peripheral clock enable in Sleep mode register (APB1SMENR)
 * Offset: 0x0048
 * Reset value:
 */
#define RCC_APB1SMENR_LPTIM1SMEN  (0x80000000)
#define RCC_APB1SMENR_PWRSMEN     (0x00040000)
#define RCC_APB1SMENR_I2C1SMEN    (0x00200000)
#define RCC_APB1SMENR_LPUART1SMEN (0x00040000)
#define RCC_APB1SMENR_USART2SMEN  (0x00020000)
#define RCC_APB1SMENR_WWDGSMEN    (0x00000800)
#define RCC_APB1SMENR_TIM2SMEN    (0x00000001)

/** Clock configuration register
 * Offset: 0x004c
 * Reset value: 0x0000 0000
 */
#define RCC_CCIPR_LPTIM1SEL  (0x000c0000)
#define RCC_CCIPR_I2C1SEL    (0x00003000)
#define RCC_CCIPR_LPUART1SEL (0x00000c00)
#define RCC_CCIPR_USART2SEL  (0x0000000c)

/** Control/status register (CSR)
 * Offset: 0x0050
 * Reset value: 0x0c00 0004
 */
#define RCC_CSR_LPWRRSTF (0x80000000)
#define RCC_CSR_WWDGRSTF (0x40000000)
#define RCC_CSR_IWDGRSTF (0x20000000)
#define RCC_CSR_SFTRSTF  (0x10000000)
#define RCC_CSR_PORRSTF  (0x08000000)
#define RCC_CSR_PINRSTF  (0x04000000)
#define RCC_CSR_OBLRSTF  (0x02000000)
#define RCC_CSR_FWRSTF   (0x01000000)
#define RCC_CSR_RMVF     (0x00800000)
#define RCC_CSR_RTCRST   (0x00080000)
#define RCC_CSR_RTCEN    (0x00040000)
#define RCC_CSR_RTCSEL   (0x00030000)
#define RCC_CSR_CSSLSED  (0x00004000)
#define RCC_CSR_CSSLSEON (0x00002000)
#define RCC_CSR_LSEDRV   (0x00001800)
#define RCC_CSR_LSEBYP   (0x00000400)
#define RCC_CSR_LSERDY   (0x00000200)
#define RCC_CSR_LSEON    (0x00000100)
#define RCC_CSR_LSIRDY   (0x00000002)
#define RCC_CSR_LSION    (0x00000001)

#endif
