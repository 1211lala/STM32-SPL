#include "./I2C/i2c.h"

void i2c1_init(uint32_t ClockSpeed)
{
	_IIC1_RCC_CLK_ENABLE();
	
	I2C_InitTypeDef 	I2C_InitTypeDef = {0};
	GPIO_InitTypeDef 	GPIO_InitTypeDef = {0}; 
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitTypeDef.GPIO_Pin = I2C1_SDA_Pin;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(I2C1_SDA_Port, &GPIO_InitTypeDef);
	
	GPIO_InitTypeDef.GPIO_Pin = I2C1_SCL_Pin;
	GPIO_Init(I2C1_SCL_Port, &GPIO_InitTypeDef);
	
	I2C_InitTypeDef.I2C_Ack = I2C_Ack_Enable;
	I2C_InitTypeDef.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitTypeDef.I2C_ClockSpeed = ClockSpeed;
	I2C_InitTypeDef.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitTypeDef.I2C_Mode = I2C_Mode_I2C;
//	I2C_InitTypeDef.I2C_OwnAddress1 = ���ӻ�ʱʹ��
	I2C_Init(I2C1, &I2C_InitTypeDef);
	
	I2C_Cmd(I2C1, ENABLE);
}

#define I2CT_FLAG_TIMEOUT   ((uint32_t)0x1000)





uint8_t I2C_WriteBytes(I2C_TypeDef* I2Cx, uint8_t I2CAddress, uint8_t* Txbuf, uint16_t Size)
{
	uint16_t I2CTimeout = I2CT_FLAG_TIMEOUT;

	I2C_GenerateSTART(I2Cx,ENABLE);
	
	while(I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR)
	{
		if((I2CTimeout--) == 0) return 1;
	}
	
	I2C_Send7bitAddress(I2Cx,I2CAddress,I2C_Direction_Transmitter);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR)
	{
		if((I2CTimeout--) == 0) return 2;
	}
	
	for(uint16_t i=0; i<Size; i++)
	{
		I2C_SendData(I2Cx, Txbuf[i]);
    I2CTimeout = I2CT_FLAG_TIMEOUT;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        if((I2CTimeout--) == 0) return 3;
    }
	}
	
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	return 0;
}


uint8_t I2C_ReadBytes(I2C_TypeDef* I2Cx, uint8_t I2CAddress, uint8_t ReadReg,uint8_t* Rxbuf, uint16_t Size)
{
		uint32_t I2CTimeout =0 ;
		I2CTimeout = I2CT_FLAG_TIMEOUT * 10;

    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0) return 1;
    }
		
	   /* ����I2C��ʼ�ź� */
    I2C_GenerateSTART(I2Cx, ENABLE);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* ��� EV5 �¼��������־*/
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((I2CTimeout--) == 0) return 2;
    }	
		
		/* ����EEPROM�豸��ַ */
    I2C_Send7bitAddress(I2Cx,I2CAddress,I2C_Direction_Transmitter);	
		    /* ��� EV6 �¼��������־*/
    while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if ((I2CTimeout--) == 0) return 3;
    }
		 I2C_Cmd(I2Cx, ENABLE);
		
		I2C_SendData(I2Cx, ReadReg);
		
		I2CTimeout = I2CT_FLAG_TIMEOUT;
		
		/* ��� EV8 �¼��������־*/
    while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if ((I2CTimeout--) == 0) return 4;
    }
		
		delay_ms(200);
		/* �����ڶ���I2C��ʼ�ź� */
    I2C_GenerateSTART(I2Cx, ENABLE);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* ��� EV5 �¼��������־*/
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((I2CTimeout--) == 0) return 5;
    }	
		
		/* ����EEPROM�豸��ַ */
    I2C_Send7bitAddress(I2Cx, I2CAddress, I2C_Direction_Receiver);

    I2CTimeout = I2CT_FLAG_TIMEOUT;
		    /* ��� EV6 �¼��������־*/
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if ((I2CTimeout--) == 0) return 6;
    }
		
		while (Size)
    {
        /*��NumByteToRead=1����ʾ�Ѿ����յ����һ�������ˣ�
        ���ͷ�Ӧ���źţ���������*/
        if (Size == 1)
        {
            /* ���ͷ�Ӧ���ź� */
            I2C_AcknowledgeConfig(I2C1, DISABLE);

            /* ����ֹͣ�ź� */
            I2C_GenerateSTOP(I2C1, ENABLE);
        }

        I2CTimeout = I2CT_FLAG_TIMEOUT * 10;
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)
        {
            if ((I2CTimeout--) == 0) return 7;
        }
        {
            /*ͨ��I2C�����豸�ж�ȡһ���ֽڵ����� */
            *Rxbuf = I2C_ReceiveData(I2C1);

            /* �洢���ݵ�ָ��ָ����һ����ַ */
            Rxbuf++;

            /* ���������Լ� */
            Size--;
        }
    }

    /* ʹ��Ӧ�𣬷�����һ��I2C���� */
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    return 1;
		
}
	

