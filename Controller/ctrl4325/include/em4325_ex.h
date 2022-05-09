#ifndef _EM4325_EX_H
#define _EM4325_EX_H

#include <stdint.h>


#define EM4325_EX_CONFIG_ADDRESS (0x3c)

struct em4325_ex_config_t {
  uint8_t interval_time;
};

struct em4325_ex_config_t *em4325_ex_get_config(uint8_t required_init);

#endif
