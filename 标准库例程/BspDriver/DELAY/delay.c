#include "./DELAY/delay.h"


uint32_t us_num = 0;
uint32_t ms_num = 0;

void systick_delay_init(uint8_t sysfreq)
{
	/*时钟源选择HCLK 系统时钟 */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	
	
	us_num = sysfreq;
	ms_num = us_num * 1000;
}

/*
	最大计数时间 0xffffff/72 约 200000us;
*/
void delay_us(uint32_t nus)
{
	uint32_t reg_state = 0;
	
	/* 设置加载值 */
	SysTick->LOAD = us_num * nus;
	/* 设置当前计数值为0 会自动的加载LOAD中的值 */
	SysTick->VAL = 0;
	/* 开启定时器 */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		reg_state = SysTick->CTRL;
	}
	/* reg_state&0x01判断systick是否使能   reg_state&(1<<16)) 判断超时溢出 */
	while((reg_state&0x01)&&!(reg_state&(1<<16)));
	/* 关闭定时器 */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0;
}


void delay_ms(uint32_t nms)
{
	while(nms --)
	{
		delay_us(1000);
	}
}


