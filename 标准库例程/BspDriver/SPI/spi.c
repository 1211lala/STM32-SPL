#include "./SPI/spi.h"

void spi1_init(void)
{
	_SPI1_RCC_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitTypeDef = {0};
	SPI_InitTypeDef SPI_InitTypeDef = {0};
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef.GPIO_Pin = SPI1_SCK_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI1_SCK_Port, &GPIO_InitTypeDef);
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef.GPIO_Pin = SPI1_MOSI_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI1_MOSI_Port, &GPIO_InitTypeDef);	
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeDef.GPIO_Pin = SPI1_MISO_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI1_MISO_Port, &GPIO_InitTypeDef);	
	
	SPI_InitTypeDef.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitTypeDef.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitTypeDef.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitTypeDef.SPI_CRCPolynomial = 7;
	SPI_InitTypeDef.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitTypeDef.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitTypeDef.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitTypeDef.SPI_Mode = SPI_Mode_Master;
	SPI_InitTypeDef.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI1, &SPI_InitTypeDef);
	
	SPI_Cmd(SPI1, ENABLE);
	delay_ms(10);
}





void SPI_SetSpeed(SPI_TypeDef* SPIX ,uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPIX->CR1&=0XFFC7;
	SPIX->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(SPIX,ENABLE); 
} 





uint8_t SPI_ReadWrite_Byte(SPI_TypeDef* SPIX, uint8_t Txchar)
{
	uint16_t timeout = 1000;
	while (SPI_I2S_GetFlagStatus(SPIX, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		
		if(timeout-- == 0) 
		{
			return 0;
		}
	}
	SPI_I2S_SendData(SPIX, Txchar); 
	
	while (SPI_I2S_GetFlagStatus(SPIX, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		if(timeout-- == 0) 
		{
			return 0;
		}
	}	
	return SPI_I2S_ReceiveData(SPIX);
}


void SPI_ReadWrite_Bytes(SPI_TypeDef* SPIX, uint8_t* Rxbuf, uint8_t* Txbuf, uint16_t Size)
{
	for(uint16_t i=0; i<Size; i++)
	{
		Rxbuf[i] = SPI_ReadWrite_Byte(SPIX, Txbuf[i]);
	}
}
