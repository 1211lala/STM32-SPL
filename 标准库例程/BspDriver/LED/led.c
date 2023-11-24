#include "./LED/led.h"





void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeDef = {0};
	
	_LED_PORT_RCC_CLK_ENABLE();
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef.GPIO_Pin = LED_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(LED_GPIO_Port, &GPIO_InitTypeDef);
}

void led_toggle(void)
{
	if(GPIO_ReadOutputDataBit(LED_GPIO_Port, LED_Pin) == Bit_SET)
	{
		GPIO_WriteBit(LED_GPIO_Port, LED_Pin, Bit_RESET);
	}else
	{
		GPIO_WriteBit(LED_GPIO_Port, LED_Pin, Bit_SET);
	}
}
