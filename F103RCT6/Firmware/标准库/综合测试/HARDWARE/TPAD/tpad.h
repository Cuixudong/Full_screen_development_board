#ifndef __TPAD_H
#define __TPAD_H
#include "sys.h"		
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//TPAD��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
extern volatile uint16_t tpad_default_val;
							   	    
void		TPAD_Reset(void);
uint16_t	TPAD_Get_Val(void);
uint16_t	TPAD_Get_MaxVal(uint8_t n);
uint8_t		TPAD_Init(uint8_t psc);
uint8_t		TPAD_Scan(uint8_t mode);
void		TIM2_CH1_Cap_Init(uint16_t arr,uint16_t psc);   
#endif
