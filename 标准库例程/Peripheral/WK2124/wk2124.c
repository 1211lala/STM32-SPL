#include "./WK2124/wk2124.h"


void wk2124_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitTypeDef = {0};
	
	GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDef.GPIO_Pin = WK_CS_Pin|GPIO_Pin_3;
	GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(WK_CS_Port, &GPIO_InitTypeDef);
	
	spi1_init();
}


/*
1��WK2124 ��Ϊ SPI ���豸��֧�� SPI ģʽ 0,������������Ҫ���� CPOL=0(SPI ʱ�Ӽ���ѡ��λ����CPHA=0( SPI ʱ����λѡ��λ)��
2��Ƭѡ�ź��ڿ���ʱӦ�ñ���Ϊ�ߵ�ƽ������Ƭѡ�ź���Ϊһ�ζ�д�����Ŀ�ʼ��������Ϊһ�β����Ľ�����
*/

void SPI1_CS_Ctrl(uint8_t cs)
{
	if (cs == 0)
	{
		GPIO_WriteBit(WK_CS_Port, WK_CS_Pin, Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(WK_CS_Port, WK_CS_Pin, Bit_SET);
	}
}


void WK2124_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	SPI1_CS_Ctrl(0);
	SPI_ReadWrite_Bytes(SPI1, pRxData, pTxData, Size);
	SPI1_CS_Ctrl(1);
}

/**@Description WK2124��ʼ����ƽ
 */
void Wk2xxxRstInit(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
	delay_ms(10);
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
	delay_ms(10);
}

/**@Description ��ȫ�ּĴ�����д����
 *@param greg:ȫ�ּĴ�����ַ
 *@param dat:��ȫ�ּĴ�����д��ֵ
 *@retval ��
 */
void WkWriteGlobalRegister(uint8_t greg, uint8_t dat)
{
	uint8_t tdat[2], rdat[2], cmd;
	cmd = 0 | greg; /* д�Ĵ���ʱ�����ֽ�cmd��bit7 bit6 ����Ϊ 00 21ҳ*/
	tdat[0] = cmd;	/* ��ַ */
	tdat[1] = dat;	/* ���� */
	WK2124_TransmitReceive(tdat, rdat, 2);
}

/**@Description ��ȫ�ּĴ����ж�����
 *@param  greg:ȫ�ּĴ�����ַ
 *@retval :��ȡ����ֵ
 */
uint8_t WkReadGlobalRegister(uint8_t greg)
{
	uint8_t tdat[2], rdat[2], cmd;
	cmd = 0x40 | greg; /* ���Ĵ���ʱ�����ֽ�cmd��bit7 bit6 ����Ϊ 01 21ҳ*/
	tdat[0] = cmd;
	tdat[1] = 0x34;
	WK2124_TransmitReceive(tdat, rdat, 2);
	
	return rdat[1];
}

/**@Description д�Ӵ��ڼĴ�������
	* @param port:�Ӵ��ں�
	* @param sreg:�Ӵ��ڵ�4λ��ַ
	* @param dat:���Ӵ��ڵ�ַд���ֵ
	* @retval
	C1 C2 == 0 0 ����һ
	C1 C2 == 0 1 ���ڶ�
	C1 C2 == 1 0 ������
	C1 C2 == 1 1 ������
	*д�Ӵ��ڼĴ�����ʽ == 0 0 C1 C2 + ��λ�Ӵ��ڵ�ַ
*/
void WkWriteSlaveRegister(uint8_t port, uint8_t sreg, uint8_t dat)
{
	uint8_t tdat[2], rdat[2], cmd;
	cmd = 0x0 | ((port - 1) << 4) | sreg;
	tdat[0] = cmd;
	tdat[1] = dat;
	WK2124_TransmitReceive(tdat, rdat, 2);
}

/**@Description ���Ӵ��ڼĴ�������
	*@param  sreg:�Ӵ��ں�
	*@param  sreg:�Ӵ��ڵ�4λ��ַ
	*@retval :Read ���Ӵ��ڵ�ַ������ֵ

	C1 C2 == 0 0 ����һ
	C1 C2 == 0 1 ���ڶ�
	C1 C2 == 1 0 ������
	C1 C2 == 1 1 ������
	*���Ӵ��ڼĴ�����ʽ == 0 1 C1 C2 +��λ�Ӵ��ڵ�ַ
*/
uint8_t WkReadSlaveRegister(uint8_t port, uint8_t sreg)
{
	uint8_t tdat[2], rdat[2], cmd;
	cmd = 0x40 | ((port - 1) << 4) | sreg;
	tdat[0] = cmd;
	WK2124_TransmitReceive(tdat, rdat, 2);
	return rdat[1];
}

/**@Description ���Ӵ���FIFO��д����
* @param port:���ں�
* @param dat:���͵�����
* @param len:�������ݵĳ���
* @retval
	C1 C2 == 0 0 ����һ
	C1 C2 == 0 1 ���ڶ�
	C1 C2 == 1 0 ������
	C1 C2 == 1 1 ������
	*д�Ӵ���FIFO��ʽ == 1 0 C1 C2 + x x x x
*/
void WkWriteSlaveFifo(uint8_t port, uint8_t *dat, uint16_t len)
{
	uint8_t tdat[257], rdat[257], cmd;
	int i;
	cmd = 0x80 | ((port - 1) << 4);
	tdat[0] = cmd;
	for (i = 0; i < len; i++)
	{
		tdat[1 + i] = *(dat + i);
	}
	WK2124_TransmitReceive(tdat, rdat, len + 1);
}

/**@Description ���Ӵ���FIFO�ж�����
	* @param port:���ں�
	* @param rec:���յĳ���
	* @param len:�������ݵĳ���
	* @retval
	C1 C2 == 0 0 ����һ
	C1 C2 == 0 1 ���ڶ�
	C1 C2 == 1 0 ������
	C1 C2 == 1 1 ������
	*���Ӵ���FIFO��ʽ == 1 1 C1 C2 + x x x x
*/
void WkReadSlaveFifo(uint8_t port, uint8_t *rec, int len)
{
	uint8_t tdat[257], rdat[257], cmd;
	int i;
	cmd = 0xc0 | ((port - 1) << 4);
	tdat[0] = cmd;
	WK2124_TransmitReceive(tdat, rdat, len + 1);
	for (i = 0; i < len; i++)
	{
		*(rec + i) = rdat[1 + i];
	}
}

/**
 *@Description ��ʼ���Ӵ���
 */
void WkUartInit(uint8_t port)
{
	uint8_t gena, grst, gier, sier, scr;
	/* ��ȡȫ�ּĴ����е�ֵ */
	gena = WkReadGlobalRegister(WK2XXX_GENA_REG);
	/* ʹ���Ӵ���ʱ�� */
//	printf("gena = 0x%02x\r\n", gena);
	
	gena = gena | (1 << (port - 1));
	WkWriteGlobalRegister(WK2XXX_GENA_REG, gena);
	/* ��ȡȫ���Ӵ��ڸ�λ�Ĵ�����ֵ */
	grst = WkReadGlobalRegister(WK2XXX_GRST_REG);
	/* �����λ�Ӵ��� */
	grst = grst | (1 << (port - 1));
	WkWriteGlobalRegister(WK2XXX_GRST_REG, grst);
	/*ʹ�ܴ������ж� */
	gier = WkReadGlobalRegister(WK2XXX_GIER_REG);
	gier = gier | (1 << (port - 1));
	WkWriteGlobalRegister(WK2XXX_GIER_REG, gier);
	// ʹ���Ӵ��ڽ��մ����жϺͳ�ʱ�ж�
	sier = WkReadSlaveRegister(port, WK2XXX_SIER_REG);
	sier |= SIER_RFTRIG_IEN_BIT | SIER_RXOUT_IEN_BIT;
	WkWriteSlaveRegister(port, WK2XXX_SIER_REG, sier);
	// ��ʼ��FIFO�����ù̶��жϴ���
	WkWriteSlaveRegister(port, WK2XXX_FCR_REG, 0XFF);
	// ���������жϴ��㣬��������������Ч��
	// ��ô����FCR�Ĵ����жϵĹ̶��жϴ��㽫ʧЧ
	WkWriteSlaveRegister(port, WK2XXX_SPAGE_REG, 1);   // �л���page1
	WkWriteSlaveRegister(port, WK2XXX_RFTL_REG, 0X40); // ���ý��մ���Ϊ64���ֽ�
	WkWriteSlaveRegister(port, WK2XXX_TFTL_REG, 0X10); // ���÷��ʹ���Ϊ16���ֽ�
	WkWriteSlaveRegister(port, WK2XXX_SPAGE_REG, 0);   // �л���page0
	// ʹ���Ӵ��ڵķ��ͺͽ���ʹ��
	scr = WkReadSlaveRegister(port, WK2XXX_SCR_REG);
	scr |= SCR_TXEN_BIT | SCR_RXEN_BIT;
	WkWriteSlaveRegister(port, WK2XXX_SCR_REG, scr);
	
}

/**
 *@Description ��λ�Ӵ���
 */
void WkUartDeInit(uint8_t port)
{
	uint8_t gena, grst, gier;
	// �ر��Ӵ�����ʱ��
	gena = WkReadGlobalRegister(WK2XXX_GENA_REG);
	gena = gena & (~(1 << (port - 1)));
	WkWriteGlobalRegister(WK2XXX_GENA_REG, gena);
	// ʹ���Ӵ������ж�
	gier = WkReadGlobalRegister(WK2XXX_GIER_REG);
	gier = gier & (~(1 << (port - 1)));
	WkWriteGlobalRegister(WK2XXX_GIER_REG, gier);
	// �����λ�Ӵ���
	grst = WkReadGlobalRegister(WK2XXX_GRST_REG);
	grst = grst | (1 << (port - 1));
	WkWriteGlobalRegister(WK2XXX_GRST_REG, grst);
}

/****@Description �����Ӵ��ڲ����ʺ������˺����в����ʵ�ƥ��ֵ�Ǹ���16Mhz�µ��ⲿ��������
 * @param port:�Ӵ��ں�
 * baud:�����ʴ�С.�����ʱ�ʾ��ʽ��
 * @retval
 */
uint8_t WkUartSetBaud(uint8_t port, uint32_t baudrate)
{
	uint32_t temp, freq;
	uint8_t scr;
	uint8_t baud1, baud0, pres;
	freq=11059200;/*оƬ�ⲿʱ��Ƶ��*/
//	freq = 16000000; /*оƬ�ⲿʱ��Ƶ��*/
	if (freq >= (baudrate * 16))
	{
		temp = (freq) / (baudrate * 16);
		temp = temp - 1;
		baud1 = (uint8_t)((temp >> 8) & 0xff);
		baud0 = (uint8_t)(temp & 0xff);

		/* д��С������ ���Ǻ����Ϊʲô����д ֱ�ӵó�С������һ�ٱ����벻�ͺ����� */
		temp = (((freq % (baudrate * 16)) * 100) / (baudrate));
		pres = (temp + 100 / 2) / 100;
		/* д��С������ ���Ǻ����Ϊʲô����д ֱ�ӵó�С������һ�ٱ����벻�ͺ����� */

//		printf("Wk_SetBaud---freq:%d,baudrate:%d\n", freq, baudrate);
//		printf("Wk_SetBaud---baud1:%x,baud0:%x,pres:%x\n", baud1, baud0, pres);
		// �ص��Ӵ����շ�ʹ��
		scr = WkReadSlaveRegister(port, WK2XXX_SCR_REG);
		WkWriteSlaveRegister(port, WK2XXX_SCR_REG, 0);
		// ���ò�������ؼĴ���
		WkWriteSlaveRegister(port, WK2XXX_SPAGE_REG, 1); // �л���page1
		WkWriteSlaveRegister(port, WK2XXX_BAUD1_REG, baud1);
		WkWriteSlaveRegister(port, WK2XXX_BAUD0_REG, baud0);
		WkWriteSlaveRegister(port, WK2XXX_PRES_REG, pres);
		WkWriteSlaveRegister(port, WK2XXX_SPAGE_REG, 0); // �л���page0
		// ʹ���Ӵ����շ�ʹ��
		WkWriteSlaveRegister(port, WK2XXX_SCR_REG, scr);
		return 0;
	}
	else
	{
		printf("Wk_SetBaud error!!!\n");
		return 1;
	}
}

/**************************�������ݸ�ʽ*******************************************************/
// �������ܣ������Ӵ���ͨ�����ݸ�ʽ������ֹͣλ��У�鷽ʽ
// ������
/**********************************************************************************************/
// stopformat:֧��һλֹͣλ����λֹͣλ���������£�
// WK2XXX_UART_STOPBITS_1 ,WK2XXX_UART_STOPBITS_2
/**********************************************************************************************/
// paritytype:У�鷽ʽ��֧�ֶ���У�鷽ʽ��NONE(��У��),ODD,EVEN,MARK,SPACE�����庯���������£�
// WK2XXX_UART_PARITY_NONE,  ��У��
// WK2XXX_UART_PARITY_ODD,   ��У��
// WK2XXX_UART_PARITY_EVEN,  żУ��
// WK2XXX_UART_PARITY_MARK ��MARKУ��,1У��
// WK2XXX_UART_PARITY_SPACE��SPACEУ�飬0У��
/***********************************************************************************************/
unsigned char WkUartFormatSet(uint8_t port, uint8_t stopformat, uint8_t paritytype)
{
	unsigned char scr = 0, sier = 0, lcr = 0;

	/* ������ǰʧ���Ӵ����շ� */
	scr = WkReadSlaveRegister(port, WK2XXX_SCR_REG);
	WkWriteSlaveRegister(port, WK2XXX_SCR_REG, 0);
	/* ������ǰʧ���Ӵ����ж��շ� */
	sier = WkReadSlaveRegister(port, WK2XXX_SIER_REG);
	WkWriteSlaveRegister(port, WK2XXX_SIER_REG, 0);

	if (stopformat == WK2XXX_UART_STOPBITS_1)
	{
		lcr = lcr | 0;
	}
	else if (stopformat == WK2XXX_UART_STOPBITS_2)
	{
		lcr = lcr | LCR_STPL_BIT;
	}
	else
	{
		return 1;
	}
	if (paritytype == WK2XXX_UART_PARITY_NONE)
	{
		lcr = lcr | 0;
	}
	else if (paritytype == WK2XXX_UART_PARITY_ODD)
	{
		lcr = lcr | (LCR_PAM0_BIT | LCR_PAEN_BIT);
	}
	else if (paritytype == WK2XXX_UART_PARITY_EVEN)
	{
		lcr = lcr | (LCR_PAM1_BIT | LCR_PAEN_BIT);
	}
	else if (paritytype == WK2XXX_UART_PARITY_MARK)
	{
		lcr = lcr | (LCR_PAM0_BIT | LCR_PAM1_BIT | LCR_PAEN_BIT);
	}
	else if (paritytype == WK2XXX_UART_PARITY_SPACE)
	{
		lcr = lcr | LCR_PAEN_BIT;
	}
	else
	{
		return 1;
	}
	WkWriteSlaveRegister(port, WK2XXX_LCR_REG, lcr);
	/* ʹ���Ӵ����շ����ж� */
	WkWriteSlaveRegister(port, WK2XXX_SCR_REG, scr);
	WkWriteSlaveRegister(port, WK2XXX_SIER_REG, sier);

	printf("Wk_FormatSet--LCR:%x,SCR:%x,SIER:%x\n", lcr, scr, sier);
	return 0;
}

/* @Description:��ȡ�Ӵ��ڷ���FIFOʣ��ռ䳤��
 * @param port:���ں�
 * @retval:����FIFOʣ��ռ䳤��
 */
int WkUartTxLen(uint8_t port)
{
	uint8_t fsr, tfcnt;
	int len = 0;
	/* �õ��Ӵ���FIFO״̬�Ĵ�����ֵ */
	fsr = WkReadSlaveRegister(port, WK2XXX_FSR_REG);
	/* �õ��Ӵ��ڷ��� FIFO �е����ݸ��� */
	tfcnt = WkReadSlaveRegister(port, WK2XXX_TFCNT_REG);
	if (fsr & FSR_TFULL_BIT) /* �Ӵ��ڷ��� FIFO ����־�����һ��˵������ */
	{
		len = 0;
	}
	else
	{
		len = 256 - tfcnt;
	}
	return len;
}

/* @Description:ͨ���Ӵ��ڷ��͹̶���������
 * @param port:���ں�
 * @param len:���η��ͳ��Ȳ�����256
 */
int WkUartTxChars(uint8_t port, int len, uint8_t *sendbuf)
{
#if 1
	WkWriteSlaveFifo(port, sendbuf, len); // ͨ��fifo��ʽ��������
	return 0;
#else
	int num = len;
	for (num = 0; num < len; num++)
	{
		/* �����ݼĴ���д���� */
		WkWriteSlaveRegister(port, WK2XXX_FDAT_REG, *(sendbuf + num));
	}
	return 0;
#endif
}

/* @Description:��ȡ�Ӵ���fifo�е�����
 * @param port:�˿ں�
 * @param recbuf:���յ�������
 * @retval �������ݵĳ���
 */
int WkUartRxChars(uint8_t port, uint8_t *recbuf)
{
	uint8_t fsr = 0, rfcnt = 0, rfcnt2 = 0, sifr = 0;
	int len = 0;
	sifr = WkReadSlaveRegister(port, WK2XXX_SIFR_REG);
	/*  �����ж�                         ���ճ�ʱ�ж�    */
	if ((sifr & SIFR_RFTRIG_INT_BIT) || (sifr & SIFR_RXOVT_INT_BIT)) // �н����жϺͽ��ճ�ʱ�ж�
	{
		fsr = WkReadSlaveRegister(port, WK2XXX_FSR_REG);
		if (fsr & FSR_RDAT_BIT) /* ������շǿ� */
		{
			rfcnt = WkReadSlaveRegister(port, WK2XXX_RFCNT_REG);
			if (rfcnt == 0)
			{
				rfcnt = WkReadSlaveRegister(port, WK2XXX_RFCNT_REG);
			}
			rfcnt2 = WkReadSlaveRegister(port, WK2XXX_RFCNT_REG);
			if (rfcnt2 == 0)
			{
				rfcnt2 = WkReadSlaveRegister(port, WK2XXX_RFCNT_REG);
			}
			/*�ж�fifo�����ݸ���*/
			rfcnt = (rfcnt2 >= rfcnt) ? rfcnt : rfcnt2;
			len = (rfcnt == 0) ? 256 : rfcnt;
#if 1
			WkReadSlaveFifo(port, recbuf, len);
#else
			for (n = 0; n < len; n++)
				*(recbuf + n) = WkReadSlaveRegister(port, WK2XXX_FDAT_REG);
#endif
			return len;
		}
		else
		{
			return len;
		}
	}
	return len;
}




/************************************************************************************************/
// ��������:���ݴ�����������Ҫʵ�ְѽ��յ����ݣ�Ȼ���ٷ��ͳ�����
/**************************uint8_t WK2xxxPortProcess(void)********************************************/
uint8_t WkUartProcess(void)
{
	int rxlen = 0;
	uint8_t gifr, rxbuf[260];
	gifr = WkReadGlobalRegister(WK2XXX_GIFR_REG);
	do
	{
		// �ж��Ӵ���1�Ƿ����ж�
		if (gifr & GIFR_UT1INT_BIT)
		{									 /*���ݴ���*/
											 /*���ݽ���*/
			rxlen = WkUartRxChars(1, rxbuf); // һ�ν��յ����ݲ��ᳬ��256Byte
			/*���ݷ���*/
			// �ѽ��յ����ݷ��ͳ�ȥ
			if (rxlen > 0)
			{
				WkUartTxChars(1, rxlen, rxbuf);
			}
		}

		// �ж��Ӵ���2�Ƿ����ж�
		if (gifr & GIFR_UT2INT_BIT)
		{
			/*���ݽ���*/
			rxlen = WkUartRxChars(2, rxbuf); // һ�ν��յ����ݲ��ᳬ��256Byte
			/*���ݷ���*/
			// �ѽ��յ����ݷ��ͳ�ȥ
			if (rxlen > 0)
			{
				WkUartTxChars(2, rxlen, rxbuf);
			}
		}
		// �ж��Ӵ���3�Ƿ����ж�
		if (gifr & GIFR_UT3INT_BIT)
		{
			/*���ݽ���*/
			rxlen = WkUartRxChars(3, rxbuf); // һ�ν��յ����ݲ��ᳬ��256Byte
			/*���ݷ���*/
			// �ѽ��յ����ݷ��ͳ�ȥ
			if (rxlen > 0)
			{
				WkUartTxChars(3, rxlen, rxbuf);
			}
		}
		// �ж��Ӵ���4�Ƿ����ж�
		if (gifr & GIFR_UT4INT_BIT)
		{
			/*���ݽ���*/
			rxlen = WkUartRxChars(4, rxbuf); // һ�ν��յ����ݲ��ᳬ��256Byte
			/*���ݷ���*/
			// �ѽ��յ����ݷ��ͳ�ȥ
			if (rxlen > 0)
			{
				WkUartTxChars(4, rxlen, rxbuf);
			}
		}

		gifr = WkReadGlobalRegister(WK2XXX_GIFR_REG);
	} while (gifr & 0x0f);

	return gifr;
}

