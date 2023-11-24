#ifndef _DELAY_H_
#define _DELAY_H_

#include "main.h"

extern uint32_t us_num;
extern uint32_t ms_num;

void systick_delay_init(uint8_t sysfreq);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
#endif

