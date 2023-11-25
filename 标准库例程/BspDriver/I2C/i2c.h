#ifndef _I2C_H_
#define _I2C_H_

#include "main.h"


#define _IIC1_RCC_CLK_ENABLE() 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); \
																RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE)															
/*
	I2C1_SCL -- PB6
	I2C1_SDA -- PB7
*/																
#define I2C1_SDA_Port		GPIOB
#define I2C1_SCL_Port		GPIOB

#define I2C1_SDA_Pin		GPIO_Pin_7
#define I2C1_SCL_Pin		GPIO_Pin_6

void i2c1_init(uint32_t ClockSpeed);
uint8_t I2C_WriteBytes(I2C_TypeDef* I2Cx, uint8_t I2CAddress, uint8_t* Txbuf, uint16_t Size);
uint8_t I2C_ReadBytes(I2C_TypeDef* I2Cx, uint8_t I2CAddress, uint8_t ReadReg,uint8_t* Rxbuf, uint16_t Size);
#endif
