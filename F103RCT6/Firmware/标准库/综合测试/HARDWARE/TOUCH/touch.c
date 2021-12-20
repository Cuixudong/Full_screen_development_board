#include "touch.h" 
#include "lcd.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include "24cxx.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//触摸屏驱动(支持ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A/GT9147/FT5206等)代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/25
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved						 
//////////////////////////////////////////////////////////////////////////////////

_m_tp_dev tp_dev=
{
	TP_Init,
	0,
	0,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,
};

//触摸屏初始化  		    
//返回值:0,没有进行校准
//       1,进行过校准
uint8_t TP_Init(void)
{
	if(lcddev.id==0X5510)				//4.3寸电容触摸屏
	{
		if(GT9147_Init()==0)			//是GT9147
		{ 
			tp_dev.scan=GT9147_Scan;	//扫描函数指向GT9147触摸屏扫描
		}
		tp_dev.touchtype|=0X80;			//电容屏 
		tp_dev.touchtype|=lcddev.dir&0X01;//横屏还是竖屏 
		return 0;
	}
	return 1;
}
