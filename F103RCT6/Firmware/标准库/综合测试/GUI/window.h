#ifndef __WINDOW_H
#define __WINDOW_H 			 
#include "guix.h"  
#include "button.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2012/10/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
//����˵�� 
//V1.1 20140815
//1,����window_creat������window_delete������Сbug
//2,�޸�window_msg_box����,����ʱ�����
//////////////////////////////////////////////////////////////////////////////////

//Ĭ�ϵĴ���caption����ɫcaption����ɫ.
//�Լ����屳��ɫ.
#define WIN_CAPTION_UPC	   	  			0X7D7C	//����CAPTION�ϲ������ɫ
#define WIN_CAPTION_DOWNC				0X5458	//����CAPTION�²������ɫ
#define WIN_CAPTION_COLOR				0XFFFF	//��������ɫΪ��ɫ
#define WIN_BODY_BKC					0XD699	//���ڵ�ɫ,0XEF5D

#define WIN_CAPTION_HEIGHT				0X20	//Ĭ�ϵĸ߶�

//�����ϵĹرհ�ť�����Ϣ����
#define WIN_BTN_SIZE					0X18	//�����γ� ��߳�(����С��WIN_CAPTION_HEIGHT)
#define WIN_BTN_OFFSIDE					0X06	//��ť/����ƫ��߿������

#define WIN_BTN_FUPC					0XFFFF	//��ť�ɿ�ʱ���ֵ���ɫ
#define WIN_BTN_FDOWNC					0XDCD0	//��ť����ʱ���ֵ���ɫ
#define WIN_BTN_RIMC					0XFE18	//�߿���ɫ
#define WIN_BTN_TP1C					0XF36D	//��һ�е���ɫ
#define WIN_BTN_UPHC					0XF36D	//�ϰ벿����ɫ,0X6D3C
#define WIN_BTN_DNHC					0XC800	//�°벿����ɫ,0XAE5C



//��׼����߿���ɫ����
#define STD_WIN_RIM_OUTC 	0X3317	    //������ɫ
#define STD_WIN_RIM_MIDC 	0X859B		//������ɫ
#define STD_WIN_RIM_INC 	0X2212		//������ɫ	    		   
//Բ�ߴ���߿���ɫ����
#define ARC_WIN_RIM_COLOR 	0XB595	    //������ɫ  


//window�ṹ�嶨��
__packed typedef struct 
{
	uint16_t top; 				  		//window��������
	uint16_t left;                       //window�������
	uint16_t width; 				  		//window���(�����������Ŀ��)
	uint16_t height;						//window�߶�

	uint8_t id;							//window
	uint8_t type;						//window����
									//[7]:0,û�йرհ�ť.1,�йرհ�ť			   
									//[6]:0,����ȡ����ɫ.1,��ȡ����ɫ.					 
									//[5]:0,���⿿��.1,�������.					 
									//[4:2]:����					 
									//[1:0]:0,��׼�Ĵ���(��XP);1,Բ�ߴ���(��Andriod)			   

	uint8_t sta;							//window״̬
 									//[7:0]:����

	uint8_t *caption;					//window����
	uint8_t captionheight;				//caption���ĸ߶�
	uint8_t font;						//window��������
	uint8_t arcwinr;						//Բ�Ǵ��ڵ�Բ�ǵİ뾶	
										
	uint16_t captionbkcu; 				//caption���ϰ벿�ֱ���ɫ
	uint16_t captionbkcd; 				//caption���°벿�ֱ���ɫ
 	uint16_t captioncolor; 				//caption����ɫ
	uint16_t windowbkc; 					//window�ı���ɫ

	uint16_t *bkctbl;					//����ɫ��(��Ҫ��ȡ���屳��ɫ��ʱ���õ�)
	_btn_obj* closebtn;				//���ڹرհ�ť
}_window_obj;

_window_obj * window_creat(uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint8_t id,uint8_t type,uint8_t font);
void window_delete(_window_obj * window_del);
void window_draw(_window_obj * windowx);
uint8_t window_msg_box(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t *str,uint8_t *caption,uint8_t font,uint16_t color,uint8_t mode,uint16_t time);




void win_test(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t type,uint16_t cup,uint16_t cdown,uint8_t *caption);
#endif

















