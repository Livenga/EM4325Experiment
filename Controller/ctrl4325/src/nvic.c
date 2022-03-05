#include "../../libstm32l0/include/libstm32l0.h"


void NVIC_enable_IRQ(irq_type_t n) {
  if(n < 0)
    return;
  NVIC->ISER = (1 << n);
}

void NVIC_disable_IRQ(irq_type_t n) {
  if(n < 0)
    return;
  NVIC->ICER = (1 << n);
}

void NVIC_set_priority(
    irq_type_t n,
    uint32_t   priority) {
  int p = n / 4;
  int shift_size = (n % 4) * 8;

  if(n >= 0) {
    // IPR 0 移行の優先度の設定
    *(NVIC->IPR + p) = (*(NVIC->IPR + p) & ~(0xff << shift_size))
      | (priority << (shift_size + 6));
  } else {
    // SVCall, SysTick, PendSV の優先度設定
    switch(n) {
      case PendSV_IRQn: // TODO
        SCB->SHPR3 = (SCB->SHPR3 & ~(SCB_SHPR3_PRI_14)) | (priority << 22);
        break;

      case SVCall_IRQn: // TODO
        SCB->SHPR2 = (SCB->SHPR2 & ~(SCB_SHPR2_PRI_11)) | (priority << 30);
        break;

      case SysTick_IRQn: // TODO
        SCB->SHPR3 = (SCB->SHPR3 & ~(SCB_SHPR3_PRI_15)) | (priority << 30);
        break;

      default:
        break;
    }
  }
}
