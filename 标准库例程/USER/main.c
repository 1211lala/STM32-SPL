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
		
		/*�����ô������ݳ��ȣ�������һ��ʹ�� */
		DMA_SetCurrDataCounter(DMA1_Channel2, 9);	 
		/* ��DMAͨ��2 */
		DMA_Cmd(DMA1_Channel2, ENABLE);	
	}
	uint8_t rx[40];
	
	{
		wk2124_init();
		
	}
  while(1)
	{
		

		delay_ms(200);
		led_toggle();
		
	}
}

