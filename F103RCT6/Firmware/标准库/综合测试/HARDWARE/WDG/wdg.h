#ifndef __WDG_H
#define __WDG_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//看门狗 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/06
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved						
//********************************************************************************
//V1.1 20140306
//增加了窗口看门狗相关函数。
////////////////////////////////////////////////////////////////////////////////// 	  


void IWDG_Init(uint8_t prer,uint16_t rlr);
void IWDG_Feed(void);
void WWDG_Init(uint8_t tr,uint8_t wr,uint8_t fprer);
void WWDG_Set_Counter(uint8_t cnt);
#endif




























