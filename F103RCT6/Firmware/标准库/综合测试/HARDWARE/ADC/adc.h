#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define ADC_CH1  		1  		//ͨ��1		 
#define ADC_CH_TEMP  	16 		//�¶ȴ�����ͨ��

void Adc_Init(void);
uint16_t  Get_Adc(uint8_t ch); 
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times); 
int Get_Temp(void);					//��ȡ�¶�ֵ
void Get_Battery_Message(float * vol,uint8_t * percent);

#endif 
