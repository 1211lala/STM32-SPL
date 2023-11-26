#include "./I2C/i2c.h"




void i2c_init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeDef;

	_IIC1_RCC_CLK_ENABLE();

	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitTypeDef.GPIO_Pin = I2C1_SDA_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C1_SDA_Port, &GPIO_InitTypeDef);
	/* SDA����ģʽ����,��©���,����, �����Ͳ���������IO������, ��©�����ʱ��(=1), Ҳ���Զ�ȡ�ⲿ�źŵĸߵ͵�ƽ */
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef.GPIO_Pin = I2C1_SCL_Pin;
	GPIO_Init(I2C1_SCL_Port, &GPIO_InitTypeDef);
	
}

/**
 * @brief       IIC��ʱ����,���ڿ���IIC��д�ٶ�
 * @param       ��
 * @retval      ��
 */
static void iic_delay(void)
{
    delay_us(2);    /* 2us����ʱ, ��д�ٶ���250Khz���� */
}

/**
 * @brief       ����IIC��ʼ�ź�
 * @param       ��
 * @retval      ��
 */
void i2c_start(void)
{
    I2C_SDA(1);
    I2C_SCL(1);
    iic_delay();
    I2C_SDA(0);     /* START�ź�: ��SCLΪ��ʱ, SDA�Ӹ߱�ɵ�, ��ʾ��ʼ�ź� */
    iic_delay();
    I2C_SCL(0);     /* ǯסI2C���ߣ�׼�����ͻ�������� */
    iic_delay();
}

/**
 * @brief       ����IICֹͣ�ź�
 * @param       ��
 * @retval      ��
 */
void i2c_stop(void)
{
    I2C_SDA(0);     /* STOP�ź�: ��SCLΪ��ʱ, SDA�ӵͱ�ɸ�, ��ʾֹͣ�ź� */
    iic_delay();
    I2C_SCL(1);
    iic_delay();
    I2C_SDA(1);     /* ����I2C���߽����ź� */
    iic_delay();
}

/**
 * @brief       �ȴ�Ӧ���źŵ���
 * @param       ��
 * @retval      1������Ӧ��ʧ��
 *              0������Ӧ��ɹ�
 */
uint8_t i2c_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;

    I2C_SDA(1);     /* �����ͷ�SDA��(��ʱ�ⲿ������������SDA��) */
    iic_delay();
    I2C_SCL(1);     /* SCL=1, ��ʱ�ӻ����Է���ACK */
    iic_delay();

    while (I2C_READ_SDA)    /* �ȴ�Ӧ�� */
    {
        waittime++;

        if (waittime > 250)
        {
            i2c_stop();
            rack = 1;
            break;
        }
    }

    I2C_SCL(0);     /* SCL=0, ����ACK��� */
    iic_delay();
    return rack;
}

/**
 * @brief       ����ACKӦ��
 * @param       ��
 * @retval      ��
 */
void i2c_ack(void)
{
    I2C_SDA(0);     /* SCL 0 -> 1 ʱ SDA = 0,��ʾӦ�� */
    iic_delay();
    I2C_SCL(1);     /* ����һ��ʱ�� */
    iic_delay();
    I2C_SCL(0);
    iic_delay();
    I2C_SDA(1);     /* �����ͷ�SDA�� */
    iic_delay();
}

/**
 * @brief       ������ACKӦ��
 * @param       ��
 * @retval      ��
 */
void i2c_nack(void)
{
    I2C_SDA(1);     /* SCL 0 -> 1  ʱ SDA = 1,��ʾ��Ӧ�� */
    iic_delay();
    I2C_SCL(1);     /* ����һ��ʱ�� */
    iic_delay();
    I2C_SCL(0);
    iic_delay();
}

/**
 * @brief       IIC����һ���ֽ�
 * @param       data: Ҫ���͵�����
 * @retval      ��
 */
void i2c_send_byte(uint8_t data)
{
    uint8_t t;
    
    for (t = 0; t < 8; t++)
    {
        I2C_SDA((data & 0x80) >> 7);    /* ��λ�ȷ��� */
        iic_delay();
        I2C_SCL(1);
        iic_delay();
        I2C_SCL(0);
        data <<= 1;     /* ����1λ,������һ�η��� */
    }
    I2C_SDA(1);         /* �������, �����ͷ�SDA�� */
}

/**
 * @brief       IIC��ȡһ���ֽ�
 * @param       ack:  ack=1ʱ������ack; ack=0ʱ������nack
 * @retval      ���յ�������
 */
uint8_t i2c_read_byte(uint8_t ack)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++ )    /* ����1���ֽ����� */
    {
        receive <<= 1;  /* ��λ�����,�������յ�������λҪ���� */
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
        i2c_nack();     /* ����nACK */
    }
    else
    {
        i2c_ack();      /* ����ACK */
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
////	I2C_InitTypeDef.I2C_OwnAddress1 = ���ӻ�ʱʹ��
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
//	   /* ����I2C��ʼ�ź� */
//    I2C_GenerateSTART(I2Cx, ENABLE);

//    I2CTimeout = I2CT_FLAG_TIMEOUT;

//    /* ��� EV5 �¼��������־*/
//    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
//    {
//        if ((I2CTimeout--) == 0) return 2;
//    }	
//		
//		/* ����EEPROM�豸��ַ */
//    I2C_Send7bitAddress(I2Cx,I2CAddress,I2C_Direction_Transmitter);	
//		    /* ��� EV6 �¼��������־*/
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
//		/* ��� EV8 �¼��������־*/
//    while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
//    {
//        if ((I2CTimeout--) == 0) return 4;
//    }
//		
//		delay_ms(200);
//		/* �����ڶ���I2C��ʼ�ź� */
//    I2C_GenerateSTART(I2Cx, ENABLE);

//    I2CTimeout = I2CT_FLAG_TIMEOUT;

//    /* ��� EV5 �¼��������־*/
//    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
//    {
//        if ((I2CTimeout--) == 0) return 5;
//    }	
//		
//		/* ����EEPROM�豸��ַ */
//    I2C_Send7bitAddress(I2Cx, I2CAddress, I2C_Direction_Receiver);

//    I2CTimeout = I2CT_FLAG_TIMEOUT;
//		    /* ��� EV6 �¼��������־*/
//    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
//    {
//        if ((I2CTimeout--) == 0) return 6;
//    }
//		
//		while (Size)
//    {
//        /*��NumByteToRead=1����ʾ�Ѿ����յ����һ�������ˣ�
//        ���ͷ�Ӧ���źţ���������*/
//        if (Size == 1)
//        {
//            /* ���ͷ�Ӧ���ź� */
//            I2C_AcknowledgeConfig(I2C1, DISABLE);

//            /* ����ֹͣ�ź� */
//            I2C_GenerateSTOP(I2C1, ENABLE);
//        }

//        I2CTimeout = I2CT_FLAG_TIMEOUT * 10;
//        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)
//        {
//            if ((I2CTimeout--) == 0) return 7;
//        }
//        {
//            /*ͨ��I2C�����豸�ж�ȡһ���ֽڵ����� */
//            *Rxbuf = I2C_ReceiveData(I2C1);

//            /* �洢���ݵ�ָ��ָ����һ����ַ */
//            Rxbuf++;

//            /* ���������Լ� */
//            Size--;
//        }
//    }

//    /* ʹ��Ӧ�𣬷�����һ��I2C���� */
//    I2C_AcknowledgeConfig(I2C1, ENABLE);
//    return 1;
//		
//}
