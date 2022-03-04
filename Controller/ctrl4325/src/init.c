#include <stdint.h>

void init_flash(void) {
#if 1
  extern uint8_t 
    *__text_start__, *__text_end__,
    *__data_start__, *__data_end__,
    *__bss_start__, *__bss_end__;

  uint8_t *p_start, *p_end, *p_data;

  p_data = (uint8_t *)&__data_start__;

  p_start = (uint8_t *)&__text_start__;
  p_end = (uint8_t *)&__text_end__;
  //p_end = (uint8_t *)&__data_end__;

  for(; p_start < p_end; ++p_start, ++p_data) {
    p_data = p_start;
  }

  p_start = (uint8_t *)&__bss_start__;
  p_end = (uint8_t *)&__bss_end__;
  for(; p_start < p_end; ++p_start) {
    *p_start = 0;
  }
#endif
}
