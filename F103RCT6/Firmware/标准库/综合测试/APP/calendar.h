#ifndef __CALENDAR_H
#define __CALENDAR_H
#include "sys.h"
#include "includes.h" 	   	 
#include "common.h" 
#include "rtc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   
 
//���ӽṹ��						   
__packed typedef struct  
{																				   			  
	uint8_t  weekmask;		//������������ bit0~bit6,��������~��6.   
	uint8_t  ringsta;		//����״̬��������־.
						//[7]:0,������;1,������;
						//[6:3]:����
						//[2:0]:������������
	uint8_t  hour;	   		//����Сʱ
	uint8_t  min;			//�������	 
	uint8_t saveflag;		//�����־,0X0A,�������;����,����δ����	   
}_alarm_obj;

extern _alarm_obj alarm;//���ӽṹ��
extern uint8_t*const calendar_week_table[GUI_LANGUAGE_NUM][7];//�ⲿ��������ڱ�

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












