#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include "io.h"

#define GPIOA_ADDR (0x50000000)
#define GPIOB_ADDR (0x50000400)
#define GPIOC_ADDR (0x50000800)
#define GPIOD_ADDR (0x50000c00)
#define GPIOE_ADDR (0x50001000)
#define GPIOH_ADDR (0x50001c00)

#define GPIOA ((volatile struct gpio_t *)GPIOA_ADDR)
#define GPIOB ((volatile struct gpio_t *)GPIOB_ADDR)
#define GPIOC ((volatile struct gpio_t *)GPIOC_ADDR)
#define GPIOD ((volatile struct gpio_t *)GPIOD_ADDR)
#define GPIOE ((volatile struct gpio_t *)GPIOE_ADDR)
#define GPIOH ((volatile struct gpio_t *)GPIOH_ADDR)

struct gpio_t {
  _IO uint32_t MODER;
  _IO uint32_t OTYPER;
  _IO uint32_t OSPEEDR;
  _IO uint32_t PUPDR;
  _RO uint32_t IDR;
  _IO uint32_t ODR;
  _IO uint32_t BSRR;
  _IO uint32_t LCKR;
  _IO uint32_t AFRL;
  _IO uint32_t AFRH;
  _IO uint32_t BRR;
};


/** GPIO port mode register (MODER)
 * Offset: 0x0000
 * Reset value:
 */
#define GPIO_MODER_MODE15 (0xc0000000)
#define GPIO_MODER_MODE14 (0x30000000)
#define GPIO_MODER_MODE13 (0x0c000000)
#define GPIO_MODER_MODE12 (0x03000000)
#define GPIO_MODER_MODE11 (0x00c00000)
#define GPIO_MODER_MODE10 (0x00300000)
#define GPIO_MODER_MODE9  (0x000c0000)
#define GPIO_MODER_MODE8  (0x00030000)
#define GPIO_MODER_MODE7  (0x0000c000)
#define GPIO_MODER_MODE6  (0x00003000)
#define GPIO_MODER_MODE5  (0x00000c00)
#define GPIO_MODER_MODE4  (0x00000300)
#define GPIO_MODER_MODE3  (0x000000c0)
#define GPIO_MODER_MODE2  (0x00000030)
#define GPIO_MODER_MODE1  (0x0000000c)
#define GPIO_MODER_MODE0  (0x00000003)

#define GPIO_MODER_MODE_INPUT              (0b00)
#define GPIO_MODER_MODE_GPO                (0b01)
#define GPIO_MODER_MODE_ALTERNATE_FUNCTION (0b10)
#define GPIO_MODER_MODE_ANALOG             (0b11)

/** GPIO port output type register (OTYPER)
 * Offset: 0x0004
 * Reset value: 0x0000 0000
 */
#define GPIO_OTYPER_OT15 (0x00008000)
#define GPIO_OTYPER_OT14 (0x00004000)
#define GPIO_OTYPER_OT13 (0x00002000)
#define GPIO_OTYPER_OT12 (0x00001000)
#define GPIO_OTYPER_OT11 (0x00000800)
#define GPIO_OTYPER_OT10 (0x00000400)
#define GPIO_OTYPER_OT9  (0x00000200)
#define GPIO_OTYPER_OT8  (0x00000100)
#define GPIO_OTYPER_OT7  (0x00000080)
#define GPIO_OTYPER_OT6  (0x00000040)
#define GPIO_OTYPER_OT5  (0x00000020)
#define GPIO_OTYPER_OT4  (0x00000010)
#define GPIO_OTYPER_OT3  (0x00000008)
#define GPIO_OTYPER_OT2  (0x00000004)
#define GPIO_OTYPER_OT1  (0x00000002)
#define GPIO_OTYPER_OT0  (0x00000001)

/** GPIO port output speed register (OSPEEDR)
 * Offset: 0x0008
 * Reset value: 0x0c00 0000 (for port A)
 *              0x0000 0000
 */
#define GPIO_OSPEEDR_OSPEED15 (0xc0000000)
#define GPIO_OSPEEDR_OSPEED14 (0x30000000)
#define GPIO_OSPEEDR_OSPEED13 (0x0c000000)
#define GPIO_OSPEEDR_OSPEED12 (0x03000000)
#define GPIO_OSPEEDR_OSPEED11 (0x00c00000)
#define GPIO_OSPEEDR_OSPEED10 (0x00300000)
#define GPIO_OSPEEDR_OSPEED9  (0x000c0000)
#define GPIO_OSPEEDR_OSPEED8  (0x00030000)
#define GPIO_OSPEEDR_OSPEED7  (0x0000c000)
#define GPIO_OSPEEDR_OSPEED6  (0x00003000)
#define GPIO_OSPEEDR_OSPEED5  (0x00000c00)
#define GPIO_OSPEEDR_OSPEED4  (0x00000300)
#define GPIO_OSPEEDR_OSPEED3  (0x000000c0)
#define GPIO_OSPEEDR_OSPEED2  (0x00000030)
#define GPIO_OSPEEDR_OSPEED1  (0x0000000c)
#define GPIO_OSPEEDR_OSPEED0  (0x00000003)

/** GPIO port pull-up/pull-down register (PUPDR)
 * Offset: 0x000c
 * Reset value: 0x2400 0000
 */
#define GPIO_PUPDR_PUPD15 (0xc0000000)
#define GPIO_PUPDR_PUPD14 (0x30000000)
#define GPIO_PUPDR_PUPD13 (0x0c000000)
#define GPIO_PUPDR_PUPD12 (0x03000000)
#define GPIO_PUPDR_PUPD11 (0x00c00000)
#define GPIO_PUPDR_PUPD10 (0x00300000)
#define GPIO_PUPDR_PUPD9  (0x000c0000)
#define GPIO_PUPDR_PUPD8  (0x00030000)
#define GPIO_PUPDR_PUPD7  (0x0000c000)
#define GPIO_PUPDR_PUPD6  (0x00003000)
#define GPIO_PUPDR_PUPD5  (0x00000c00)
#define GPIO_PUPDR_PUPD4  (0x00000300)
#define GPIO_PUPDR_PUPD3  (0x000000c0)
#define GPIO_PUPDR_PUPD2  (0x00000030)
#define GPIO_PUPDR_PUPD1  (0x0000000c)
#define GPIO_PUPDR_PUPD0  (0x00000003)

/** GPIO port input data register (IDR)
 * Offset: 0x0010
 * Reset value: 0x0000 xxxx
 */
#define GPIO_IDR_ID15 (0x00008000)
#define GPIO_IDR_ID14 (0x00004000)
#define GPIO_IDR_ID13 (0x00002000)
#define GPIO_IDR_ID12 (0x00001000)
#define GPIO_IDR_ID11 (0x00000800)
#define GPIO_IDR_ID10 (0x00000400)
#define GPIO_IDR_ID9  (0x00000200)
#define GPIO_IDR_ID8  (0x00000100)
#define GPIO_IDR_ID7  (0x00000080)
#define GPIO_IDR_ID6  (0x00000040)
#define GPIO_IDR_ID5  (0x00000020)
#define GPIO_IDR_ID4  (0x00000010)
#define GPIO_IDR_ID3  (0x00000008)
#define GPIO_IDR_ID2  (0x00000004)
#define GPIO_IDR_ID1  (0x00000002)
#define GPIO_IDR_ID0  (0x00000001)

/** GPIO port output data register (ODR)
 * Offset: 0x0014
 * Reset value: 0x0000 0000
 */
#define GPIO_ODR_OD15 (0x00008000)
#define GPIO_ODR_OD14 (0x00004000)
#define GPIO_ODR_OD13 (0x00002000)
#define GPIO_ODR_OD12 (0x00001000)
#define GPIO_ODR_OD11 (0x00000800)
#define GPIO_ODR_OD10 (0x00000400)
#define GPIO_ODR_OD9  (0x00000200)
#define GPIO_ODR_OD8  (0x00000100)
#define GPIO_ODR_OD7  (0x00000080)
#define GPIO_ODR_OD6  (0x00000040)
#define GPIO_ODR_OD5  (0x00000020)
#define GPIO_ODR_OD4  (0x00000010)
#define GPIO_ODR_OD3  (0x00000008)
#define GPIO_ODR_OD2  (0x00000004)
#define GPIO_ODR_OD1  (0x00000002)
#define GPIO_ODR_OD0  (0x00000001)

/** GPIO port bit set/reset register (BSRR)
 * Offset: 0x0018
 * Reset value: 0x0000 0000
 */
#define GPIO_BSRR_BR15 (0x80000000)
#define GPIO_BSRR_BR14 (0x40000000)
#define GPIO_BSRR_BR13 (0x20000000)
#define GPIO_BSRR_BR12 (0x10000000)
#define GPIO_BSRR_BR11 (0x08000000)
#define GPIO_BSRR_BR10 (0x04000000)
#define GPIO_BSRR_BR9  (0x02000000)
#define GPIO_BSRR_BR8  (0x01000000)
#define GPIO_BSRR_BR7  (0x00800000)
#define GPIO_BSRR_BR6  (0x00400000)
#define GPIO_BSRR_BR5  (0x00200000)
#define GPIO_BSRR_BR4  (0x00100000)
#define GPIO_BSRR_BR3  (0x00080000)
#define GPIO_BSRR_BR2  (0x00040000)
#define GPIO_BSRR_BR1  (0x00020000)
#define GPIO_BSRR_BR0  (0x00010000)
#define GPIO_BSRR_BS15 (0x00008000)
#define GPIO_BSRR_BS14 (0x00004000)
#define GPIO_BSRR_BS13 (0x00002000)
#define GPIO_BSRR_BS12 (0x00001000)
#define GPIO_BSRR_BS11 (0x00000800)
#define GPIO_BSRR_BS10 (0x00000400)
#define GPIO_BSRR_BS9  (0x00000200)
#define GPIO_BSRR_BS8  (0x00000100)
#define GPIO_BSRR_BS7  (0x00000080)
#define GPIO_BSRR_BS6  (0x00000040)
#define GPIO_BSRR_BS5  (0x00000020)
#define GPIO_BSRR_BS4  (0x00000010)
#define GPIO_BSRR_BS3  (0x00000008)
#define GPIO_BSRR_BS2  (0x00000004)
#define GPIO_BSRR_BS1  (0x00000002)
#define GPIO_BSRR_BS0  (0x00000001)

/** GPIO port configuration lock register (LCKR)
 * Offset: 0x001c
 * Reset value: 0x0000 0000
 */
#define GPIO_LCKR_LCKK  (0x00010000)
#define GPIO_LCKR_LCK15 (0x00008000)
#define GPIO_LCKR_LCK14 (0x00004000)
#define GPIO_LCKR_LCK13 (0x00002000)
#define GPIO_LCKR_LCK12 (0x00001000)
#define GPIO_LCKR_LCK11 (0x00000800)
#define GPIO_LCKR_LCK10 (0x00000400)
#define GPIO_LCKR_LCK9  (0x00000200)
#define GPIO_LCKR_LCK8  (0x00000100)
#define GPIO_LCKR_LCK7  (0x00000080)
#define GPIO_LCKR_LCK6  (0x00000040)
#define GPIO_LCKR_LCK5  (0x00000020)
#define GPIO_LCKR_LCK4  (0x00000010)
#define GPIO_LCKR_LCK3  (0x00000008)
#define GPIO_LCKR_LCK2  (0x00000004)
#define GPIO_LCKR_LCK1  (0x00000002)
#define GPIO_LCKR_LCK0  (0x00000001)

/** GPIO alternate function low register (AFRL)
 * Offset: 0x0020
 * Reset value: 0x0000 0000
 */
#define GPIO_AFRL_AFSEL7 (0xf0000000)
#define GPIO_AFRL_AFSEL6 (0x0f000000)
#define GPIO_AFRL_AFSEL5 (0x00f00000)
#define GPIO_AFRL_AFSEL4 (0x000f0000)
#define GPIO_AFRL_AFSEL3 (0x0000f000)
#define GPIO_AFRL_AFSEL2 (0x00000f00)
#define GPIO_AFRL_AFSEL1 (0x000000f0)
#define GPIO_AFRL_AFSEL0 (0x0000000f)

/** GPIO alternate function high register (AFRH)
 * Offset: 0x0024
 * Reset value: 0x0000 0000
 */
#define GPIO_AFRH_AFSEL15 (0xf0000000)
#define GPIO_AFRH_AFSEL14 (0x0f000000)
#define GPIO_AFRH_AFSEL13 (0x00f00000)
#define GPIO_AFRH_AFSEL12 (0x000f0000)
#define GPIO_AFRH_AFSEL11 (0x0000f000)
#define GPIO_AFRH_AFSEL10 (0x00000f00)
#define GPIO_AFRH_AFSEL9  (0x000000f0)
#define GPIO_AFRH_AFSEL8  (0x0000000f)


/** GPIO port bit reset register (BRR)
 * Offset: 0x0028
 * Reset value: 0x0000 0000
 */
#define GPIO_BRR_BR15 (0x00008000)
#define GPIO_BRR_BR14 (0x00004000)
#define GPIO_BRR_BR13 (0x00002000)
#define GPIO_BRR_BR12 (0x00001000)
#define GPIO_BRR_BR11 (0x00000800)
#define GPIO_BRR_BR10 (0x00000400)
#define GPIO_BRR_BR9  (0x00000200)
#define GPIO_BRR_BR8  (0x00000100)
#define GPIO_BRR_BR7  (0x00000080)
#define GPIO_BRR_BR6  (0x00000040)
#define GPIO_BRR_BR5  (0x00000020)
#define GPIO_BRR_BR4  (0x00000010)
#define GPIO_BRR_BR3  (0x00000008)
#define GPIO_BRR_BR2  (0x00000004)
#define GPIO_BRR_BR1  (0x00000002)
#define GPIO_BRR_BR0  (0x00000001)
#endif
