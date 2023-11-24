#include "./DELAY/delay.h"


uint32_t us_num = 0;
uint32_t ms_num = 0;

void systick_delay_init(uint8_t sysfreq)
{
	/*ʱ��Դѡ��HCLK ϵͳʱ�� */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	
	
	us_num = sysfreq;
	ms_num = us_num * 1000;
}

/*
	������ʱ�� 0xffffff/72 Լ 200000us;
*/
void delay_us(uint32_t nus)
{
	uint32_t reg_state = 0;
	
	/* ���ü���ֵ */
	SysTick->LOAD = us_num * nus;
	/* ���õ�ǰ����ֵΪ0 ���Զ��ļ���LOAD�е�ֵ */
	SysTick->VAL = 0;
	/* ������ʱ�� */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		reg_state = SysTick->CTRL;
	}
	/* reg_state&0x01�ж�systick�Ƿ�ʹ��   reg_state&(1<<16)) �жϳ�ʱ��� */
	while((reg_state&0x01)&&!(reg_state&(1<<16)));
	/* �رն�ʱ�� */
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


