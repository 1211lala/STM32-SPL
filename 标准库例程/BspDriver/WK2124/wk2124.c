#include "./WK2124/wk2124.h"


void wk2124_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef = {0};
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef.GPIO_Pin = WK_CS_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(WK_CS_Port, &GPIO_InitTypeDef);
	
	spi1_init();
}
