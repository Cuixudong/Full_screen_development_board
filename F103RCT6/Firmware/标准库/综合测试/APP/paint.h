#ifndef __PAINT_H
#define __PAINT_H 	
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-画笔 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/2/16
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//新增对各种分辨率LCD的支持.
////////////////////////////////////////////////////////////////////////////////// 	   

////////////////////////////////////////////////////////////////////////////////////////////
//各图标/图片路径
extern const uint8_t *PAINT_COLOR_TBL_PIC;//颜色表路径
////////////////////////////////////////////////////////////////////////////////////////////




void paint_new_pathname(uint8_t *pname);
void paint_show_colorbar(uint16_t sx,uint16_t sy,uint8_t height);
uint8_t paint_pen_color_set(uint16_t x,uint16_t y,uint16_t* color,uint8_t*caption);
uint8_t paint_pen_size_set(uint16_t x,uint16_t y,uint16_t color,uint8_t *mode,uint8_t*caption);
void paint_draw_point(uint16_t x,uint16_t y,uint16_t color,uint8_t mode);	 
uint8_t paint_play(void);


#endif























