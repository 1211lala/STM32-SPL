/*
 * @Author: liuao 2494210546@qq.com
 * @Date: 2023-11-23 11:26:15
 * @LastEditors: liuao 2494210546@qq.com
 * @LastEditTime: 2023-11-25 13:02:42
 * @FilePath: \USERe:\MY_CODE\Standard-Peripheral\标准库例程\BspDriver\UART\uart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _UART_H_
#define _UART_H_

#include "main.h"

/*************************************************USART1*********************************************/
#define USART1_TX_Port	GPIOA
#define USART1_RX_Port	GPIOA

#define USART1_TX_Pin		GPIO_Pin_9
#define USART1_RX_Pin		GPIO_Pin_10


#define _USART1_RCC_CLK_ENABLE()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); \
									RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
	

#define _USART1_ClEAR_IDLEA_Flag()	volatile uint16_t temp =0; temp = USART1->SR; temp = USART1->DR

extern uint8_t usart1_rec_buf[];
extern uint16_t usart1_rec_number;

void usart1_uart_init(uint32_t buad);	
void USART1_INT_RXNE_Callback(void);
void USART1_INT_IDLE_Callback(void);



/*************************************************USART1*********************************************/




void uart_transmit(USART_TypeDef* Base, uint8_t* Txbuf, uint16_t Size);			










#endif

