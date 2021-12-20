#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//DS18B20���� ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


//IO��������
#define DS18B20_IO_IN()  {GPIOE->CRL&=0XF0FFFFFF;GPIOE->CRL|=8<<24;}
#define DS18B20_IO_OUT() {GPIOE->CRL&=0XF0FFFFFF;GPIOE->CRL|=3<<24;}
////IO��������
#define	DS18B20_DQ_OUT PEout(6) //���ݶ˿�	PE6
#define	DS18B20_DQ_IN  PEin(6)  //���ݶ˿�	PE6

u8 DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20
#endif
