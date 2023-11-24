#include "main.h"


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	systick_delay_init(72);
	led_init();
	usart1_uart_init(115200);
  while(1)
	{
		
	}
}

