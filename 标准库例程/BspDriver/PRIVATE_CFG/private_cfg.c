#include "./PRIVATE_CFG/private_cfg.h"



void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
/* �ر������ж� */
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
/* ���������ж� */
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
/* ����ջ����ַ */
/* addr:ջ����ַ */
__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			
    BX r14
}



/* �������´���,֧��printf����,������Ҫѡ��use MicroLIB */
#pragma import(__use_no_semihosting)             
/* ��׼����Ҫ��֧�ֺ��� */                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x) 
{ 
	x = x; 
} 




/* �ض���fputc���� */ 
int fputc(int ch, FILE *f)
{      
	/* �ж�TCλ */
	while((USART1->SR & (1 << 6)) == 0);
	USART1->DR = (uint8_t) ch;      
	return ch;
}







