#ifndef _SPI_EX_H
#define _SPI_EX_H

#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"


#define CS_OFF(gpio, cs) gpio->BSRR |= (1 << (cs + 16))
#define CS_ON(gpio, cs)  gpio->BSRR |= (1 << cs)


#endif
