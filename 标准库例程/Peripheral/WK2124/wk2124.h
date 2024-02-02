#ifndef _WK2124_H_
#define _WK2124_H_

#include "main.h"


#define WK_CS_Port	GPIOA
#define WK_CS_Pin 	GPIO_Pin_4

/*External clock=11.0592Mhz*/
#define 	WK2XXX_FREQ_CLK     (11059200)
/*TX FIFO Trigger level*/
#define 	WK2XXX_TX_FIFO_ TRI    (0X10)
/*RX FIFO Trigger level*/
#define 	WK2XXX_RX_FIFO_ TRI    (0X40)


/* WK2xxxȫ����λ�Ĵ�����ַ���� */
#define 	WK2XXX_GENA_REG     (0X00)		/* ȫ�ֿ��ƼĴ��� */
#define 	WK2XXX_GRST_REG     (0X01)		/* ȫ���Ӵ��ڸ�λ�Ĵ��� */
#define		WK2XXX_GMUT_REG     (0X02)		/* û�ҵ�ɶ���� */
#define 	WK2XXX_GIER_REG     (0X10)		/* ȫ���жϼĴ��� */
#define 	WK2XXX_GIFR_REG     (0X11)		/* ȫ���жϱ�־�Ĵ��� */
	
#define 	WK2XXX_GPDIR_REG    (0X21)		/* only on wk2168/wk2212*/
#define 	WK2XXX_GPDAT_REG    (0X31)		/* only on wk2168/wk2212*/


/*WK2xxx�Ӵ�����λ�Ĵ�����ַ����*/
#define 	WK2XXX_SPAGE_REG    (0X03)		/* �Ӵ���ҳ���ƼĴ��� */
/*PAGE0*/
#define 	WK2XXX_SCR_REG      (0X04)		/* �Ӵ��ڿ��ƼĴ��� */
#define 	WK2XXX_LCR_REG      (0X05)  	/* �Ӵ������üĴ��� */
#define 	WK2XXX_FCR_REG      (0X06)  	/* �Ӵ��� FIFO ���ƼĴ��� */
#define 	WK2XXX_SIER_REG     (0X07)  	/* �Ӵ����ж�ʹ�ܼĴ��� */
#define 	WK2XXX_SIFR_REG     (0X08)		/* �Ӵ����жϱ�־�Ĵ��� */
#define 	WK2XXX_TFCNT_REG    (0X09)  	/* �Ӵ��ڷ��� FIFO �����Ĵ��� */
#define 	WK2XXX_RFCNT_REG    (0X0A)  	/* �Ӵ��ڽ��� FIFO �����Ĵ��� */
#define 	WK2XXX_FSR_REG      (0X0B)		/* �Ӵ��� FIFO ״̬�Ĵ��� */
#define 	WK2XXX_LSR_REG      (0X0C)		/* �Ӵ��ڽ���״̬�Ĵ��� */
#define 	WK2XXX_FDAT_REG     (0X0D)		/* �Ӵ��� FIFO ���ݼĴ��� */

#define 	WK2XXX_FWCR_REG     (0X0E)		/* WK2124�޶��� */
#define 	WK2XXX_RS485_REG    (0X0F)		/* WK2124�޶��� */
/*PAGE1*/
#define 	WK2XXX_BAUD1_REG    (0X04)		/* �Ӵ��ڲ��������üĴ������ֽ� */
#define 	WK2XXX_BAUD0_REG    (0X05)		/* �Ӵ��ڲ��������üĴ������ֽ� */
#define 	WK2XXX_PRES_REG     (0X06)		/* �Ӵ��ڲ��������üĴ���С������ */
#define 	WK2XXX_RFTL_REG     (0X07)  	/* �Ӵ��ڽ��� FIFO �жϴ��������üĴ��� */
#define 	WK2XXX_TFTL_REG     (0X08)  	/* �Ӵ��ڷ��� FIFO �жϴ��������üĴ��� */

#define 	WK2XXX_FWTH_REG     (0X09)		/* WK2124�޶��� */
#define 	WK2XXX_FWTL_REG     (0X0A)		/* WK2124�޶��� */
#define 	WK2XXX_XON1_REG     (0X0B)  	/* WK2124�޶��� */
#define 	WK2XXX_XOFF1_REG    (0X0C)		/* WK2124�޶��� */
#define 	WK2XXX_SADR_REG     (0X0D)		/* WK2124�޶��� */
#define 	WK2XXX_SAEN_REG     (0X0E)		/* WK2124�޶��� */
#define 	WK2XXX_RTSDLY_REG   (0X0F)		/* WK2124�޶��� */


/* GENA �Ĵ�����λ���� */
#define 	GENA_UT4EN_BIT		  (1 << 3)		/* �Ӵ���4ʱ��ʹ��λ 1:ʹ�� 0:δʹ�� */
#define 	GENA_UT3EN_BIT		  (1 << 2)		/* �Ӵ���3ʱ��ʹ��λ 1:ʹ�� 0:δʹ�� */
#define 	GENA_UT2EN_BIT		  (1 << 1)		/* �Ӵ���2ʱ��ʹ��λ 1:ʹ�� 0:δʹ�� */
#define 	GENA_UT1EN_BIT	      (1 << 0)		/* �Ӵ���1ʱ��ʹ��λ 1:ʹ�� 0:δʹ�� */
/* GRST �Ĵ�����λ���� */
#define 	GRST_UT4SLEEP_BIT	  (1 << 7)		/* �Ӵ��� 4 ����״̬λ */
#define 	GRST_UT3SLEEP_BIT	  (1 << 6)		/* �Ӵ��� 3 ����״̬λ */
#define 	GRST_UT2SLEEP_BIT	  (1 << 5)		/* �Ӵ��� 2 ����״̬λ */
#define 	GRST_UT1SLEEP_BIT	  (1 << 4)		/* �Ӵ��� 1 ����״̬λ */
#define 	GRST_UT4RST_BIT	      (1 << 3)		/* �Ӵ��� 4 ��λ����λ */
#define 	GRST_UT3RST_BIT	      (1 << 2)		/* �Ӵ��� 3 ��λ����λ */
#define 	GRST_UT2RST_BIT	      (1 << 1)		/* �Ӵ��� 2 ��λ����λ */	
#define 	GRST_UT1RST_BIT	      (1 << 0)		/* �Ӵ��� 1 ��λ����λ */
/* GIER �Ĵ�����λ���� */
#define 	GIER_UT4IE_BIT	      (1 << 3)		/* �Ӵ��� 4 �ж�ʹ�ܿ���λ */
#define 	GIER_UT3IE_BIT	      (1 << 2)		/* �Ӵ��� 3 �ж�ʹ�ܿ���λ */
#define 	GIER_UT2IE_BIT	      (1 << 1)		/* �Ӵ��� 2 �ж�ʹ�ܿ���λ */	
#define 	GIER_UT1IE_BIT	      (1 << 0)		/* �Ӵ��� 1 �ж�ʹ�ܿ���λ */
/* GIFR �Ĵ�����λ���� */
#define 	GIFR_UT4INT_BIT	      (1 << 3)		/* �Ӵ��� 4 �жϱ�־λ */
#define 	GIFR_UT3INT_BIT	      (1 << 2)		/* �Ӵ��� 3 �жϱ�־λ */
#define 	GIFR_UT2INT_BIT	      (1 << 1)		/* �Ӵ��� 2 �жϱ�־λ */
#define 	GIFR_UT1INT_BIT	      (1 << 0)		/* �Ӵ��� 1 �жϱ�־λ */
/* GPDIR register bits */
/* GPDAT register bits */


/* SPAGE register */
#define 	WK2XXX_SPAGE0	      (0x00)		/*PAGE �Ӵ���ҳ����λ(�Ӵ��ڼĴ����ֲ��� PAGE0 ��PAGE1 �ϣ���ͬҳ֮����л���ͨ���üĴ���������)*/
#define 	WK2XXX_SPAGE1         (0x01)
/* SCR register bits */
#define 	SCR_SLEEPEN_BIT	      (1 << 2)		/* �Ӵ�������ʹ��λ */
#define 	SCR_TXEN_BIT          (1 << 1)		/* �Ӵ��ڷ���ʹ��λ */
#define 	SCR_RXEN_BIT          (1 << 0)		/* �Ӵ��ڽ���ʹ��λ */
/* LCR register bits */
#define 	LCR_BREAK_BIT	      (1 << 5)		/* �Ӵ��� Line-Break �������λ */
#define 	LCR_IREN_BIT          (1 << 4)		/* �Ӵ��ں���ʹ��λ */
#define 	LCR_PAEN_BIT          (1 << 3)		/* �Ӵ���У��ʹ��λ  0����У��λ��8 λ���ݣ� 1����У��λ��9 λ���ݣ� */
#define 	LCR_PAM1_BIT          (1 << 2)		/* �Ӵ���У��ģʽѡ��λ  00��0 У�� ��01����У�� ��10��żУ�� ��11��1У��*/
#define 	LCR_PAM0_BIT          (1 << 1)		/* �Ӵ���У��ģʽѡ��λ */
#define 	LCR_STPL_BIT          (1 << 0)		/* �Ӵ���ֹͣλ���ȿ���λ 0:1bit 1:2bits*/
/* FCR register bits */
#define 	FCR_TFTRIG1_BIT	      (1 << 7)		/* �Ӵ��ڷ��� FIFO ��������λ*/
#define 	FCR_TFTRIG0_BIT       (1 << 6)		/* �Ӵ��ڷ��� FIFO ��������λ*/
#define 	FCR_RFTRIG1_BIT	      (1 << 5)		/* �Ӵ��ڽ��� FIFO ��������λ */
#define 	FCR_RFTRIG0_BIT       (1 << 4)		/* �Ӵ��ڽ��� FIFO ��������λ */
#define 	FCR_TFEN_BIT          (1 << 3)		/* �Ӵ��ڷ��� FIFO ʹ��λ */
#define 	FCR_RFEN_BIT          (1 << 2)		/* �Ӵ��ڽ��� FIFO ʹ��λ */
#define 	FCR_TFRST_BIT         (1 << 1)		/* �Ӵ��ڷ��� FIFO ��λλ */
#define 	FCR_RFRST_BIT         (1 << 0)		/* �Ӵ��ڽ��� FIFO ��λλ */
/* SIER register bits */
#define 	SIER_FERR_IEN_BIT     (1 << 7)		/* ���� FIFO ���ݴ����ж�ʹ��λ */
#define 	SIER_CTS_IEN_BIT      (1 << 6)		/* */
#define 	SIER_RTS_IEN_BIT      (1 << 5)		/* */
#define 	SIER_XOFF_IEN_BIT     (1 << 4)		/* */
#define 	SIER_TFEMPTY_IEN_BIT  (1 << 3)		/* ���� FIFO ���ж�ʹ��λ */
#define 	SIER_TFTRIG_IEN_BIT   (1 << 2)		/* ���� FIFO �����ж�ʹ��λ */	
#define 	SIER_RXOUT_IEN_BIT    (1 << 1)		/* ���� FIFO ��ʱ�ж�ʹ��λ */
#define 	SIER_RFTRIG_IEN_BIT   (1 << 0)		/* ���� FIFO �����ж�ʹ��λ */
/* SIFR register bits */
#define 	SIFR_FERR_INT_BIT     (1 << 7)		/* ���� FIFO ���ݴ����жϱ�־λ */
#define 	SIFR_CTS_INT_BIT      (1 << 6)
#define 	SIFR_RTS_INT_BIT      (1 << 5)
#define 	SIFR_XOFF_INT_BIT     (1 << 4)
#define 	SIFR_TFEMPTY_INT_BIT  (1 << 3)		/* ���� FIFO ���жϱ�־λ */
#define 	SIFR_TFTRIG_INT_BIT   (1 << 2)		/* ���� FIFO �����жϱ�־λ */
#define 	SIFR_RXOVT_INT_BIT    (1 << 1)		/* ���� FIFO ��ʱ�жϱ�־λ */
#define 	SIFR_RFTRIG_INT_BIT   (1 << 0)		/* ���� FIFO �����жϱ�־λ */

/* FSR register bits */
#define 	FSR_RFOE_BIT          (1 << 7)		/* �Ӵ��ڽ��� FIFO ��������������־λ */
#define 	FSR_RFBI_BIT          (1 << 6)		/* �Ӵ��ڽ��� FIFO �������� Line-Break ���� */
#define 	FSR_RFFE_BIT          (1 << 5)		/* �Ӵ��ڽ��� FIFO ������֡�����־λ */
#define 	FSR_RFPE_BIT          (1 << 4)		/* �Ӵ��ڽ��� FIFO ������У������־λ */
#define 	FSR_RDAT_BIT          (1 << 3)		/* �Ӵ��ڽ��� FIFO �ձ�־λ */
#define 	FSR_TDAT_BIT          (1 << 2)		/* �Ӵ��ڷ��� FIFO �ձ�־λ */
#define 	FSR_TFULL_BIT         (1 << 1)		/* �Ӵ��ڷ��� FIFO ����־λ */
#define 	FSR_TBUSY_BIT         (1 << 0)		/* �Ӵ��ڷ��� TX æ��־λ */
/* LSR register bits */
#define 	LSR_OE_BIT            (1 << 3)		/* �Ӵ��ڽ��� FIFO �е�ǰ����ȡ���ֽ���������־λ */
#define 	LSR_BI_BIT            (1 << 2)		/* �Ӵ��ڽ��� FIFO �е�ǰ����ȡ�ֽ� Line-Break �����־λ */
#define 	LSR_FE_BIT            (1 << 1)		/* �Ӵ��ڽ��� FIFO �е�ǰ����ȡ�ֽ�֡�����־λ */
#define 	LSR_PE_BIT            (1 << 0)		/* �Ӵ��ڽ��� FIFO �е�ǰ����ȡ�ֽ�У������־λ */
/* FWCR register bits */
#define 	FWCR_X2RF_BIT         (1 << 7)
#define 	FWCR_FWM2_BIT         (1 << 6)
#define 	FWCR_FWM1_BIT         (1 << 5)
#define 	FWCR_FWM0_BIT         (1 << 4)
#define 	FWCR_FWTRIG1_BIT      (1 << 3)
#define 	FWCR_FWTRIG0_BIT      (1 << 2)
#define 	FWCR_RTS_BIT          (1 << 1)
#define 	FWCR_CTS_BIT          (1 << 0)
/* RS485 register bits */
#define 	RS485_RS485_BIT       (1 << 6)
#define 	RS485_ATADD_BIT       (1 << 5)
#define 	RS485_DATEN_BIT       (1 << 4)
#define 	RS485_RTSEN_BIT       (1 << 1)
#define 	RS485_RTSINV_BIT      (1 << 0)



#define WK2XXX_UART_STOPBITS_1                     0x00
#define WK2XXX_UART_STOPBITS_2                     ((uint8_t)LCR_STPL_BIT)


/**UART_Parity : UART ����ѡ��
*/
#define WK2XXX_UART_PARITY_NONE                    0x00																										/* ��У��(NONE) */
#define WK2XXX_UART_PARITY_SPACE                   ((uint8_t)( LCR_PAEN_BIT)) 								/* 0У��(SPACE) */
#define WK2XXX_UART_PARITY_EVEN                    ((uint8_t)(LCR_PAM1_BIT | LCR_PAEN_BIT))					/* żУ��(EVEN) */
#define WK2XXX_UART_PARITY_ODD                     ((uint8_t)(LCR_PAM0_BIT | LCR_PAEN_BIT))					/* ��У��(ODD) */ 
#define WK2XXX_UART_PARITY_MARK                    ((uint8_t)(LCR_PAM0_BIT | LCR_PAM1_BIT|LCR_PAEN_BIT)) 	/* 1У��(MARK) */






void wk2124_init(void);
void Wk2xxxRstInit(void);
void WK2124_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
void WkWriteGlobalRegister(uint8_t greg,uint8_t dat);
uint8_t WkReadGlobalRegister(uint8_t greg);
void WkWriteSlaveRegister(uint8_t port,uint8_t sreg,uint8_t dat);
uint8_t WkReadSlaveRegister(uint8_t port,uint8_t sreg);
void WkWriteSlaveFifo(uint8_t port,uint8_t *dat,uint16_t len);
void WkReadSlaveFifo(uint8_t port,uint8_t *rec,int len);
void WkUartInit(uint8_t port);
void WkUartDeInit(uint8_t port);
uint8_t WkUartSetBaud(uint8_t port,uint32_t baudrate);
unsigned char WkUartFormatSet(uint8_t port,uint8_t stopformat,uint8_t paritytype);


int WkUartTxChars(uint8_t port,int len,uint8_t *sendbuf);
int WkUartTxLen(uint8_t port);
int WkUartRxChars(uint8_t port,uint8_t *recbuf);
void WkUartRS485(uint8_t port);
void WkUartRTSCTS(uint8_t port);
uint8_t WkUartProcess(void);
#endif
