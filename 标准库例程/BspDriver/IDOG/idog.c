#include "./IDOG/idog.h"

/*
	时钟来源 LSI 40K 实际会在（30-60KHz变化）
	8位分频寄存器
	12位重装载寄存器
*/
void idog_init(uint8_t prc,uint16_t rlr)
{
	/* 使能写入才能对 PR RLR 寄存器操作 写入0x5555*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(prc);
	IWDG_SetReload(rlr);
	/* 重新加载重装载值 防止重启 写入0xaaaa*/
	IWDG_ReloadCounter();
	/* 使能IDOG 写入0xcccc*/
	IWDG_Enable();
}


void idog_restart(void)
{
	IWDG_ReloadCounter();
}


