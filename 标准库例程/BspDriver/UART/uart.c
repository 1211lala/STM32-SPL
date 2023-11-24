#include "./UART/uart.h"


uint8_t usart1_rec_buf[100] = {0};
uint16_t usart1_rec_number = 0;


void usart1_uart_init(uint32_t buad)
{
	_USART1_RCC_CLK_ENABLE();
	/* 设置GPIO口复用 */
	GPIO_InitTypeDef  GPIO_InitTypeDef = {0};
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef.GPIO_Pin = USART1_TX_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(USART1_TX_Port, &GPIO_InitTypeDef);
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeDef.GPIO_Pin = USART1_RX_Pin;
	GPIO_Init(USART1_RX_Port, &GPIO_InitTypeDef);
	
	/* 配置串口参数 */
	USART_InitTypeDef USART_InitTypeDef = {0};
	
	USART_InitTypeDef.USART_BaudRate = buad;
	USART_InitTypeDef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitTypeDef.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitTypeDef.USART_Parity = USART_Parity_No;
	USART_InitTypeDef.USART_StopBits = USART_StopBits_1;
	USART_InitTypeDef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitTypeDef);
	/* 使能串口 */
	USART_Cmd(USART1, ENABLE);
	/* 开启中断 */
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
	
	/* 设置串口中断的NVIC */
	NVIC_InitTypeDef NVIC_InitTypeDef = {0};
	
	NVIC_InitTypeDef.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeDef);
}


__weak void USART1_INT_RXNE_Callback(void)
{
	usart1_rec_buf[usart1_rec_number] = USART1->DR;
	usart1_rec_number += 1;
}

__weak void USART1_INT_IDLE_Callback(void)
{
	uart_transmit(USART1, usart1_rec_buf, usart1_rec_number);
	usart1_rec_number = 0;
}
	


void uart_transmit(USART_TypeDef* Base, uint8_t* Txbuf, uint16_t Size)
{
	for(uint16_t i=0; i < Size; i++)
	{
		USART_SendData(Base, *Txbuf++);	
		/* 等待发送完成 */		
		while(USART_GetFlagStatus(Base, USART_FLAG_TXE) == RESET);		
	}
	/* 等待发送区为空 */
	while(USART_GetFlagStatus(Base, USART_FLAG_TC) == RESET);		
}




