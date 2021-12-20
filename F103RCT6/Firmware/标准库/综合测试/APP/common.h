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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APPͨ�� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/2/16
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//�����Ը��ֱַ���LCD��֧��.
////////////////////////////////////////////////////////////////////////////////// 	  


//Ӳ��ƽ̨��Ӳ���汾����	   	
#define HARDWARE_VERSION	   		30		//Ӳ���汾,�Ŵ�10��,��1.0��ʾΪ10
#define SOFTWARE_VERSION	    	230		//����汾,�Ŵ�100��,��1.00,��ʾΪ100
//Ӳ��V3.0
//1������STM32F103RCT6��Ϊ����
//2������CH340G��ΪUSBת����оƬ
//3���޸�JTAG SWD������IO�ڱ�ռ��,�Ӷ�Ӱ����������.
//4������W25Q128��Ϊ�ⲿFLASH�洢��
//5�����Ĳ�����������ӷ�ʽ.
//6��ȥ��JF24C��Ԥ��λ��
 




//ϵͳ���ݱ����ַ			  
#define SYSTEM_PARA_SAVE_BASE 		100		//ϵͳ��Ϣ�����׵�ַ.��100��ʼ.
			    
extern volatile uint8_t system_task_return;

////////////////////////////////////////////////////////////////////////////////////////////
//��ͼ��/ͼƬ·��
extern uint8_t*const  APP_OK_PIC;			//ȷ��ͼ��
extern uint8_t*const  APP_CANCEL_PIC;		//ȡ��ͼ��
extern uint8_t*const  APP_UNSELECT_PIC;		//δѡ��ͼ��
extern uint8_t*const  APP_SELECT_PIC;		//ѡ��ͼ��
extern uint8_t*const  APP_ASCII_60;			//����������·��
extern uint8_t*const  APP_ASCII_28;			//����������·��
extern uint8_t*const  APP_VOL_PIC;			//����ͼƬ·��

extern uint8_t*const APP_ASCII_S6030;	//����ܴ�����·��
extern uint8_t*const APP_ASCII_5427;		//��ͨ������·��
extern uint8_t*const APP_ASCII_3618;		//��ͨ������·��
extern uint8_t*const APP_ASCII_2814;		//��ͨ������·��

extern uint8_t* asc2_s6030;				//���������60*30���������
extern uint8_t* asc2_5427;				//��ͨ����54*27���������
extern uint8_t* asc2_3618;				//��ͨ����36*18���������
extern uint8_t* asc2_2814;				//��ͨ����28*14���������

extern const uint8_t APP_ALIENTEK_ICO1824[];	//��������ͼ��,�����flash
extern const uint8_t APP_ALIENTEK_ICO2432[];	//��������ͼ��,�����flash
extern const uint8_t APP_ALIENTEK_ICO3648[];	//��������ͼ��,�����flash
////////////////////////////////////////////////////////////////////////////////////////////
//APP���ܹ�����Ŀ
#define APP_FUNS_NUM	9

//app��Ҫ���ܽ������
extern uint8_t*const  APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern uint8_t*const  APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM];
//ƽ���ߵ���ֹ��ɫ����
#define WIN_SMOOTH_LINE_SEC	0XB1FFC4	//��ֹ��ɫ
#define WIN_SMOOTH_LINE_MC	0X1600B1	//�м���ɫ

//��������ѡ����Ŀ��������Ϣ
#define APP_ITEM_BTN1_WIDTH		60	  		//��2������ʱ�Ŀ��
#define APP_ITEM_BTN2_WIDTH		100			//ֻ��1������ʱ�Ŀ��
#define APP_ITEM_BTN_HEIGHT		30			//�����߶�
#define APP_ITEM_ICO_SIZE		32			//ICOͼ��ĳߴ�

#define APP_ITEM_SEL_BKCOLOR	0X0EC3		//ѡ��ʱ�ı���ɫ
#define APP_WIN_BACK_COLOR	 	0XC618		//���屳��ɫ


#define APP_FB_TOPBAR_HEIGHT	20			//�ļ��������,���������ĸ߶�
#define APP_FB_BTMBAR_HEIGHT	20			//�ļ��������/���Խ���,�ײ������ĸ߶�
#define APP_TEST_TOPBAR_HEIGHT	20			//���Խ���,���������߶�

//��ֵ����
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

uint8_t app_system_file_check(uint8_t* diskx);//ϵͳ�ļ����
uint8_t app_boot_cpdmsg(uint8_t*pname,uint8_t pct,uint8_t mode);
void app_boot_cpdmsg_set(uint16_t x,uint16_t y,uint8_t fsize);
uint8_t app_system_update(uint8_t(*fcpymsg)(uint8_t*pname,uint8_t pct,uint8_t mode));
void app_getstm32_sn(uint32_t *sn0,uint32_t *sn1,uint32_t *sn2);
void app_get_version(uint8_t*buf,uint32_t ver,uint8_t len);//�õ��汾��

void app_usmart_getsn(void);//USMARTר��.
uint8_t app_system_parameter_init(void);//ϵͳ��Ϣ��ʼ��
#endif




























































