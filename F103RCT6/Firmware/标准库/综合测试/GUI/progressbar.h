#ifndef __PROGRESSBAR_H
#define __PROGRESSBAR_H 	 
#include "guix.h" 	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-������ ����	   
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
//�޸�progressbar_check��������ģ����� 
//////////////////////////////////////////////////////////////////////////////////

////�������ϵķ��ŵ�Ĭ����ɫ 
#define PRGB_DFT_BKACOLOR		0XEF7D		//����ɫA��ɫ
#define PRGB_DFT_BKBCOLOR		0XE73C		//����ɫB��ɫ
#define PRGB_DFT_FILLACOLOR		0X0FBB		//���ɫA��ɫ
#define PRGB_DFT_FILLBCOLOR		0X071F		//���ɫB��ɫ
#define PRGB_DFT_RIMCOLOR		0X4A49		//�߿���ɫ
#define PRGB_DFT_BTNCOLOR		0X0000		//������/������ɫ,��ɫ

//������type
#define PRGB_TYPE_HOR 			0X00		//ˮƽ��
#define PRGB_TYPE_VER			0X80		//��ֱ��
#define PRGB_TYPE_FEN			0X40  		//�����Ƿ���ʾ(�ٷֽ�������ʱ��,��ʾ�ٷ����Ƿ���ʾ)
#define PRGB_TYPE_PEN			0X20  		//�������Ƿ���ʾ
#define PRGB_TYPE_STD			0X00  		//��׼������
#define PRGB_TYPE_TEXT			0X01  		//�ٷ���������

#define PRGB_BTN_DOWN			0X01  		//�м䰴ť��������


//�������ṹ�嶨��
__packed typedef struct 
{
	uint16_t top; 				  		//��������������
	uint16_t left;                       //�������������
	uint16_t width; 				  		//���(���ٴ���40)
	uint16_t height;						//�߶�(���ٴ���2)

	uint8_t type;						//���ͱ���� 
									//[bit7]:����,0,ˮƽ;1,��ֱ;
									//[bit6]:0,����ʾ����;1,��ʾ����;
									//[bit5]:0,����ʾ������,1,��ʾ������(��ʵ������ɫ�Ƿ����,�Ƿ���Ÿ��������ɫ.)
									//[bit4:2]:����;
									//[bit1:0]:0,��׼������;1,�ٷ���������;2,3,����.
	uint8_t sta;							//������״̬ bit0:������������.	 
	uint8_t id;							//������id

 	uint32_t totallen;					//�ܳ���		    
	uint32_t curpos;						//��ǰλ��
	uint16_t prgbarlen;					//�������� ���û��趨.���ڱ�׼������ʱ��Ч
 
	uint16_t inbkcolora; 				//�ڲ�������ɫ
	uint16_t inbkcolorb; 				//�ڲ�������ɫ
	uint16_t infcolora; 					//�ڲ������ɫa
	uint16_t infcolorb; 					//�ڲ������ɫb
 	uint16_t btncolor;					//�������ɫ(��׼prgʱΪ�ڲ����������ɫ,�ٷ���prgʱ,Ϊ������ɫ,��չʱ,��Ч)
	uint16_t rimcolor;					//�߿���ɫ
}_progressbar_obj;


_progressbar_obj * progressbar_creat(uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint8_t type);
uint8_t progressbar_check(_progressbar_obj * prgbx,void * in_key);
void progressbar_delete(_progressbar_obj *progressbar_del);	 
void progressbar_hook(_progressbar_obj *prgbx);
void progressbar_draw_progressbar(_progressbar_obj *prgbx);
void progressbar_setpos(_progressbar_obj *prgbx);
void progressbar_draw_sign(_progressbar_obj *prgbx,uint16_t x,uint16_t y);
void progressbar_show_percnt(uint16_t x,uint16_t y,uint8_t dir,uint8_t num,uint16_t color);

#endif





