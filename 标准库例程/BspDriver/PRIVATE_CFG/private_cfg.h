#ifndef _PRIVATE_CFG_H_
#define _PRIVATE_CFG_H_

#include "main.h"


#define 	HIGH		1
#define 	LOW			1

#define 	ON			1
#define 	OFF			0




/* ִ��WFIָ�� */
void WFI_SET(void);
/* �ر������ж� */
void INTX_DISABLE(void);
/* ���������ж� */
void INTX_ENABLE(void);
/* ���ö�ջ��ַ */
void MSR_MSP(uint32_t addr);	






#endif

