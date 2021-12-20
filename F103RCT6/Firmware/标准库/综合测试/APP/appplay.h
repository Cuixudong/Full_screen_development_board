#ifndef __APPPLAY_H
#define __APPPLAY_H 	
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-其他应用程序 代码	   
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
extern uint8_t*const appplay_icospath_tbl[16];//icos的路径表
////////////////////////////////////////////////////////////////////////////////////////////


//APP图标参数管理
__packed typedef struct _m_app_icos
{										    
	uint16_t x;			//图标坐标及尺寸
	uint16_t y;
	uint8_t width;
	uint8_t height; 
	uint8_t * path;		//图标路径
	uint8_t * name;		//图标名字
}m_app_icos;

//APP控制器
typedef struct _m_app_dev
{										    
	uint8_t selico;					//当前选中的图标.
								//0~15,被选中的图标编号	 
								//其他,没有任何图标被选中	  
	m_app_icos icos[16];		//总共16个图标
}m_app_dev;
		 

uint8_t app_play(void);
uint8_t Remote_Play(uint8_t* caption);

#endif























