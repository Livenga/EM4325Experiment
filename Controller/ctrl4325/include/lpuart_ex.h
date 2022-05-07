#ifndef _LPUART_EX_H
#define _LPUART_EX_H

#include <stdint.h>
#include "../../libstm32l0/include/libstm32l0.h"


extern void lpuart_print(struct lpuart_t *lpuart, const char * str);
extern void lpuart_putchar(struct lpuart_t *lpuart, const int8_t c);
extern void lpuart_println(struct lpuart_t *lpuart, const char *str);

#endif
