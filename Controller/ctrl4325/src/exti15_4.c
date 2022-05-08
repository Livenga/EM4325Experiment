#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/nvic_ex.h"
#include "../include/lpuart_ex.h"
#include "../include/em4325.h"
#include "../include/mpl115a1.h"
#include "../include/digit_util.h"


static uint32_t _ticks = 0;
static uint32_t _previous_ticks = 0;


void LPTIM1_handler(void) {
  const uint32_t isr = LPTIM1->ISR;

  if((isr & LPTIM_ISR_ARRM) == LPTIM_ISR_ARRM) {
    ++_ticks;
    LPTIM1->ICR = LPTIM_ICR_ARRMCF;
  }
}

void set_ticks(uint32_t ticks) { _ticks = ticks; }
uint32_t get_ticks(void) { return _ticks; }
void clear_ticks(void) { _ticks = 0; }


/**
 */
void EXTI15_4_handler(void) {
  uint32_t pr = EXTI->PR;
  // 一時的に割り込みを無効化
  NVIC_disable_IRQ(EXTI15_4_IRQn);

  if((pr & EXTI_PR_PIF4) == EXTI_PR_PIF4) {
    EXTI->PR = EXTI_PR_PIF4;
    uint32_t current_ticks = get_ticks();

#ifdef __DEBUG__
      lpuart_println((struct lpuart_t *)LPUART1, "// PA4 立ち上がり検出...");
#endif
    if(_previous_ticks == 0 || (current_ticks - _previous_ticks) > 4) {
      _previous_ticks = current_ticks;

      // 気圧データの取得と EPC 領域への書き込み
      float pressure = mpl115a1_get_pressure();
#ifdef __DEBUG__
      lpuart_print((struct lpuart_t *)LPUART1, "\t書き込み実行... 気圧値 = ");
      print_float_value(pressure, 3);
      lpuart_println((struct lpuart_t *)LPUART1, "[kPa]");
#endif

      uint16_t buf_pressure[2];
      memset((void *)buf_pressure, '\0', sizeof(buf_pressure));
      memcpy((void *)buf_pressure, (const void *)&pressure, sizeof(buf_pressure));

      uint16_t pc_bits = em4325_read_word(SPI1, 0x15);
      uint8_t epc_length = (pc_bits >> 11) & 0x1f;

      em4325_write_word(SPI1, 0x16 + (epc_length - 2), *(buf_pressure + 1));
      em4325_write_word(SPI1, 0x16 + (epc_length - 1), *buf_pressure);
    }
#ifdef __DEBUG__
    else {
      lpuart_print((struct lpuart_t *)LPUART1, "\t以前の書き込みより経過時間が 5秒未満(");
      lpuart_putchar((struct lpuart_t *)LPUART1, '0' + (current_ticks - _previous_ticks));
      lpuart_println((struct lpuart_t *)LPUART1, "[s])であるため書き込みを無視します.");
    }
#endif
  }


  // 割り込みの最有効化
  NVIC_enable_IRQ(EXTI15_4_IRQn);
  //NVIC_set_priority(EXTI15_4_IRQn, 2);
}
