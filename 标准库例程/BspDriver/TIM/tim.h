#ifndef _TIM_H_
#define _TIM_H_

#include "main.h"

#define _TIM1_RCC_CLK_ENABLE()  			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE)

#define _TIM1_CC1_PORT_CLK_ENABLE() 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)

#define TIM1_CC1_Port		GPIOA
#define TIM1_CC1_Pin		GPIO_Pin_8		


void tim1_it_update_init(uint16_t psc, uint16_t arr);
void tim1_pwm_init(uint16_t psc, uint16_t arr, uint16_t pulse);

void TIM1_INT_UPDATE_Callback(void);




#endif

