#ifndef _DIGIT_UTIL_H
#define _DIGIT_UTIL_H

#include <stdio.h>
#include <stdint.h>

extern void print_to_hex(uint32_t value, size_t size);
extern void print_to_dec(int32_t value);
extern void print_float_value(float value, size_t n);

#endif
