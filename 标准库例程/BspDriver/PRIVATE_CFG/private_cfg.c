#include "./PRIVATE_CFG/private_cfg.h"



void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
/* 关闭所有中断 */
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
/* 开启所有中断 */
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
/* 设置栈顶地址 */
/* addr:栈顶地址 */
__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			
    BX r14
}



/* 加入以下代码,支持printf函数,而不需要选择use MicroLIB */
#pragma import(__use_no_semihosting)             
/* 标准库需要的支持函数 */                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x) 
{ 
	x = x; 
} 




/* 重定义fputc函数 */ 
int fputc(int ch, FILE *f)
{      
	/* 判断TC位 */
	while((USART1->SR & (1 << 6)) == 0);
	USART1->DR = (uint8_t) ch;      
	return ch;
}







