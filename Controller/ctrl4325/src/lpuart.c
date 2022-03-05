#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"


void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c);

void LPUART1_handler(void) {
  uint32_t isr = LPUART1->ISR;

  if((isr & LPUART_ISR_RXNE) > 0) {
    int8_t recv = (LPUART1->RDR & 0xff);
    LPUART1->RQR = LPUART_RQR_RXFRQ;

    int8_t number = (recv >= '0' && recv <= '9') ? (recv - '0') : -1;
    if(number >= 0) {
      if(number == 9)
        lpuart_putchar((struct lpuart_t *)LPUART1, '0');
      else
        lpuart_putchar((struct lpuart_t *)LPUART1, (number + 1) + '0');
    } else {
      lpuart_putchar((struct lpuart_t *)LPUART1, '.');
    }
  }
}


void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c) {
  lpuart->TDR = c;
  while((lpuart->ISR & LPUART_ISR_TC) == 0);

  lpuart->ICR = LPUART_ICR_TCCF;
}

void lpuart_print(
    struct lpuart_t *lpuart,
    const char *str) {
  while(*str) {
    lpuart_putchar(lpuart, *str);
    ++str;
  }
}

void lpuart_println(
    struct lpuart_t *lpuart,
    const char *str) {
  lpuart_print(lpuart, str);
  lpuart_print(lpuart, "\r\n");
}
