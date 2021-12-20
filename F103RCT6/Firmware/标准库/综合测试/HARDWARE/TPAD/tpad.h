#ifndef __TPAD_H
#define __TPAD_H
#include "sys.h"		
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//TPAD驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/5
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
extern volatile uint16_t tpad_default_val;
							   	    
void		TPAD_Reset(void);
uint16_t	TPAD_Get_Val(void);
uint16_t	TPAD_Get_MaxVal(uint8_t n);
uint8_t		TPAD_Init(uint8_t psc);
uint8_t		TPAD_Scan(uint8_t mode);
void		TIM2_CH1_Cap_Init(uint16_t arr,uint16_t psc);   
#endif
