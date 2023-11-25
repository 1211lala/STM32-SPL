/*
 * @Author: liuao 2494210546@qq.com
 * @Date: 2023-11-23 09:43:44
 * @LastEditors: liuao 2494210546@qq.com
 * @LastEditTime: 2023-11-25 13:25:37
 * @FilePath: \USERe:\MY_CODE\Standard-Peripheral\标准库例程\BspDriver\DELAY\delay.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _DELAY_H_
#define _DELAY_H_

#include "main.h"

extern uint32_t us_num;
extern uint32_t ms_num;

void systick_delay_init(uint8_t sysfreq);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
#endif
