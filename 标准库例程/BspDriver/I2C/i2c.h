#ifndef _I2C_H_
#define _I2C_H_

#include "main.h"



#define _IIC1_RCC_CLK_ENABLE() 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 													
/*
	I2C1_SCL -- PB6
	I2C1_SDA -- PB7
*/																
#define I2C1_SDA_Port		GPIOB
#define I2C1_SCL_Port		GPIOB

#define I2C1_SDA_Pin		GPIO_Pin_7
#define I2C1_SCL_Pin		GPIO_Pin_6

/* IO���� */
#define I2C_SCL(x)        do{ x ? \
                              GPIO_WriteBit(I2C1_SCL_Port, I2C1_SCL_Pin, Bit_SET) : \
                              GPIO_WriteBit(I2C1_SCL_Port, I2C1_SCL_Pin, Bit_RESET); \
                          }while(0)       /* SCL */

#define I2C_SDA(x)        do{ x ? \
                              GPIO_WriteBit(I2C1_SDA_Port, I2C1_SDA_Pin, Bit_SET) : \
                              GPIO_WriteBit(I2C1_SDA_Port, I2C1_SDA_Pin, Bit_RESET); \
                          }while(0)       /* SDA */

#define I2C_READ_SDA     	GPIO_ReadInputDataBit(I2C1_SDA_Port, I2C1_SDA_Pin) /* ��ȡSDA */
													
													

/* IIC���в������� */
void i2c_init(void);            /* ��ʼ��IIC��IO�� */
void i2c_start(void);           /* ����IIC��ʼ�ź� */
void i2c_stop(void);            /* ����IICֹͣ�ź� */
void i2c_ack(void);             /* IIC����ACK�ź� */
void i2c_nack(void);            /* IIC������ACK�ź� */
uint8_t i2c_wait_ack(void);     /* IIC�ȴ�ACK�ź� */
void i2c_send_byte(uint8_t txd);/* IIC����һ���ֽ� */
uint8_t i2c_read_byte(unsigned char ack);/* IIC��ȡһ���ֽ� */

													
													
//{
//			float data;
//			i2c_start();
//			i2c_send_byte(0x80);
//			i2c_wait_ack();
//			i2c_send_byte(0xe3);
//			i2c_wait_ack();
//			i2c_stop();

//			
//			
//			i2c_start();					
//			i2c_send_byte(0x81);		
//			i2c_wait_ack();
//			delay_ms(100);
//			buf[0] = i2c_read_byte(1);
//			buf[1] = i2c_read_byte(1);
//			buf[2] = i2c_read_byte(0);
//			i2c_stop();
//		data = (buf[0] << 8) | buf[1];
//		data = (175.72 * data / 65536 - 46.85) *10;	//�¶ȼ��㹫ʽ
//		printf("T %f \r\n",data);

//}

#endif
