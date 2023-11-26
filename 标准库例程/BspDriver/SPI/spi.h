#ifndef _SPI_H_
#define _SPI_H_

#include "main.h"



#define _SPI1_RCC_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);\
																	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
#define SPI1_SCK_Port 	GPIOA
#define SPI1_MOSI_Port 	GPIOA
#define SPI1_MISO_Port 	GPIOA

#define SPI1_SCK_Pin 		GPIO_Pin_5
#define SPI1_MISO_Pin 	GPIO_Pin_6
#define SPI1_MOSI_Pin 	GPIO_Pin_7


void spi1_init(void);
void SPI_SetSpeed(SPI_TypeDef* SPIX ,uint8_t SPI_BaudRatePrescaler);
uint8_t SPI_ReadWrite_Byte(SPI_TypeDef* SPIX, uint8_t Txchar);
void SPI_ReadWrite_Bytes(SPI_TypeDef* SPIX, uint8_t* Rxbuf, uint8_t* Txbuf, uint16_t Size);
#endif
