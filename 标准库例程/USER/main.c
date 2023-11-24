#include "main.h"


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	systick_delay_init(72);
	led_init();
	usart1_uart_init(115200);
	{
		RCC_ClocksTypeDef RCC_ClocksTypeDef;
		SystemCoreClockUpdate();
		RCC_GetClocksFreq(&RCC_ClocksTypeDef);
		printf("SYSCLK = %d\r\n", RCC_ClocksTypeDef.SYSCLK_Frequency);
		printf("HCLK = %d\r\n", RCC_ClocksTypeDef.HCLK_Frequency);
		printf("PCLK1 = %d\r\n", RCC_ClocksTypeDef.PCLK1_Frequency);
		printf("PCLK2 = %d\r\n", RCC_ClocksTypeDef.PCLK2_Frequency);
		printf("ADCCLK = %d\r\n", RCC_ClocksTypeDef.ADCCLK_Frequency);
	}
	tim1_pwm_init(72-1, 1000, 100);
	TIM_Cmd(TIM1,ENABLE);
	
  while(1)
	{
		printf("ok\r\n");
		delay_ms(100);
	}
}

