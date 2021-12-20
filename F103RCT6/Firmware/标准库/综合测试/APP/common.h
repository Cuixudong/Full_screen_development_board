#ifndef __COMMON_H
#define __COMMON_H 	
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
#include "key.h"
#include "tpad.h"
#include "wdg.h" 	 
#include "timer.h"	 	 	 
#include "lcd.h"
#include "usmart.h"	
#include "rtc.h"
#include "wkup.h"	
#include "adc.h"	
#include "dac.h"	
#include "dma.h"	
#include "24cxx.h"	
#include "flash.h"	
#include "touch.h"	
#include "24l01.h"	
#include "remote.h"	 
#include "ds18b20.h"
#include "mpu6050.h"
#include "eMPL/inv_mpu.h"
#include "eMPL/inv_mpu_dmp_motion_driver.h"
#include "ps2.h"	
#include "mouse.h"	 
#include "stmflash.h"	 
#include "malloc.h"
#include "string.h"
#include "mmc_sd.h"
#include "ff.h"
#include "exfuns.h"  
#include "fontupd.h"
#include "text.h"		
#include "piclib.h"
#include "t9input.h" 
#include "includes.h"
#include "ff.h"
#include "piclib.h"
#include "gui.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP通用 代码	   
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


//硬件平台软硬件版本定义	   	
#define HARDWARE_VERSION	   		30		//硬件版本,放大10倍,如1.0表示为10
#define SOFTWARE_VERSION	    	230		//软件版本,放大100倍,如1.00,表示为100
//硬件V3.0
//1，采用STM32F103RCT6作为主控
//2，采用CH340G作为USB转串口芯片
//3，修改JTAG SWD的两个IO口被占用,从而影响仿真的问题.
//4，采用W25Q128作为外部FLASH存储器
//5，更改部分外设的连接方式.
//6，去掉JF24C的预留位置
 




//系统数据保存基址			  
#define SYSTEM_PARA_SAVE_BASE 		100		//系统信息保存首地址.从100开始.
			    
extern volatile uint8_t system_task_return;

////////////////////////////////////////////////////////////////////////////////////////////
//各图标/图片路径
extern uint8_t*const  APP_OK_PIC;			//确认图标
extern uint8_t*const  APP_CANCEL_PIC;		//取消图标
extern uint8_t*const  APP_UNSELECT_PIC;		//未选中图标
extern uint8_t*const  APP_SELECT_PIC;		//选中图标
extern uint8_t*const  APP_ASCII_60;			//大数字字体路径
extern uint8_t*const  APP_ASCII_28;			//大数字字体路径
extern uint8_t*const  APP_VOL_PIC;			//音量图片路径

extern uint8_t*const APP_ASCII_S6030;	//数码管大字体路径
extern uint8_t*const APP_ASCII_5427;		//普通大字体路径
extern uint8_t*const APP_ASCII_3618;		//普通大字体路径
extern uint8_t*const APP_ASCII_2814;		//普通大字体路径

extern uint8_t* asc2_s6030;				//数码管字体60*30大字体点阵集
extern uint8_t* asc2_5427;				//普通字体54*27大字体点阵集
extern uint8_t* asc2_3618;				//普通字体36*18大字体点阵集
extern uint8_t* asc2_2814;				//普通字体28*14大字体点阵集

extern const uint8_t APP_ALIENTEK_ICO1824[];	//启动界面图标,存放在flash
extern const uint8_t APP_ALIENTEK_ICO2432[];	//启动界面图标,存放在flash
extern const uint8_t APP_ALIENTEK_ICO3648[];	//启动界面图标,存放在flash
////////////////////////////////////////////////////////////////////////////////////////////
//APP的总功能数目
#define APP_FUNS_NUM	9

//app主要功能界面标题
extern uint8_t*const  APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM];
//平滑线的起止颜色定义
#define WIN_SMOOTH_LINE_SEC	0XB1FFC4	//起止颜色
#define WIN_SMOOTH_LINE_MC	0X1600B1	//中间颜色

//弹出窗口选择条目的设置信息
#define APP_ITEM_BTN1_WIDTH		60	  		//有2个按键时的宽度
#define APP_ITEM_BTN2_WIDTH		100			//只有1个按键时的宽度
#define APP_ITEM_BTN_HEIGHT		30			//按键高度
#define APP_ITEM_ICO_SIZE		32			//ICO图标的尺寸

#define APP_ITEM_SEL_BKCOLOR	0X0EC3		//选择时的背景色
#define APP_WIN_BACK_COLOR	 	0XC618		//窗体背景色


#define APP_FB_TOPBAR_HEIGHT	20			//文件浏览界面,顶部横条的高度
#define APP_FB_BTMBAR_HEIGHT	20			//文件浏览界面/测试界面,底部横条的高度
#define APP_TEST_TOPBAR_HEIGHT	20			//测试界面,顶部横条高度

//π值定义
#define	app_pi	3.1415926535897932384626433832795  
/////////////////////////////////////////////////////////////////////////
																			    
uint32_t  app_get_rand(uint32_t max);
void app_srand(uint32_t seed);
void app_set_lcdsize(uint8_t mode);
void app_read_bkcolor(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t *ctbl);
void app_recover_bkcolor(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t *ctbl);
void app_gui_tcbar(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t mode);
uint8_t app_get_numlen(long long num,uint8_t dir);
void app_show_float(uint16_t x,uint16_t y,long long num,uint8_t flen,uint8_t clen,uint8_t font,uint16_t color,uint16_t bkcolor);
void app_filebrower(uint8_t *topname,uint8_t mode);		 
void app_showbigchar(uint8_t *fontbase,uint16_t x,uint16_t y,uint8_t chr,uint8_t size,uint16_t color,uint16_t bkcolor);
void app_showbigstring(uint8_t *fontbase,uint16_t x,uint16_t y,const uint8_t *p,uint8_t size,uint16_t color,uint16_t bkcolor);
void app_showbignum(uint8_t *fontbase,uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color,uint16_t bkcolor);
void app_showbig2num(uint8_t *fontbase,uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint16_t color,uint16_t bkcolor);
void app_show_nummid(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint32_t num,uint8_t len,uint8_t size,uint16_t ptcolor,uint16_t bkcolor);
void app_draw_smooth_line(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint32_t sergb,uint32_t mrgb);
void app_show_mono_icos(uint16_t x,uint16_t y,uint8_t width,uint8_t height,uint8_t *icosbase,uint16_t color,uint16_t bkcolor);

uint8_t app_tp_is_in_area(_m_tp_dev *tp,uint16_t x,uint16_t y,uint16_t width,uint16_t height);
void app_show_items(uint16_t x,uint16_t y,uint16_t itemwidth,uint16_t itemheight,uint8_t*name,uint8_t*icopath,uint16_t color,uint16_t bkcolor);
uint8_t * app_get_icopath(uint8_t mode,uint8_t *selpath,uint8_t *unselpath,uint8_t selx,uint8_t index);
uint8_t app_items_sel(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t *items[],uint8_t itemsize,uint8_t *selx,uint8_t mode,uint8_t*caption);
uint8_t app_listbox_select(uint8_t *sel,uint8_t *top,uint8_t * caption,uint8_t *items[],uint8_t itemsize);
void app_show_mono_icos(uint16_t x,uint16_t y,uint8_t width,uint8_t height,uint8_t *icosbase,uint16_t color,uint16_t bkcolor);

uint8_t app_system_file_check(uint8_t* diskx);//系统文件检测
uint8_t app_boot_cpdmsg(uint8_t*pname,uint8_t pct,uint8_t mode);
void app_boot_cpdmsg_set(uint16_t x,uint16_t y,uint8_t fsize);
uint8_t app_system_update(uint8_t(*fcpymsg)(uint8_t*pname,uint8_t pct,uint8_t mode));
void app_getstm32_sn(uint32_t *sn0,uint32_t *sn1,uint32_t *sn2);
void app_get_version(uint8_t*buf,uint32_t ver,uint8_t len);//得到版本号

void app_usmart_getsn(void);//USMART专用.
uint8_t app_system_parameter_init(void);//系统信息初始化
#endif




























































