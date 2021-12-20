#ifndef __I2S_H
#define __I2S_H
#include "sys.h"    									
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//I2S ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/24
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//******************************************************************************** 
//V1.1 20141220  
//����I2S2_SampleRate_Set����ODDλ���õ�bug 	
////////////////////////////////////////////////////////////////////////////////// 	
 

extern void (*i2s_tx_callback)(void);		//IIS TX�ص�����ָ��  

void I2S2_Init(u8 std,u8 mode,u8 cpol,u8 datalen);  
u8 I2S2_SampleRate_Set(u32 samplerate);
void I2S2_TX_DMA_Init(u8* buf0,u8 *buf1,u16 num); 
void I2S_Play_Start(void); 
void I2S_Play_Stop(void);  
#endif





















