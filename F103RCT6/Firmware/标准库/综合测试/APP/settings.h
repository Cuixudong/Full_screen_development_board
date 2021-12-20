#ifndef __SETTINGS_H
#define __SETTINGS_H
#include "sys.h"
#include "includes.h" 	   	 
#include "common.h"    
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-设置 代码	   
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
 
//list结构体.链表结构
__packed typedef struct 
{
	uint8_t syslanguage;			//默认系统语言
 	uint8_t lcdbklight;			//LED背光亮度 10~110.10代表最暗;110代表最亮
	uint8_t picmode;				//图片浏览模式:0,顺序循环播放;1,随机播放.
	uint8_t audiomode;			//音频播放模式:0,顺序循环播放;1,随机播放;2,单曲循环播放.
	uint8_t videomode;			//视频播放模式:0,顺序循环播放;1,随机播放;2,单曲循环播放.
	uint8_t saveflag;			//保存标志,0X0A,保存过了;其他,还从未保存	   
}_system_setings;

extern _system_setings systemset;	//在settings.c里面设置 

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
