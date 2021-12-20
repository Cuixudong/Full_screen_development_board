#ifndef __SETTINGS_H
#define __SETTINGS_H
#include "sys.h"
#include "includes.h" 	   	 
#include "common.h"    
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
 
//list�ṹ��.����ṹ
__packed typedef struct 
{
	uint8_t syslanguage;			//Ĭ��ϵͳ����
 	uint8_t lcdbklight;			//LED�������� 10~110.10�����;110��������
	uint8_t picmode;				//ͼƬ���ģʽ:0,˳��ѭ������;1,�������.
	uint8_t audiomode;			//��Ƶ����ģʽ:0,˳��ѭ������;1,�������;2,����ѭ������.
	uint8_t videomode;			//��Ƶ����ģʽ:0,˳��ѭ������;1,�������;2,����ѭ������.
	uint8_t saveflag;			//�����־,0X0A,�������;����,����δ����	   
}_system_setings;

extern _system_setings systemset;	//��settings.c�������� 

uint8_t sysset_time_set(uint16_t x,uint16_t y,uint8_t *hour,uint8_t *min,uint8_t*caption);
uint8_t sysset_date_set(uint16_t x,uint16_t y,uint16_t *year,uint8_t *month,uint8_t *date,uint8_t*caption);
//void sysset_wm8978_vol3d_show(uint16_t x,uint16_t y,uint8_t mask,uint8_t val);
//void sysset_wm8978_eq_show(uint16_t x,uint16_t y,uint8_t mask,uint8_t eqx,uint8_t val);
//uint8_t sysset_wm8978_vol3d_set(uint16_t x,uint16_t y,_wm8978_obj *wmset,uint8_t* caption);
//uint8_t sysset_wm8978_eq_set(uint16_t x,uint16_t y,_wm8978_obj *wmset,uint8_t eqx,uint8_t* caption);
uint8_t sysset_bklight_set(uint16_t x,uint16_t y,uint8_t* caption,uint16_t *bkval);
uint8_t sysset_system_update_cpymsg(uint8_t*pname,uint8_t pct,uint8_t mode);
void sysset_system_update(uint8_t*caption,uint16_t sx,uint16_t sy);
void sysset_system_info(uint16_t x,uint16_t y,uint8_t*caption);
void sysset_system_status(uint16_t x,uint16_t y,uint8_t* caption);
void sysset_system_about(uint16_t x,uint16_t y,uint8_t*caption);
uint8_t* set_search_caption(const uint8_t *mcaption);	 
void sysset_read_para(_system_setings * sysset);
void sysset_save_para(_system_setings * sysset);

uint8_t sysset_play(void);

void wifi_set(uint16_t x,uint16_t y,uint8_t*caption);

#endif
