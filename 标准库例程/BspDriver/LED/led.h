#ifndef _LED_H_
#define _LED_H_

#include "main.h"


#define _LED_PORT_RCC_CLK_ENABLE()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)


#define LED_Pin					GPIO_Pin_13
#define LED_GPIO_Port		GPIOC


#define led_state(x)		(x ? GPIO_WriteBit(LED_GPIO_Port, GPIO_Pin_13, Bit_RESET) : GPIO_WriteBit(LED_GPIO_Port, GPIO_Pin_13, Bit_SET))


void led_init(void);
void led_toggle(void);

#endif

