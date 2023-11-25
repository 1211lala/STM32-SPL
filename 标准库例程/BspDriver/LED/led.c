/*
 * @Author: liuao 2494210546@qq.com
 * @Date: 2023-11-23 09:17:06
 * @LastEditors: liuao 2494210546@qq.com
 * @LastEditTime: 2023-11-25 13:02:07
 * @FilePath: \USERe:\MY_CODE\Standard-Peripheral\标准库例程\BspDriver\LED\led.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
	if (GPIO_ReadOutputDataBit(LED_GPIO_Port, LED_Pin) == Bit_SET)
	{
		GPIO_WriteBit(LED_GPIO_Port, LED_Pin, Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(LED_GPIO_Port, LED_Pin, Bit_SET);
	}
}
