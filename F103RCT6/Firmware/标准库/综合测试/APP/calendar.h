#ifndef __CALENDAR_H
#define __CALENDAR_H
#include "sys.h"
#include "includes.h" 	   	 
#include "common.h" 
#include "rtc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-日历 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/7/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//修改信息
//无
////////////////////////////////////////////////////////////////////////////////// 	   
 
//闹钟结构体						   
__packed typedef struct  
{																				   			  
	uint8_t  weekmask;		//闹钟响铃掩码 bit0~bit6,代表周日~周6.   
	uint8_t  ringsta;		//闹铃状态及铃声标志.
						//[7]:0,无闹铃;1,闹铃中;
						//[6:3]:保留
						//[2:0]:闹钟铃声类型
	uint8_t  hour;	   		//闹铃小时
	uint8_t  min;			//闹铃分钟	 
	uint8_t saveflag;		//保存标志,0X0A,保存过了;其他,还从未保存	   
}_alarm_obj;

extern _alarm_obj alarm;//闹钟结构体
extern uint8_t*const calendar_week_table[GUI_LANGUAGE_NUM][7];//外部定义的星期表

void calendar_alarm_init(_alarm_obj *alarmx,_calendar_obj *calendarx);
void calendar_alarm_ring(uint8_t type);
void calendar_get_time(_calendar_obj *calendarx);
void calendar_get_date(_calendar_obj *calendarx);
void calendar_date_refresh(void);
void calendar_read_para(_alarm_obj * alarm);
void calendar_save_para(_alarm_obj * alarm);
uint8_t calendar_alarm_msg(uint16_t x,uint16_t y);
void calendar_circle_clock_drawpanel(uint16_t x,uint16_t y,uint16_t size,uint16_t d);
void calendar_circle_clock_showtime(uint16_t x,uint16_t y,uint16_t size,uint16_t d,uint8_t hour,uint8_t min,uint8_t sec);
uint8_t calendar_play(void);
					    				   
#endif












