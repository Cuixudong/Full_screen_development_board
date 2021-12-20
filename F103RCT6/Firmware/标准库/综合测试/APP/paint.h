#ifndef __PAINT_H
#define __PAINT_H 	
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-���� ����	   
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

////////////////////////////////////////////////////////////////////////////////////////////
//��ͼ��/ͼƬ·��
extern const uint8_t *PAINT_COLOR_TBL_PIC;//��ɫ��·��
////////////////////////////////////////////////////////////////////////////////////////////




void paint_new_pathname(uint8_t *pname);
void paint_show_colorbar(uint16_t sx,uint16_t sy,uint8_t height);
uint8_t paint_pen_color_set(uint16_t x,uint16_t y,uint16_t* color,uint8_t*caption);
uint8_t paint_pen_size_set(uint16_t x,uint16_t y,uint16_t color,uint8_t *mode,uint8_t*caption);
void paint_draw_point(uint16_t x,uint16_t y,uint16_t color,uint8_t mode);	 
uint8_t paint_play(void);


#endif























