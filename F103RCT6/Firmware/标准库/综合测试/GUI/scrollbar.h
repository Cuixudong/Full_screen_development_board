#ifndef __SCROLLBAR_H
#define __SCROLLBAR_H 		 
#include "guix.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-������ ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/10/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//�������ϵķ��ŵ���ɫ
#define SCROLLBAR_SIGN_RCOLOR 	0X0000	    //�����ɿ���ɫΪ��ɫ
#define SCROLLBAR_SIGN_PCOLOR 	0XFFFF	    //���Ű�����ɫΪ��ɫ

//�������ߴ��趨
#define SCROLLBAR_PART_LEN 		20			//���˰�ť�ĳ���(�����)
#define SCROLLBAR_MIN_THICK		10			//��С�ĺ��(���߶�)

//������
#define SCROLLBAR_DIR_HOR		0X00		//ˮƽscrollbar
#define SCROLLBAR_DIR_VER		0X80		//��ֱscrollbar
//ͼ����
#define SCROLLBAR_SIGN_UP	 	0X00	    //��ͼ��
#define SCROLLBAR_SIGN_DOWN	 	0X01	    //��ͼ��
#define SCROLLBAR_SIGN_LEFT	 	0X02	    //��ͼ��
#define SCROLLBAR_SIGN_RIGHT 	0X03	    //��ͼ��
#define SCROLLBAR_SIGN_HOR	 	0X04	    //ˮƽͼ��
#define SCROLLBAR_SIGN_VER 		0X05	    //��ֱͼ��
//��ť����
#define SCROLLBAR_BTN_LTP 		0X01	    //���/������ť������
#define SCROLLBAR_BTN_MID 		0X02	    //�м䰴��
#define SCROLLBAR_BTN_RBP 		0X04	    //�Ҷ�/�ײ���ť������
//���������Ͷ���
#define SCROLLBAR_TYPE_STD	 	0X00
#define SCROLLBAR_TYPE_NBT   	0X01

//������Ĭ����ɫ 
#define SCLB_DFT_INBKCOLOR		0XFFFF		//���ɫA��ɫ
#define SCLB_DFT_BTNCOLOR		0X2DDA //0X031F		//���ɫB��ɫ
#define SCLB_DFT_RIMCOLOR		0X4A49		//�߿���ɫ

//�������ṹ�嶨��
__packed typedef struct 
{
	uint16_t top; 				  		//��ť��������
	uint16_t left;                       //��ť�������
	uint16_t width; 				  		//���(���ٴ���40)
	uint16_t height;						//�߶�(���ٴ���2)

	uint8_t type;						//���ͱ���ֽ� [bit7]:����,0,ˮƽ;1,��ֱ;bit[6:2]:����;[bit1:0]:��ť����,0,��׼������;1,û�ж˰�ť�Ĺ�����;2,3,����.
	uint8_t sta;							//��ť״̬ bit0:���/������ť;bit1:�м䰴ť;bit2:�Ҷ�/�ײ���ť.	 
	uint8_t id;							//������id

 	uint16_t totalitems;					//����Ŀ��
	uint16_t itemsperpage;				//ÿҳ��ʾ����Ŀ��
	uint16_t topitem;					//�/��˵���Ŀ 
	uint16_t scbbarlen;					//��������
 
	uint16_t inbkcolor; 					//�ڲ���ɫ
	uint16_t btncolor;					//���Ű�ť���ɫ
	uint16_t rimcolor;					//�߿���ɫ
}_scrollbar_obj;


_scrollbar_obj * scrollbar_creat(uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint8_t type);
void scrollbar_delete(_scrollbar_obj *scrollbar_del);	 
void scrollbar_draw_sign(uint16_t x,uint16_t y,uint16_t signcolor,uint8_t signx);
void scrollbar_draw_btn(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t bkcolor,uint16_t outcolor,uint16_t signcolor,uint8_t signx);
void scrollbar_setpos(_scrollbar_obj *scbx);				//���û�����λ��
void scrollbar_draw_scrollbar(_scrollbar_obj *scbx);		//��������
uint8_t scrollbar_check(_scrollbar_obj * scbx,void * in_key);	//����������������
void scrollbar_hook(_scrollbar_obj *scbx);					//���Ӻ���

void test_scb(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t type,uint16_t icur,uint16_t incolor,uint16_t btncolor,uint16_t outcolor);
#endif





