#ifndef DELAY_DRIVER_
#define DELAY_DRIVER_

#include "global.h"


void sleep_config(void);
void timer3_init(void);
void sleep_us(uint16_t delay_us);
void sleep_ms(uint16_t delay_ms);


#endif
