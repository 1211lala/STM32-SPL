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
	
	{
		tim1_pwm_init(72-1, 1000, 100);
		dma_channel2_tc_it_enable();
		tim1_update_it_enable();
		TIM_Cmd(TIM1,ENABLE);
		
		/*先设置传输数据长度，再有下一步使能 */
		DMA_SetCurrDataCounter(DMA1_Channel2, 9);	 
		/* 打开DMA通道2 */
		DMA_Cmd(DMA1_Channel2, ENABLE);	
	}
	{
		wk2124_init();
		
		Wk2xxxRstInit();
		WkUartInit(1);
		WkUartSetBaud(1,115200);
	}
	{
		idog_init(IWDG_Prescaler_32,4000);
	}
	WkUartTxChars(1, strlen("system restart\r\n"), (uint8_t*)"system restart\r\n");
  while(1)
	{
		idog_restart();
		led_toggle();
	}
}

