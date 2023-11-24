#ifndef _PRIVATE_CFG_H_
#define _PRIVATE_CFG_H_

#include "main.h"


#define 	HIGH		1
#define 	LOW			1

#define 	ON			1
#define 	OFF			0




/* 执行WFI指令 */
void WFI_SET(void);
/* 关闭所有中断 */
void INTX_DISABLE(void);
/* 开启所有中断 */
void INTX_ENABLE(void);
/* 设置堆栈地址 */
void MSR_MSP(uint32_t addr);	






#endif

