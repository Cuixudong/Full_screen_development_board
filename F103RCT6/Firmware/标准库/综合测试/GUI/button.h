#ifndef __BUTTON_H
#define __BUTTON_H 			 
#include "guix.h"  
#include "button.h"
#include "piclib.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-��ť ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2012/10/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved	
//********************************************************************************
//����˵�� 
//V1.1 20140722
//1,�޸�btn_draw_picbtn����,֧��ͼƬ��ť�ߴ����ͼƬ�ߴ�,ͼƬ������ʾ
//2,�޸�btn_check����,���Ӷ���Ч�������жϴ���.
//////////////////////////////////////////////////////////////////////////////////

//��׼��ť�߿���ɫ����
#define STD_BTN_LTOC 	0XFFFF	    //��������ɫ
#define STD_BTN_LTIC 	0XDEFC		//��������ɫ
#define STD_BTN_RBOC 	0X8431		//��������ɫ
#define STD_BTN_RBIC 	0XA535		//��������ɫ
#define STD_BTN_INSC	0XEF5D	    //��ť�ڲ������ɫ
#define STD_BTN_DFLC	0XA535 		//δʹ�ܰ�ťcaption�����ɫ
#define STD_BTN_DFRC	0XFFFF		//δʹ�ܰ�ťcaption�ұ���ɫ
//Բ�ǰ�ť��ɫ����
#define ARC_BTN_RIMC	0X0000		//Բ�ǰ�ť�߿���ɫ
#define ARC_BTN_TP1C	0XD6BB		//��һ�е���ɫ
#define ARC_BTN_UPHC	0X8452		//�ϰ벿����ɫ
#define ARC_BTN_DNHC	0X52CD		//�°벿����ɫ
//��ť��ɫ����
#define BTN_DFU_BCFUC	0X0000		//Ĭ���ɿ�����ɫ
#define BTN_DFU_BCFDC	0X0000		//Ĭ�ϰ��µ���ɫ

//��ť״̬����
#define BTN_RELEASE 	0X00
#define BTN_PRESS   	0X01
#define BTN_INACTIVE   	0X02
//��ť���Ͷ���
#define BTN_TYPE_STD 	0X00
#define BTN_TYPE_PIC   	0X01
#define BTN_TYPE_ANG 	0X02
#define BTN_TYPE_TEXTA 	0X03
#define BTN_TYPE_TEXTB 	0X04


//��ť�ṹ�嶨��
__packed typedef struct 
{
	uint16_t top; 				  		//��ť��������
	uint16_t left;                       //��ť�������
	uint16_t width; 				  		//���
	uint16_t height;						//�߶�

	uint8_t id;							//��ťID
	uint8_t type;						//��ť����
									//[7]:0,ģʽA,������һ��״̬,�ɿ���һ��״̬.
									//	  1,ģʽB,ÿ����һ��,״̬�ı�һ��.��һ�°���,�ٰ�һ�µ���.
									//[6:4]:����
									//[3:0]:0,��׼��ť;1,ͼƬ��ť;2,�߽ǰ�ť;3,���ְ�ť(����͸��),4,���ְ�ť(������һ)
	uint8_t sta;							//��ť״̬
									//[7]:����״̬ 0,�ɿ�.1,����.(������ʵ�ʵ�TP״̬)
									//[6]:0,�˴ΰ�����Ч;1,�˴ΰ�����Ч.(����ʵ�ʵ�TP״̬����)
									//[5:2]:����
									//[1:0]:0,�����(�ɿ�);1,����;2,δ�������

	uint8_t *caption;					//��ť����
	uint8_t font;						//caption��������
	uint8_t arcbtnr;						//Բ�ǰ�ťʱԲ�ǵİ뾶										
	uint16_t bcfucolor; 				  	//button caption font up color
	uint16_t bcfdcolor; 				  	//button caption font down color

	uint16_t *bkctbl;					//�������ְ�ť:
									//����ɫ��(��ťΪ���ְ�ť��ʱ��ʹ��)
									//a,��Ϊ���ְ�ť(����͸��ʱ),���ڴ洢����ɫ
									//b,��Ϊ���ְ�ť(������һ��),bkctbl[0]:����ɿ�ʱ�ı���ɫ;bkctbl[1]:��Ű���ʱ�ı���ɫ.
									//���ڱ߽ǰ�ť:
									//bkctbl[0]:Բ�ǰ�ť�߿����ɫ
									//bkctbl[1]:Բ�ǰ�ť��һ�е���ɫ
									//bkctbl[2]:Բ�ǰ�ť�ϰ벿�ֵ���ɫ
									//bkctbl[3]:Բ�ǰ�ť�°벿�ֵ���ɫ	

	uint8_t *picbtnpathu;				//ͼƬ��ť�ɿ�ʱ��ͼƬ·��
	uint8_t *picbtnpathd;		 		//ͼƬ��ť����ʱ��ͼƬ·��
}_btn_obj;

void btn_read_backcolor(_btn_obj * btnx);
void btn_recover_backcolor(_btn_obj * btnx);
_btn_obj * btn_creat(uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint8_t id,uint8_t type);
void btn_delete(_btn_obj * btn_del);
void set_color(uint16_t up,uint16_t down);
uint8_t btn_check(_btn_obj * btnx,void * in_key);	//��ť�Ƿ񱻰��¼��
void btn_draw(_btn_obj * btnx);					//����ť
void btn_on_keyup(_btn_obj * btnx);				//��ť�ɿ�����
void btn_on_keydown(_btn_obj * btnx);			//��ť���²���
void btn_draw_stdbtn(_btn_obj * btnx);			//����׼��ť
void btn_press_hook(_btn_obj *btnx);
void btn_release_hook(_btn_obj *btnx);
void btn_draw_arcrectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t r,uint8_t mode,uint16_t upcolor,uint16_t downcolor);
void btn_draw_arcbtn(_btn_obj * btnx);
void btn_draw_picbtn(_btn_obj * btnx);
void btn_draw_textabtn(_btn_obj * btnx);
void btn_draw_textbbtn(_btn_obj * btnx);

void btn_test(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t type,uint8_t sta,uint8_t r,uint8_t *caption,uint8_t *uppath,uint8_t *downpath);

#endif
