#include "../../libstm32l0/include/nvic.h"

void NVIC_enable_IRQ(
    struct nvic_t *nvic,
    irq_type_t n) {
  if(n < 0)
    return;

  nvic->ISER = (1 << n);
}

void NVIC_disable_IRQ(
    struct nvic_t *nvic,
    irq_type_t n) {
  if(n < 0)
    return;

  nvic->ICER = (1 << n);
}

void NVIC_set_priority(
    struct nvic_t *nvic,
    irq_type_t    n,
    uint32_t      priority) {
  int p = n / 4;
  int shift_size = (n % 4) * 8;

  if(n >= 0) {
    *(nvic->IPR + p) = (*(nvic->IPR + p) & ~(0xff << shift_size)) | (priority << (shift_size + 6));
  } else {
  }
}
