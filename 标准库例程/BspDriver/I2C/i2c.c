#include "./I2C/i2c.h"




void i2c_init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeDef;

	_IIC1_RCC_CLK_ENABLE();

	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitTypeDef.GPIO_Pin = I2C1_SDA_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C1_SDA_Port, &GPIO_InitTypeDef);
	/* SDA引脚模式设置,开漏输出,上拉, 这样就不用再设置IO方向了, 开漏输出的时候(=1), 也可以读取外部信号的高低电平 */
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef.GPIO_Pin = I2C1_SCL_Pin;
	GPIO_Init(I2C1_SCL_Port, &GPIO_InitTypeDef);
	
}

/**
 * @brief       IIC延时函数,用于控制IIC读写速度
 * @param       无
 * @retval      无
 */
static void iic_delay(void)
{
    delay_us(2);    /* 2us的延时, 读写速度在250Khz以内 */
}

/**
 * @brief       产生IIC起始信号
 * @param       无
 * @retval      无
 */
void i2c_start(void)
{
    I2C_SDA(1);
    I2C_SCL(1);
    iic_delay();
    I2C_SDA(0);     /* START信号: 当SCL为高时, SDA从高变成低, 表示起始信号 */
    iic_delay();
    I2C_SCL(0);     /* 钳住I2C总线，准备发送或接收数据 */
    iic_delay();
}

/**
 * @brief       产生IIC停止信号
 * @param       无
 * @retval      无
 */
void i2c_stop(void)
{
    I2C_SDA(0);     /* STOP信号: 当SCL为高时, SDA从低变成高, 表示停止信号 */
    iic_delay();
    I2C_SCL(1);
    iic_delay();
    I2C_SDA(1);     /* 发送I2C总线结束信号 */
    iic_delay();
}

/**
 * @brief       等待应答信号到来
 * @param       无
 * @retval      1，接收应答失败
 *              0，接收应答成功
 */
uint8_t i2c_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;

    I2C_SDA(1);     /* 主机释放SDA线(此时外部器件可以拉低SDA线) */
    iic_delay();
    I2C_SCL(1);     /* SCL=1, 此时从机可以返回ACK */
    iic_delay();

    while (I2C_READ_SDA)    /* 等待应答 */
    {
        waittime++;

        if (waittime > 250)
        {
            i2c_stop();
            rack = 1;
            break;
        }
    }

    I2C_SCL(0);     /* SCL=0, 结束ACK检查 */
    iic_delay();
    return rack;
}

/**
 * @brief       产生ACK应答
 * @param       无
 * @retval      无
 */
void i2c_ack(void)
{
    I2C_SDA(0);     /* SCL 0 -> 1 时 SDA = 0,表示应答 */
    iic_delay();
    I2C_SCL(1);     /* 产生一个时钟 */
    iic_delay();
    I2C_SCL(0);
    iic_delay();
    I2C_SDA(1);     /* 主机释放SDA线 */
    iic_delay();
}

/**
 * @brief       不产生ACK应答
 * @param       无
 * @retval      无
 */
void i2c_nack(void)
{
    I2C_SDA(1);     /* SCL 0 -> 1  时 SDA = 1,表示不应答 */
    iic_delay();
    I2C_SCL(1);     /* 产生一个时钟 */
    iic_delay();
    I2C_SCL(0);
    iic_delay();
}

/**
 * @brief       IIC发送一个字节
 * @param       data: 要发送的数据
 * @retval      无
 */
void i2c_send_byte(uint8_t data)
{
    uint8_t t;
    
    for (t = 0; t < 8; t++)
    {
        I2C_SDA((data & 0x80) >> 7);    /* 高位先发送 */
        iic_delay();
        I2C_SCL(1);
        iic_delay();
        I2C_SCL(0);
        data <<= 1;     /* 左移1位,用于下一次发送 */
    }
    I2C_SDA(1);         /* 发送完成, 主机释放SDA线 */
}

/**
 * @brief       IIC读取一个字节
 * @param       ack:  ack=1时，发送ack; ack=0时，发送nack
 * @retval      接收到的数据
 */
uint8_t i2c_read_byte(uint8_t ack)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++ )    /* 接收1个字节数据 */
    {
        receive <<= 1;  /* 高位先输出,所以先收到的数据位要左移 */
        I2C_SCL(1);
        iic_delay();

        if (I2C_READ_SDA)
        {
            receive++;
        }
        
        I2C_SCL(0);
        iic_delay();
    }

    if (!ack)
    {
        i2c_nack();     /* 发送nACK */
    }
    else
    {
        i2c_ack();      /* 发送ACK */
    }

    return receive;
}






//void i2c1_init(uint32_t ClockSpeed)
//{
//	_IIC1_RCC_CLK_ENABLE();
//	
//	I2C_InitTypeDef 	I2C_InitTypeDef = {0};
//	GPIO_InitTypeDef 	GPIO_InitTypeDef = {0}; 
//	
//	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_OD;
//	GPIO_InitTypeDef.GPIO_Pin = I2C1_SDA_Pin;
//	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(I2C1_SDA_Port, &GPIO_InitTypeDef);
//	
//	GPIO_InitTypeDef.GPIO_Pin = I2C1_SCL_Pin;
//	GPIO_Init(I2C1_SCL_Port, &GPIO_InitTypeDef);
//	
//	I2C_InitTypeDef.I2C_Ack = I2C_Ack_Enable;
//	I2C_InitTypeDef.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	I2C_InitTypeDef.I2C_ClockSpeed = ClockSpeed;
//	I2C_InitTypeDef.I2C_DutyCycle = I2C_DutyCycle_2;
//	I2C_InitTypeDef.I2C_Mode = I2C_Mode_I2C;
////	I2C_InitTypeDef.I2C_OwnAddress1 = 做从机时使用
//	I2C_Init(I2C1, &I2C_InitTypeDef);
//	
//	I2C_Cmd(I2C1, ENABLE);
//}


//#define I2CT_FLAG_TIMEOUT   ((uint32_t)0x1000)
//uint8_t I2C_WriteBytes(I2C_TypeDef* I2Cx, uint8_t I2CAddress, uint8_t* Txbuf, uint16_t Size)
//{
//	uint16_t I2CTimeout = I2CT_FLAG_TIMEOUT;

//	I2C_GenerateSTART(I2Cx,ENABLE);
//	
//	while(I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR)
//	{
//		if((I2CTimeout--) == 0) return 1;
//	}
//	
//	I2C_Send7bitAddress(I2Cx,I2CAddress,I2C_Direction_Transmitter);
//	
//	I2CTimeout = I2CT_FLAG_TIMEOUT;
//	while(I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR)
//	{
//		if((I2CTimeout--) == 0) return 2;
//	}
//	
//	for(uint16_t i=0; i<Size; i++)
//	{
//		I2C_SendData(I2Cx, Txbuf[i]);
//    I2CTimeout = I2CT_FLAG_TIMEOUT;
//    while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
//    {
//        if((I2CTimeout--) == 0) return 3;
//    }
//	}
//	
//	I2C_GenerateSTOP(I2Cx, ENABLE);
//	
//	return 0;
//}


//uint8_t I2C_ReadBytes(I2C_TypeDef* I2Cx, uint8_t I2CAddress, uint8_t ReadReg,uint8_t* Rxbuf, uint16_t Size)
//{
//		uint32_t I2CTimeout =0 ;
//		I2CTimeout = I2CT_FLAG_TIMEOUT * 10;

//    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
//    {
//        if ((I2CTimeout--) == 0) return 1;
//    }
//		
//	   /* 产生I2C起始信号 */
//    I2C_GenerateSTART(I2Cx, ENABLE);

//    I2CTimeout = I2CT_FLAG_TIMEOUT;

//    /* 检测 EV5 事件并清除标志*/
//    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
//    {
//        if ((I2CTimeout--) == 0) return 2;
//    }	
//		
//		/* 发送EEPROM设备地址 */
//    I2C_Send7bitAddress(I2Cx,I2CAddress,I2C_Direction_Transmitter);	
//		    /* 检测 EV6 事件并清除标志*/
//    while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
//    {
//        if ((I2CTimeout--) == 0) return 3;
//    }
//		 I2C_Cmd(I2Cx, ENABLE);
//		
//		I2C_SendData(I2Cx, ReadReg);
//		
//		I2CTimeout = I2CT_FLAG_TIMEOUT;
//		
//		/* 检测 EV8 事件并清除标志*/
//    while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
//    {
//        if ((I2CTimeout--) == 0) return 4;
//    }
//		
//		delay_ms(200);
//		/* 产生第二次I2C起始信号 */
//    I2C_GenerateSTART(I2Cx, ENABLE);

//    I2CTimeout = I2CT_FLAG_TIMEOUT;

//    /* 检测 EV5 事件并清除标志*/
//    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
//    {
//        if ((I2CTimeout--) == 0) return 5;
//    }	
//		
//		/* 发送EEPROM设备地址 */
//    I2C_Send7bitAddress(I2Cx, I2CAddress, I2C_Direction_Receiver);

//    I2CTimeout = I2CT_FLAG_TIMEOUT;
//		    /* 检测 EV6 事件并清除标志*/
//    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
//    {
//        if ((I2CTimeout--) == 0) return 6;
//    }
//		
//		while (Size)
//    {
//        /*若NumByteToRead=1，表示已经接收到最后一个数据了，
//        发送非应答信号，结束传输*/
//        if (Size == 1)
//        {
//            /* 发送非应答信号 */
//            I2C_AcknowledgeConfig(I2C1, DISABLE);

//            /* 发送停止信号 */
//            I2C_GenerateSTOP(I2C1, ENABLE);
//        }

//        I2CTimeout = I2CT_FLAG_TIMEOUT * 10;
//        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)
//        {
//            if ((I2CTimeout--) == 0) return 7;
//        }
//        {
//            /*通过I2C，从设备中读取一个字节的数据 */
//            *Rxbuf = I2C_ReceiveData(I2C1);

//            /* 存储数据的指针指向下一个地址 */
//            Rxbuf++;

//            /* 接收数据自减 */
//            Size--;
//        }
//    }

//    /* 使能应答，方便下一次I2C传输 */
//    I2C_AcknowledgeConfig(I2C1, ENABLE);
//    return 1;
//		
//}
