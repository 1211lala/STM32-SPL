#include "./TIM/tim.h"

uint32_t tim1_pwm_dma_buf[100] = {100, 200, 300,400, 500, 600, 700, 800, 900};




void tim1_base_init(uint16_t psc, uint16_t arr)
{
	_TIM1_RCC_CLK_ENABLE();

	/* 设置时钟源为内部ck_int */
	TIM1->SMCR &= (7 << 0);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDef = {0};

	/* 设置时基 */
	TIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeDef.TIM_Period = arr;
	TIM_TimeBaseInitTypeDef.TIM_Prescaler = psc;
	TIM_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitTypeDef);
	/* 开启定时器 */
	//	TIM_Cmd(TIM1,ENABLE);
}



void tim1_pwm_init(uint16_t psc, uint16_t arr, uint16_t pulse)
{
	/* 使用上一个函数配置时基 */
	tim1_base_init(psc, arr);

	_TIM1_CC1_PORT_CLK_ENABLE();

	/* 高级定时器使用PWM要加上这一句 中文参考手册 248页 */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	GPIO_InitTypeDef GPIO_InitTypeDef = {0};
	TIM_OCInitTypeDef TIM_OCInitTypeDef = {0};
	/* PWM输出引脚配置 */
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef.GPIO_Pin = TIM1_CC1_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TIM1_CC1_Port, &GPIO_InitTypeDef);
	/* 配置OC1参数 */
	TIM_OCInitTypeDef.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitTypeDef.TIM_Pulse = pulse;
	TIM_OCInitTypeDef.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM1, &TIM_OCInitTypeDef);
	/* 使能OC1的预装载功能 */
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	tim1_pwm_dma_init();
}

void tim1_pwm_dma_init(void)
{
	/*
		TIM1->CH1 DMA1_Channel2
		TIM1->CH2 DMA1_Channel3
		TIM1->CH3 DMA1_Channel6
		TIM1->UP DMA1_Channel5
	*/
	DMA_InitTypeDef DMA_InitTypeDef = {0};

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel2);
	TIM_DMACmd(TIM1, TIM_DMA_CC1, ENABLE);

	DMA_InitTypeDef.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitTypeDef.DMA_MemoryBaseAddr = (uint32_t)tim1_pwm_dma_buf;
	DMA_InitTypeDef.DMA_PeripheralBaseAddr = (uint32_t)(&TIM1->CCR1);
	DMA_InitTypeDef.DMA_BufferSize = 0;
	DMA_InitTypeDef.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitTypeDef.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitTypeDef.DMA_M2M = DMA_M2M_Disable;
	DMA_InitTypeDef.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitTypeDef.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitTypeDef.DMA_Mode = DMA_Mode_Normal;
	DMA_InitTypeDef.DMA_Priority = DMA_Priority_Low;

	DMA_Init(DMA1_Channel2, &DMA_InitTypeDef);
	/* 不开启DMA传输 */
	DMA_Cmd(DMA1_Channel2, DISABLE);
	
}	



void tim1_update_it_enable(void)
{
	/* 开启更新中断 */
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	/* 清除更新标志位 */
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	/* 设置NVIC */
	NVIC_InitTypeDef NVIC_InitTypeDef = {0};
	NVIC_InitTypeDef.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeDef);
}

void dma_channel2_tc_it_enable(void)
{
	/* 开启DMA完成中断 */
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitTypeDef = {0};
	
	NVIC_InitTypeDef.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitTypeDef);
}
__weak void TIM1_INT_UPDATE_Callback(void)
{

}

__weak void DMA_CHANNEL2_INT_TC_Callback(void)
{
	
}

