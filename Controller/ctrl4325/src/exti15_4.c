#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"
#include "../include/lpuart_ex.h"


/**
 */
void EXTI15_4_handler(void) {
  uint32_t pr = EXTI->PR;
  lpuart_println((struct lpuart_t *)LPUART1, "// EXTI15_4_handler...");

  if((pr & EXTI_PR_PIF4) == EXTI_PR_PIF4) {
    EXTI->PR = EXTI_PR_PIF4;
    lpuart_println((struct lpuart_t *)LPUART1, "// PA4 立ち上がり検出...");
  }
}
