#ifndef _NVIC_EX_H
#define _NVIC_EX_H

#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"

extern void NVIC_enable_IRQ(irq_type_t n);

extern void NVIC_disable_IRQ(irq_type_t n);

extern void NVIC_set_priority(
    irq_type_t    n,
    uint32_t      priority);

#endif
