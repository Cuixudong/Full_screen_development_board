#ifndef __MEMO_H
#define __MEMO_H 			 
#include "guix.h"  
#include "scrollbar.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-�ı��� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2012/10/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
//����˵�� 
//V1.1 20140814
//�޸�memo_draw_memo����,���ģʽ����,ʵ�ִ�ͷ��ʾ/��β��ʾ
//////////////////////////////////////////////////////////////////////////////////

//memoĬ�ϵ�������ɫ������ɫ		 
#define MEMO_DFT_TBKC 	0XFFFF		//Ĭ�ϵ��ı�����ɫ
#define MEMO_DFT_TXTC 	0X0000		//Ĭ�ϵ��ı���ɫ

//memo�Ĺ�������ȶ���
#define MEMO_SCB_WIDTH 	0X0E		//���������Ϊ15������


//memo�ṹ�嶨��
__packed typedef struct 
{
	uint16_t top; 				  		//memo��������
	uint16_t left;                       //memo�������
	uint16_t width; 				  		//memo���(�����������Ŀ��)
	uint16_t height;						//memo�߶�

	uint8_t id;							//memoID
	uint8_t type;						//memo����
									//[7:1]:����					 
									//[0]:0,������༭;1,����༭			   

	uint8_t sta;							//memo״̬
									//[7]:0,memoû�м�⵽�����¼�;1,�а����¼�.
									//[6]:��ʱ������Ч��־
									//[5]:������־
									//[4:2]:����
									//[1]:�����ʾ״̬ 0,δ��ʾ.1,��ʾ.	  
									//[0]:memoѡ��״̬ 0,δѡ��.1,ѡ��.	  

	uint32_t textlen;					//memo�ַ���text�ĳ���
	uint8_t *text;						//memo������,��textlen�Ĵ�С������
	uint32_t *offsettbl;					//�ַ���ƫ������,��¼ÿ�п�ʼ���ַ�����text�����λ��,��СΪ:scbv->totalitems
	uint8_t font;						//text��������
											  
 	uint16_t lin;						//������ڵ���λ��(��ָ������)
	uint16_t col;						//���������λ��(����ȳ���(font/2)����)

	uint16_t typos;						//��ʱ��y����
	uint16_t txpos;						//��ʱ��x����

	uint32_t memo_timer_old;				//��һ��ʱ��

	_scrollbar_obj * scbv;			//��ֱ������
	uint16_t textcolor; 				  	//������ɫ
	uint16_t textbkcolor;				//���ֱ���ɫ
}_memo_obj;

_memo_obj * memo_creat(uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint8_t id,uint8_t type,uint8_t font,uint32_t textlen);
void memo_delete(_memo_obj * memo_del);
void memo_draw(_memo_obj * memox);


uint8_t memo_set_fontsize(_memo_obj * memox,uint8_t size);
uint16_t memo_get_cursorxpos(_memo_obj * memox);
void memo_read_cursorbkctbl(_memo_obj * memox);
void memo_draw_cursor(_memo_obj * memox,uint16_t color);
void memo_recover_cursorbkctbl(_memo_obj * memox);
void memo_show_cursor(_memo_obj * memox,uint8_t sta);
void memo_cursor_flash(_memo_obj *memox);
void memo_draw_text(_memo_obj * memox);	  
void memo_add_text(_memo_obj * memox,uint8_t * str);
void memo_draw_memo(_memo_obj * memox,uint8_t mode);
uint8_t memo_check(_memo_obj * memox,void * in_key);	 
 
//
void memo_test(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t type,uint8_t sta,uint16_t textlen);

#endif

















